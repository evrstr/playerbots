/// 测试命令：测试环境初始化与场景布置命令实现
#include "playerbot/playerbot.h"
#include "CommandSetup.h"
#include "playerbot/WorldPosition.h"
#include "playerbot/TravelMgr.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"
#include "TestAction.h"
#include "TestRegistry.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/LootObjectStack.h"

using namespace ai;

/// 执行 teleport 命令：按命名地点或坐标将机器人安全传送到位
TestResult CommandSetupTeleport::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    GuidPosition loc;
    if (!TestRegistry::ParseLocation(params, loc))
    {
        message = "Invalid teleport location: " + params;
        return TestResult::IMPOSSIBLE;
    }

    if (bot->TeleportTo(loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z, bot->GetOrientation()))
    {
        return TestResult::PASS;
    }
    else
    {
        message = "Teleport failed to " + params;
        return TestResult::IMPOSSIBLE;
    }
}

/// 执行 gm 命令：切换机器人 GM 模式及可见性（gm visible on/off）
TestResult CommandSetupGM::Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    if (params == "on")
    {
        bot->SetGameMaster(true);
        bot->GetSession()->SendNotification(LANG_GM_ON);
        return TestResult::PASS;
    }
    else if (params == "off")
    {
        bot->SetGameMaster(false);
        bot->GetSession()->SendNotification(LANG_GM_OFF);
        return TestResult::PASS;
    }
    else if (params == "visible on")
    {
        bot->SetGMVisible(true);
        bot->GetSession()->SendNotification(LANG_INVISIBLE_VISIBLE);
        return TestResult::PASS;
    }
    else if (params == "visible off")
    {
        bot->SetGMVisible(false);
        bot->GetSession()->SendNotification(LANG_INVISIBLE_INVISIBLE);
        return TestResult::PASS;
    }
    else if (params == "fly on")
    {
        bot->SetCanFly(true);
        bot->GetSession()->SendNotification(LANG_COMMAND_FLYMODE_STATUS);
        return TestResult::PASS;
    }
    else if (params == "fly off")
    {
        bot->SetCanFly(false);
        bot->GetSession()->SendNotification(LANG_COMMAND_FLYMODE_STATUS);
        return TestResult::PASS;
    }
    else
    {
        message = "Invalid parameter for setgm: " + params + ". Use 'on' or 'off'.";
        return TestResult::IMPOSSIBLE;
    }
}

/// 执行 give 命令：向机器人背包或银行发放指定 ID 与数量的物品
TestResult CommandSetupGiveItem::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    std::string param = params;

    bool isBank = false;
    if (param.find("bank ") == 0)
    {
        isBank = true;
        param = param.substr(5); // Remove "bank " prefix
    }  
    
    uint32 itemId = atoi(param.c_str());
    if (itemId > 0)
    {

        Item* pItem = bot->StoreNewItemInInventorySlot(itemId, 1);

        if (!pItem)
        {
            message = "Failed to create item with ID: " + param;
            return TestResult::IMPOSSIBLE;
        }

        if (isBank)
        {
            ItemPosCountVec dest;
            uint8 bagSlot;
            InventoryResult msg = bot->CanBankItem(NULL_BAG, NULL_SLOT, dest, pItem, false, bagSlot);

            if (msg != EQUIP_ERR_OK)
            {
                message = "Item can not be stored in bank: " + params;
                return TestResult::IMPOSSIBLE;
            }

            bot->RemoveItem(pItem->GetBagSlot(), pItem->GetSlot(), true);
            bot->BankItem(dest, pItem, true);
        }

        return TestResult::PASS;
    }
    else
    {
        message = "Invalid item ID: " + params;
        return TestResult::IMPOSSIBLE;
    }
}

/// 执行 equip 命令：为机器人直接生成并装备指定物品
TestResult CommandSetupEquipItem::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    uint32 itemId = atoi(params.c_str());
    if (itemId > 0)
    {
        bot->StoreNewItemInInventorySlot(itemId, 1);
        return TestResult::PASS;
    }
    else
    {
        message = "Invalid item ID: " + params;
        return TestResult::IMPOSSIBLE;
    }
}

