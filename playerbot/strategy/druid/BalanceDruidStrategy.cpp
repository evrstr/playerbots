// 德鲁伊 - 平衡德鲁伊策略实现文件 (BalanceDruidStrategy.cpp)

#include "playerbot/playerbot.h"
#include "DruidMultipliers.h"
#include "BalanceDruidStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class BalanceDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    BalanceDruidStrategyActionNodeFactory()
    {
        creators["starfall"] = &starfall;
        creators["starfire"] = &starfire;
        creators["innervate"] = &innervate;
    }

private:

    // 构建 激活 (innervate) 动作节点
    static ActionNode* innervate(PlayerbotAI* ai)
    {
        return new ActionNode("innervate",
            /*P*/ NextAction::array(0, new NextAction("balance caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("mana potion"), NULL),
            /*C*/ NULL);
    }

    // 动作节点 starfall：星辰坠落 -> 备选(A)动作：飓风
    ACTION_NODE_A(starfall, "starfall", "hurricane");

    // 动作节点 starfire：星火术 -> 备选(A)动作：愤怒
    ACTION_NODE_A(starfire, "starfire", "wrath");
};

// 构造函数：初始化平衡德鲁伊策略并挂载动作节点工厂
BalanceDruidStrategy::BalanceDruidStrategy(PlayerbotAI* ai) : DruidStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<BalanceDruidStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (平衡德鲁伊策略)
NextAction** BalanceDruidStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("starfire", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊策略)
void BalanceDruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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
        "faerie fire",
        NextAction::array(0, new NextAction("faerie fire", ACTION_NORMAL + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊策略)
void BalanceDruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (平衡德鲁伊策略)
void BalanceDruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (平衡德鲁伊策略)
void BalanceDruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊PVE策略)
void BalanceDruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitCombatTriggers(triggers);
    DruidPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "insect swarm",
        NextAction::array(0, new NextAction("insect swarm", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "moonfire",
        NextAction::array(0, new NextAction("moonfire", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("starfire", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊PVE策略)
void BalanceDruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (平衡德鲁伊PVE策略)
void BalanceDruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitReactionTriggers(triggers);
    DruidPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (平衡德鲁伊PVE策略)
void BalanceDruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitDeadTriggers(triggers);
    DruidPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊PVP策略)
void BalanceDruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitCombatTriggers(triggers);
    DruidPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "insect swarm",
        NextAction::array(0, new NextAction("insect swarm", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "moonfire",
        NextAction::array(0, new NextAction("moonfire", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("starfire", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊PVP策略)
void BalanceDruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (平衡德鲁伊PVP策略)
void BalanceDruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitReactionTriggers(triggers);
    DruidPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (平衡德鲁伊PVP策略)
void BalanceDruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitDeadTriggers(triggers);
    DruidPvpStrategy::InitDeadTriggers(triggers);
}

// 获取默认战斗动作序列 (平衡德鲁伊团队副本策略)
ai::NextAction** BalanceDruidRaidStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("starfire", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊团队副本策略)
void BalanceDruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitCombatTriggers(triggers);
    DruidRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊团队副本策略)
void BalanceDruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitNonCombatTriggers(triggers);
    DruidRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (平衡德鲁伊团队副本策略)
void BalanceDruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitReactionTriggers(triggers);
    DruidRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (平衡德鲁伊团队副本策略)
void BalanceDruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitDeadTriggers(triggers);
    DruidRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊AOE群体策略)
void BalanceDruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("starfall", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊AOE群体策略)
void BalanceDruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊AOE群体PVE策略)
void BalanceDruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊AOE群体PVE策略)
void BalanceDruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊AOE群体PVP策略)
void BalanceDruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊AOE群体PVP策略)
void BalanceDruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊AOE群体团队副本策略)
void BalanceDruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊AOE群体团队副本策略)
void BalanceDruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊增益Buff策略)
void BalanceDruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "moonkin form",
        NextAction::array(0, new NextAction("moonkin form", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "innervate",
        NextAction::array(0, new NextAction("innervate", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊增益Buff策略)
void BalanceDruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊增益BuffPVE策略)
void BalanceDruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊增益BuffPVE策略)
void BalanceDruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊增益BuffPVP策略)
void BalanceDruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊增益BuffPVP策略)
void BalanceDruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊增益Buff团队副本策略)
void BalanceDruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊增益Buff团队副本策略)
void BalanceDruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊爆发增益策略)
void BalanceDruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "nature's swiftness",
        NextAction::array(0, new NextAction("nature's swiftness", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊爆发增益策略)
void BalanceDruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊爆发增益PVE策略)
void BalanceDruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊爆发增益PVE策略)
void BalanceDruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊爆发增益PVP策略)
void BalanceDruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊爆发增益PVP策略)
void BalanceDruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊爆发增益团队副本策略)
void BalanceDruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊爆发增益团队副本策略)
void BalanceDruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊控制(CC)策略)
void BalanceDruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "entangling roots",
        NextAction::array(0, new NextAction("entangling roots on cc", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "entangling roots kite",
        NextAction::array(0, new NextAction("entangling roots", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy five yards",
        NextAction::array(0, new NextAction("nature's grasp", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊控制(CC)策略)
void BalanceDruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊控制(CC)PVE策略)
void BalanceDruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊控制(CC)PVE策略)
void BalanceDruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊控制(CC)PVP策略)
void BalanceDruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊控制(CC)PVP策略)
void BalanceDruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊控制(CC)团队副本策略)
void BalanceDruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊控制(CC)团队副本策略)
void BalanceDruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊驱散净化策略)
void BalanceDruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊驱散净化策略)
void BalanceDruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊驱散净化PVE策略)
void BalanceDruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊驱散净化PVE策略)
void BalanceDruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊驱散净化PVP策略)
void BalanceDruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊驱散净化PVP策略)
void BalanceDruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊驱散净化团队副本策略)
void BalanceDruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊驱散净化团队副本策略)
void BalanceDruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif

// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (平衡德鲁伊策略)
NextAction** BalanceDruidStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("starfire", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊策略)
void BalanceDruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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
        "faerie fire",
        NextAction::array(0, new NextAction("faerie fire", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "insect swarm",
        NextAction::array(0, new NextAction("insect swarm", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "moonfire",
        NextAction::array(0, new NextAction("moonfire", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("starfire", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊策略)
void BalanceDruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (平衡德鲁伊策略)
void BalanceDruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (平衡德鲁伊策略)
void BalanceDruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊PVE策略)
void BalanceDruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitCombatTriggers(triggers);
    DruidPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊PVE策略)
void BalanceDruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (平衡德鲁伊PVE策略)
void BalanceDruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitReactionTriggers(triggers);
    DruidPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (平衡德鲁伊PVE策略)
void BalanceDruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitDeadTriggers(triggers);
    DruidPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊PVP策略)
void BalanceDruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitCombatTriggers(triggers);
    DruidPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊PVP策略)
void BalanceDruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (平衡德鲁伊PVP策略)
void BalanceDruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitReactionTriggers(triggers);
    DruidPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (平衡德鲁伊PVP策略)
void BalanceDruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitDeadTriggers(triggers);
    DruidPvpStrategy::InitDeadTriggers(triggers);
}

// 获取默认战斗动作序列 (平衡德鲁伊团队副本策略)
ai::NextAction** BalanceDruidRaidStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("starfire", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊团队副本策略)
void BalanceDruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitCombatTriggers(triggers);
    DruidRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊团队副本策略)
void BalanceDruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitNonCombatTriggers(triggers);
    DruidRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (平衡德鲁伊团队副本策略)
void BalanceDruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitReactionTriggers(triggers);
    DruidRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (平衡德鲁伊团队副本策略)
void BalanceDruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitDeadTriggers(triggers);
    DruidRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊AOE群体策略)
void BalanceDruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("starfall", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊AOE群体策略)
void BalanceDruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊AOE群体PVE策略)
void BalanceDruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊AOE群体PVE策略)
void BalanceDruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊AOE群体PVP策略)
void BalanceDruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊AOE群体PVP策略)
void BalanceDruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊AOE群体团队副本策略)
void BalanceDruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊AOE群体团队副本策略)
void BalanceDruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊增益Buff策略)
void BalanceDruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "moonkin form",
        NextAction::array(0, new NextAction("moonkin form", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "innervate",
        NextAction::array(0, new NextAction("innervate", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊增益Buff策略)
void BalanceDruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊增益BuffPVE策略)
void BalanceDruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊增益BuffPVE策略)
void BalanceDruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊增益BuffPVP策略)
void BalanceDruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊增益BuffPVP策略)
void BalanceDruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊增益Buff团队副本策略)
void BalanceDruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊增益Buff团队副本策略)
void BalanceDruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊爆发增益策略)
void BalanceDruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "nature's swiftness",
        NextAction::array(0, new NextAction("nature's swiftness", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊爆发增益策略)
void BalanceDruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊爆发增益PVE策略)
void BalanceDruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊爆发增益PVE策略)
void BalanceDruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊爆发增益PVP策略)
void BalanceDruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊爆发增益PVP策略)
void BalanceDruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊爆发增益团队副本策略)
void BalanceDruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊爆发增益团队副本策略)
void BalanceDruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊控制(CC)策略)
void BalanceDruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "entangling roots",
        NextAction::array(0, new NextAction("entangling roots on cc", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "entangling roots kite",
        NextAction::array(0, new NextAction("entangling roots", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy five yards",
        NextAction::array(0, new NextAction("nature's grasp", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊控制(CC)策略)
void BalanceDruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊控制(CC)PVE策略)
void BalanceDruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊控制(CC)PVE策略)
void BalanceDruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊控制(CC)PVP策略)
void BalanceDruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊控制(CC)PVP策略)
void BalanceDruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊控制(CC)团队副本策略)
void BalanceDruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊控制(CC)团队副本策略)
void BalanceDruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊驱散净化策略)
void BalanceDruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊驱散净化策略)
void BalanceDruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊驱散净化PVE策略)
void BalanceDruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊驱散净化PVE策略)
void BalanceDruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊驱散净化PVP策略)
void BalanceDruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊驱散净化PVP策略)
void BalanceDruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊驱散净化团队副本策略)
void BalanceDruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊驱散净化团队副本策略)
void BalanceDruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif

// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (平衡德鲁伊策略)
NextAction** BalanceDruidStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("wrath", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊策略)
void BalanceDruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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
        "eclipse (solar)",
        NextAction::array(0, new NextAction("wrath", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "eclipse (lunar)",
        NextAction::array(0, new NextAction("starfire", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "faerie fire",
        NextAction::array(0, new NextAction("faerie fire", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "insect swarm",
        NextAction::array(0, new NextAction("insect swarm", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "moonfire",
        NextAction::array(0, new NextAction("moonfire", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("starfire", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊策略)
void BalanceDruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (平衡德鲁伊策略)
void BalanceDruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (平衡德鲁伊策略)
void BalanceDruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊PVE策略)
void BalanceDruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitCombatTriggers(triggers);
    DruidPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊PVE策略)
void BalanceDruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (平衡德鲁伊PVE策略)
void BalanceDruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitReactionTriggers(triggers);
    DruidPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (平衡德鲁伊PVE策略)
void BalanceDruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitDeadTriggers(triggers);
    DruidPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊PVP策略)
void BalanceDruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitCombatTriggers(triggers);
    DruidPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊PVP策略)
void BalanceDruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (平衡德鲁伊PVP策略)
void BalanceDruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitReactionTriggers(triggers);
    DruidPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (平衡德鲁伊PVP策略)
void BalanceDruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitDeadTriggers(triggers);
    DruidPvpStrategy::InitDeadTriggers(triggers);
}

// 获取默认战斗动作序列 (平衡德鲁伊团队副本策略)
ai::NextAction** BalanceDruidRaidStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("starfire", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊团队副本策略)
void BalanceDruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitCombatTriggers(triggers);
    DruidRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊团队副本策略)
void BalanceDruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitNonCombatTriggers(triggers);
    DruidRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (平衡德鲁伊团队副本策略)
void BalanceDruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitReactionTriggers(triggers);
    DruidRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (平衡德鲁伊团队副本策略)
void BalanceDruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidStrategy::InitDeadTriggers(triggers);
    DruidRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊AOE群体策略)
void BalanceDruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("starfall", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊AOE群体策略)
void BalanceDruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊AOE群体PVE策略)
void BalanceDruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊AOE群体PVE策略)
void BalanceDruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊AOE群体PVP策略)
void BalanceDruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊AOE群体PVP策略)
void BalanceDruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊AOE群体团队副本策略)
void BalanceDruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊AOE群体团队副本策略)
void BalanceDruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊增益Buff策略)
void BalanceDruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "moonkin form",
        NextAction::array(0, new NextAction("moonkin form", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "innervate",
        NextAction::array(0, new NextAction("innervate", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊增益Buff策略)
void BalanceDruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊增益BuffPVE策略)
void BalanceDruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊增益BuffPVE策略)
void BalanceDruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊增益BuffPVP策略)
void BalanceDruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊增益BuffPVP策略)
void BalanceDruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊增益Buff团队副本策略)
void BalanceDruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊增益Buff团队副本策略)
void BalanceDruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊爆发增益策略)
void BalanceDruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "nature's swiftness",
        NextAction::array(0, new NextAction("nature's swiftness", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊爆发增益策略)
void BalanceDruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊爆发增益PVE策略)
void BalanceDruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊爆发增益PVE策略)
void BalanceDruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊爆发增益PVP策略)
void BalanceDruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊爆发增益PVP策略)
void BalanceDruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊爆发增益团队副本策略)
void BalanceDruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊爆发增益团队副本策略)
void BalanceDruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊控制(CC)策略)
void BalanceDruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "entangling roots",
        NextAction::array(0, new NextAction("entangling roots on cc", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "entangling roots kite",
        NextAction::array(0, new NextAction("entangling roots", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy five yards",
        NextAction::array(0, new NextAction("nature's grasp", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊控制(CC)策略)
void BalanceDruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊控制(CC)PVE策略)
void BalanceDruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊控制(CC)PVE策略)
void BalanceDruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊控制(CC)PVP策略)
void BalanceDruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊控制(CC)PVP策略)
void BalanceDruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊控制(CC)团队副本策略)
void BalanceDruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊控制(CC)团队副本策略)
void BalanceDruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊驱散净化策略)
void BalanceDruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊驱散净化策略)
void BalanceDruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊驱散净化PVE策略)
void BalanceDruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊驱散净化PVE策略)
void BalanceDruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊驱散净化PVP策略)
void BalanceDruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊驱散净化PVP策略)
void BalanceDruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (平衡德鲁伊驱散净化团队副本策略)
void BalanceDruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (平衡德鲁伊驱散净化团队副本策略)
void BalanceDruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BalanceDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
