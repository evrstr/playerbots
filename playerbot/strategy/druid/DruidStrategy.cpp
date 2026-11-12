// 德鲁伊 - 德鲁伊策略实现文件 (DruidStrategy.cpp)

#include "playerbot/playerbot.h"
#include "DruidStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class DruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DruidStrategyActionNodeFactory()
    {
        creators["healing touch"] = &healing_touch;
        creators["healing touch on party"] = &healing_touch_on_party;
        creators["regrowth"] = &regrowth;
        creators["regrowth on party"] = &regrowth_on_party;
        creators["rejuvenation"] = &rejuvenation;
        creators["rejuvenation on party"] = &rejuvenation_on_party;
        creators["rebirth"] = &rebirth;
        creators["abolish poison"] = &abolish_poison;
        creators["abolish poison on party"] = &abolish_poison_on_party;
        creators["remove curse"] = &remove_curse;
        creators["remove curse on party"] = &remove_curse_on_party;
        creators["hibernate on cc"] = &hibernate_on_cc;
        creators["thorns"] = &thorns;
        creators["thorns on party"] = &thorns_on_party;
        creators["mark of the wild"] = &mark_of_the_wild;
        creators["mark of the wild on party"] = &mark_of_the_wild_on_party;
        creators["gift of the wild on party"] = &gift_of_the_wild_on_party;
        creators["dire bear form"] = &dire_bear_form;
        creators["cat form"] = &cat_form;
        creators["travel form"] = &travel_form;
    }

private:
    // 构建 驱毒术 (abolish_poison) 动作节点
    static ActionNode* abolish_poison(PlayerbotAI* ai)
    {
        return new ActionNode("abolish poison",
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
            /*P*/ NextAction::array(0, new NextAction("balance or restoration caster form"), NULL),
#else
            /*P*/ NextAction::array(0, new NextAction("restoration caster form"), NULL),
#endif
            /*A*/ NextAction::array(0, new NextAction("cure poison"), NULL),
            /*C*/ NULL);
    }

    // 构建 驱毒术 (对队友) (abolish_poison_on_party) 动作节点
    static ActionNode* abolish_poison_on_party(PlayerbotAI* ai)
    {
        return new ActionNode("abolish poison on party",
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
            /*P*/ NextAction::array(0, new NextAction("balance or restoration caster form"), NULL),
#else
            /*P*/ NextAction::array(0, new NextAction("restoration caster form"), NULL),
#endif
            /*A*/ NextAction::array(0, new NextAction("cure poison on party"), NULL),
            /*C*/ NULL);
    }

    // 构建 巨熊形态 (dire_bear_form) 动作节点
    static ActionNode* dire_bear_form(PlayerbotAI* ai)
    {
        return new ActionNode("dire bear form",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("bear form"), NULL),
            /*C*/ NULL);
    }

// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
    // 动作节点 remove_curse：解除诅咒 -> 前置(P)动作：平衡或恢复施法者形态
    ACTION_NODE_P(remove_curse, "remove curse", "balance or restoration caster form");
    // 动作节点 remove_curse_on_party：对队友解除诅咒 -> 前置(P)动作：平衡或恢复施法者形态
    ACTION_NODE_P(remove_curse_on_party, "remove curse on party", "balance or restoration caster form");
#elif MANGOSBOT_ONE
    // 动作节点 remove_curse：解除诅咒 -> 前置(P)动作：平衡施法者形态
    ACTION_NODE_P(remove_curse, "remove curse", "balance caster form");
    // 动作节点 remove_curse_on_party：对队友解除诅咒 -> 前置(P)动作：平衡施法者形态
    ACTION_NODE_P(remove_curse_on_party, "remove curse on party", "balance caster form");
#else
    // 动作节点 remove_curse：解除诅咒 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(remove_curse, "remove curse", "caster form");
    // 动作节点 remove_curse_on_party：对队友解除诅咒 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(remove_curse_on_party, "remove curse on party", "caster form");