/// 执行 clear 命令：清理机器人周围指定半径内非例外条目的生物
TestResult CommandSetupClearMobs::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    float radius = 50.0f;
    size_t pos = params.find("radius");
    if (pos != std::string::npos)
    {
        std::string radStr = params.substr(pos + 6);
        if (!radStr.empty() && radStr[0] == '=')
            radStr = radStr.substr(1);
        radius = atof(radStr.c_str());
    }

    uint32 exceptEntry = 0;
    size_t exceptPos = params.find("except=");
    if (exceptPos != std::string::npos)
    {
        std::string exceptStr = params.substr(exceptPos + 7);
        size_t spacePos = exceptStr.find(' ');
        if (spacePos != std::string::npos)
            exceptStr = exceptStr.substr(0, spacePos);
        exceptEntry = atoi(exceptStr.c_str());
    }

    // Force load the grid at bot's location to ensure creatures are visible | 强制加载机器人当前所在坐标网格以确保生物可见
    bot->GetMap()->ForceLoadGrid(bot->GetPositionX(), bot->GetPositionY());

    std::list<Creature*> creatures;
    MaNGOS::AnyUnitInObjectRangeCheck checker(bot, radius);
    MaNGOS::CreatureListSearcher<MaNGOS::AnyUnitInObjectRangeCheck> searcher(creatures, checker);
    Cell::VisitAllObjects(bot, searcher, radius);

    uint32 cleared = 0;
    for (auto& creature : creatures)
    {
        if (!creature->IsAlive())
            continue;

        if (exceptEntry && creature->GetEntry() == exceptEntry)
        {
            sLog.outString("[TestAction] clear: SKIPPING boss %s (entry %u)", creature->GetName(), creature->GetEntry());
            continue;
        }

        // Skip critters and non-combat pets | 跳过小动物与非战斗宠物
#ifndef MANGOSBOT_ZERO 
        if (creature->GetCreatureType() == CREATURE_TYPE_CRITTER || creature->GetCreatureType() == CREATURE_TYPE_NON_COMBAT_PET)
#else          
        if (creature->GetCreatureType() == CREATURE_TYPE_CRITTER)
#endif
            continue;

        creature->SetDeathState(JUST_DIED);
        creature->SetHealth(0);
        cleared++;
    }
    sLog.outString("[TestAction] clear: killed %u creatures, except entry %u", cleared, exceptEntry);
    return TestResult::PASS;
}

