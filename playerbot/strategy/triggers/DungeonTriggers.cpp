/// 副本与首领战斗通用触发器实现

#include "playerbot/playerbot.h"
#include "DungeonTriggers.h"
#include "playerbot/strategy/values/PositionValue.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/AiObjectContext.h"
#include "playerbot/strategy/values/HazardsValue.h"
#include "playerbot/strategy/actions/MovementActions.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"

using namespace ai;

/// 检测机器人是否已进入目标副本且尚未启用对应策略
bool EnterDungeonTrigger::IsActive()
{
    // Don't trigger if strategy already set | 若策略已启用则不触发
    if (!ai->HasStrategy(dungeonStrategy, BotState::BOT_STATE_COMBAT))
    {
        // If the bot is ready | 检查机器人是否已进入世界且未在传送
        if (bot->IsInWorld() && !bot->IsBeingTeleported())
        {
            // If the bot is on the specified dungeon | 检查机器人是否位于目标副本中
            Map* map = bot->GetMap();
            if (map && (map->IsDungeon() || map->IsRaid()))
            {
                return map->GetId() == mapID;
            }
        }
    }

    return false;
}

/// 检测机器人是否已离开目标副本且策略仍处于激活状态
bool LeaveDungeonTrigger::IsActive()
{
    // Don't trigger if strategy already unset | 若策略已关闭则不触发
    if (ai->HasStrategy(dungeonStrategy, BotState::BOT_STATE_COMBAT))
    {
        // If the bot is ready | 检查机器人是否就绪
        if (bot->IsInWorld() && !bot->IsBeingTeleported())
        {
            // If the bot is not on the specified dungeon | 检查机器人是否已离开目标副本
            return bot->GetMapId() != mapID;
        }
    }

    return false;
}

