// 战士 - 武器战士策略实现文件 (ArmsWarriorStrategy.cpp)

#include "playerbot/playerbot.h"
#include "ArmsWarriorStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class ArmsWarriorStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    ArmsWarriorStrategyActionNodeFactory()
    {
        creators["charge"] = &charge;
        creators["death wish"] = &death_wish;
        creators["berserker rage fear"] = &berserker_rage_fear;
        creators["piercing howl"] = &piercing_howl;
        creators["mocking blow"] = &mocking_blow;
        creators["heroic strike"] = &heroic_strike;
        creators["whirlwind"] = &whirlwind;
        creators["sweeping strikes"] = &sweeping_strikes;
    }

private:
    // 动作节点 charge：冲锋 -> 备选(A)动作：reach melee
    ACTION_NODE_A(charge, "charge", "reach melee");

    // 动作节点 death_wish：死亡之愿 -> 备选(A)动作：血性狂暴
    ACTION_NODE_A(death_wish, "death wish", "bloodrage");

    // 动作节点 piercing_howl：刺耳怒吼 -> 备选(A)动作：断筋
    ACTION_NODE_A(piercing_howl, "piercing howl", "hamstring");

    // 动作节点 mocking_blow：惩戒痛击 -> 备选(A)动作：断筋
    ACTION_NODE_A(mocking_blow, "mocking blow", "hamstring");

    // 动作节点 heroic_strike：英勇打击 -> 备选(A)动作：melee
    ACTION_NODE_A(heroic_strike, "heroic strike", "melee");

    // 动作节点 berserker_rage_fear：狂暴之怒 -> 备选(A)动作：死亡之愿
    ACTION_NODE_A(berserker_rage_fear, "berserker rage", "death wish");

    // 动作节点 whirlwind：旋风斩 -> 前置(P)动作：狂暴姿态
    ACTION_NODE_P(whirlwind, "whirlwind", "berserker stance");

    // 动作节点 sweeping_strikes：横扫攻击 -> 前置(P)动作：战斗姿态
    ACTION_NODE_P(sweeping_strikes, "sweeping strikes", "battle stance");
};

// 构造函数：初始化武器战士策略并挂载动作节点工厂
ArmsWarriorStrategy::ArmsWarriorStrategy(PlayerbotAI* ai) : WarriorStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<ArmsWarriorStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (武器战士策略)
NextAction** ArmsWarriorStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (武器战士策略)
void ArmsWarriorStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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
        NextAction::array(0, new NextAction("execute", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "overpower",
        NextAction::array(0, new NextAction("overpower", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "mortal strike",
        NextAction::array(0, new NextAction("mortal strike", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "whirlwind",
        NextAction::array(0, new NextAction("whirlwind", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "heroic strike",
        NextAction::array(0, new NextAction("heroic strike", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "rend",
        NextAction::array(0, new NextAction("rend", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士策略)
void ArmsWarriorStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (武器战士策略)
void ArmsWarriorStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (武器战士策略)
void ArmsWarriorStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士PVE策略)
void ArmsWarriorPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士PVE策略)
void ArmsWarriorPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (武器战士PVE策略)
void ArmsWarriorPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (武器战士PVE策略)
void ArmsWarriorPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士PVP策略)
void ArmsWarriorPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士PVP策略)
void ArmsWarriorPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (武器战士PVP策略)
void ArmsWarriorPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (武器战士PVP策略)
void ArmsWarriorPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士团队副本策略)
void ArmsWarriorRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitCombatTriggers(triggers);
    WarriorRaidStrategy::InitCombatTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        "sunder armor",
        NextAction::array(0, new NextAction("sunder armor", ACTION_HIGH + 2), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士团队副本策略)
void ArmsWarriorRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (武器战士团队副本策略)
void ArmsWarriorRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitReactionTriggers(triggers);
    WarriorRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (武器战士团队副本策略)
void ArmsWarriorRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitDeadTriggers(triggers);
    WarriorRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士AOE群体策略)
void ArmsWarriorAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("sweeping strikes", ACTION_HIGH + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("whirlwind", ACTION_HIGH + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "melee high aoe",
        NextAction::array(0, new NextAction("retaliation", ACTION_HIGH + 5), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士AOE群体策略)
void ArmsWarriorAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士AOE群体PVE策略)
void ArmsWarriorAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士AOE群体PVE策略)
void ArmsWarriorAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士AOE群体PVP策略)
void ArmsWarriorAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士AOE群体PVP策略)
void ArmsWarriorAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士AOE群体团队副本策略)
void ArmsWarriorAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士AOE群体团队副本策略)
void ArmsWarriorAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士增益Buff策略)
void ArmsWarriorBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "berserker stance",
        NextAction::array(0, new NextAction("berserker stance", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "feared",
        NextAction::array(0, new NextAction("berserker rage fear", ACTION_INTERRUPT), NULL)));

}