/// 执行 set destination 命令：为机器人设置旅行目的地（支持 nonforced 模式）
TestResult CommandSetupSetDestination::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    std::string dest = params;
    bool nonForced = false;
    if (params.find("destination ") == 0)
        dest = params.substr(std::string("destination ").length());

    // Optional trailing qualifier: "... nonforced" lets the bot genuinely travel to the | 可选尾部修饰符 "... nonforced"：允许机器人真实赶路前往目的地而非硬锁，
    // destination instead of pinning it (a forced target fights the arrival check that | 避免强制目标与到达检测产生冲突。
    // teleported-delivery bypasses).
    const std::string nonForcedTag = " nonforced";
    if (dest.size() > nonForcedTag.size() &&
        dest.compare(dest.size() - nonForcedTag.size(), nonForcedTag.size(), nonForcedTag) == 0)
    {
        nonForced = true;
        dest.erase(dest.size() - nonForcedTag.size());
    }

    GuidPosition loc;
    if (!TestRegistry::ParseLocation(dest, loc))
    {
        message = "Invalid destination: " + dest;
        return TestResult::IMPOSSIBLE;
    }

    ctx.destinationPosition = loc;

    AiObjectContext* context = ai->GetAiObjectContext();
    TravelTarget* target = AI_VALUE(TravelTarget*,"travel target");
    if (target)
    {
        // Pass the guid-backed entry through: rpg triggers match "rpg target entry == travel | 传入真实 GUID 对应的生物 Entry，确保灰名/低级任务 RPG 触发器能正确匹配
        // target entry" for gray/low-level quests, and a coords-only destination reports 0.
        TemporaryTravelDestination* tempDest = new TemporaryTravelDestination(loc, (int32)loc.GetEntry());
        target->SetTarget(tempDest, tempDest->GetPosition());
        target->SetStatus(TravelStatus::TRAVEL_STATUS_TRAVEL);
        target->SetForced(!nonForced);
        target->SetConditions({"not::manual bool::is travel refresh"});

        // The default TRAVEL budget is distance-based (2x theoretical walk time + 3 s), sized for | 赋予真实长途旅行时间预算，防止 90 码短途途中因战斗/上马延迟导致目标过期（BL-47(a)）
        // destinations the bot itself picks from far away. A test's 90 yd drop computes to ~16 s,
        // so any real-world delay on the leg (one combat, a mount-up, the 10 s re-path gate)
        // expires the target before the arrival flip can happen and the default re-roll machinery
        // steals the destination (BL-47(a)). Grant a real leg budget instead; the arrival flip to
        // WORK then uses the destination's fixed 5-minute expire, as designed.
        if (nonForced)
            target->SetExpireIn(20 * MINUTE * IN_MILLISECONDS); // reviewer P3: stay above the test monitor's 900 s fail line so a late arrival still finds a live target

        if (!nonForced && !ai->HasStrategy("travel", BotState::BOT_STATE_NON_COMBAT))
            ai->ChangeStrategy("+travel once", BotState::BOT_STATE_NON_COMBAT);
    }
    else
    {
        message = "Could not get travel target value";
        return TestResult::IMPOSSIBLE;
    }
    return TestResult::PASS;
}

// BL-46: aim the bot's rpg machinery at a specific world object. After this step the normal | BL-46：将机器人 RPG 机制指向指定世界对象，后续由旅行到达自动触发接交任务链路
// chain runs: arrival flips the travel target to WORK, the rpg trigger fires, and the
// accept/hand-in action runs - the bot decides, the step only points it.
/// 执行 set rpg target 命令：将机器人的 RPG 目标手动指向指定世界对象
TestResult CommandSetupRpgTarget::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    std::string target = params;
    if (target.find("rpg target ") == 0)
        target = target.substr(std::string("rpg target ").length());

    GuidPosition loc;
    if (!TestRegistry::ParseLocation(target, loc))
    {
        message = "Invalid rpg target: " + target;
        return TestResult::IMPOSSIBLE;
    }

    AiObjectContext* context = ai->GetAiObjectContext();
    SET_AI_VALUE(GuidPosition, "rpg target", loc);
    return TestResult::PASS;
}

