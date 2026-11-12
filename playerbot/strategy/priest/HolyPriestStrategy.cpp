// 牧师 - 神圣牧师策略实现文件 (HolyPriestStrategy.cpp)
#include "playerbot/playerbot.h"
#include "PriestMultipliers.h"
#include "HolyPriestStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class HolyPriestStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    HolyPriestStrategyActionNodeFactory()
    {
        creators["lightwell"] = &lightwell;
        creators["circle of healing"] = &circle_of_healing;
    }

private:
    // 动作节点 lightwell：光明之泉 -> 备选(A)动作：治疗之环
    ACTION_NODE_A(lightwell, "lightwell", "circle of healing");

    // 动作节点 circle_of_healing：治疗之环 -> 备选(A)动作：治疗祷言
    ACTION_NODE_A(circle_of_healing, "circle of healing", "prayer of healing");
};

// 构造函数：初始化神圣牧师策略并挂载动作节点工厂
HolyPriestStrategy::HolyPriestStrategy(PlayerbotAI* ai) : PriestStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<HolyPriestStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (神圣牧师策略)
void HolyPriestStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("flash heal on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_MEDIUM_HEAL + 2),
                             new NextAction("greater heal on party", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("renew on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (神圣牧师策略)
void HolyPriestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_MOVE + 1),
            new NextAction("flash heal on party", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_HIGH + 2),
            new NextAction("greater heal on party", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("renew on party", ACTION_NORMAL), NULL)));
}

// 初始化反应阶段触发器列表 (神圣牧师策略)
void HolyPriestStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣牧师策略)
void HolyPriestStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师PVE策略)
void HolyPriestPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitCombatTriggers(triggers);
    PriestPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师PVE策略)
void HolyPriestPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitNonCombatTriggers(triggers);
    PriestPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣牧师PVE策略)
void HolyPriestPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitReactionTriggers(triggers);
    PriestPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣牧师PVE策略)
void HolyPriestPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitDeadTriggers(triggers);
    PriestPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师PVP策略)
void HolyPriestPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitCombatTriggers(triggers);
    PriestPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师PVP策略)
void HolyPriestPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitNonCombatTriggers(triggers);
    PriestPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣牧师PVP策略)
void HolyPriestPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitReactionTriggers(triggers);
    PriestPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣牧师PVP策略)
void HolyPriestPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitDeadTriggers(triggers);
    PriestPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师团队副本策略)
void HolyPriestRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitCombatTriggers(triggers);
    PriestRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师团队副本策略)
void HolyPriestRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitNonCombatTriggers(triggers);
    PriestRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣牧师团队副本策略)
void HolyPriestRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitReactionTriggers(triggers);
    PriestRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣牧师团队副本策略)
void HolyPriestRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitDeadTriggers(triggers);
    PriestRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师AOE群体策略)
void HolyPriestAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("circle of healing", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (神圣牧师AOE群体策略)
void HolyPriestAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师AOE群体PVE策略)
void HolyPriestAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师AOE群体PVE策略)
void HolyPriestAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师AOE群体PVP策略)
void HolyPriestAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师AOE群体PVP策略)
void HolyPriestAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师AOE群体团队副本策略)
void HolyPriestAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师AOE群体团队副本策略)
void HolyPriestAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师增益Buff策略)
void HolyPriestBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师增益Buff策略)
void HolyPriestBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师增益BuffPVE策略)
void HolyPriestBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师增益BuffPVE策略)
void HolyPriestBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师增益BuffPVP策略)
void HolyPriestBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师增益BuffPVP策略)
void HolyPriestBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师增益Buff团队副本策略)
void HolyPriestBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师增益Buff团队副本策略)
void HolyPriestBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师爆发增益策略)
void HolyPriestBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师爆发增益策略)
void HolyPriestBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师爆发增益PVE策略)
void HolyPriestBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师爆发增益PVE策略)
void HolyPriestBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师爆发增益PVP策略)
void HolyPriestBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师爆发增益PVP策略)
void HolyPriestBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师爆发增益团队副本策略)
void HolyPriestBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师爆发增益团队副本策略)
void HolyPriestBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师控制(CC)策略)
void HolyPriestCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师控制(CC)策略)
void HolyPriestCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师控制(CC)PVE策略)
void HolyPriestCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师控制(CC)PVE策略)
void HolyPriestCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师控制(CC)PVP策略)
void HolyPriestCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师控制(CC)PVP策略)
void HolyPriestCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师控制(CC)团队副本策略)
void HolyPriestCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师控制(CC)团队副本策略)
void HolyPriestCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师驱散净化策略)
void HolyPriestCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师驱散净化策略)
void HolyPriestCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师驱散净化PVE策略)
void HolyPriestCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师驱散净化PVE策略)
void HolyPriestCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师驱散净化PVP策略)
void HolyPriestCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师驱散净化PVP策略)
void HolyPriestCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师驱散净化团队副本策略)
void HolyPriestCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师驱散净化团队副本策略)
void HolyPriestCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (神圣牧师策略)
void HolyPriestStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("flash heal on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_MEDIUM_HEAL + 2),
                             new NextAction("greater heal on party", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("renew on party", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "binding heal",
        NextAction::array(0, new NextAction("binding heal", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (神圣牧师策略)
void HolyPriestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_MOVE + 1),
            new NextAction("flash heal on party", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_HIGH + 2),
            new NextAction("greater heal on party", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("renew on party", ACTION_NORMAL), NULL)));
}

// 初始化反应阶段触发器列表 (神圣牧师策略)
void HolyPriestStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣牧师策略)
void HolyPriestStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师PVE策略)
void HolyPriestPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitCombatTriggers(triggers);
    PriestPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师PVE策略)
void HolyPriestPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitNonCombatTriggers(triggers);
    PriestPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣牧师PVE策略)
void HolyPriestPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitReactionTriggers(triggers);
    PriestPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣牧师PVE策略)
void HolyPriestPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitDeadTriggers(triggers);
    PriestPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师PVP策略)
void HolyPriestPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitCombatTriggers(triggers);
    PriestPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师PVP策略)
void HolyPriestPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitNonCombatTriggers(triggers);
    PriestPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣牧师PVP策略)
void HolyPriestPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitReactionTriggers(triggers);
    PriestPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣牧师PVP策略)
void HolyPriestPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitDeadTriggers(triggers);
    PriestPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师团队副本策略)
void HolyPriestRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitCombatTriggers(triggers);
    PriestRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师团队副本策略)
void HolyPriestRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitNonCombatTriggers(triggers);
    PriestRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣牧师团队副本策略)
void HolyPriestRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitReactionTriggers(triggers);
    PriestRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣牧师团队副本策略)
void HolyPriestRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitDeadTriggers(triggers);
    PriestRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师AOE群体策略)
void HolyPriestAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("prayer of mending", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("circle of healing", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (神圣牧师AOE群体策略)
void HolyPriestAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师AOE群体PVE策略)
void HolyPriestAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师AOE群体PVE策略)
void HolyPriestAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师AOE群体PVP策略)
void HolyPriestAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师AOE群体PVP策略)
void HolyPriestAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师AOE群体团队副本策略)
void HolyPriestAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师AOE群体团队副本策略)
void HolyPriestAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师增益Buff策略)
void HolyPriestBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师增益Buff策略)
void HolyPriestBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师增益BuffPVE策略)
void HolyPriestBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师增益BuffPVE策略)
void HolyPriestBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师增益BuffPVP策略)
void HolyPriestBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师增益BuffPVP策略)
void HolyPriestBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师增益Buff团队副本策略)
void HolyPriestBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师增益Buff团队副本策略)
void HolyPriestBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师爆发增益策略)
void HolyPriestBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师爆发增益策略)
void HolyPriestBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师爆发增益PVE策略)
void HolyPriestBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师爆发增益PVE策略)
void HolyPriestBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师爆发增益PVP策略)
void HolyPriestBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师爆发增益PVP策略)
void HolyPriestBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师爆发增益团队副本策略)
void HolyPriestBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师爆发增益团队副本策略)
void HolyPriestBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师控制(CC)策略)
void HolyPriestCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师控制(CC)策略)
void HolyPriestCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师控制(CC)PVE策略)
void HolyPriestCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师控制(CC)PVE策略)
void HolyPriestCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师控制(CC)PVP策略)
void HolyPriestCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师控制(CC)PVP策略)
void HolyPriestCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师控制(CC)团队副本策略)
void HolyPriestCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师控制(CC)团队副本策略)
void HolyPriestCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师驱散净化策略)
void HolyPriestCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师驱散净化策略)
void HolyPriestCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师驱散净化PVE策略)
void HolyPriestCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师驱散净化PVE策略)
void HolyPriestCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师驱散净化PVP策略)
void HolyPriestCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师驱散净化PVP策略)
void HolyPriestCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师驱散净化团队副本策略)
void HolyPriestCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师驱散净化团队副本策略)
void HolyPriestCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (神圣牧师策略)
void HolyPriestStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("flash heal on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_MEDIUM_HEAL + 2),
                             new NextAction("greater heal on party", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("renew on party", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "binding heal",
        NextAction::array(0, new NextAction("binding heal", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (神圣牧师策略)
void HolyPriestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_MOVE + 1),
            new NextAction("flash heal on party", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_HIGH + 2),
            new NextAction("greater heal on party", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("renew on party", ACTION_NORMAL), NULL)));
}

// 初始化反应阶段触发器列表 (神圣牧师策略)
void HolyPriestStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣牧师策略)
void HolyPriestStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师PVE策略)
void HolyPriestPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitCombatTriggers(triggers);
    PriestPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师PVE策略)
void HolyPriestPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitNonCombatTriggers(triggers);
    PriestPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣牧师PVE策略)
void HolyPriestPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitReactionTriggers(triggers);
    PriestPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣牧师PVE策略)
void HolyPriestPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitDeadTriggers(triggers);
    PriestPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师PVP策略)
void HolyPriestPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitCombatTriggers(triggers);
    PriestPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师PVP策略)
void HolyPriestPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitNonCombatTriggers(triggers);
    PriestPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣牧师PVP策略)
void HolyPriestPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitReactionTriggers(triggers);
    PriestPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣牧师PVP策略)
void HolyPriestPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitDeadTriggers(triggers);
    PriestPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师团队副本策略)
void HolyPriestRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitCombatTriggers(triggers);
    PriestRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师团队副本策略)
void HolyPriestRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitNonCombatTriggers(triggers);
    PriestRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (神圣牧师团队副本策略)
void HolyPriestRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitReactionTriggers(triggers);
    PriestRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (神圣牧师团队副本策略)
void HolyPriestRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestStrategy::InitDeadTriggers(triggers);
    PriestRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师AOE群体策略)
void HolyPriestAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("prayer of mending", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("circle of healing", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (神圣牧师AOE群体策略)
void HolyPriestAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师AOE群体PVE策略)
void HolyPriestAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师AOE群体PVE策略)
void HolyPriestAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师AOE群体PVP策略)
void HolyPriestAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师AOE群体PVP策略)
void HolyPriestAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师AOE群体团队副本策略)
void HolyPriestAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师AOE群体团队副本策略)
void HolyPriestAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师增益Buff策略)
void HolyPriestBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师增益Buff策略)
void HolyPriestBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师增益BuffPVE策略)
void HolyPriestBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师增益BuffPVE策略)
void HolyPriestBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师增益BuffPVP策略)
void HolyPriestBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师增益BuffPVP策略)
void HolyPriestBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师增益Buff团队副本策略)
void HolyPriestBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师增益Buff团队副本策略)
void HolyPriestBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师爆发增益策略)
void HolyPriestBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师爆发增益策略)
void HolyPriestBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师爆发增益PVE策略)
void HolyPriestBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师爆发增益PVE策略)
void HolyPriestBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师爆发增益PVP策略)
void HolyPriestBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师爆发增益PVP策略)
void HolyPriestBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师爆发增益团队副本策略)
void HolyPriestBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师爆发增益团队副本策略)
void HolyPriestBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师控制(CC)策略)
void HolyPriestCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师控制(CC)策略)
void HolyPriestCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师控制(CC)PVE策略)
void HolyPriestCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师控制(CC)PVE策略)
void HolyPriestCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师控制(CC)PVP策略)
void HolyPriestCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师控制(CC)PVP策略)
void HolyPriestCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师控制(CC)团队副本策略)
void HolyPriestCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师控制(CC)团队副本策略)
void HolyPriestCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师驱散净化策略)
void HolyPriestCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师驱散净化策略)
void HolyPriestCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师驱散净化PVE策略)
void HolyPriestCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师驱散净化PVE策略)
void HolyPriestCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师驱散净化PVP策略)
void HolyPriestCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师驱散净化PVP策略)
void HolyPriestCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (神圣牧师驱散净化团队副本策略)
void HolyPriestCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (神圣牧师驱散净化团队副本策略)
void HolyPriestCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    HolyPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
