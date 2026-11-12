// 德鲁伊 - 输出野性德鲁伊策略实现文件 (DpsFeralDruidStrategy.cpp)

#include "playerbot/playerbot.h"
#include "DruidMultipliers.h"
#include "DpsFeralDruidStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class DpsFeralDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsFeralDruidStrategyActionNodeFactory()
    {
        creators["survival instincts"] = &survival_instincts;
        creators["omen of clarity"] = &omen_of_clarity;
        creators["feral charge - cat"] = &feral_charge_cat;
        creators["shred"] = &shred;
        creators["mangle (cat)"] = &mangle_cat;
        creators["powershift"] = &powershift;
    }

private:
    // 动作节点 survival_instincts：生存本能 -> 备选(A)动作：树皮术
    ACTION_NODE_A(survival_instincts, "survival instincts", "barskin");

    // 动作节点 omen_of_clarity：清晰预兆 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(omen_of_clarity, "omen of clarity", "caster form");

    // 动作节点 feral_charge_cat：野性冲锋(豹) -> 备选(A)动作：reach melee
    ACTION_NODE_A(feral_charge_cat, "feral charge - cat", "reach melee");

    // 动作节点 shred：撕碎 -> 备选(A)动作：裂伤(豹)
    ACTION_NODE_A(shred, "shred", "mangle (cat)");

    // 动作节点 mangle_cat：裂伤(豹) -> 备选(A)动作：爪击
    ACTION_NODE_A(mangle_cat, "mangle (cat)", "claw");

    // 动作节点 pounce：突袭 -> 备选(A)动作：毁灭
    ACTION_NODE_A(pounce, "pounce", "ravage");

    // 动作节点 ravage：毁灭 -> 备选(A)动作：撕碎
    ACTION_NODE_A(ravage, "ravage", "shred");

    // 动作节点 powershift：人形态(施法者形态) -> 后续(C)动作：猎豹形态
    ACTION_NODE_C(powershift, "caster form", "cat form");
};

// 构造函数：初始化输出野性德鲁伊策略并挂载动作节点工厂
DpsFeralDruidStrategy::DpsFeralDruidStrategy(PlayerbotAI* ai) : DruidStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<DpsFeralDruidStrategyActionNodeFactory>());
}

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class DpsFeralDruidStealthStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsFeralDruidStealthStrategyActionNodeFactory()
    {
        creators["pounce"] = &pounce;
        creators["ravage"] = &ravage;
        creators["shred"] = &shred;
        creators["mangle (cat)"] = &mangle_cat;
        creators["feral charge - cat"] = &feral_charge_cat;
    }

private:
    // 动作节点 feral_charge_cat：野性冲锋(豹) -> 备选(A)动作：reach melee
    ACTION_NODE_A(feral_charge_cat, "feral charge - cat", "reach melee");

    // 动作节点 shred：撕碎 -> 备选(A)动作：裂伤(豹)
    ACTION_NODE_A(shred, "shred", "mangle (cat)");

    // 动作节点 mangle_cat：裂伤(豹) -> 备选(A)动作：爪击
    ACTION_NODE_A(mangle_cat, "mangle (cat)", "claw");

    // 动作节点 pounce：突袭 -> 备选(A)动作：毁灭
    ACTION_NODE_A(pounce, "pounce", "ravage");

    // 动作节点 ravage：毁灭 -> 备选(A)动作：撕碎
    ACTION_NODE_A(ravage, "ravage", "shred");
};