/// 执行 teleport group 命令：通过所属线程将队伍全部成员跨图传送至机器人身边
TestResult CommandSetupTeleportGroup::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    Group* group = bot->GetGroup();
    if (!group)
    {
        // BL-44: a missing group used to be a silent PASS ("skipping"), which let a lost group join | BL-44：缺少队伍时直接诚实判定失败（不再静默跳过导致后续超时）
        // (BL-42) surface later as the hop monitor's timeout. Fail honestly at the moment of the hop.
        message = "teleport group: group never formed (bot has no group)";
        return TestResult::ABORT;
    }

    // BL-44: optional "expect=<n>" - abort when the group never reached the expected size instead of | BL-44：支持可选 "expect=<n>" 参数，若队伍人数不足直接中止测试
    // delivering to a fragment and letting the pass monitor time out.
    uint32 expect = 0;
    {
        std::string expectKey = "expect=";
        size_t pos = params.find(expectKey);
        if (pos != std::string::npos)
        {
            std::string valueStr = params.substr(pos + expectKey.length());
            size_t end = valueStr.find(' ');
            if (end != std::string::npos)
                valueStr = valueStr.substr(0, end);
            if (!valueStr.empty() && std::all_of(valueStr.begin(), valueStr.end(), ::isdigit))
                expect = (uint32)atoi(valueStr.c_str());
        }
    }
    if (expect && group->GetMembersCount() < expect)
    {
        message = "teleport group: group never formed (size " + std::to_string(group->GetMembersCount()) +
                  " < expected " + std::to_string(expect) + ")";
        return TestResult::ABORT;
    }

    float x = bot->GetPositionX();
    float y = bot->GetPositionY();
    float z = bot->GetPositionZ();
    uint32 mapId = bot->GetMapId();
    float orient = bot->GetOrientation();

    uint32 count = 0;
    std::string states;
    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        Player* member = ref->getSource();
        if (!member || member == bot)
            continue;

        // Test bots normally share the host's map, but route through the owning thread anyway so | 通过 RunOnOwningThread 调度传送确保跨地图线程安全，并在回调内部记录真实传送结果
        // the helper stays safe (and consistent with the rest of the codebase) if a test spans maps.
        //
        // The delivery is logged from *inside* the callback, because that is the only place that knows it
        // happened: RunOnOwningThread runs the callback inline when the member is on this map and defers
        // it to the world thread otherwise, and it silently skips a member that is out of world or
        // mid-teleport. The previous version counted the call instead, so "Teleported 3 group members"
        // could mean three no-ops. Logging inside the callback is also race-free: it runs on whichever
        // thread actually performs the move.
        states += " " + std::string(member->GetName()) + "(map" + std::to_string(member->GetMapId()) +
                  ",inWorld=" + (member->IsInWorld() ? "1" : "0") +
                  ",tp=" + (member->IsBeingTeleported() ? "1" : "0") + ")";

        ai->RunOnOwningThread(member, [&ctx, mapId, x, y, z, orient](Player* m)
        {
            // The return value matters: Player::TeleportTo refuses a charmed player, an invalid | 检查 TeleportTo 返回值以准确记录失败情况；详情日志仅在 LogLevel >= 2 时输出
            // coordinate, or a map the player may not enter - reporting the attempt without it was the
            // original over-claim. outDetail because one line per member per call is too much noise for
            // the generated instance scenarios; run with LogLevel = 2 to see it.
            const uint32 fromMap = m->GetMapId();
            const bool wasInWorld = m->IsInWorld();
            const bool wasTeleporting = m->IsBeingTeleported();
            const bool moved = m->TeleportTo(mapId, x, y, z, orient);

            // BL-44: record the members that were ACTUALLY delivered (moved=true). The "group on map" | BL-44：仅记录实际传送成功的成员 GUID，用于因果模式校验防止巧合路过误判
            // monitor switches to causal mode when this sink is non-empty, so a member that roams to
            // the host's map by coincidence can no longer satisfy the pass condition. ctx (TestAction's
            // member) outlives the deferred callback: callbacks run on the next world tick while the
            // test is still in its observe window.
            if (moved)
                ctx.RecordDeliveredGroupMember(m->GetObjectGuid());

            sLog.outDetail("[TestAction] teleport group: delivering %s to map %u (from map %u, inWorld=%d, tp=%d) -> moved=%d",
                m->GetName(), mapId, fromMap, wasInWorld ? 1 : 0, wasTeleporting ? 1 : 0, moved ? 1 : 0);
        });
        ++count;
    }

    sLog.outString("[TestAction] teleport group: issued %u to map %u at (%.1f, %.1f, %.1f);%s",
        count, mapId, x, y, z, states.c_str());
    return TestResult::PASS;
}