// 初始化非战斗阶段触发器列表 (武器战士增益Buff策略)
void ArmsWarriorBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士增益BuffPVE策略)
void ArmsWarriorBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士增益BuffPVE策略)
void ArmsWarriorBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士增益BuffPVP策略)
void ArmsWarriorBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士增益BuffPVP策略)
void ArmsWarriorBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士增益Buff团队副本策略)
void ArmsWarriorBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士增益Buff团队副本策略)
void ArmsWarriorBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士爆发增益策略)
void ArmsWarriorBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "recklessness",
        NextAction::array(0, new NextAction("recklessness", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士爆发增益策略)
void ArmsWarriorBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士爆发增益PVE策略)
void ArmsWarriorBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士爆发增益PVE策略)
void ArmsWarriorBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士爆发增益PVP策略)
void ArmsWarriorBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士爆发增益PVP策略)
void ArmsWarriorBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士爆发增益团队副本策略)
void ArmsWarriorBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士爆发增益团队副本策略)
void ArmsWarriorBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士控制(CC)策略)
void ArmsWarriorCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hamstring",
        NextAction::array(0, new NextAction("piercing howl", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士控制(CC)策略)
void ArmsWarriorCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士控制(CC)PVE策略)
void ArmsWarriorCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士控制(CC)PVE策略)
void ArmsWarriorCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士控制(CC)PVP策略)
void ArmsWarriorCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士控制(CC)PVP策略)
void ArmsWarriorCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士控制(CC)团队副本策略)
void ArmsWarriorCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士控制(CC)团队副本策略)
void ArmsWarriorCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC


