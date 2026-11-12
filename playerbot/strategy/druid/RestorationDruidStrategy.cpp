// 德鲁伊 - 恢复德鲁伊策略实现文件 (RestorationDruidStrategy.cpp)

#include "playerbot/playerbot.h"
#include "DruidMultipliers.h"
#include "RestorationDruidStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class RestorationDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    RestorationDruidStrategyActionNodeFactory()
    {
        creators["innervate"] = &innervate;
        creators["tranquility"] = &tranquility;
        creators["swiftmend"] = &swiftmend;
        creators["swiftmend on party"] = &swiftmend_on_party;
    }

private:
    // 构建 激活 (innervate) 动作节点
    static ActionNode* innervate(PlayerbotAI* ai)
    {
        return new ActionNode("innervate",
            /*P*/ NextAction::array(0, new NextAction("restoration caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("mana potion"), NULL),
            /*C*/ NULL);
    }

    // 构建 迅捷治愈 (swiftmend) 动作节点
    static ActionNode* swiftmend(PlayerbotAI* ai)
    {
        return new ActionNode("swiftmend",
            /*P*/ NextAction::array(0, new NextAction("restoration caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("healing touch"), NULL),
            /*C*/ NULL);
    }

    // 构建 迅捷治愈 (对队友) (swiftmend_on_party) 动作节点
    static ActionNode* swiftmend_on_party(PlayerbotAI* ai)
    {
        return new ActionNode("swiftmend on party",
            /*P*/ NextAction::array(0, new NextAction("restoration caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("healing touch on party"), NULL),
            /*C*/ NULL);
    }
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
    // 动作节点 tranquility：宁静 -> 前置(P)动作：恢复施法者形态
    ACTION_NODE_P(tranquility, "tranquility", "restoration caster form");
#else
    // 动作节点 tranquility：宁静 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(tranquility, "tranquility", "caster form");
#endif
};

// 构造函数：初始化恢复德鲁伊策略并挂载动作节点工厂
RestorationDruidStrategy::RestorationDruidStrategy(PlayerbotAI* ai) : DruidStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<RestorationDruidStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (恢复德鲁伊策略)
void RestorationDruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rebirth",
        NextAction::array(0, new NextAction("rebirth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("regrowth", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("swiftmend", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("swiftmend on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("tranquility", ACTION_MEDIUM_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("rejuvenation", ACTION_LIGHT_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊策略)
void RestorationDruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("regrowth", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("swiftmend", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("swiftmend on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("tranquility", ACTION_MEDIUM_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("rejuvenation", ACTION_LIGHT_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (恢复德鲁伊策略)
void RestorationDruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复德鲁伊策略)
void RestorationDruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊PVE策略)
void RestorationDruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitCombatTriggers(triggers);
    DruidPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊PVE策略)
void RestorationDruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复德鲁伊PVE策略)
void RestorationDruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitReactionTriggers(triggers);
    DruidPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复德鲁伊PVE策略)
void RestorationDruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitDeadTriggers(triggers);
    DruidPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊PVP策略)
void RestorationDruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitCombatTriggers(triggers);
    DruidPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊PVP策略)
void RestorationDruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复德鲁伊PVP策略)
void RestorationDruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitReactionTriggers(triggers);
    DruidPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复德鲁伊PVP策略)
void RestorationDruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitDeadTriggers(triggers);
    DruidPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊团队副本策略)
void RestorationDruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitCombatTriggers(triggers);
    DruidRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊团队副本策略)
void RestorationDruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitNonCombatTriggers(triggers);
    DruidRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复德鲁伊团队副本策略)
void RestorationDruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitReactionTriggers(triggers);
    DruidRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复德鲁伊团队副本策略)
void RestorationDruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitDeadTriggers(triggers);
    DruidRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊AOE群体策略)
void RestorationDruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊AOE群体策略)
void RestorationDruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊AOE群体PVE策略)
void RestorationDruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊AOE群体PVE策略)
void RestorationDruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊AOE群体PVP策略)
void RestorationDruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊AOE群体PVP策略)
void RestorationDruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊AOE群体团队副本策略)
void RestorationDruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊AOE群体团队副本策略)
void RestorationDruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊增益Buff策略)
void RestorationDruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "innervate",
        NextAction::array(0, new NextAction("innervate", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊增益Buff策略)
void RestorationDruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊增益BuffPVE策略)
void RestorationDruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊增益BuffPVE策略)
void RestorationDruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊增益BuffPVP策略)
void RestorationDruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊增益BuffPVP策略)
void RestorationDruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊增益Buff团队副本策略)
void RestorationDruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊增益Buff团队副本策略)
void RestorationDruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊爆发增益策略)
void RestorationDruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "nature's swiftness",
        NextAction::array(0, new NextAction("nature's swiftness", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊爆发增益策略)
void RestorationDruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊爆发增益PVE策略)
void RestorationDruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊爆发增益PVE策略)
void RestorationDruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊爆发增益PVP策略)
void RestorationDruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊爆发增益PVP策略)
void RestorationDruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊爆发增益团队副本策略)
void RestorationDruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊爆发增益团队副本策略)
void RestorationDruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊控制(CC)策略)
void RestorationDruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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