/// 执行 pull 命令：查找或刷出指定生物并强制拉入战斗（禁用脱战归位）
TestResult CommandSetupPull::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    uint32 entryId = atoi(params.c_str());
    if (!entryId)
    {
        message = "Invalid creature entry: " + params;
        return TestResult::IMPOSSIBLE;
    }

    // Force load the grid at bot's location to ensure creatures are visible | 强制加载周围网格
    bot->GetMap()->ForceLoadGrid(bot->GetPositionX(), bot->GetPositionY());

    // First: search via Cell::VisitWorldObjects | 第一步：通过 Cell::VisitWorldObjects 在 500 码内查找
    Creature* target = nullptr;
    {
        std::list<Creature*> creatures;
        MaNGOS::AnyUnitInObjectRangeCheck checker(bot, 500.0f);
        MaNGOS::CreatureListSearcher<MaNGOS::AnyUnitInObjectRangeCheck> searcher(creatures, checker);
        Cell::VisitWorldObjects(bot, searcher, 500.0f);

        for (auto& creature : creatures)
        {
            if (creature->GetEntry() == entryId && creature->IsAlive())
            {
                target = creature;
                break;
            }
        }
    }

    // Second: search via Map object store (finds creatures not in loaded grid cells) | 第二步：搜索地图全量对象库（兼容未加载网格中的生物）
    if (!target)
    {
        auto& store = bot->GetMap()->GetObjectsStore();
        for (auto itr = store.begin<Creature>(); itr != store.end<Creature>(); ++itr)
        {
            if (Creature* c = itr->second)
            {
                if (c->GetEntry() == entryId && c->IsAlive())
                {
                    target = c;
                    sLog.outString("[TestAction] pull: found %s (entry %u) via map store at dist %.1f",
                        c->GetName(), entryId, bot->GetDistance(c));
                    break;
                }
            }
        }
    }

    // Third: spawn the creature if it doesn't exist in the instance | 第三步：若副本中不存在则直接刷出该生物
    if (!target)
    {
        static bool pullDebugLogged = false;
        if (!pullDebugLogged)
        {
            sLog.outString("[TestAction] pull %u: creature not found on map %u at (%.1f, %.1f, %.1f), spawning it",
                entryId, bot->GetMapId(),
                bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ());
            pullDebugLogged = true;
        }

        target = bot->SummonCreature(entryId,
            bot->GetPositionX() + 5.0f, bot->GetPositionY(), bot->GetPositionZ(),
            bot->GetOrientation() + M_PI_F,
            TEMPSPAWN_MANUAL_DESPAWN, 0);

        if (!target)
        {
            message = "Failed to spawn creature entry " + std::to_string(entryId);
            return TestResult::IMPOSSIBLE;
        }

        sLog.outString("[TestAction] pull: spawned %s (entry %u) near bot", target->GetName(), entryId);
    }

    bot->SetSelectionGuid(target->GetObjectGuid());
    bot->Attack(target, true);
    // Make the boss attack the bot too (prevents evade) | 让 Boss 主动攻击机器人以防脱离战斗
    if (target->AI())
        target->AI()->AttackStart(bot);
    // Disable leashing so the boss doesn't evade | 禁用脱战归位距离（Leashing）
    target->GetCombatManager().SetLeashingDisable(true);
    ctx.focusMobEntry = entryId;
    ctx.focusMobGuid = target->GetObjectGuid();
    sLog.outString("[TestAction] Bot %s pulling creature %s (entry %u) at distance %.1f",
        bot->GetName(), target->GetName(), entryId, bot->GetDistance(target));
    return TestResult::PASS;
}

