/// 战斗药水、治疗石与绷带使用策略实现

#include "playerbot/playerbot.h"
#include "UsePotionsStrategy.h"

using namespace ai;

/// 动作节点工厂：构建治疗石->红药->绷带及黑暗符文->蓝药的降级链
class UsePotionsStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    UsePotionsStrategyActionNodeFactory()
    {
        creators["healthstone"] = &healthstone;
        creators["healing potion"] = &healing_potion;
        creators["dark rune"] = &dark_rune;
    }

private:
    ACTION_NODE_A(healthstone, "healthstone", "healing potion");

    ACTION_NODE_A(healing_potion, "healing potion", "use bandage");

    ACTION_NODE_A(dark_rune, "dark rune", "mana potion");
};

/// 构造药水策略并注册备用药水动作工厂
UsePotionsStrategy::UsePotionsStrategy(PlayerbotAI* ai) : Strategy(ai)
{
    actionNodeFactories.Add(std::make_unique<UsePotionsStrategyActionNodeFactory>());
}

/// 初始化战斗触发器：危急血量吃糖/萝卜/红药，低血打绷带，低蓝吃符文/蓝药，中毒解毒
void UsePotionsStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("healthstone", ACTION_CRITICAL_HEAL + 1), NULL)));

#ifdef MANGOSBOT_ZERO
    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("whipper root tuber", ACTION_CRITICAL_HEAL), NULL)));
#endif

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("use bandage", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("dark rune", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "has poison debuff",
        NextAction::array(0, new NextAction("anti-venom", ACTION_DISPEL), NULL)));
}

/// 初始化反应触发器：复用战斗药水触发器
void UsePotionsStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    InitCombatTriggers(triggers);
}