/// 检测攻击者列表中是否包含目标 Boss
bool StartBossFightTrigger::IsActive()
{
    // Don't trigger if strategy already set | 若 Boss 策略已启用则不触发
    if (!ai->HasStrategy(bossStrategy, BotState::BOT_STATE_COMBAT))
    {
        // If the bot is ready | 检查机器人是否就绪
        if (bot->IsInWorld() && !bot->IsBeingTeleported())
        {
            AiObjectContext* context = ai->GetAiObjectContext();
            const std::list<ObjectGuid> attackers = AI_VALUE(std::list<ObjectGuid>, "attackers");
            for (const ObjectGuid& attackerGuid : attackers)
            {
                Unit* attacker = ai->GetUnit(attackerGuid);
                if (attacker && attacker->GetEntry() == bossID)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

/// 检测当前是否已脱离战斗以关闭 Boss 策略
bool EndBossFightTrigger::IsActive()
{
    // Don't trigger if strategy already unset | 若 Boss 策略已关闭则不触发
    if (ai->HasStrategy(bossStrategy, BotState::BOT_STATE_COMBAT))
    {
        // We consider the fight is over if not in combat | 脱战即视为 Boss 战斗结束
        return !ai->IsStateActive(BotState::BOT_STATE_COMBAT);
    }

    return false;
}

/// 检测是否处于危险半径内并缓存危险源，若正在移动则暂不触发
bool CloseToHazardTrigger::IsActive()
{
    // If the bot is ready | 检查机器人是否就绪
    bool closeToHazard = false;
    if (bot->IsInWorld() && !bot->IsBeingTeleported())
    {
        const std::list<ObjectGuid>& possibleHazards = GetPossibleHazards();
        for (const ObjectGuid& possibleHazardGuid : possibleHazards)
        {
            if (IsHazardValid(possibleHazardGuid))
            {
                // Check if the bot is inside the hazard | 检查机器人是否位于危险区域半径内
                const float distanceToHazard = GetDistanceToHazard(possibleHazardGuid);
                if (distanceToHazard <= hazardRadius)
                {
                    closeToHazard = true;
                }
            }

            // Cache the hazards | 将危险源信息写入 AI 缓存
            Hazard hazard(possibleHazardGuid, hazardDuration, hazardRadius);
            SET_AI_VALUE(Hazard, "add hazard", std::move(hazard));
        }
    }

    // Don't trigger if the bot is moving | 若机器人正在执行移动动作则避免重复触发
    if (closeToHazard)
    {
        const Action* lastExecutedAction = ai->GetLastExecutedAction(BotState::BOT_STATE_COMBAT);
        if (lastExecutedAction)
        {
            const MovementAction* movementAction = dynamic_cast<const MovementAction*>(lastExecutedAction);
            if (movementAction)
            {
                closeToHazard = false;
            }
        }
    }

    return closeToHazard;
}

/// 验证危险源 GUID 是否为有效的游戏对象或生物
bool CloseToHazardTrigger::IsHazardValid(const ObjectGuid& hazzardGuid)
{
    if (hazzardGuid.IsGameObject())
    {
        return ai->GetGameObject(hazzardGuid) != nullptr;
    }
    else if (hazzardGuid.IsCreature())
    {
        return ai->GetCreature(hazzardGuid) != nullptr;
    }

    return false;
}

/// 计算机器人到危险源的实际距离（包含碰撞半径）
float CloseToHazardTrigger::GetDistanceToHazard(const ObjectGuid& hazzardGuid)
{
    if (hazzardGuid.IsGameObject())
    {
        GameObject* gameObjectHazard = ai->GetGameObject(hazzardGuid);
        if (gameObjectHazard)
        {
            return bot->GetDistance(gameObjectHazard) + gameObjectHazard->GetObjectBoundingRadius();
        }
    }
    else if (hazzardGuid.IsCreature())
    {
        Creature* creatureHazard = ai->GetCreature(hazzardGuid);
        if (creatureHazard)
        {
            return bot->GetDistance(creatureHazard, true, DIST_CALC_COMBAT_REACH);
        }
    }

    return 99999999.0f;
}

/// 获取视野范围内指定 ID 的游戏对象列表
std::list<ObjectGuid> CloseToGameObjectHazardTrigger::GetPossibleHazards()
{
    // This game objects have a maximum range equal to the sight distance on config file (default 60 yards) | 游戏对象搜索最大距离遵循配置文件视野距离（默认 60 码）
    return AI_VALUE2(std::list<ObjectGuid>, "nearest game objects no los", gameObjectID);
}

/// 搜索危险半径内指定 ID 的生物列表
std::list<ObjectGuid> CloseToCreatureHazardTrigger::GetPossibleHazards()
{
    std::list<ObjectGuid> possibleHazards;

    std::list<Unit*> creatures;
    MaNGOS::AllCreaturesOfEntryInRangeCheck u_check(bot, creatureID, hazardRadius);
    MaNGOS::UnitListSearcher<MaNGOS::AllCreaturesOfEntryInRangeCheck> searcher(creatures, u_check);
    Cell::VisitAllObjects(bot, searcher, hazardRadius);
    for (Unit* unit : creatures)
    {
        possibleHazards.push_back(unit->GetObjectGuid());
    }

    return possibleHazards;
}

/// 验证生物危险源是否有效（未以机器人自身为当前目标）
bool CloseToCreatureHazardTrigger::IsHazardValid(const ObjectGuid& hazzardGuid)
{
    Creature* creatureHazard = ai->GetCreature(hazzardGuid);
    if (creatureHazard)
    {
        // Check if the creature is not targeting the bot | 检查该生物当前目标是否不是机器人自身
        if (!creatureHazard->GetVictim() || (creatureHazard->GetVictim()->GetObjectGuid() != bot->GetObjectGuid()))
        {
            return true;
        }
    }

    return false;
}

/// 从当前攻击者中筛选指定 ID 的敌对生物作为危险源
std::list<ObjectGuid> CloseToHostileCreatureHazardTrigger::GetPossibleHazards()
{
    std::list<ObjectGuid> possibleHazards;
    std::list<ObjectGuid> attackers = AI_VALUE(std::list<ObjectGuid>, "attackers");

    for (const ObjectGuid& attackerGuid : attackers)
    {
        Creature* attacker = ai->GetCreature(attackerGuid);
        if (attacker && attacker->GetEntry() == creatureID)
        {
            possibleHazards.push_back(attackerGuid);
        }
    }

    return possibleHazards;
}

/// 检测周围是否存在指定 ID 的存活生物位于警戒距离内
bool CloseToCreatureTrigger::IsActive()
{
    // If the bot is ready | 检查机器人是否就绪
    if (bot->IsInWorld() && !bot->IsBeingTeleported())
    {
        AiObjectContext* context = ai->GetAiObjectContext();

        // Iterate through the near creatures | 遍历附近的同类生物
        std::list<Unit*> creatures;
        MaNGOS::AllCreaturesOfEntryInRangeCheck u_check(bot, creatureID, range);
        MaNGOS::UnitListSearcher<MaNGOS::AllCreaturesOfEntryInRangeCheck> searcher(creatures, u_check);
        Cell::VisitAllObjects(bot, searcher, range);
        for (Unit* unit : creatures)
        {
            Creature* creature = (Creature*)unit;
            if (creature && creature->IsAlive())
            {
                // Check if the bot is not being targeted by the creature, unless we don't care | 检查生物未以机器人为目标（除非忽略目标判定）
                if ((!creature->GetVictim() || (creature->GetVictim()->GetObjectGuid() != bot->GetObjectGuid())) || ignoreVictim)
                {
                    // See if the creature is within the specified distance | 判断生物是否进入指定半径内
                    if (bot->IsWithinDist(creature, range))
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

/// 检测规避生物列表中的任意生物是否进入 8 码范围内
bool CloseToSpecificCreaturesTrigger::IsActive()
{
    // If the bot is ready | 检查机器人是否就绪
    if (bot->IsInWorld() && !bot->IsBeingTeleported())
    {
        AiObjectContext* context = ai->GetAiObjectContext();
        std::set<uint32>&creatureIDList = AI_VALUE(std::set<uint32>&, "avoid creature list");
        // Check if any of the creatures listed is nearby | 检查规避列表中的生物是否在附近
        float range = 8.0f;
        for (uint32 creatureToCheck : creatureIDList)
        {
            // Iterate through the near creatures | 遍历附近的同类生物
            std::list<Unit*> creatures;
            MaNGOS::AllCreaturesOfEntryInRangeCheck u_check(bot, creatureToCheck, range);
            MaNGOS::UnitListSearcher<MaNGOS::AllCreaturesOfEntryInRangeCheck> searcher(creatures, u_check);
            Cell::VisitAllObjects(bot, searcher, range);
            for (Unit* unit : creatures)
            {
                Creature* creature = (Creature*)unit;
                if (creature && creature->IsAlive())
                {
                    // Check if the bot is not being targeted by the creature, unless we don't care | 检查生物未以机器人为目标（除非忽略目标判定）
                    if ((!creature->GetVictim() || (creature->GetVictim()->GetObjectGuid() != bot->GetObjectGuid())) || ignoreVictim)
                    {
                        // See if the creature is within the specified distance | 判断生物是否进入指定半径内
                        if (bot->IsWithinDist(creature, range))
                        {
                            return true;
                        }
                    }
                }
            }
        }

    }

    return false;
}

/// 检测物品是否持有且其使用法术未处于冷却状态
bool ItemReadyTrigger::IsActive()
{
    // Check if the bot has the item or if it has cheats enabled | 检查机器人是否持有该物品或启用了物品作弊
    if (bot->HasItemCount(itemID, 1) || ai->HasCheat(BotCheatMask::item))
    {
        const ItemPrototype* proto = sObjectMgr.GetItemPrototype(itemID);
        if (proto)
        {
            // Check if the item is in cooldown | 检查物品触发法术是否处于冷却中
            bool inCooldown = false;
            for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
            {
                if (proto->Spells[i].SpellTrigger != ITEM_SPELLTRIGGER_ON_USE)
                {
                    continue;
                }

                const uint32 spellID = proto->Spells[i].SpellId;
                if (spellID > 0)
                {
                    if (!sServerFacade.IsSpellReady(bot, spellID) ||
                        !sServerFacade.IsSpellReady(bot, spellID, itemID))
                    {
                        inCooldown = true;
                        break;
                    }
                }
            }

            return !inCooldown;
        }
    }

    return false;
}

/// 在物品就绪的基础上检查自身是否缺少对应增益光环
bool ItemBuffReadyTrigger::IsActive()
{
    if (!bot->HasAura(buffID))
    {
        return ItemReadyTrigger::IsActive();
    }

    return false;
}