/// 执行 spawn mob 命令：按距离、朝向、等级与血量参数刷出测试用怪物
TestResult CommandSpawnMob::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    uint32 entryId = atoi(params.c_str());
    if (!entryId)
    {
        message = "Invalid creature entry: " + params;
        return TestResult::IMPOSSIBLE;
    }

    float distance = 5.0f;
    size_t distancePos = params.find("dist=");
    if (distancePos != std::string::npos)
        distance = atof(params.c_str() + distancePos + 5);

    if (distance <= 0.0f)
    {
        message = "Invalid spawn distance: " + params;
        return TestResult::IMPOSSIBLE;
    }

    uint32 spawnLevel = 0;
    size_t levelPos = params.find("level=");
    if (levelPos != std::string::npos)
        spawnLevel = (uint32)atoi(params.c_str() + levelPos + 6);

    float leashRange = 0.0f;
    size_t leashPos = params.find("leash=");
    if (leashPos != std::string::npos)
        leashRange = atof(params.c_str() + leashPos + 6);

    if (leashPos != std::string::npos && leashRange <= 0.0f)
    {
        message = "Invalid leash range: " + params;
        return TestResult::IMPOSSIBLE;
    }

    float x = bot->GetPositionX() + distance;
    float y = bot->GetPositionY();

    size_t towardPos = params.find("toward ");
    if (towardPos != std::string::npos)
    {
        std::string towardName = params.substr(towardPos + 7);
        size_t nameEnd = towardName.find(' ');
        if (nameEnd != std::string::npos)
            towardName = towardName.substr(0, nameEnd);

        GuidPosition toward;
        if (!TestRegistry::ParseLocation(towardName, toward))
        {
            message = "Invalid spawn direction: " + towardName;
            return TestResult::IMPOSSIBLE;
        }

        float dx = toward.coord_x - bot->GetPositionX();
        float dy = toward.coord_y - bot->GetPositionY();
        float length = sqrt(dx * dx + dy * dy);
        if (length > 1.0f)
        {
            x = bot->GetPositionX() + dx / length * distance;
            y = bot->GetPositionY() + dy / length * distance;
        }
    }

    bot->GetMap()->ForceLoadGrid(bot->GetPositionX(), bot->GetPositionY());

    TempSpawnSettings settings(bot, entryId, x, y, bot->GetPositionZ(),
        bot->GetOrientation() + M_PI_F, TEMPSPAWN_MANUAL_DESPAWN, 0);
    settings.level = spawnLevel;

#ifdef MANGOSBOT_TWO
    Creature* spawned = WorldObject::SummonCreature(settings, bot->GetMap(), bot->GetPhaseMask());
#else
    Creature* spawned = WorldObject::SummonCreature(settings, bot->GetMap());
#endif

    if (!spawned)
    {
        message = "Failed to spawn creature entry " + std::to_string(entryId);
        return TestResult::IMPOSSIBLE;
    }

    ctx.focusMobEntry = entryId;
    ctx.focusMobGuid = spawned->GetObjectGuid();
    ctx.focusMobPassive = true;

    if (leashRange > 0.0f)
    {
        float const sx = spawned->GetPositionX();
        float const sy = spawned->GetPositionY();
        spawned->GetCombatManager().SetLeashingCheck([sx, sy, leashRange](Unit*, float x, float y, float z)
        {
            return sqrt((x - sx) * (x - sx) + (y - sy) * (y - sy)) > leashRange;
        });
    }

    if (params.find("aggro") != std::string::npos && spawned->AI())
        spawned->AI()->AttackStart(bot);

    if (params.find("select") != std::string::npos)
    {
        bot->SetSelectionGuid(spawned->GetObjectGuid());
        AiObjectContext* context = ai->GetAiObjectContext();
        SET_AI_VALUE(ObjectGuid, "current target", spawned->GetObjectGuid());
    }

    sLog.outString("[TestAction] Bot %s spawned creature %s (entry %u) at distance %.1f",
        bot->GetName(), spawned->GetName(), entryId, bot->GetDistance(spawned));
    return TestResult::PASS;
}

/// 执行 follow focus 命令：命令小队切换为跟随策略并协助攻击焦点目标
TestResult CommandFollowFocus::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    Creature* focus = bot->IsInWorld() && bot->GetMap() ? bot->GetMap()->GetCreature(ctx.focusMobGuid) : nullptr;
    if (!focus || !focus->IsInWorld())
    {
        message = "follow focus: no focus mob spawned yet";
        return TestResult::PENDING;
    }

    ai->ChangeStrategy("+follow,-rpg,-travel,-stay,-guard,-wander,-passive", BotState::BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("-stay,-guard,-wander", BotState::BOT_STATE_COMBAT);
    AiObjectContext* context = ai->GetAiObjectContext();
    SET_AI_VALUE(GuidPosition, "manual follow target", focus);

    return TestResult::PASS;
}

