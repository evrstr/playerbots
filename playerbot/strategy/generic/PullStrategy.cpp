/// 拉怪（Pull）、防 Add 与拉怪归位策略实现

#include "playerbot/playerbot.h"
#include "playerbot/strategy/PassiveMultiplier.h"
#include "PullStrategy.h"

using namespace ai;

/// 内部动作节点工厂：构建 pull start 复合动作节点
class PullStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    PullStrategyActionNodeFactory()
    {
        creators["pull start"] = &pull_start;
    }

private:
    static ActionNode* pull_start(PlayerbotAI* ai)
    {
        return new ActionNode("pull start",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("pull action", ACTION_NORMAL), NULL));
    }
};

/// 构造拉怪策略，初始化拉怪技能、前置形态动作及宠物防御姿态
PullStrategy::PullStrategy(PlayerbotAI* ai, std::string pullAction, std::string prePullAction)
: Strategy(ai)
, pullActionName(pullAction)
, preActionName(prePullAction)
, pendingToStart(false)
, pullStartTime(0)
, petReactState(REACT_DEFENSIVE)
{
    actionNodeFactories.Add(std::make_unique<PullStrategyActionNodeFactory>());

    if (!ai->GetBot())
        return;
}

/// 获取实际执行的拉怪动作名（野德自动将精灵之火替换为野性精灵之火）
std::string PullStrategy::GetPullActionName() const
{
    std::string modPullActionName = pullActionName;

    // Select the faerie fire based on druid strategy | 根据德鲁伊天赋策略选择精灵之火变体
    if (ai->GetBot()->getClass() == CLASS_DRUID)
    {
        if (modPullActionName == "faerie fire")
        {
            if (ai->HasSpell("faerie fire (feral)") && (ai->HasStrategy("tank feral", BotState::BOT_STATE_COMBAT) || ai->HasStrategy("dps feral", BotState::BOT_STATE_COMBAT)))
            {
                modPullActionName = "faerie fire (feral)";
            }
        }
    }

    return modPullActionName;
}

/// 将通用射击动作解析为具体装备的弓/枪/弩/投掷武器技能名
std::string PullStrategy::GetSpellName() const
{
    std::string spellName = GetPullActionName();
    if (spellName == "shoot")
    {
        const Item* equippedWeapon = ai->GetBot()->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
        if (equippedWeapon)
        {
            const ItemPrototype* itemPrototype = equippedWeapon->GetProto();
            if (itemPrototype)
            {
                switch (itemPrototype->SubClass)
                {
#ifdef MANGOSBOT_ZERO
                    case ITEM_SUBCLASS_WEAPON_GUN:
                    {
                        spellName += " gun";
                        break;
                    }

                    case ITEM_SUBCLASS_WEAPON_BOW:
                    {
                        spellName += " bow";
                        break;
                    }

                    case ITEM_SUBCLASS_WEAPON_CROSSBOW:
                    {
                        spellName += " crossbow";
                        break;
                    }
#endif
                    case ITEM_SUBCLASS_WEAPON_THROWN:
                    {
                        spellName = "throw";
                        break;
                    }

                    default: break;
                }
            }
        }
    }

    return spellName;
}

/// 计算拉怪动作的最大有效施法/射程距离
float PullStrategy::GetRange() const
{
    float range;

    // Try to get the pull action range | 尝试查询拉怪法术的实际射程
    if (ai->GetSpellRange(GetSpellName(), &range))
    {
        range -= CONTACT_DISTANCE;
    }
    else
    {
        // Set the default range if the range was not found | 未查到法术射程时回退使用配置的射击/法术默认距离
        range = (pullActionName == "shoot") ? ai->GetRange("shoot") : ai->GetRange("spell");
    }

    return range;
}

/// 获取拉怪前需要执行的准备动作（如变形巨熊形态）
std::string PullStrategy::GetPreActionName() const
{
    std::string modPullActionName = preActionName;

    // Select the faerie fire based on druid strategy | 根据德鲁伊天赋策略决定是否保留前置变形动作
    if (ai->GetBot()->getClass() == CLASS_DRUID)
    {
        if (modPullActionName == "dire bear form")
        {
            if (GetPullActionName() == "faerie fire")
            {
                modPullActionName.clear();
            }
        }
    }

    return modPullActionName;
}

/// 初始化拉怪战斗触发器：响应拉怪开始与结束
void PullStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "pull start",
        NextAction::array(0, new NextAction("pull start", ACTION_MOVE), new NextAction("pull action", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "pull end",
        NextAction::array(0, new NextAction("pull end", ACTION_MOVE), NULL)));
}