#endif

    // 动作节点 hibernate_on_cc：对控制目标施放休眠 -> 前置(P)动作：平衡施法者形态
    ACTION_NODE_P(hibernate_on_cc, "hibernate on cc", "balance caster form");

    // 动作节点 rebirth：复生 -> 前置(P)动作：恢复施法者形态
    ACTION_NODE_P(rebirth, "rebirth", "restoration caster form");

    // 动作节点 regrowth：愈合 -> 前置(P)动作：恢复施法者形态
    ACTION_NODE_P(regrowth, "regrowth", "restoration caster form");

    // 动作节点 regrowth_on_party：对队友施放愈合 -> 前置(P)动作：恢复施法者形态
    ACTION_NODE_P(regrowth_on_party, "regrowth on party", "restoration caster form");

// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO
    // 动作节点 healing_touch：治疗之触 -> 前置(P)动作：恢复施法者形态
    ACTION_NODE_P(healing_touch, "healing touch", "restoration caster form");
    // 动作节点 healing_touch_on_party：对队友施放治疗之触 -> 前置(P)动作：恢复施法者形态
    ACTION_NODE_P(healing_touch_on_party, "healing touch on party", "restoration caster form");
    // 动作节点 thorns：荆棘术 -> 前置(P)动作：恢复施法者形态
    ACTION_NODE_P(thorns, "thorns", "restoration caster form");
    // 动作节点 thorns_on_party：对队友施放荆棘术 -> 前置(P)动作：恢复施法者形态
    ACTION_NODE_P(thorns_on_party, "thorns on party", "restoration caster form");
    // 动作节点 mark_of_the_wild：野性印记 -> 前置(P)动作：恢复施法者形态
    ACTION_NODE_P(mark_of_the_wild, "mark of the wild", "restoration caster form");
    // 动作节点 mark_of_the_wild_on_party：对队友施放野性印记 -> 前置(P)动作：恢复施法者形态
    ACTION_NODE_P(mark_of_the_wild_on_party, "mark of the wild on party", "restoration caster form");
    // 动作节点 gift_of_the_wild_on_party：对队友施放野性赐福 -> 前置(P)动作：恢复施法者形态
    ACTION_NODE_P(gift_of_the_wild_on_party, "gift of the wild on party", "restoration caster form");
#else
    // 动作节点 healing_touch：治疗之触 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(healing_touch, "healing touch", "caster form");
    // 动作节点 healing_touch_on_party：对队友施放治疗之触 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(healing_touch_on_party, "healing touch on party", "caster form");
    // 动作节点 thorns：荆棘术 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(thorns, "thorns", "caster form");
    // 动作节点 thorns_on_party：对队友施放荆棘术 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(thorns_on_party, "thorns on party", "caster form");
    // 动作节点 mark_of_the_wild：野性印记 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(mark_of_the_wild, "mark of the wild", "caster form");
    // 动作节点 mark_of_the_wild_on_party：对队友施放野性印记 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(mark_of_the_wild_on_party, "mark of the wild on party", "caster form");
    // 动作节点 gift_of_the_wild_on_party：对队友施放野性赐福 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(gift_of_the_wild_on_party, "gift of the wild on party", "caster form");
#endif

    // 动作节点 rejuvenation：回春术 -> 前置(P)动作：恢复施法者形态
    ACTION_NODE_P(rejuvenation, "rejuvenation", "restoration caster form");

    // 动作节点 rejuvenation_on_party：对队友施放回春术 -> 前置(P)动作：恢复施法者形态
    ACTION_NODE_P(rejuvenation_on_party, "rejuvenation on party", "restoration caster form");

    // 动作节点 cat_form：猎豹形态 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(cat_form, "cat form", "caster form");

    // 动作节点 travel_form：旅行形态 -> 前置(P)动作：人形态(施法者形态)
    ACTION_NODE_P(travel_form, "travel form", "caster form");
};