/// 执行 kill focus 命令：直接击杀当前记录的焦点怪物
TestResult CommandKillFocus::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    Creature* focus = bot->IsInWorld() && bot->GetMap() ? bot->GetMap()->GetCreature(ctx.focusMobGuid) : nullptr;
    if (!focus)
    {
        message = "kill focus: no focus mob spawned yet";
        return TestResult::PENDING;
    }

    if (!focus->IsAlive())
    {
        message = "kill focus: focus mob already dead";
        return TestResult::PASS;
    }

    Unit::Kill(bot, focus, DIRECT_DAMAGE, nullptr, false, false);

    return TestResult::PASS;
}

/// 执行 await focus corpse 命令：等待焦点怪物进入尸体状态（带超时宽限）
TestResult CommandAwaitFocusCorpse::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    uint32 graceSeconds = 20;
    if (!params.empty())
    {
        std::string graceStr = params;
        if (TryParseUInt32Strict(graceStr, graceSeconds, message, GetName()) != TestResult::PASS)
            return TestResult::IMPOSSIBLE;
    }

    Creature* focus = bot->IsInWorld() && bot->GetMap() ? bot->GetMap()->GetCreature(ctx.focusMobGuid) : nullptr;
    if (!focus)
    {
        message = "await focus corpse: focus mob despawned";
        return TestResult::FAIL;
    }

    if (focus->IsAlive())
        return TestResult::PENDING;

    if (sServerFacade.GetDeathState(focus) == CORPSE && focus->HasFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE))
    {
        AiObjectContext* context = bot->GetPlayerbotAI()->GetAiObjectContext();
        AI_VALUE(LootObjectStack*, "available loot")->Add(focus->GetObjectGuid());
        ctx.waitTime = 0;
        message = "focus corpse lootable and registered";
        return TestResult::PASS;
    }

    if (!ctx.waitTime)
        ctx.waitTime = WorldTimer::getMSTime();

    if (WorldTimer::getMSTimeDiff(ctx.waitTime, WorldTimer::getMSTime()) < graceSeconds * 1000)
        return TestResult::PENDING;

    message = "await focus corpse: corpse never became lootable (no loot recipient?)";
    return TestResult::FAIL;
}

