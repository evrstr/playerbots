
#include "playerbot/playerbot.h"
#include "playerbot/strategy/generic/PullStrategy.h"
#include "playerbot/strategy/values/AttackersValue.h"
#include "PullActions.h"
#include "playerbot/strategy/values/PositionValue.h"

using namespace ai;

/// 检查机器人是否装备了当前拉怪策略所需的远程武器或投掷武器
static bool HasRequiredPullWeapon(Player* bot, PullStrategy* strategy)
{
    const bool needsRanged = bot->getClass() == CLASS_HUNTER || strategy->GetPullActionName() == "shoot";
    return !needsRanged || bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
}

/// 执行动作主逻辑（拉怪状态检查指令动作）
bool PullCheckAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (!requester)
        return false;

    PullStrategy* strategy = PullStrategy::Get(ai);
    const bool strategyActive = strategy != nullptr;
    if (!strategy)
        strategy = dynamic_cast<PullStrategy*>(ai->GetAiObjectContext()->GetStrategy("pull"));

    if (!strategy)
    {
        ai->TellPlayerNoFacing(requester, "My class has no pull ability.");
        return true;
    }

    const std::string spellName = strategy->GetSpellName();

    if (getName() == "pull capability")
    {
        if (strategyActive)
        {
            bool canPull = strategy->CanDoPullAction(nullptr);
            ai->TellPlayerNoFacing(requester, canPull ? "I am capable of pulling with " + spellName + "." : "I don't have a usable pull action.");
            return true;
        }

        if (!HasRequiredPullWeapon(bot, strategy))
        {
            ai->TellPlayerNoFacing(requester, "I can't pull: I have no ranged weapon equipped.");
            return true;
        }

        if (!ai->HasSpell(spellName))
        {
            ai->TellPlayerNoFacing(requester, "I can't pull: I don't know " + spellName + ".");
            return true;
        }

        ai->TellPlayerNoFacing(requester, "I can pull with " + spellName + ".");
        return true;
    }

    Unit* target = ai->GetUnit(requester->GetSelectionGuid());
    if (!target)
    {
        ai->TellPlayerNoFacing(requester, "Select a target to check pull readiness.");
        return true;
    }
    if (target->GetDistance(bot) > sPlayerbotAIConfig.reactDistance * 3)
    {
        ai->TellPlayerNoFacing(requester, "The target is too far away.");
        return true;
    }
    if (!AttackersValue::IsValid(target, bot, nullptr, false))
    {
        ai->TellPlayerNoFacing(requester, "That target can't be pulled.");
        return true;
    }
    if (!bot->IsWithinLOSInMap(target))
    {
        ai->TellPlayerNoFacing(requester, "I can't see that target.");
        return true;
    }

    if (!strategyActive)
    {
        const bool ready = HasRequiredPullWeapon(bot, strategy) && ai->HasSpell(spellName) && ai->CanCastSpell(spellName, target, true, nullptr, true);
        ai->TellPlayerNoFacing(requester, ready ? "I am ready to pull that target with " + spellName + "." : "I can't pull that target right now.");
        return true;
    }

    bool canPull = strategy->CanDoPullAction(target);
    if (canPull)
    {
        ObjectGuid previousTarget = AI_VALUE(ObjectGuid, "pull target");
        SET_AI_VALUE(ObjectGuid, "pull target", target->GetObjectGuid());
        canPull = ai->CanDoSpecificAction("pull action", true, true);
        SET_AI_VALUE(ObjectGuid, "pull target", previousTarget);
    }
    ai->TellPlayerNoFacing(requester, canPull ? "I am ready to pull that target." : "I can't pull that target right now.");
    return true;
}

/// 执行动作主逻辑（拉怪请求基类动作）
bool PullRequestAction::Execute(Event& event)
{
    PullStrategy* strategy = PullStrategy::Get(ai);
    if (!strategy)
    {
        return false;
    }

    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();

    Unit* target = GetTarget(event);
    if (!target)
    {
        ai->TellPlayerNoFacing(requester, "You have no target");
        return false;
    }

    const float maxPullDistance = sPlayerbotAIConfig.reactDistance * 3;
    const float distanceToPullTarget = target->GetDistance(ai->GetBot());
    if (distanceToPullTarget > maxPullDistance)
    {
        ai->TellPlayerNoFacing(requester, "The target is too far away");
        return false;
    }

    if (!AttackersValue::IsValid(target, bot, nullptr, false))
    {
        ai->TellPlayerNoFacing(requester, "The target can't be pulled");
        return false;
    }

    if (!strategy->CanDoPullAction(target))
    {
        std::ostringstream out; out << "Can't perform pull action '" << strategy->GetPullActionName() << "'";
        ai->TellPlayerNoFacing(requester, out.str());
        return false;
    }

    // Set position to return to after pulling. (记录拉怪结束后需要返回的位置。)
    PositionMap& posMap = AI_VALUE(PositionMap&, "position");
    PositionEntry pullPosition = posMap["pull"];

    pullPosition.Set(bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ(), bot->GetMapId());
    posMap["pull"] = pullPosition;

    strategy->RequestPull(target);

    // Force change combat state to have a faster reaction time (强制切换至战斗状态以提高反应速度)
    ai->OnCombatStarted();

    return true;
}

