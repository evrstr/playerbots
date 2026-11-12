// 战士 - 狂怒战士策略实现文件 (FuryWarriorStrategy.cpp)

#include "playerbot/playerbot.h"
#include "FuryWarriorStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class FuryWarriorStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    FuryWarriorStrategyActionNodeFactory()
    {
        creators["charge"] = &charge;
        creators["berserker rage fear"] = &berserker_rage_fear;
        creators["piercing howl"] = &piercing_howl;
        creators["pummel"] = &pummel;
    }

private:
    // 动作节点 charge：冲锋 -> 备选(A)动作：拦截
    ACTION_NODE_A(charge, "charge", "intercept");

    // 动作节点 piercing_howl：刺耳怒吼 -> 备选(A)动作：断筋
    ACTION_NODE_A(piercing_howl, "piercing howl", "hamstring");

    // 动作节点 berserker_rage_fear：狂暴之怒 -> 备选(A)动作：死亡之愿
    ACTION_NODE_A(berserker_rage_fear, "berserker rage", "death wish");

    // 动作节点 pummel：拳击 -> 备选(A)动作：拦截
    ACTION_NODE_A(pummel, "pummel", "intercept");
};

// 构造函数：初始化狂怒战士策略并挂载动作节点工厂
FuryWarriorStrategy::FuryWarriorStrategy(PlayerbotAI* ai) : WarriorStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<FuryWarriorStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (狂怒战士策略)
NextAction** FuryWarriorStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (狂怒战士策略)
void FuryWarriorStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("intimidating shout", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("charge", ACTION_MOVE + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("execute", ACTION_NORMAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "bloodthirst",
        NextAction::array(0, new NextAction("bloodthirst", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "whirlwind",
        NextAction::array(0, new NextAction("whirlwind", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "heroic strike",
        NextAction::array(0, new NextAction("heroic strike", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "intercept on snare target",
        NextAction::array(0, new NextAction("intercept on snare target", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士策略)
void FuryWarriorStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (狂怒战士策略)
void FuryWarriorStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (狂怒战士策略)
void FuryWarriorStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士PVE策略)
void FuryWarriorPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士PVE策略)
void FuryWarriorPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (狂怒战士PVE策略)
void FuryWarriorPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (狂怒战士PVE策略)
void FuryWarriorPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士PVP策略)
void FuryWarriorPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士PVP策略)
void FuryWarriorPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (狂怒战士PVP策略)
void FuryWarriorPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (狂怒战士PVP策略)
void FuryWarriorPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士团队副本策略)
void FuryWarriorRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitCombatTriggers(triggers);
    WarriorRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "sunder armor",
        NextAction::array(0, new NextAction("sunder armor", ACTION_HIGH + 2), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士团队副本策略)
void FuryWarriorRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (狂怒战士团队副本策略)
void FuryWarriorRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitReactionTriggers(triggers);
    WarriorRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (狂怒战士团队副本策略)
void FuryWarriorRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitDeadTriggers(triggers);
    WarriorRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士AOE群体策略)
void FuryWarriorAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("whirlwind", ACTION_HIGH + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "melee high aoe",
        NextAction::array(0, new NextAction("retaliation", ACTION_HIGH + 5), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士AOE群体策略)
void FuryWarriorAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士AOE群体PVE策略)
void FuryWarriorAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士AOE群体PVE策略)
void FuryWarriorAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士AOE群体PVP策略)
void FuryWarriorAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士AOE群体PVP策略)
void FuryWarriorAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士AOE群体团队副本策略)
void FuryWarriorAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士AOE群体团队副本策略)
void FuryWarriorAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士增益Buff策略)
void FuryWarriorBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "berserker stance",
        NextAction::array(0, new NextAction("berserker stance", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "feared",
        NextAction::array(0, new NextAction("berserker rage fear", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "stunned",
        NextAction::array(0, new NextAction("berserker rage", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士增益Buff策略)
void FuryWarriorBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士增益BuffPVE策略)
void FuryWarriorBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士增益BuffPVE策略)
void FuryWarriorBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士增益BuffPVP策略)
void FuryWarriorBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士增益BuffPVP策略)
void FuryWarriorBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士增益Buff团队副本策略)
void FuryWarriorBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士增益Buff团队副本策略)
void FuryWarriorBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士爆发增益策略)
void FuryWarriorBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "death wish",
        NextAction::array(0, new NextAction("death wish", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "recklessness",
        NextAction::array(0, new NextAction("recklessness", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士爆发增益策略)
void FuryWarriorBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士爆发增益PVE策略)
void FuryWarriorBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士爆发增益PVE策略)
void FuryWarriorBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士爆发增益PVP策略)
void FuryWarriorBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士爆发增益PVP策略)
void FuryWarriorBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士爆发增益团队副本策略)
void FuryWarriorBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士爆发增益团队副本策略)
void FuryWarriorBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士控制(CC)策略)
void FuryWarriorCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "pummel",
        NextAction::array(0, new NextAction("pummel", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "pummel on enemy healer",
        NextAction::array(0, new NextAction("pummel on enemy healer", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "hamstring",
        NextAction::array(0, new NextAction("piercing howl", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士控制(CC)策略)
void FuryWarriorCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士控制(CC)PVE策略)
void FuryWarriorCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士控制(CC)PVE策略)
void FuryWarriorCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士控制(CC)PVP策略)
void FuryWarriorCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士控制(CC)PVP策略)
void FuryWarriorCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士控制(CC)团队副本策略)
void FuryWarriorCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士控制(CC)团队副本策略)
void FuryWarriorCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (狂怒战士策略)
NextAction** FuryWarriorStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (狂怒战士策略)
void FuryWarriorStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("intimidating shout", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("charge", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("execute", ACTION_NORMAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "bloodthirst",
        NextAction::array(0, new NextAction("bloodthirst", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "whirlwind",
        NextAction::array(0, new NextAction("whirlwind", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "heroic strike",
        NextAction::array(0, new NextAction("heroic strike", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "intercept on snare target",
        NextAction::array(0, new NextAction("intercept on snare target", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士策略)
void FuryWarriorStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (狂怒战士策略)
void FuryWarriorStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (狂怒战士策略)
void FuryWarriorStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士PVE策略)
void FuryWarriorPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士PVE策略)
void FuryWarriorPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (狂怒战士PVE策略)
void FuryWarriorPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (狂怒战士PVE策略)
void FuryWarriorPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士PVP策略)
void FuryWarriorPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士PVP策略)
void FuryWarriorPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (狂怒战士PVP策略)
void FuryWarriorPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (狂怒战士PVP策略)
void FuryWarriorPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士团队副本策略)
void FuryWarriorRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitCombatTriggers(triggers);
    WarriorRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "sunder armor",
        NextAction::array(0, new NextAction("sunder armor", ACTION_HIGH + 2), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士团队副本策略)
void FuryWarriorRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (狂怒战士团队副本策略)
void FuryWarriorRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitReactionTriggers(triggers);
    WarriorRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (狂怒战士团队副本策略)
void FuryWarriorRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitDeadTriggers(triggers);
    WarriorRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士AOE群体策略)
void FuryWarriorAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("whirlwind", ACTION_HIGH + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("bloodthirst", ACTION_HIGH + 4), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士AOE群体策略)
void FuryWarriorAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士AOE群体PVE策略)
void FuryWarriorAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士AOE群体PVE策略)
void FuryWarriorAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士AOE群体PVP策略)
void FuryWarriorAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士AOE群体PVP策略)
void FuryWarriorAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士AOE群体团队副本策略)
void FuryWarriorAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士AOE群体团队副本策略)
void FuryWarriorAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士增益Buff策略)
void FuryWarriorBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "berserker stance",
        NextAction::array(0, new NextAction("berserker stance", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "feared",
        NextAction::array(0, new NextAction("berserker rage fear", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "stunned",
        NextAction::array(0, new NextAction("berserker rage", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士增益Buff策略)
void FuryWarriorBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士增益BuffPVE策略)
void FuryWarriorBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士增益BuffPVE策略)
void FuryWarriorBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士增益BuffPVP策略)
void FuryWarriorBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士增益BuffPVP策略)
void FuryWarriorBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士增益Buff团队副本策略)
void FuryWarriorBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士增益Buff团队副本策略)
void FuryWarriorBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士爆发增益策略)
void FuryWarriorBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rampage",
        NextAction::array(0, new NextAction("rampage", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "recklessness",
        NextAction::array(0, new NextAction("recklessness", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士爆发增益策略)
void FuryWarriorBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士爆发增益PVE策略)
void FuryWarriorBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士爆发增益PVE策略)
void FuryWarriorBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士爆发增益PVP策略)
void FuryWarriorBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士爆发增益PVP策略)
void FuryWarriorBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士爆发增益团队副本策略)
void FuryWarriorBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士爆发增益团队副本策略)
void FuryWarriorBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士控制(CC)策略)
void FuryWarriorCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "pummel",
        NextAction::array(0, new NextAction("pummel", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "pummel on enemy healer",
        NextAction::array(0, new NextAction("pummel on enemy healer", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "hamstring",
        NextAction::array(0, new NextAction("piercing howl", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士控制(CC)策略)
void FuryWarriorCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士控制(CC)PVE策略)
void FuryWarriorCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士控制(CC)PVE策略)
void FuryWarriorCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士控制(CC)PVP策略)
void FuryWarriorCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士控制(CC)PVP策略)
void FuryWarriorCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士控制(CC)团队副本策略)
void FuryWarriorCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士控制(CC)团队副本策略)
void FuryWarriorCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (狂怒战士策略)
NextAction** FuryWarriorStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (狂怒战士策略)
void FuryWarriorStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("intimidating shout", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("charge", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "instant slam",
        NextAction::array(0, new NextAction("slam", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "bloodthirst",
        NextAction::array(0, new NextAction("bloodthirst", ACTION_NORMAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "whirlwind",
        NextAction::array(0, new NextAction("whirlwind", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "heroic strike",
        NextAction::array(0, new NextAction("heroic strike", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("execute", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "intercept on snare target",
        NextAction::array(0, new NextAction("intercept on snare target", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士策略)
void FuryWarriorStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (狂怒战士策略)
void FuryWarriorStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (狂怒战士策略)
void FuryWarriorStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士PVE策略)
void FuryWarriorPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士PVE策略)
void FuryWarriorPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (狂怒战士PVE策略)
void FuryWarriorPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (狂怒战士PVE策略)
void FuryWarriorPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士PVP策略)
void FuryWarriorPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士PVP策略)
void FuryWarriorPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (狂怒战士PVP策略)
void FuryWarriorPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (狂怒战士PVP策略)
void FuryWarriorPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士团队副本策略)
void FuryWarriorRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitCombatTriggers(triggers);
    WarriorRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "sunder armor",
        NextAction::array(0, new NextAction("sunder armor", ACTION_HIGH + 2), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士团队副本策略)
void FuryWarriorRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (狂怒战士团队副本策略)
void FuryWarriorRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitReactionTriggers(triggers);
    WarriorRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (狂怒战士团队副本策略)
void FuryWarriorRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorStrategy::InitDeadTriggers(triggers);
    WarriorRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士AOE群体策略)
void FuryWarriorAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士AOE群体策略)
void FuryWarriorAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("whirlwind", ACTION_HIGH + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("bloodthirst", ACTION_HIGH + 4), NULL)));
}

// 初始化战斗阶段触发器列表 (狂怒战士AOE群体PVE策略)
void FuryWarriorAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士AOE群体PVE策略)
void FuryWarriorAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士AOE群体PVP策略)
void FuryWarriorAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士AOE群体PVP策略)
void FuryWarriorAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士AOE群体团队副本策略)
void FuryWarriorAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士AOE群体团队副本策略)
void FuryWarriorAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士增益Buff策略)
void FuryWarriorBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "berserker stance",
        NextAction::array(0, new NextAction("berserker stance", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "feared",
        NextAction::array(0, new NextAction("berserker rage fear", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士增益Buff策略)
void FuryWarriorBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士增益BuffPVE策略)
void FuryWarriorBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士增益BuffPVE策略)
void FuryWarriorBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士增益BuffPVP策略)
void FuryWarriorBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士增益BuffPVP策略)
void FuryWarriorBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士增益Buff团队副本策略)
void FuryWarriorBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士增益Buff团队副本策略)
void FuryWarriorBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士爆发增益策略)
void FuryWarriorBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "death wish",
        NextAction::array(0, new NextAction("death wish", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "recklessness",
        NextAction::array(0, new NextAction("recklessness", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士爆发增益策略)
void FuryWarriorBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士爆发增益PVE策略)
void FuryWarriorBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士爆发增益PVE策略)
void FuryWarriorBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士爆发增益PVP策略)
void FuryWarriorBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士爆发增益PVP策略)
void FuryWarriorBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士爆发增益团队副本策略)
void FuryWarriorBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士爆发增益团队副本策略)
void FuryWarriorBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士控制(CC)策略)
void FuryWarriorCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "pummel",
        NextAction::array(0, new NextAction("pummel", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "pummel on enemy healer",
        NextAction::array(0, new NextAction("pummel on enemy healer", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "hamstring",
        NextAction::array(0, new NextAction("piercing howl", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (狂怒战士控制(CC)策略)
void FuryWarriorCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士控制(CC)PVE策略)
void FuryWarriorCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士控制(CC)PVE策略)
void FuryWarriorCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士控制(CC)PVP策略)
void FuryWarriorCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士控制(CC)PVP策略)
void FuryWarriorCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (狂怒战士控制(CC)团队副本策略)
void FuryWarriorCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (狂怒战士控制(CC)团队副本策略)
void FuryWarriorCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FuryWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