/// 执行 set value 命令：解析数据类型并修改机器人 AI ObjectContext 中的指定 Value
TestResult CommandSetValue::Execute(const std::string& params, Player* bot, PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    // Expected format: "set value <datatype> <valueName> <valueToSetTo>" | 预期格式："set value <datatype> <valueName> <valueToSetTo>"
    AiObjectContext* context = bot->GetPlayerbotAI()->GetAiObjectContext();

    std::string datatype;
    std::string valueStr;

    if (TrySplitOnce(params, " ", datatype, valueStr, message, GetName()) != TestResult::PASS)
    {
        message = "Invalid format for set value: " + params;
        return TestResult::IMPOSSIBLE;
    }

    std::string valueName;
    std::string valueToSetTo;
    if (TrySplitOnce(valueStr, "=>", valueName, valueToSetTo, message, GetName()) != TestResult::PASS)
    {
        message = "Invalid format for set value: " + params;
        return TestResult::IMPOSSIBLE;
    }

    bool isAiValue = context->HasSupportedValue(valueToSetTo);

    if (datatype == "bool")
    {
        bool value = isAiValue ? AI_VALUE(bool, valueToSetTo) : (valueToSetTo == "true");
        SET_AI_VALUE(bool, valueName, value);
        return TestResult::PASS;
    }
    else if (datatype == "uint32")
    {
        uint32 value = isAiValue ? AI_VALUE(uint32, valueToSetTo) : atoi(valueToSetTo.c_str());
        SET_AI_VALUE(uint32, valueName, value);
        return TestResult::PASS;
    }
    else if (datatype == "GuidPosition")
    {
        GuidPosition value = isAiValue ? AI_VALUE(GuidPosition, valueToSetTo) : GuidPosition(valueToSetTo);
        SET_AI_VALUE(GuidPosition, valueName, value);
        return TestResult::PASS;
    }
    else if (datatype == "string")
    {
        std::string value = isAiValue ? AI_VALUE(std::string, valueToSetTo) : valueToSetTo;
        SET_AI_VALUE(std::string, valueName, value);
        return TestResult::PASS;
    }

    message = "Unsupported datatype for set value: " + datatype;
    return TestResult::IMPOSSIBLE;
}
// BL-47(a) follow-up: honest setup check for "is the giver/taker actually alive in the world". | BL-47(a) 后续：快速前置检查任务发布者/交付者在世界中是否存活
// five_signets evidence: the bot teleported to the giver's exact coords and the travel flip fired,
// but the creature was not found by an 80-yd unit search - the run then burned 900 s on an accept
// that could never happen. This command fails fast instead. Usage:
//   "require creature alive <location> [yd]"   (yd defaults to 300; searches around the bot)
/// 执行 require creature alive 命令：验证命名点周围指定半径内目标生物是否存活
TestResult CommandRequireCreatureAlive::Execute(const std::string& params, Player* bot,
                    PlayerbotAI* ai, TestContext& ctx, std::string& message)
{
    std::string locName = params;
    float radius = 300.0f;

    // Optional trailing numeric radius: "<location> <yd>" | 可选尾部半径参数："<location> <yd>"
    size_t lastSpace = locName.find_last_of(" \t");
    if (lastSpace != std::string::npos)
    {
        std::string maybeRadius = locName.substr(lastSpace + 1);
        if (!maybeRadius.empty() && std::all_of(maybeRadius.begin(), maybeRadius.end(), ::isdigit))
        {
            radius = (float)atoi(maybeRadius.c_str());
            if (radius <= 0.0f)
                radius = 300.0f;
            locName = locName.substr(0, lastSpace);
        }
    }

    // Trim leading whitespace left over from the command-name split. | 去除命令分割后残留的前导空白
    size_t nameStart = locName.find_first_not_of(" \t");
    if (nameStart == std::string::npos)
    {
        message = "require creature alive: missing location";
        return TestResult::IMPOSSIBLE;
    }
    locName = locName.substr(nameStart);

    GuidPosition loc;
    if (!TestRegistry::ParseLocation(locName, loc))
    {
        message = "Invalid location: " + locName;
        return TestResult::IMPOSSIBLE;
    }

    if (!loc || !loc.IsCreature() || !loc.GetEntry())
    {
        // GameObject locations (rare givers/takers) are not covered by this check - skip honestly. | 少数游戏对象类型任务点不适用生物存活校验，诚实跳过
        message = "Location " + locName + " is not a creature - alive check skipped";
        return TestResult::PASS;
    }

    uint32 entry = loc.GetEntry();

    std::list<Creature*> found;
    MaNGOS::NearestCreatureEntryWithLiveStateInObjectRangeCheck checker(*bot, entry, true, false, radius);
    MaNGOS::CreatureListSearcher<MaNGOS::NearestCreatureEntryWithLiveStateInObjectRangeCheck> searcher(found, checker);
    Cell::VisitAllObjects(bot, searcher, radius);

    if (found.empty())
    {
        message = "Creature " + std::to_string(entry) + " (" + locName + ") not found ALIVE within "
            + std::to_string((uint32)radius) + " yd of the bot - giver/taker missing from the world";
        return TestResult::ABORT;
    }

    Creature* creature = found.front();
    std::ostringstream out;
    out << "Creature " << entry << " (" << (creature->GetName() ? creature->GetName() : "?")
        << ") alive at " << (uint32)bot->GetDistance(creature) << " yd";
    message = out.str();
    return TestResult::PASS;
}
