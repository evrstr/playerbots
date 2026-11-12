// 德鲁伊 - 坦克野性德鲁伊策略实现文件 (TankFeralDruidStrategy.cpp)

#include "playerbot/playerbot.h"
#include "DruidMultipliers.h"
#include "TankFeralDruidStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class TankFeralDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    TankFeralDruidStrategyActionNodeFactory()
    {
        creators["survival instincts"] = &survival_instincts;
        creators["omen of clarity"] = &omen_of_clarity;
        creators["feral charge - bear"] = &feral_charge_bear;
        creators["mangle (bear)"] = &mangle_bear;
    }

private:
    // 动作节点 survival_instincts：生存本能 -> 备选(A)动作：树皮术
    ACTION_NODE_A(survival_instincts, "survival instincts", "barskin");

    // 动作节点 omen_of_clarity：清晰预兆 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(omen_of_clarity, "omen of clarity", "caster form");

    // 动作节点 feral_charge_bear：野性冲锋(熊) -> 备选(A)动作：reach melee
    ACTION_NODE_A(feral_charge_bear, "feral charge - bear", "reach melee");

    // 动作节点 mangle_bear：裂伤(熊) -> 备选(A)动作：重殴
    ACTION_NODE_A(mangle_bear, "mangle (bear)", "maul");
};

// 构造函数：初始化坦克野性德鲁伊策略并挂载动作节点工厂
TankFeralDruidStrategy::TankFeralDruidStrategy(PlayerbotAI* ai) : DruidStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<TankFeralDruidStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (坦克野性德鲁伊策略)
NextAction** TankFeralDruidStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊策略)
void TankFeralDruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("frenzied regeneration", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("feral charge - bear", ACTION_MOVE + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("growl", ACTION_PASSTROUGH), NULL)));

    triggers.push_back(new TriggerNode(
        "faerie fire (feral)",
        NextAction::array(0, new NextAction("faerie fire (feral)", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "demoralizing roar",
        NextAction::array(0, new NextAction("demoralizing roar", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "medium rage available",
        NextAction::array(0, new NextAction("mangle (bear)", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for melee",
        NextAction::array(0, new NextAction("move out of enemy contact", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊策略)
void TankFeralDruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (坦克野性德鲁伊策略)
void TankFeralDruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (坦克野性德鲁伊策略)
void TankFeralDruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊PVE策略)
void TankFeralDruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
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

    TankFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊PVE策略)
void TankFeralDruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (坦克野性德鲁伊PVE策略)
void TankFeralDruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (坦克野性德鲁伊PVE策略)
void TankFeralDruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊PVP策略)
void TankFeralDruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
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

    TankFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊PVP策略)
void TankFeralDruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (坦克野性德鲁伊PVP策略)
void TankFeralDruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (坦克野性德鲁伊PVP策略)
void TankFeralDruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊团队副本策略)
void TankFeralDruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊团队副本策略)
void TankFeralDruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (坦克野性德鲁伊团队副本策略)
void TankFeralDruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (坦克野性德鲁伊团队副本策略)
void TankFeralDruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊AOE群体策略)
void TankFeralDruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("challenging roar", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("demoralizing roar", ACTION_HIGH + 2),
                             new NextAction("swipe (bear)", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("swipe (bear)", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊AOE群体策略)
void TankFeralDruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊AOE群体PVE策略)
void TankFeralDruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊AOE群体PVE策略)
void TankFeralDruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊AOE群体PVP策略)
void TankFeralDruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊AOE群体PVP策略)
void TankFeralDruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊AOE群体团队副本策略)
void TankFeralDruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊AOE群体团队副本策略)
void TankFeralDruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊增益Buff策略)
void TankFeralDruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "bear form",
        NextAction::array(0, new NextAction("dire bear form", ACTION_MOVE + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "enrage",
        NextAction::array(0, new NextAction("enrage", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊增益Buff策略)
void TankFeralDruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "omen of clarity",
        NextAction::array(0, new NextAction("omen of clarity", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊增益BuffPVE策略)
void TankFeralDruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊增益BuffPVE策略)
void TankFeralDruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊增益BuffPVP策略)
void TankFeralDruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊增益BuffPVP策略)
void TankFeralDruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊增益Buff团队副本策略)
void TankFeralDruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("stoneshield potion", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊增益Buff团队副本策略)
void TankFeralDruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊爆发增益策略)
void TankFeralDruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊爆发增益策略)
void TankFeralDruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊爆发增益PVE策略)
void TankFeralDruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊爆发增益PVE策略)
void TankFeralDruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊爆发增益PVP策略)
void TankFeralDruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊爆发增益PVP策略)
void TankFeralDruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊爆发增益团队副本策略)
void TankFeralDruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊爆发增益团队副本策略)
void TankFeralDruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)策略)
void TankFeralDruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "bash",
        NextAction::array(0, new NextAction("bash", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "bash on enemy healer",
        NextAction::array(0, new NextAction("bash on enemy healer", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)策略)
void TankFeralDruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)PVE策略)
void TankFeralDruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)PVE策略)
void TankFeralDruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)PVP策略)
void TankFeralDruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)PVP策略)
void TankFeralDruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)团队副本策略)
void TankFeralDruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)团队副本策略)
void TankFeralDruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊驱散净化策略)
void TankFeralDruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊驱散净化策略)
void TankFeralDruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊驱散净化PVE策略)
void TankFeralDruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊驱散净化PVE策略)
void TankFeralDruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊驱散净化PVP策略)
void TankFeralDruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊驱散净化PVP策略)
void TankFeralDruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊驱散净化团队副本策略)
void TankFeralDruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊驱散净化团队副本策略)
void TankFeralDruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif

// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (坦克野性德鲁伊策略)
NextAction** TankFeralDruidStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊策略)
void TankFeralDruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("survival instincts", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("frenzied regeneration", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("feral charge - bear", ACTION_MOVE + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("growl", ACTION_PASSTROUGH), NULL)));

    triggers.push_back(new TriggerNode(
        "faerie fire (feral)",
        NextAction::array(0, new NextAction("faerie fire (feral)", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "lacerate",
        NextAction::array(0, new NextAction("lacerate", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "medium rage available",
        NextAction::array(0, new NextAction("mangle (bear)", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "demoralizing roar",
        NextAction::array(0, new NextAction("demoralizing roar", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for melee",
        NextAction::array(0, new NextAction("move out of enemy contact", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊策略)
void TankFeralDruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (坦克野性德鲁伊策略)
void TankFeralDruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (坦克野性德鲁伊策略)
void TankFeralDruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊PVE策略)
void TankFeralDruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidPveStrategy::InitCombatTriggers(triggers);

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
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊PVE策略)
void TankFeralDruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (坦克野性德鲁伊PVE策略)
void TankFeralDruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (坦克野性德鲁伊PVE策略)
void TankFeralDruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊PVP策略)
void TankFeralDruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidPvpStrategy::InitCombatTriggers(triggers);

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
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊PVP策略)
void TankFeralDruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (坦克野性德鲁伊PVP策略)
void TankFeralDruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (坦克野性德鲁伊PVP策略)
void TankFeralDruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊团队副本策略)
void TankFeralDruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊团队副本策略)
void TankFeralDruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (坦克野性德鲁伊团队副本策略)
void TankFeralDruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (坦克野性德鲁伊团队副本策略)
void TankFeralDruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊AOE群体策略)
void TankFeralDruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("challenging roar", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("demoralizing roar", ACTION_HIGH + 2),
                             new NextAction("swipe (bear)", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("swipe (bear)", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊AOE群体策略)
void TankFeralDruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊AOE群体PVE策略)
void TankFeralDruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊AOE群体PVE策略)
void TankFeralDruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊AOE群体PVP策略)
void TankFeralDruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊AOE群体PVP策略)
void TankFeralDruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊AOE群体团队副本策略)
void TankFeralDruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊AOE群体团队副本策略)
void TankFeralDruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊增益Buff策略)
void TankFeralDruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "bear form",
        NextAction::array(0, new NextAction("dire bear form", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "enrage",
        NextAction::array(0, new NextAction("enrage", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊增益Buff策略)
void TankFeralDruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "omen of clarity",
        NextAction::array(0, new NextAction("omen of clarity", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊增益BuffPVE策略)
void TankFeralDruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊增益BuffPVE策略)
void TankFeralDruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊增益BuffPVP策略)
void TankFeralDruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊增益BuffPVP策略)
void TankFeralDruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊增益Buff团队副本策略)
void TankFeralDruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊增益Buff团队副本策略)
void TankFeralDruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊爆发增益策略)
void TankFeralDruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊爆发增益策略)
void TankFeralDruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊爆发增益PVE策略)
void TankFeralDruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊爆发增益PVE策略)
void TankFeralDruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊爆发增益PVP策略)
void TankFeralDruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊爆发增益PVP策略)
void TankFeralDruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊爆发增益团队副本策略)
void TankFeralDruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊爆发增益团队副本策略)
void TankFeralDruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)策略)
void TankFeralDruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "bash",
        NextAction::array(0, new NextAction("bash", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "bash on enemy healer",
        NextAction::array(0, new NextAction("bash on enemy healer", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)策略)
void TankFeralDruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)PVE策略)
void TankFeralDruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)PVE策略)
void TankFeralDruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)PVP策略)
void TankFeralDruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)PVP策略)
void TankFeralDruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)团队副本策略)
void TankFeralDruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)团队副本策略)
void TankFeralDruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊驱散净化策略)
void TankFeralDruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊驱散净化策略)
void TankFeralDruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊驱散净化PVE策略)
void TankFeralDruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊驱散净化PVE策略)
void TankFeralDruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊驱散净化PVP策略)
void TankFeralDruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊驱散净化PVP策略)
void TankFeralDruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊驱散净化团队副本策略)
void TankFeralDruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊驱散净化团队副本策略)
void TankFeralDruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif

// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (坦克野性德鲁伊策略)
NextAction** TankFeralDruidStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊策略)
void TankFeralDruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("survival instincts", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("frenzied regeneration", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("feral charge - bear", ACTION_MOVE + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("growl", ACTION_PASSTROUGH), NULL)));

    triggers.push_back(new TriggerNode(
        "faerie fire (feral)",
        NextAction::array(0, new NextAction("faerie fire (feral)", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "lacerate",
        NextAction::array(0, new NextAction("lacerate", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "demoralizing roar",
        NextAction::array(0, new NextAction("demoralizing roar", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "medium rage available",
        NextAction::array(0, new NextAction("mangle (bear)", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for melee",
        NextAction::array(0, new NextAction("move out of enemy contact", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊策略)
void TankFeralDruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (坦克野性德鲁伊策略)
void TankFeralDruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (坦克野性德鲁伊策略)
void TankFeralDruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊PVE策略)
void TankFeralDruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidPveStrategy::InitCombatTriggers(triggers);

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
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊PVE策略)
void TankFeralDruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (坦克野性德鲁伊PVE策略)
void TankFeralDruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (坦克野性德鲁伊PVE策略)
void TankFeralDruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊PVP策略)
void TankFeralDruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidPvpStrategy::InitCombatTriggers(triggers);

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
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊PVP策略)
void TankFeralDruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (坦克野性德鲁伊PVP策略)
void TankFeralDruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (坦克野性德鲁伊PVP策略)
void TankFeralDruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊团队副本策略)
void TankFeralDruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitCombatTriggers(triggers);
    DruidRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊团队副本策略)
void TankFeralDruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitNonCombatTriggers(triggers);
    DruidRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (坦克野性德鲁伊团队副本策略)
void TankFeralDruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitReactionTriggers(triggers);
    DruidRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (坦克野性德鲁伊团队副本策略)
void TankFeralDruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidStrategy::InitDeadTriggers(triggers);
    DruidRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊AOE群体策略)
void TankFeralDruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("challenging roar", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("demoralizing roar", ACTION_HIGH + 2),
                             new NextAction("swipe (bear)", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("swipe (bear)", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊AOE群体策略)
void TankFeralDruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊AOE群体PVE策略)
void TankFeralDruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊AOE群体PVE策略)
void TankFeralDruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊AOE群体PVP策略)
void TankFeralDruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊AOE群体PVP策略)
void TankFeralDruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊AOE群体团队副本策略)
void TankFeralDruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊AOE群体团队副本策略)
void TankFeralDruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊增益Buff策略)
void TankFeralDruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "bear form",
        NextAction::array(0, new NextAction("dire bear form", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "enrage",
        NextAction::array(0, new NextAction("enrage", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊增益Buff策略)
void TankFeralDruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "omen of clarity",
        NextAction::array(0, new NextAction("omen of clarity", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊增益BuffPVE策略)
void TankFeralDruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊增益BuffPVE策略)
void TankFeralDruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊增益BuffPVP策略)
void TankFeralDruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊增益BuffPVP策略)
void TankFeralDruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊增益Buff团队副本策略)
void TankFeralDruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊增益Buff团队副本策略)
void TankFeralDruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊爆发增益策略)
void TankFeralDruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊爆发增益策略)
void TankFeralDruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊爆发增益PVE策略)
void TankFeralDruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊爆发增益PVE策略)
void TankFeralDruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊爆发增益PVP策略)
void TankFeralDruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊爆发增益PVP策略)
void TankFeralDruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊爆发增益团队副本策略)
void TankFeralDruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊爆发增益团队副本策略)
void TankFeralDruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)策略)
void TankFeralDruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "bash",
        NextAction::array(0, new NextAction("bash", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "bash on enemy healer",
        NextAction::array(0, new NextAction("bash on enemy healer", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)策略)
void TankFeralDruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)PVE策略)
void TankFeralDruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)PVE策略)
void TankFeralDruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)PVP策略)
void TankFeralDruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)PVP策略)
void TankFeralDruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)团队副本策略)
void TankFeralDruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊控制(CC)团队副本策略)
void TankFeralDruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊驱散净化策略)
void TankFeralDruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊驱散净化策略)
void TankFeralDruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊驱散净化PVE策略)
void TankFeralDruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊驱散净化PVE策略)
void TankFeralDruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊驱散净化PVP策略)
void TankFeralDruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊驱散净化PVP策略)
void TankFeralDruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (坦克野性德鲁伊驱散净化团队副本策略)
void TankFeralDruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (坦克野性德鲁伊驱散净化团队副本策略)
void TankFeralDruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    TankFeralDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
