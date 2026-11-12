/// 通用战斗与避险策略实现

#include "playerbot/playerbot.h"
#include "CombatStrategy.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

/// 初始化通用战斗触发器（重选无效目标、解除卡死/僵持、饰品与光束泉使用）
void CombatStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "invalid target",
        NextAction::array(0, new NextAction("select new target", 89.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "combat standoff",
        NextAction::array(0, new NextAction("drop standoff", 91.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "movement loop stuck",
        NextAction::array(0, new NextAction("release stuck movement", 101.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "mounted",
        NextAction::array(0, new NextAction("check mount state", 88.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "combat stuck",
        NextAction::array(0, new NextAction("unstuck", 0.7f), NULL)));

    triggers.push_back(new TriggerNode(
        "combat long stuck",
        NextAction::array(0, new NextAction("unstuck", 0.9f), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("use trinket", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("use lightwell", 80.0f), NULL)));
}

/// 乘数判定：身处地面 AoE 危险减益中时禁用需要读条/引导的法术，优先跑位躲避
float AvoidAoeStrategyMultiplier::GetValue(Action* action)
{
    if (!action)
        return 1.0f;

    std::string name = action->getName();
    if (name == "follow" || name == "co" || name == "nc" || name == "react" || name == "select new target" || name == "flee")
        return 1.0f;

    uint32 spellId = AI_VALUE2(uint32, "spell id", name);
    const SpellEntry* const pSpellInfo = sServerFacade.LookupSpellInfo(spellId);
    if (!pSpellInfo) return 1.0f;

    if (spellId && pSpellInfo->Targets & TARGET_FLAG_DEST_LOCATION)
        return 1.0f;
    else if (spellId && pSpellInfo->Targets & TARGET_FLAG_SOURCE_LOCATION)
        return 1.0f;

    uint32 CastingTime = !IsChanneledSpell(pSpellInfo) ? GetSpellCastTime(pSpellInfo, bot) : GetSpellDuration(pSpellInfo);

    if (AI_VALUE2(bool, "has area debuff", "self target") && spellId && CastingTime > 0)
    {
        return 0.0f;
    }

    return 1.0f;
}

/// 初始化躲避 AoE 战斗触发器：检测到区域减益时立即紧急逃离
void AvoidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "has area debuff",
        NextAction::array(0, new NextAction("flee", ACTION_EMERGENCY + 5), NULL)));
}

/// 初始化躲避 AoE 反应触发器
void AvoidAoeStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    InitCombatTriggers(triggers);
}

/// 注册躲避 AoE 战斗乘数
void AvoidAoeStrategy::InitCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    multipliers.push_back(new AvoidAoeStrategyMultiplier(ai));
}

/// 注册躲避 AoE 反应乘数
void AvoidAoeStrategy::InitReactionMultipliers(std::list<Multiplier*>& multipliers)
{
    InitCombatMultipliers(multipliers);
}

/// 初始化躲避特定生物战斗触发器
void AvoidSpecificCreaturesStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "specific creature too close",
        NextAction::array(0, new NextAction("move away from specific creatures", ACTION_EMERGENCY + 5), NULL)));
}

/// 初始化躲避特定生物反应触发器
void AvoidSpecificCreaturesStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    InitCombatTriggers(triggers);
}

/// 注册躲避特定生物战斗乘数
void AvoidSpecificCreaturesStrategy::InitCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    multipliers.push_back(new AvoidSpecificCreaturesStrategyMultiplier(ai));
}

/// 注册躲避特定生物反应乘数
void AvoidSpecificCreaturesStrategy::InitReactionMultipliers(std::list<Multiplier*>& multipliers)
{
    InitCombatMultipliers(multipliers);
}

/// 初始化等待开怪战斗触发器：开战初期保持安全距离
void WaitForAttackStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "wait for attack safe distance",
        NextAction::array(0, new NextAction("wait for attack keep safe distance", ACTION_MOVE), NULL)));
}

/// 注册等待开怪战斗乘数
void WaitForAttackStrategy::InitCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    multipliers.push_back(new WaitForAttackMultiplier(ai));
}

/// 获取机器人当前激活的 WaitForAttackStrategy 实例
WaitForAttackStrategy* WaitForAttackStrategy::Get(PlayerbotAI* ai)
{
    return ai ? ai->GetStrategy<WaitForAttackStrategy>("wait for attack", BotState::BOT_STATE_COMBAT) : nullptr;
}

/// 判断是否仍处于开战前的等待仇恨稳定窗口期内
bool WaitForAttackStrategy::ShouldWait(PlayerbotAI* ai)
{
    // Only check if the bot has the strategy enabled | 仅在启用了 wait for attack 策略时检查
    if (ai->HasStrategy("wait for attack", BotState::BOT_STATE_COMBAT))
    {
        // Only check if bot is in a group with a real player | 仅在与真人玩家组队时生效
        Player* bot = ai->GetBot();
        AiObjectContext* context = ai->GetAiObjectContext();
        if (bot->GetGroup() && ai->HasRealPlayerMaster())
        {
            // Don't wait if the current target is an enemy player | 若当前目标为敌对玩家则不等待
            bool enemyPlayer = false;
            PlayerbotAI* ai = bot->GetPlayerbotAI();
            Unit* target = ai->GetUnit(context->GetValue<ObjectGuid>("current target")->Get());
            if (target)
            {
                Player* player = dynamic_cast<Player*>(target);
                if (player)
                {
                    enemyPlayer = !sServerFacade.IsFriendlyTo(target, player);
                }
            }

            if (!enemyPlayer)
            {
                // Check if bot is currently in combat | 检查当前是否已进入战斗
                const time_t combatStartTime = AI_VALUE(time_t, "combat start time");
                if (combatStartTime > 0)
                {
                    // Check the amount of time elapsed from the combat start | 判断自进战起经过的时间是否小于等待时长
                    const time_t elapsedTime = time(0) - combatStartTime;
                    return elapsedTime < GetWaitTime(ai);
                }
            }
        }
    }

    return false;
}

/// 获取配置的等待开怪秒数
uint8 WaitForAttackStrategy::GetWaitTime(PlayerbotAI* ai)
{
    AiObjectContext* context = ai->GetAiObjectContext();
    return AI_VALUE(uint8, "wait for attack time");
}

/// 乘数判定：等待开怪期间屏蔽高威胁攻击动作，仅保留走位、协助与拉怪动作
float WaitForAttackMultiplier::GetValue(Action* action)
{
    // Allow some movement and targeting actions and non threat actions (like cc!) | 允许移动、选目标及无威胁动作（如控场）执行
    const std::string& actionName = action->getName();
    if ((actionName != "wait for attack keep safe distance") && 
        (actionName != "dps assist") && 
        (actionName != "set facing") &&
        (actionName != "pull my target") &&
        (actionName != "pull rti target") &&
        (actionName != "pull start") &&
        (actionName != "pull action") &&
        (actionName != "pull end") &&
        (action->getThreatType() != ActionThreatType::ACTION_THREAT_NONE))
    {
        return WaitForAttackStrategy::ShouldWait(ai) ? 0.0f : 1.0f;
    }

    return 1.0f;
}

/// 初始化治疗打断战斗触发器：治疗目标满血时立即中断当前读条
void HealInterruptStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "heal target full health",
        NextAction::array(0, new NextAction("interrupt current spell", ACTION_EMERGENCY), NULL)));
}

/// 初始化治疗打断反应触发器
void HealInterruptStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    InitCombatTriggers(triggers);
}