// 构造函数：初始化德鲁伊策略并挂载动作节点工厂
DruidStrategy::DruidStrategy(PlayerbotAI* ai) : ClassStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<DruidStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (德鲁伊策略)
void DruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊策略)
void DruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (德鲁伊策略)
void DruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (德鲁伊策略)
void DruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊PVP策略)
void DruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("travel form", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (德鲁伊PVP策略)
void DruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("travel form", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (德鲁伊PVP策略)
void DruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (德鲁伊PVP策略)
void DruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊PVE策略)
void DruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊PVE策略)
void DruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (德鲁伊PVE策略)
void DruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (德鲁伊PVE策略)
void DruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊团队副本策略)
void DruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊团队副本策略)
void DruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (德鲁伊团队副本策略)
void DruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (德鲁伊团队副本策略)
void DruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊AOE群体策略)
void DruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊AOE群体策略)
void DruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊AOE群体PVP策略)
void DruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊AOE群体PVP策略)
void DruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊AOE群体PVE策略)
void DruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊AOE群体PVE策略)
void DruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊AOE群体团队副本策略)
void DruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊AOE群体团队副本策略)
void DruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊驱散净化策略)
void DruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("abolish poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member remove curse",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "rooted",
        NextAction::array(0, new NextAction("caster form", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (德鲁伊驱散净化策略)
void DruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("abolish poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member remove curse",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_DISPEL), NULL)));
}

// 初始化战斗阶段触发器列表 (德鲁伊驱散净化PVP策略)
void DruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊驱散净化PVP策略)
void DruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊驱散净化PVE策略)
void DruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊驱散净化PVE策略)
void DruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊驱散净化团队副本策略)
void DruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊驱散净化团队副本策略)
void DruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊控制(CC)策略)
void DruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hibernate",
        NextAction::array(0, new NextAction("hibernate on cc", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (德鲁伊控制(CC)策略)
void DruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊控制(CC)PVP策略)
void DruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊控制(CC)PVP策略)
void DruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊控制(CC)PVE策略)
void DruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊控制(CC)PVE策略)
void DruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊控制(CC)团队副本策略)
void DruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊控制(CC)团队副本策略)
void DruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊增益Buff策略)
void DruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

}

// 初始化非战斗阶段触发器列表 (德鲁伊增益Buff策略)
void DruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "gift of the wild on party",
        NextAction::array(0, new NextAction("gift of the wild on party", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "mark of the wild on party",
        NextAction::array(0, new NextAction("mark of the wild on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "thorns on party",
        NextAction::array(0, new NextAction("thorns on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "mark of the wild",
        NextAction::array(0, new NextAction("mark of the wild", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "thorns",
        NextAction::array(0, new NextAction("thorns", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (德鲁伊增益BuffPVP策略)
void DruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊增益BuffPVP策略)
void DruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊增益BuffPVE策略)
void DruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊增益BuffPVE策略)
void DruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊增益Buff团队副本策略)
void DruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊增益Buff团队副本策略)
void DruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊爆发增益策略)
void DruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊爆发增益策略)
void DruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊爆发增益PVP策略)
void DruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊爆发增益PVP策略)
void DruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊爆发增益PVE策略)
void DruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊爆发增益PVE策略)
void DruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊爆发增益团队副本策略)
void DruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊爆发增益团队副本策略)
void DruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助治疗策略)
void DruidOffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("healing touch on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助治疗策略)
void DruidOffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助治疗PVP策略)
void DruidOffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助治疗PVP策略)
void DruidOffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助治疗PVE策略)
void DruidOffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助治疗PVE策略)
void DruidOffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助治疗团队副本策略)
void DruidOffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitCombatTriggers(triggers);
    OffhealRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助治疗团队副本策略)
void DruidOffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助输出策略)
void DruidOffdpsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffdpsStrategy::InitCombatTriggers(triggers);

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
        "wrath",
        NextAction::array(0, new NextAction("wrath", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助输出策略)
void DruidOffdpsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffdpsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助输出PVP策略)
void DruidOffdpsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffdpsStrategy::InitCombatTriggers(triggers);
    OffdpsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助输出PVP策略)
void DruidOffdpsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffdpsStrategy::InitNonCombatTriggers(triggers);
    OffdpsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助输出PVE策略)
void DruidOffdpsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffdpsStrategy::InitCombatTriggers(triggers);
    OffdpsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助输出PVE策略)
void DruidOffdpsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffdpsStrategy::InitNonCombatTriggers(triggers);
    OffdpsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助输出团队副本策略)
void DruidOffdpsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffdpsStrategy::InitCombatTriggers(triggers);
    OffdpsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助输出团队副本策略)
void DruidOffdpsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffdpsStrategy::InitNonCombatTriggers(triggers);
    OffdpsRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (德鲁伊策略)
void DruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊策略)
void DruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (德鲁伊策略)
void DruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (德鲁伊策略)
void DruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊PVP策略)
void DruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("travel form", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (德鲁伊PVP策略)
void DruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("travel form", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (德鲁伊PVP策略)
void DruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (德鲁伊PVP策略)
void DruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊PVE策略)
void DruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊PVE策略)
void DruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (德鲁伊PVE策略)
void DruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (德鲁伊PVE策略)
void DruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊团队副本策略)
void DruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊团队副本策略)
void DruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (德鲁伊团队副本策略)
void DruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (德鲁伊团队副本策略)
void DruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊AOE群体策略)
void DruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊AOE群体策略)
void DruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊AOE群体PVP策略)
void DruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊AOE群体PVP策略)
void DruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊AOE群体PVE策略)
void DruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊AOE群体PVE策略)
void DruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊AOE群体团队副本策略)
void DruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊AOE群体团队副本策略)
void DruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊驱散净化策略)
void DruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("abolish poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member remove curse",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (德鲁伊驱散净化策略)
void DruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("abolish poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member remove curse",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_DISPEL), NULL)));
}

// 初始化战斗阶段触发器列表 (德鲁伊驱散净化PVP策略)
void DruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊驱散净化PVP策略)
void DruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊驱散净化PVE策略)
void DruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊驱散净化PVE策略)
void DruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊驱散净化团队副本策略)
void DruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊驱散净化团队副本策略)
void DruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊控制(CC)策略)
void DruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hibernate",
        NextAction::array(0, new NextAction("hibernate on cc", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (德鲁伊控制(CC)策略)
void DruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊控制(CC)PVP策略)
void DruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊控制(CC)PVP策略)
void DruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊控制(CC)PVE策略)
void DruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊控制(CC)PVE策略)
void DruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊控制(CC)团队副本策略)
void DruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊控制(CC)团队副本策略)
void DruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊增益Buff策略)
void DruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊增益Buff策略)
void DruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "gift of the wild on party",
        NextAction::array(0, new NextAction("gift of the wild on party", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "mark of the wild on party",
        NextAction::array(0, new NextAction("mark of the wild on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "thorns on party",
        NextAction::array(0, new NextAction("thorns on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "mark of the wild",
        NextAction::array(0, new NextAction("mark of the wild", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "thorns",
        NextAction::array(0, new NextAction("thorns", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (德鲁伊增益BuffPVP策略)
void DruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊增益BuffPVP策略)
void DruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊增益BuffPVE策略)
void DruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊增益BuffPVE策略)
void DruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊增益Buff团队副本策略)
void DruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊增益Buff团队副本策略)
void DruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊爆发增益策略)
void DruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊爆发增益策略)
void DruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊爆发增益PVP策略)
void DruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊爆发增益PVP策略)
void DruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊爆发增益PVE策略)
void DruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊爆发增益PVE策略)
void DruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊爆发增益团队副本策略)
void DruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊爆发增益团队副本策略)
void DruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助治疗策略)
void DruidOffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_CRITICAL_HEAL + 1),
            new NextAction("healing touch on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助治疗策略)
void DruidOffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助治疗PVP策略)
void DruidOffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助治疗PVP策略)
void DruidOffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助治疗PVE策略)
void DruidOffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助治疗PVE策略)
void DruidOffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助治疗团队副本策略)
void DruidOffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitCombatTriggers(triggers);
    OffhealRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助治疗团队副本策略)
void DruidOffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (德鲁伊策略)
void DruidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊策略)
void DruidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (德鲁伊策略)
void DruidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (德鲁伊策略)
void DruidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊PVP策略)
void DruidPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("travel form", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (德鲁伊PVP策略)
void DruidPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("travel form", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (德鲁伊PVP策略)
void DruidPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (德鲁伊PVP策略)
void DruidPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊PVE策略)
void DruidPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊PVE策略)
void DruidPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (德鲁伊PVE策略)
void DruidPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (德鲁伊PVE策略)
void DruidPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊团队副本策略)
void DruidRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊团队副本策略)
void DruidRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (德鲁伊团队副本策略)
void DruidRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (德鲁伊团队副本策略)
void DruidRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊AOE群体策略)
void DruidAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊AOE群体策略)
void DruidAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊AOE群体PVP策略)
void DruidAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊AOE群体PVP策略)
void DruidAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊AOE群体PVE策略)
void DruidAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊AOE群体PVE策略)
void DruidAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊AOE群体团队副本策略)
void DruidAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊AOE群体团队副本策略)
void DruidAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊驱散净化策略)
void DruidCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("abolish poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member remove curse",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (德鲁伊驱散净化策略)
void DruidCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("abolish poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member remove curse",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_DISPEL), NULL)));
}

// 初始化战斗阶段触发器列表 (德鲁伊驱散净化PVP策略)
void DruidCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊驱散净化PVP策略)
void DruidCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊驱散净化PVE策略)
void DruidCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊驱散净化PVE策略)
void DruidCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊驱散净化团队副本策略)
void DruidCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊驱散净化团队副本策略)
void DruidCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊控制(CC)策略)
void DruidCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hibernate",
        NextAction::array(0, new NextAction("hibernate on cc", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (德鲁伊控制(CC)策略)
void DruidCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊控制(CC)PVP策略)
void DruidCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊控制(CC)PVP策略)
void DruidCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊控制(CC)PVE策略)
void DruidCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊控制(CC)PVE策略)
void DruidCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊控制(CC)团队副本策略)
void DruidCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊控制(CC)团队副本策略)
void DruidCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊增益Buff策略)
void DruidBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊增益Buff策略)
void DruidBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member dead",
        NextAction::array(0, new NextAction("revive", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "gift of the wild on party",
        NextAction::array(0, new NextAction("gift of the wild on party", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "mark of the wild on party",
        NextAction::array(0, new NextAction("mark of the wild on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "thorns on party",
        NextAction::array(0, new NextAction("thorns on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "mark of the wild",
        NextAction::array(0, new NextAction("mark of the wild", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "thorns",
        NextAction::array(0, new NextAction("thorns", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (德鲁伊增益BuffPVP策略)
void DruidBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊增益BuffPVP策略)
void DruidBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊增益BuffPVE策略)
void DruidBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊增益BuffPVE策略)
void DruidBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊增益Buff团队副本策略)
void DruidBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊增益Buff团队副本策略)
void DruidBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊爆发增益策略)
void DruidBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊爆发增益策略)
void DruidBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊爆发增益PVP策略)
void DruidBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊爆发增益PVP策略)
void DruidBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊爆发增益PVE策略)
void DruidBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊爆发增益PVE策略)
void DruidBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊爆发增益团队副本策略)
void DruidBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊爆发增益团队副本策略)
void DruidBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助治疗策略)
void DruidOffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_CRITICAL_HEAL + 1),
            new NextAction("healing touch on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助治疗策略)
void DruidOffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助治疗PVP策略)
void DruidOffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助治疗PVP策略)
void DruidOffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助治疗PVE策略)
void DruidOffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助治疗PVE策略)
void DruidOffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (德鲁伊辅助治疗团队副本策略)
void DruidOffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitCombatTriggers(triggers);
    OffhealRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (德鲁伊辅助治疗团队副本策略)
void DruidOffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DruidOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