/// 获取当前动作的目标单位（拉取主人目标动作）
Unit* PullMyTargetAction::GetTarget(Event& event)
{
    Unit* target = nullptr;

    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (event.getSource() == "attack anything")
    {
        ObjectGuid guid = event.getObject();
        target = ai->GetCreature(guid);
    }
    else if (requester)
    {
        target = ai->GetUnit(requester->GetSelectionGuid());
    }

    return target;
}

/// 获取当前动作的目标单位（拉取团队标记目标动作）
Unit* PullRTITargetAction::GetTarget(Event& event)
{
    return ai->GetUnit(AI_VALUE(ObjectGuid, "rti target"));
}

/// 执行动作主逻辑（开始拉怪动作）
bool PullStartAction::Execute(Event& event)
{
    bool result = false;
    PullStrategy* strategy = PullStrategy::Get(ai);
    if (strategy)
    {
        Unit* target = strategy->GetTarget();
        if (target)
        {
            if (strategy->GetPreActionName().empty())
                result = true;
            else
            {
                result = ai->DoSpecificAction(strategy->GetPreActionName(), event, true);
                if(result)
                    SetDuration(3000);
            }

            // Set the pet on passive mode during the pull (拉怪期间将宠物设为被动模式)
            Pet* pet = bot->GetPet();
            if (pet)
            {
                UnitAI* creatureAI = ((Creature*)pet)->AI();
                if (creatureAI)
                {
                    strategy->SetPetReactState(creatureAI->GetReactState());
                    creatureAI->SetReactState(REACT_PASSIVE);
                }
            }

            strategy->OnPullStarted();
        }
    }

    return result;
}


/// 构造函数：初始化执行拉怪动作
PullAction::PullAction(PlayerbotAI* ai, std::string name) : CastSpellAction(ai, name)
{
    InitPullAction();
}

/// 执行动作主逻辑（执行拉怪动作）
bool PullAction::Execute(Event& event)
{
    InitPullAction();

    PullStrategy* strategy = PullStrategy::Get(ai);
    if (strategy)
    {
        Unit* target = strategy->GetTarget();
        if (target)
        {
            // Check if we are on pull range (检查是否已进入拉怪射程范围内)
            const float distanceToTarget = target->GetDistance(bot);
            if (distanceToTarget <= strategy->GetRange())
            {
                if (sServerFacade.isMoving(bot))
                {
                    // Force stop (强制停止)
                    ai->StopMoving();
                    strategy->RequestPull(target, false);
                    return false;
                }

                std::string actionName = strategy->GetPullActionName();

                // Execute the pull action (执行拉怪开怪动作)
                SET_AI_VALUE(ObjectGuid, "current target", GetTarget()->GetObjectGuid());
                if (ai->DoSpecificAction(actionName, event, true))
                {
                    strategy->RequestPull(target); // extend pull timer to walk back. (延长拉怪计时器以便走回安全位置。)
                    return true;
                }
                else
                    return false;
            }
            else
            {
                // Retry the reach pull action (重试接近拉怪动作)
                strategy->RequestPull(target, false);
            }
        }
    }

    return false;
}

/// 判断执行该动作的前置条件是否满足（执行拉怪动作）
bool PullAction::isPossible()
{
    InitPullAction();

    PullStrategy* strategy = PullStrategy::Get(ai);
    if (strategy)
    {
        std::string spellName = strategy->GetSpellName();
        Unit* target = strategy->GetTarget();
        if (!spellName.empty() && target)
        {
            if (!ai->CanCastSpell(spellName, target, true, nullptr, true))
            {
                return false;
            }
        }
    }

    return true;
}

/// 初始化拉怪动作的法术与状态参数
void PullAction::InitPullAction()
{
    // Get the pull action spell name from the strategy (从当前策略中读取拉怪使用的法术名称)
    PullStrategy* strategy = PullStrategy::Get(ai);
    if (strategy)
    {
        std::string spellName = strategy->GetSpellName();
        if (!spellName.empty())
        {
            SetSpellName(spellName);

            float spellRange;
            if (ai->GetSpellRange(spellName, &spellRange))
            {
                range = spellRange;
            }
        }
    }
}

/// 执行动作主逻辑（结束拉怪动作）
bool PullEndAction::Execute(Event& event)
{
    PullStrategy* strategy = PullStrategy::Get(ai);
    if (strategy)
    {
        // Restore the pet react state (恢复宠物原有的反应姿态)
        Pet* pet = bot->GetPet();
        if (pet)
        {
            UnitAI* creatureAI = ((Creature*)pet)->AI();
            if (creatureAI)
            {
                creatureAI->SetReactState(strategy->GetPetReactState());
                Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, "current target"));
                if (creatureAI->GetReactState() != REACT_PASSIVE && target)
                    creatureAI->AttackStart(target);
            }
        }

        // Remove the saved pull position (清除已保存的拉怪返回位置)
        AiObjectContext* context = ai->GetAiObjectContext();
        PositionMap& posMap = AI_VALUE(PositionMap&, "position");
        PositionEntry stayPosition = posMap["pull"];
        if (stayPosition.isSet())
        {
            posMap.erase("pull");
        }

        strategy->OnPullEnded();
        return true;
    }

    return false;
}