/// 初始化拉怪非战斗触发器
void PullStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    InitCombatTriggers(triggers);
}

/// 注册拉怪乘数：拉怪期间抑制其他无关动作
void PullStrategy::InitCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    multipliers.push_back(new PullMultiplier(ai));
}

/// 注册拉怪非战斗乘数
void PullStrategy::InitNonCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    InitCombatMultipliers(multipliers);
}

/// 获取机器人当前激活的拉怪策略实例
PullStrategy* PullStrategy::Get(PlayerbotAI* ai)
{
    return ai ? ai->GetStrategy<PullStrategy>("pull", BotState::BOT_STATE_COMBAT) : nullptr;
}

/// 获取当前选定的拉怪目标
Unit* PullStrategy::GetTarget() const
{
    AiObjectContext* context = ai->GetAiObjectContext();
    return ai->GetUnit(AI_VALUE(ObjectGuid, "pull target"));
}

/// 设置或清空当前拉怪目标 GUID
void PullStrategy::SetTarget(Unit* target)
{
    AiObjectContext* context = ai->GetAiObjectContext();
    SET_AI_VALUE(ObjectGuid, "pull target", target ? target->GetObjectGuid() : ObjectGuid());
}

/// 检查机器人是否具备对指定目标执行拉怪动作的条件（武器/职业与可行性）
bool PullStrategy::CanDoPullAction(Unit* target)
{
    // Check if the bot can perform the pull action | 检查机器人能否执行拉怪动作

    // check if has ranged weapon | 除德鲁伊和圣骑士外，检查是否装备了远程武器
    if (ai->GetBot()->getClass() != CLASS_DRUID && ai->GetBot()->getClass() != CLASS_PALADIN && !ai->GetBot()->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED))
        return false;

    bool canPull = false;
    const std::string& pullAction = GetPullActionName();
    if (!pullAction.empty())
    {
        // Temporarily set the pull target to be used by the can do specific action method | 临时设置拉怪目标以便调用 CanDoSpecificAction 检测可行性
        AiObjectContext* context = ai->GetAiObjectContext();
        Unit* previousTarget = GetTarget();
        SetTarget(target);

        canPull = ai->CanDoSpecificAction("pull action", true, false);

        // Restore the previous pull target | 恢复先前的拉怪目标
        SetTarget(previousTarget);
    }

    return canPull;
}


/// 拉怪开始回调：清除待启动标记
void PullStrategy::OnPullStarted()
{
    pendingToStart = false;
}

/// 拉怪结束回调：清零计时并清空拉怪目标
void PullStrategy::OnPullEnded()
{
    pullStartTime = 0;
    SetTarget(nullptr);
}

/// 请求对指定目标发起拉怪并记录拉怪开始时间戳
void PullStrategy::RequestPull(Unit* target, bool resetTime)
{
    SetTarget(target);
    pendingToStart = true;
    if(resetTime)
    {
        pullStartTime = time(0);
    }
}

/// 乘数判定：拉怪目标存在时仅允许拉怪相关动作全权重执行，其余动作降权或屏蔽
float PullMultiplier::GetValue(Action* action)
{
    const PullStrategy* strategy = PullStrategy::Get(ai);
    if (strategy && strategy->HasTarget())
    {
        if ((action->getName() == "pull my target") ||
            (action->getName() == "pull rti target") ||
            (action->getName() == "reach pull") ||
            (action->getName() == "pull start") ||
            (action->getName() == "pull action") ||
            (action->getName() == "return to pull position") ||
            (action->getName() == "pull end"))
        {
            return 1.0f;
        }

        if (action->getRelevance() >= 100)
        {
            return 0.01f;
        }

        return 0.0f;
    }

    return 1.0f;
}

/// 初始化潜在 Add 防护战斗触发器：发现可能引怪时携宠物后撤
void PossibleAddsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "possible adds",
        NextAction::array(0, new NextAction("flee with pet", ACTION_EMERGENCY), NULL)));
}

/// 初始化拉回原位（Pull Back）战斗触发器：偏离拉怪点时返回预设站位
void PullBackStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "return to pull position",
        NextAction::array(0, new NextAction("return to pull position", static_cast<float>(ACTION_MOVE) + 5.0f), NULL)));
}

/// 初始化拉回原位非战斗触发器
void PullBackStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    InitCombatTriggers(triggers);
}