// 初始化非战斗阶段触发器列表 (恢复德鲁伊控制(CC)策略)
void RestorationDruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊控制(CC)PVE策略)
void RestorationDruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊控制(CC)PVE策略)
void RestorationDruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊控制(CC)PVP策略)
void RestorationDruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊控制(CC)PVP策略)
void RestorationDruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊控制(CC)团队副本策略)
void RestorationDruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊控制(CC)团队副本策略)
void RestorationDruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊驱散净化策略)
void RestorationDruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊驱散净化策略)
void RestorationDruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊驱散净化PVE策略)
void RestorationDruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊驱散净化PVE策略)
void RestorationDruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊驱散净化PVP策略)
void RestorationDruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊驱散净化PVP策略)
void RestorationDruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊驱散净化团队副本策略)
void RestorationDruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊驱散净化团队副本策略)
void RestorationDruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif

// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (恢复德鲁伊策略)
void RestorationDruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rebirth",
        NextAction::array(0, new NextAction("rebirth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("regrowth", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("swiftmend", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("swiftmend on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "lifebloom",
        NextAction::array(0, new NextAction("lifebloom", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("tranquility", ACTION_MEDIUM_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("rejuvenation", ACTION_LIGHT_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊策略)
void RestorationDruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("regrowth", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("swiftmend", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("swiftmend on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "lifebloom",
        NextAction::array(0, new NextAction("lifebloom", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("tranquility", ACTION_MEDIUM_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("rejuvenation", ACTION_LIGHT_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (恢复德鲁伊策略)
void RestorationDruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复德鲁伊策略)
void RestorationDruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊PVE策略)
void RestorationDruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitCombatTriggers(triggers);
    DruidPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊PVE策略)
void RestorationDruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复德鲁伊PVE策略)
void RestorationDruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitReactionTriggers(triggers);
    DruidPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复德鲁伊PVE策略)
void RestorationDruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitDeadTriggers(triggers);
    DruidPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊PVP策略)
void RestorationDruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitCombatTriggers(triggers);
    DruidPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊PVP策略)
void RestorationDruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复德鲁伊PVP策略)
void RestorationDruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitReactionTriggers(triggers);
    DruidPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复德鲁伊PVP策略)
void RestorationDruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitDeadTriggers(triggers);
    DruidPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊团队副本策略)
void RestorationDruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitCombatTriggers(triggers);
    DruidRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊团队副本策略)
void RestorationDruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitNonCombatTriggers(triggers);
    DruidRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复德鲁伊团队副本策略)
void RestorationDruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitReactionTriggers(triggers);
    DruidRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复德鲁伊团队副本策略)
void RestorationDruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitDeadTriggers(triggers);
    DruidRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊AOE群体策略)
void RestorationDruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊AOE群体策略)
void RestorationDruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊AOE群体PVE策略)
void RestorationDruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊AOE群体PVE策略)
void RestorationDruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊AOE群体PVP策略)
void RestorationDruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊AOE群体PVP策略)
void RestorationDruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊AOE群体团队副本策略)
void RestorationDruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊AOE群体团队副本策略)
void RestorationDruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊增益Buff策略)
void RestorationDruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "tree form",
        NextAction::array(0, new NextAction("tree form", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "innervate",
        NextAction::array(0, new NextAction("innervate", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊增益Buff策略)
void RestorationDruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊增益BuffPVE策略)
void RestorationDruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊增益BuffPVE策略)
void RestorationDruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊增益BuffPVP策略)
void RestorationDruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊增益BuffPVP策略)
void RestorationDruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊增益Buff团队副本策略)
void RestorationDruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊增益Buff团队副本策略)
void RestorationDruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊爆发增益策略)
void RestorationDruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "nature's swiftness",
        NextAction::array(0, new NextAction("nature's swiftness", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊爆发增益策略)
void RestorationDruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊爆发增益PVE策略)
void RestorationDruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊爆发增益PVE策略)
void RestorationDruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊爆发增益PVP策略)
void RestorationDruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊爆发增益PVP策略)
void RestorationDruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊爆发增益团队副本策略)
void RestorationDruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊爆发增益团队副本策略)
void RestorationDruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊控制(CC)策略)
void RestorationDruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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

// 初始化非战斗阶段触发器列表 (恢复德鲁伊控制(CC)策略)
void RestorationDruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊控制(CC)PVE策略)
void RestorationDruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊控制(CC)PVE策略)
void RestorationDruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊控制(CC)PVP策略)
void RestorationDruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊控制(CC)PVP策略)
void RestorationDruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊控制(CC)团队副本策略)
void RestorationDruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊控制(CC)团队副本策略)
void RestorationDruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊驱散净化策略)
void RestorationDruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊驱散净化策略)
void RestorationDruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊驱散净化PVE策略)
void RestorationDruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊驱散净化PVE策略)
void RestorationDruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊驱散净化PVP策略)
void RestorationDruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊驱散净化PVP策略)
void RestorationDruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊驱散净化团队副本策略)
void RestorationDruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊驱散净化团队副本策略)
void RestorationDruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif

// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (恢复德鲁伊策略)
void RestorationDruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rebirth",
        NextAction::array(0, new NextAction("rebirth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("regrowth", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("swiftmend", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("swiftmend on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "clearcasting",
        NextAction::array(0, new NextAction("lifebloom", ACTION_CRITICAL_HEAL - 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("tranquility", ACTION_MEDIUM_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("rejuvenation", ACTION_LIGHT_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊策略)
void RestorationDruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("regrowth", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("swiftmend", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("swiftmend on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "clearcasting",
        NextAction::array(0, new NextAction("lifebloom", ACTION_CRITICAL_HEAL - 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("tranquility", ACTION_MEDIUM_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("rejuvenation", ACTION_LIGHT_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (恢复德鲁伊策略)
void RestorationDruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复德鲁伊策略)
void RestorationDruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DruidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊PVE策略)
void RestorationDruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitCombatTriggers(triggers);
    DruidPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊PVE策略)
void RestorationDruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复德鲁伊PVE策略)
void RestorationDruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitReactionTriggers(triggers);
    DruidPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复德鲁伊PVE策略)
void RestorationDruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitDeadTriggers(triggers);
    DruidPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊PVP策略)
void RestorationDruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitCombatTriggers(triggers);
    DruidPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊PVP策略)
void RestorationDruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitNonCombatTriggers(triggers);
    DruidPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复德鲁伊PVP策略)
void RestorationDruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitReactionTriggers(triggers);
    DruidPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复德鲁伊PVP策略)
void RestorationDruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitDeadTriggers(triggers);
    DruidPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊团队副本策略)
void RestorationDruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitCombatTriggers(triggers);
    DruidRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊团队副本策略)
void RestorationDruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitNonCombatTriggers(triggers);
    DruidRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复德鲁伊团队副本策略)
void RestorationDruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitReactionTriggers(triggers);
    DruidRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复德鲁伊团队副本策略)
void RestorationDruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidStrategy::InitDeadTriggers(triggers);
    DruidRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊AOE群体策略)
void RestorationDruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊AOE群体策略)
void RestorationDruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊AOE群体PVE策略)
void RestorationDruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊AOE群体PVE策略)
void RestorationDruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊AOE群体PVP策略)
void RestorationDruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊AOE群体PVP策略)
void RestorationDruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊AOE群体团队副本策略)
void RestorationDruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊AOE群体团队副本策略)
void RestorationDruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidAoeStrategy::InitNonCombatTriggers(triggers);
    DruidAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊增益Buff策略)
void RestorationDruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "tree form",
        NextAction::array(0, new NextAction("tree form", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "innervate",
        NextAction::array(0, new NextAction("innervate", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊增益Buff策略)
void RestorationDruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊增益BuffPVE策略)
void RestorationDruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊增益BuffPVE策略)
void RestorationDruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊增益BuffPVP策略)
void RestorationDruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊增益BuffPVP策略)
void RestorationDruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊增益Buff团队副本策略)
void RestorationDruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊增益Buff团队副本策略)
void RestorationDruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBuffStrategy::InitNonCombatTriggers(triggers);
    DruidBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊爆发增益策略)
void RestorationDruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "nature's swiftness",
        NextAction::array(0, new NextAction("nature's swiftness", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊爆发增益策略)
void RestorationDruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊爆发增益PVE策略)
void RestorationDruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊爆发增益PVE策略)
void RestorationDruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊爆发增益PVP策略)
void RestorationDruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊爆发增益PVP策略)
void RestorationDruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊爆发增益团队副本策略)
void RestorationDruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊爆发增益团队副本策略)
void RestorationDruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidBoostStrategy::InitNonCombatTriggers(triggers);
    DruidBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊控制(CC)策略)
void RestorationDruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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

// 初始化非战斗阶段触发器列表 (恢复德鲁伊控制(CC)策略)
void RestorationDruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊控制(CC)PVE策略)
void RestorationDruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊控制(CC)PVE策略)
void RestorationDruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊控制(CC)PVP策略)
void RestorationDruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊控制(CC)PVP策略)
void RestorationDruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊控制(CC)团队副本策略)
void RestorationDruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitCombatTriggers(triggers);
    DruidCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊控制(CC)团队副本策略)
void RestorationDruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCcStrategy::InitNonCombatTriggers(triggers);
    DruidCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊驱散净化策略)
void RestorationDruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊驱散净化策略)
void RestorationDruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊驱散净化PVE策略)
void RestorationDruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊驱散净化PVE策略)
void RestorationDruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊驱散净化PVP策略)
void RestorationDruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊驱散净化PVP策略)
void RestorationDruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复德鲁伊驱散净化团队副本策略)
void RestorationDruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitCombatTriggers(triggers);
    DruidCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复德鲁伊驱散净化团队副本策略)
void RestorationDruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationDruidCureStrategy::InitNonCombatTriggers(triggers);
    DruidCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