// 构造函数：初始化输出野性德鲁伊潜行策略并挂载动作节点工厂
DpsFeralDruidStealthStrategy::DpsFeralDruidStealthStrategy(PlayerbotAI* ai) : StealthStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<DpsFeralDruidStealthStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (输出野性德鲁伊策略)
NextAction** DpsFeralDruidStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊策略)
void DpsFeralDruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rebirth",
        NextAction::array(0, new NextAction("rebirth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("regrowth", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("healing touch", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "faerie fire (feral)",
        NextAction::array(0, new NextAction("faerie fire (feral)", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "ferocious bite",
        NextAction::array(0, new NextAction("ferocious bite", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("shred", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("mangle (cat)", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊策略)
void DpsFeralDruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (输出野性德鲁伊策略)
void DpsFeralDruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (输出野性德鲁伊策略)
void DpsFeralDruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊PVE策略)
void DpsFeralDruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rip",
        NextAction::array(0, new NextAction("rip", ACTION_NORMAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "rake",
        NextAction::array(0, new NextAction("rake", ACTION_NORMAL + 2), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊PVE策略)
void DpsFeralDruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (输出野性德鲁伊PVE策略)
void DpsFeralDruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (输出野性德鲁伊PVE策略)
void DpsFeralDruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊PVP策略)
void DpsFeralDruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "rip",
        NextAction::array(0, new NextAction("rip", ACTION_NORMAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "rake",
        NextAction::array(0, new NextAction("rake", ACTION_NORMAL + 2), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊PVP策略)
void DpsFeralDruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));
}

// 初始化反应阶段触发器列表 (输出野性德鲁伊PVP策略)
void DpsFeralDruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (输出野性德鲁伊PVP策略)
void DpsFeralDruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊团队副本策略)
void DpsFeralDruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("cower", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊团队副本策略)
void DpsFeralDruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (输出野性德鲁伊团队副本策略)
void DpsFeralDruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (输出野性德鲁伊团队副本策略)
void DpsFeralDruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊AOE群体策略)
void DpsFeralDruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("swipe (cat)", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊AOE群体策略)
void DpsFeralDruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊AOE群体PVE策略)
void DpsFeralDruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊AOE群体PVE策略)
void DpsFeralDruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊AOE群体PVP策略)
void DpsFeralDruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊AOE群体PVP策略)
void DpsFeralDruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊AOE群体团队副本策略)
void DpsFeralDruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊AOE群体团队副本策略)
void DpsFeralDruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊增益Buff策略)
void DpsFeralDruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cat form",
        NextAction::array(0, new NextAction("cat form", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "tiger's fury",
        NextAction::array(0, new NextAction("tiger's fury", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊增益Buff策略)
void DpsFeralDruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "omen of clarity",
        NextAction::array(0, new NextAction("omen of clarity", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊增益BuffPVE策略)
void DpsFeralDruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊增益BuffPVE策略)
void DpsFeralDruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊增益BuffPVP策略)
void DpsFeralDruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊增益BuffPVP策略)
void DpsFeralDruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊增益Buff团队副本策略)
void DpsFeralDruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊增益Buff团队副本策略)
void DpsFeralDruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊爆发增益策略)
void DpsFeralDruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊爆发增益策略)
void DpsFeralDruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊爆发增益PVE策略)
void DpsFeralDruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊爆发增益PVE策略)
void DpsFeralDruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊爆发增益PVP策略)
void DpsFeralDruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊爆发增益PVP策略)
void DpsFeralDruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊爆发增益团队副本策略)
void DpsFeralDruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊爆发增益团队副本策略)
void DpsFeralDruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊控制(CC)策略)
void DpsFeralDruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊控制(CC)策略)
void DpsFeralDruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊控制(CC)PVE策略)
void DpsFeralDruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊控制(CC)PVE策略)
void DpsFeralDruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊控制(CC)PVP策略)
void DpsFeralDruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊控制(CC)PVP策略)
void DpsFeralDruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊控制(CC)团队副本策略)
void DpsFeralDruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊控制(CC)团队副本策略)
void DpsFeralDruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊驱散净化策略)
void DpsFeralDruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊驱散净化策略)
void DpsFeralDruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊驱散净化PVE策略)
void DpsFeralDruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊驱散净化PVE策略)
void DpsFeralDruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊驱散净化PVP策略)
void DpsFeralDruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊驱散净化PVP策略)
void DpsFeralDruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊驱散净化团队副本策略)
void DpsFeralDruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊驱散净化团队副本策略)
void DpsFeralDruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊潜行策略)
void DpsFeralDruidStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "stealth",
        NextAction::array(0, new NextAction("stealth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "no stealth",
        NextAction::array(0, new NextAction("check stealth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("pounce", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("ravage", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "kick",
        NextAction::array(0, new NextAction("pounce", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "unstealth",
        NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊潜行策略)
void DpsFeralDruidStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no stealth",
        NextAction::array(0, new NextAction("check stealth", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "unstealth",
        NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊潜行PVE策略)
void DpsFeralDruidStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitCombatTriggers(triggers);
    StealthPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊潜行PVE策略)
void DpsFeralDruidStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitNonCombatTriggers(triggers);
    StealthPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊潜行PVP策略)
void DpsFeralDruidStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitCombatTriggers(triggers);
    StealthPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊潜行PVP策略)
void DpsFeralDruidStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitNonCombatTriggers(triggers);
    StealthPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), 
                             new NextAction("unstealth", ACTION_HIGH), NULL)));
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊潜行团队副本策略)
void DpsFeralDruidStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitCombatTriggers(triggers);
    StealthRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊潜行团队副本策略)
void DpsFeralDruidStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitNonCombatTriggers(triggers);
    StealthRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif

// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (输出野性德鲁伊策略)
NextAction** DpsFeralDruidStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊策略)
void DpsFeralDruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rebirth",
        NextAction::array(0, new NextAction("rebirth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("regrowth", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("healing touch", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "faerie fire (feral)",
        NextAction::array(0, new NextAction("faerie fire (feral)", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "rip",
        NextAction::array(0, new NextAction("rip", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "ferocious bite",
        NextAction::array(0, new NextAction("ferocious bite", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "rake",
        NextAction::array(0, new NextAction("rake", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("shred", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("mangle (cat)", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊策略)
void DpsFeralDruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (输出野性德鲁伊策略)
void DpsFeralDruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (输出野性德鲁伊策略)
void DpsFeralDruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊PVE策略)
void DpsFeralDruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊PVE策略)
void DpsFeralDruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (输出野性德鲁伊PVE策略)
void DpsFeralDruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (输出野性德鲁伊PVE策略)
void DpsFeralDruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊PVP策略)
void DpsFeralDruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊PVP策略)
void DpsFeralDruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));
}

// 初始化反应阶段触发器列表 (输出野性德鲁伊PVP策略)
void DpsFeralDruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (输出野性德鲁伊PVP策略)
void DpsFeralDruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊团队副本策略)
void DpsFeralDruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("cower", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊团队副本策略)
void DpsFeralDruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (输出野性德鲁伊团队副本策略)
void DpsFeralDruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (输出野性德鲁伊团队副本策略)
void DpsFeralDruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊AOE群体策略)
void DpsFeralDruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("swipe (cat)", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊AOE群体策略)
void DpsFeralDruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊AOE群体PVE策略)
void DpsFeralDruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊AOE群体PVE策略)
void DpsFeralDruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊AOE群体PVP策略)
void DpsFeralDruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊AOE群体PVP策略)
void DpsFeralDruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊AOE群体团队副本策略)
void DpsFeralDruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊AOE群体团队副本策略)
void DpsFeralDruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊增益Buff策略)
void DpsFeralDruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cat form",
        NextAction::array(0, new NextAction("cat form", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "tiger's fury",
        NextAction::array(0, new NextAction("tiger's fury", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊增益Buff策略)
void DpsFeralDruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "omen of clarity",
        NextAction::array(0, new NextAction("omen of clarity", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊增益BuffPVE策略)
void DpsFeralDruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊增益BuffPVE策略)
void DpsFeralDruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊增益BuffPVP策略)
void DpsFeralDruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊增益BuffPVP策略)
void DpsFeralDruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊增益Buff团队副本策略)
void DpsFeralDruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊增益Buff团队副本策略)
void DpsFeralDruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊爆发增益策略)
void DpsFeralDruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊爆发增益策略)
void DpsFeralDruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊爆发增益PVE策略)
void DpsFeralDruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊爆发增益PVE策略)
void DpsFeralDruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊爆发增益PVP策略)
void DpsFeralDruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊爆发增益PVP策略)
void DpsFeralDruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊爆发增益团队副本策略)
void DpsFeralDruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊爆发增益团队副本策略)
void DpsFeralDruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊控制(CC)策略)
void DpsFeralDruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊控制(CC)策略)
void DpsFeralDruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊控制(CC)PVE策略)
void DpsFeralDruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊控制(CC)PVE策略)
void DpsFeralDruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊控制(CC)PVP策略)
void DpsFeralDruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊控制(CC)PVP策略)
void DpsFeralDruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊控制(CC)团队副本策略)
void DpsFeralDruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊控制(CC)团队副本策略)
void DpsFeralDruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊驱散净化策略)
void DpsFeralDruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊驱散净化策略)
void DpsFeralDruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊驱散净化PVE策略)
void DpsFeralDruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊驱散净化PVE策略)
void DpsFeralDruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊驱散净化PVP策略)
void DpsFeralDruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊驱散净化PVP策略)
void DpsFeralDruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊驱散净化团队副本策略)
void DpsFeralDruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊驱散净化团队副本策略)
void DpsFeralDruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊潜行策略)
void DpsFeralDruidStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "stealth",
        NextAction::array(0, new NextAction("stealth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "no stealth",
        NextAction::array(0, new NextAction("check stealth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("pounce", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("ravage", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "kick",
        NextAction::array(0, new NextAction("pounce", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "unstealth",
        NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊潜行策略)
void DpsFeralDruidStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no stealth",
        NextAction::array(0, new NextAction("check stealth", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "unstealth",
        NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊潜行PVE策略)
void DpsFeralDruidStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitCombatTriggers(triggers);
    StealthPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊潜行PVE策略)
void DpsFeralDruidStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitNonCombatTriggers(triggers);
    StealthPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊潜行PVP策略)
void DpsFeralDruidStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitCombatTriggers(triggers);
    StealthPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊潜行PVP策略)
void DpsFeralDruidStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitNonCombatTriggers(triggers);
    StealthPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), 
                             new NextAction("unstealth", ACTION_HIGH), NULL)));
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊潜行团队副本策略)
void DpsFeralDruidStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitCombatTriggers(triggers);
    StealthRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊潜行团队副本策略)
void DpsFeralDruidStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitNonCombatTriggers(triggers);
    StealthRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif

// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (输出野性德鲁伊策略)
NextAction** DpsFeralDruidStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊策略)
void DpsFeralDruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rebirth",
        NextAction::array(0, new NextAction("rebirth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("regrowth", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("healing touch", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("feral charge - cat", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "faerie fire (feral)",
        NextAction::array(0, new NextAction("faerie fire (feral)", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "rip",
        NextAction::array(0, new NextAction("rip", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "ferocious bite",
        NextAction::array(0, new NextAction("ferocious bite", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "rake",
        NextAction::array(0, new NextAction("rake", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("shred", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("mangle (cat)", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊策略)
void DpsFeralDruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (输出野性德鲁伊策略)
void DpsFeralDruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (输出野性德鲁伊策略)
void DpsFeralDruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊PVE策略)
void DpsFeralDruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊PVE策略)
void DpsFeralDruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (输出野性德鲁伊PVE策略)
void DpsFeralDruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (输出野性德鲁伊PVE策略)
void DpsFeralDruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊PVP策略)
void DpsFeralDruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊PVP策略)
void DpsFeralDruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), NULL)));
}

// 初始化反应阶段触发器列表 (输出野性德鲁伊PVP策略)
void DpsFeralDruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (输出野性德鲁伊PVP策略)
void DpsFeralDruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊团队副本策略)
void DpsFeralDruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("cower", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊团队副本策略)
void DpsFeralDruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (输出野性德鲁伊团队副本策略)
void DpsFeralDruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (输出野性德鲁伊团队副本策略)
void DpsFeralDruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊AOE群体策略)
void DpsFeralDruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("swipe (cat)", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊AOE群体策略)
void DpsFeralDruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊AOE群体PVE策略)
void DpsFeralDruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊AOE群体PVE策略)
void DpsFeralDruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊AOE群体PVP策略)
void DpsFeralDruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊AOE群体PVP策略)
void DpsFeralDruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊AOE群体团队副本策略)
void DpsFeralDruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊AOE群体团队副本策略)
void DpsFeralDruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊增益Buff策略)
void DpsFeralDruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cat form",
        NextAction::array(0, new NextAction("cat form", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "tiger's fury",
        NextAction::array(0, new NextAction("tiger's fury", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊增益Buff策略)
void DpsFeralDruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "omen of clarity",
        NextAction::array(0, new NextAction("omen of clarity", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊增益BuffPVE策略)
void DpsFeralDruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊增益BuffPVE策略)
void DpsFeralDruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊增益BuffPVP策略)
void DpsFeralDruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊增益BuffPVP策略)
void DpsFeralDruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊增益Buff团队副本策略)
void DpsFeralDruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊增益Buff团队副本策略)
void DpsFeralDruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊爆发增益策略)
void DpsFeralDruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊爆发增益策略)
void DpsFeralDruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊爆发增益PVE策略)
void DpsFeralDruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊爆发增益PVE策略)
void DpsFeralDruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊爆发增益PVP策略)
void DpsFeralDruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊爆发增益PVP策略)
void DpsFeralDruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊爆发增益团队副本策略)
void DpsFeralDruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊爆发增益团队副本策略)
void DpsFeralDruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊控制(CC)策略)
void DpsFeralDruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊控制(CC)策略)
void DpsFeralDruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊控制(CC)PVE策略)
void DpsFeralDruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊控制(CC)PVE策略)
void DpsFeralDruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊控制(CC)PVP策略)
void DpsFeralDruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊控制(CC)PVP策略)
void DpsFeralDruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊控制(CC)团队副本策略)
void DpsFeralDruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊控制(CC)团队副本策略)
void DpsFeralDruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊驱散净化策略)
void DpsFeralDruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊驱散净化策略)
void DpsFeralDruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊驱散净化PVE策略)
void DpsFeralDruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊驱散净化PVE策略)
void DpsFeralDruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊驱散净化PVP策略)
void DpsFeralDruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊驱散净化PVP策略)
void DpsFeralDruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊驱散净化团队副本策略)
void DpsFeralDruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊驱散净化团队副本策略)
void DpsFeralDruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊潜行策略)
void DpsFeralDruidStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "stealth",
        NextAction::array(0, new NextAction("stealth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "no stealth",
        NextAction::array(0, new NextAction("check stealth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("pounce", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("ravage", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "kick",
        NextAction::array(0, new NextAction("pounce", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "unstealth",
        NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊潜行策略)
void DpsFeralDruidStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no stealth",
        NextAction::array(0, new NextAction("check stealth", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "unstealth",
        NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊潜行PVE策略)
void DpsFeralDruidStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitCombatTriggers(triggers);
    StealthPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊潜行PVE策略)
void DpsFeralDruidStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitNonCombatTriggers(triggers);
    StealthPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊潜行PVP策略)
void DpsFeralDruidStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitCombatTriggers(triggers);
    StealthPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊潜行PVP策略)
void DpsFeralDruidStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitNonCombatTriggers(triggers);
    StealthPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("dash", ACTION_HIGH), 
                             new NextAction("unstealth", ACTION_HIGH), NULL)));
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊潜行团队副本策略)
void DpsFeralDruidStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitCombatTriggers(triggers);
    StealthRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (输出野性德鲁伊潜行团队副本策略)
void DpsFeralDruidStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DpsFeralDruidStealthStrategy::InitNonCombatTriggers(triggers);
    StealthRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif

// 乘数修饰器 (DpsFeralDruidStealthedStrategyMultiplier)：动态调整特定状态下的动作权重
class DpsFeralDruidStealthedStrategyMultiplier : public Multiplier
{
public:
    DpsFeralDruidStealthedStrategyMultiplier(PlayerbotAI* ai) : Multiplier(ai, "stealthed") {}

    float GetValue(Action* action) override
    {
        // Only allow stealth actions
        const std::string& actionName = action->getName();
        if ((actionName == "unstealth") ||
            (actionName == "check stealth") ||
            (actionName == "feral charge - cat") ||
            (actionName == "claw") ||
            (actionName == "mangle (cat)") ||
            (actionName == "pounce") ||
            (actionName == "ravage") ||
            (actionName == "shred") ||
            (actionName == "food") ||
            (actionName == "drink") ||
            (actionName == "dps assist") ||
            (actionName == "select new target") ||
            (actionName == "follow") ||
            (actionName == "reach melee") ||
            (actionName == "set behind") ||
            (actionName == "set combat state") ||
            (actionName == "set non combat state") ||
            (actionName == "set dead state") ||
            (actionName == "update pvp strats") ||
            (actionName == "update pve strats") ||
            (actionName == "update raid strats"))
        {
            return 1.0f;
        }

        return 0.0f;
    }
};

// 初始化战斗阶段乘数修饰器 (输出野性德鲁伊潜行状态策略)
void DpsFeralDruidStealthedStrategy::InitCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    multipliers.push_back(new DpsFeralDruidStealthedStrategyMultiplier(ai));
}

// 初始化非战斗阶段乘数修饰器 (输出野性德鲁伊潜行状态策略)
void DpsFeralDruidStealthedStrategy::InitNonCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    DpsFeralDruidStealthedStrategy::InitCombatMultipliers(multipliers);
}

// 初始化战斗阶段触发器列表 (输出野性德鲁伊变身解控策略)
void DpsFeralDruidPowershiftStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "powershift",
        NextAction::array(0, new NextAction("powershift", ACTION_MOVE), NULL)));
}