// 获取默认战斗动作序列 (武器战士策略)
NextAction** ArmsWarriorStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (武器战士策略)
void ArmsWarriorStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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
        NextAction::array(0, new NextAction("execute", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "overpower",
        NextAction::array(0, new NextAction("overpower", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "heroic strike",
        NextAction::array(0, new NextAction("heroic strike", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "mortal strike",
        NextAction::array(0, new NextAction("mortal strike", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "rend",
        NextAction::array(0, new NextAction("rend", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士策略)
void ArmsWarriorStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (武器战士策略)
void ArmsWarriorStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (武器战士策略)
void ArmsWarriorStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士PVE策略)
void ArmsWarriorPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士PVE策略)
void ArmsWarriorPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (武器战士PVE策略)
void ArmsWarriorPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (武器战士PVE策略)
void ArmsWarriorPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士PVP策略)
void ArmsWarriorPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士PVP策略)
void ArmsWarriorPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (武器战士PVP策略)
void ArmsWarriorPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (武器战士PVP策略)
void ArmsWarriorPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士团队副本策略)
void ArmsWarriorRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitCombatTriggers(triggers);
    WarriorRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "sunder armor",
        NextAction::array(0, new NextAction("sunder armor", ACTION_HIGH + 2), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士团队副本策略)
void ArmsWarriorRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (武器战士团队副本策略)
void ArmsWarriorRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitReactionTriggers(triggers);
    WarriorRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (武器战士团队副本策略)
void ArmsWarriorRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitDeadTriggers(triggers);
    WarriorRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士AOE群体策略)
void ArmsWarriorAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士AOE群体策略)
void ArmsWarriorAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士AOE群体PVE策略)
void ArmsWarriorAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士AOE群体PVE策略)
void ArmsWarriorAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士AOE群体PVP策略)
void ArmsWarriorAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士AOE群体PVP策略)
void ArmsWarriorAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士AOE群体团队副本策略)
void ArmsWarriorAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士AOE群体团队副本策略)
void ArmsWarriorAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士增益Buff策略)
void ArmsWarriorBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "berserker stance",
        NextAction::array(0, new NextAction("berserker stance", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "death wish",
        NextAction::array(0, new NextAction("death wish", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "feared",
        NextAction::array(0, new NextAction("berserker rage fear", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士增益Buff策略)
void ArmsWarriorBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士增益BuffPVE策略)
void ArmsWarriorBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士增益BuffPVE策略)
void ArmsWarriorBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士增益BuffPVP策略)
void ArmsWarriorBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士增益BuffPVP策略)
void ArmsWarriorBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士增益Buff团队副本策略)
void ArmsWarriorBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士增益Buff团队副本策略)
void ArmsWarriorBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士爆发增益策略)
void ArmsWarriorBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "recklessness",
        NextAction::array(0, new NextAction("recklessness", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士爆发增益策略)
void ArmsWarriorBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士爆发增益PVE策略)
void ArmsWarriorBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士爆发增益PVE策略)
void ArmsWarriorBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士爆发增益PVP策略)
void ArmsWarriorBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士爆发增益PVP策略)
void ArmsWarriorBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士爆发增益团队副本策略)
void ArmsWarriorBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士爆发增益团队副本策略)
void ArmsWarriorBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士控制(CC)策略)
void ArmsWarriorCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hamstring",
        NextAction::array(0, new NextAction("piercing howl", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士控制(CC)策略)
void ArmsWarriorCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士控制(CC)PVE策略)
void ArmsWarriorCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士控制(CC)PVE策略)
void ArmsWarriorCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士控制(CC)PVP策略)
void ArmsWarriorCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士控制(CC)PVP策略)
void ArmsWarriorCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士控制(CC)团队副本策略)
void ArmsWarriorCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士控制(CC)团队副本策略)
void ArmsWarriorCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (武器战士策略)
NextAction** ArmsWarriorStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (武器战士策略)
void ArmsWarriorStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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
        NextAction::array(0, new NextAction("execute", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "sudden death",
        NextAction::array(0, new NextAction("execute", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "overpower",
        NextAction::array(0, new NextAction("overpower", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "taste for blood",
        NextAction::array(0, new NextAction("overpower", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "heroic strike",
        NextAction::array(0, new NextAction("heroic strike", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "mortal strike",
        NextAction::array(0, new NextAction("mortal strike", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "rend",
        NextAction::array(0, new NextAction("rend", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士策略)
void ArmsWarriorStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (武器战士策略)
void ArmsWarriorStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (武器战士策略)
void ArmsWarriorStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士PVE策略)
void ArmsWarriorPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士PVE策略)
void ArmsWarriorPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (武器战士PVE策略)
void ArmsWarriorPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (武器战士PVE策略)
void ArmsWarriorPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士PVP策略)
void ArmsWarriorPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士PVP策略)
void ArmsWarriorPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (武器战士PVP策略)
void ArmsWarriorPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (武器战士PVP策略)
void ArmsWarriorPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士团队副本策略)
void ArmsWarriorRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitCombatTriggers(triggers);
    WarriorRaidStrategy::InitCombatTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        "sunder armor",
        NextAction::array(0, new NextAction("sunder armor", ACTION_HIGH + 2), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士团队副本策略)
void ArmsWarriorRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (武器战士团队副本策略)
void ArmsWarriorRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitReactionTriggers(triggers);
    WarriorRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (武器战士团队副本策略)
void ArmsWarriorRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorStrategy::InitDeadTriggers(triggers);
    WarriorRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士AOE群体策略)
void ArmsWarriorAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("bladestorm", ACTION_HIGH + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("sweeping strikes", ACTION_HIGH + 4), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士AOE群体策略)
void ArmsWarriorAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士AOE群体PVE策略)
void ArmsWarriorAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士AOE群体PVE策略)
void ArmsWarriorAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士AOE群体PVP策略)
void ArmsWarriorAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士AOE群体PVP策略)
void ArmsWarriorAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士AOE群体团队副本策略)
void ArmsWarriorAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士AOE群体团队副本策略)
void ArmsWarriorAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士增益Buff策略)
void ArmsWarriorBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "berserker stance",
        NextAction::array(0, new NextAction("berserker stance", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "feared",
        NextAction::array(0, new NextAction("berserker rage fear", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士增益Buff策略)
void ArmsWarriorBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士增益BuffPVE策略)
void ArmsWarriorBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士增益BuffPVE策略)
void ArmsWarriorBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士增益BuffPVP策略)
void ArmsWarriorBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士增益BuffPVP策略)
void ArmsWarriorBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士增益Buff团队副本策略)
void ArmsWarriorBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士增益Buff团队副本策略)
void ArmsWarriorBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士爆发增益策略)
void ArmsWarriorBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "recklessness",
        NextAction::array(0, new NextAction("recklessness", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士爆发增益策略)
void ArmsWarriorBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士爆发增益PVE策略)
void ArmsWarriorBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士爆发增益PVE策略)
void ArmsWarriorBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士爆发增益PVP策略)
void ArmsWarriorBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士爆发增益PVP策略)
void ArmsWarriorBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士爆发增益团队副本策略)
void ArmsWarriorBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士爆发增益团队副本策略)
void ArmsWarriorBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士控制(CC)策略)
void ArmsWarriorCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hamstring",
        NextAction::array(0, new NextAction("piercing howl", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (武器战士控制(CC)策略)
void ArmsWarriorCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士控制(CC)PVE策略)
void ArmsWarriorCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士控制(CC)PVE策略)
void ArmsWarriorCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士控制(CC)PVP策略)
void ArmsWarriorCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士控制(CC)PVP策略)
void ArmsWarriorCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (武器战士控制(CC)团队副本策略)
void ArmsWarriorCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (武器战士控制(CC)团队副本策略)
void ArmsWarriorCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArmsWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif

// 乘数修饰器 (WarriorSweepingStrikesPveMultiplier)：动态调整特定状态下的动作权重
class WarriorSweepingStrikesPveMultiplier : public Multiplier
{
public:
    WarriorSweepingStrikesPveMultiplier(PlayerbotAI* ai) : Multiplier(ai, "aoe arms pve") {}

    float GetValue(Action* action) override
    {
        // Disable Berserker Stance
        const std::string& actionName = action->getName();
        if ((actionName == "berserker stance" ||
            actionName == "whirlwind" ||
            actionName == "mortal strike" ||
            actionName == "heroic strike" ||
            actionName == "cleave") &&
            AI_VALUE2(bool, "trigger active", "melee light aoe") &&
            bot->HasSpell(12292) &&
            bot->IsSpellReady(12292) &&
            !bot->HasAura(12292))
        {
            return 0.0f;
        }

        // Disable Battle Stance spam if SS is on CD
        if ((actionName == "battle stance") &&
            AI_VALUE2(bool, "trigger active", "melee light aoe") &&
            bot->HasSpell(12292) &&
            !bot->IsSpellReady(12292))
        {
            return 0.0f;
        }

        return 1.0f;
    }
};

// 乘数修饰器 (WarriorSweepingStrikesRaidMultiplier)：动态调整特定状态下的动作权重
class WarriorSweepingStrikesRaidMultiplier : public Multiplier
{
public:
    WarriorSweepingStrikesRaidMultiplier(PlayerbotAI* ai) : Multiplier(ai, "aoe arms raid") {}

    float GetValue(Action* action) override
    {
        // Disable Berserker Stance
        const std::string& actionName = action->getName();
        if ((actionName == "berserker stance" ||
            actionName == "whirlwind" ||
            actionName == "mortal strike" ||
            actionName == "heroic strike" ||
            actionName == "cleave") &&
            AI_VALUE2(bool, "trigger active", "melee light aoe") &&
            bot->HasSpell(12292) &&
            bot->IsSpellReady(12292) &&
            !bot->HasAura(12292))
        {
            return 0.0f;
        }

        // Disable Battle Stance spam if SS is on CD
        if ((actionName == "battle stance") &&
            AI_VALUE2(bool, "trigger active", "melee light aoe") &&
            bot->HasSpell(12292) &&
            !bot->IsSpellReady(12292))
        {
            return 0.0f;
        }

        return 1.0f;
    }
};

// 乘数修饰器 (WarriorSweepingStrikesPvpMultiplier)：动态调整特定状态下的动作权重
class WarriorSweepingStrikesPvpMultiplier : public Multiplier
{
public:
    WarriorSweepingStrikesPvpMultiplier(PlayerbotAI* ai) : Multiplier(ai, "aoe arms pvp") {}

    float GetValue(Action* action) override
    {
        // Disable Berserker Stance
        const std::string& actionName = action->getName();
        if ((actionName == "berserker stance" ||
            actionName == "whirlwind" ||
            actionName == "mortal strike" ||
            actionName == "heroic strike" ||
            actionName == "cleave") &&
            AI_VALUE2(bool, "trigger active", "melee light aoe") &&
            bot->HasSpell(12292) &&
            bot->IsSpellReady(12292) &&
            !bot->HasAura(12292))
        {
            return 0.0f;
        }

        // Disable Battle Stance spam if SS is on CD
        if ((actionName == "battle stance") &&
            AI_VALUE2(bool, "trigger active", "melee light aoe") &&
            bot->HasSpell(12292) &&
            !bot->IsSpellReady(12292))
        {
            return 0.0f;
        }

        return 1.0f;
    }
};

// 初始化战斗阶段乘数修饰器 (武器战士AOE群体策略)
void ArmsWarriorAoeStrategy::InitCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    multipliers.push_back(new WarriorSweepingStrikesPveMultiplier(ai));
    multipliers.push_back(new WarriorSweepingStrikesRaidMultiplier(ai));
    multipliers.push_back(new WarriorSweepingStrikesPvpMultiplier(ai));
}
