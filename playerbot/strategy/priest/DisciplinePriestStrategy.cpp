// 牧师 - 戒律牧师策略实现文件 (DisciplinePriestStrategy.cpp)
#include "playerbot/playerbot.h"
#include "PriestMultipliers.h"
#include "DisciplinePriestStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class DisciplinePriestStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DisciplinePriestStrategyActionNodeFactory()
    {
        
    }

private:

};

// 构造函数：初始化戒律牧师策略并挂载动作节点工厂
DisciplinePriestStrategy::DisciplinePriestStrategy(PlayerbotAI* ai) : PriestStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<DisciplinePriestStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (戒律牧师策略)
void DisciplinePriestStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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

// 初始化非战斗阶段触发器列表 (戒律牧师策略)
void DisciplinePriestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitNonCombatTriggers(triggers);

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

// 初始化反应阶段触发器列表 (戒律牧师策略)
void DisciplinePriestStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (戒律牧师策略)
void DisciplinePriestStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师PVE策略)
void DisciplinePriestPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitCombatTriggers(triggers);
    PriestPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师PVE策略)
void DisciplinePriestPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitNonCombatTriggers(triggers);
    PriestPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (戒律牧师PVE策略)
void DisciplinePriestPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitReactionTriggers(triggers);
    PriestPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (戒律牧师PVE策略)
void DisciplinePriestPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitDeadTriggers(triggers);
    PriestPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师PVP策略)
void DisciplinePriestPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitCombatTriggers(triggers);
    PriestPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师PVP策略)
void DisciplinePriestPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitNonCombatTriggers(triggers);
    PriestPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (戒律牧师PVP策略)
void DisciplinePriestPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitReactionTriggers(triggers);
    PriestPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (戒律牧师PVP策略)
void DisciplinePriestPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitDeadTriggers(triggers);
    PriestPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师团队副本策略)
void DisciplinePriestRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitCombatTriggers(triggers);
    PriestRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师团队副本策略)
void DisciplinePriestRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitNonCombatTriggers(triggers);
    PriestRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (戒律牧师团队副本策略)
void DisciplinePriestRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitReactionTriggers(triggers);
    PriestRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (戒律牧师团队副本策略)
void DisciplinePriestRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitDeadTriggers(triggers);
    PriestRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师AOE群体策略)
void DisciplinePriestAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("prayer of healing", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (戒律牧师AOE群体策略)
void DisciplinePriestAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师AOE群体PVE策略)
void DisciplinePriestAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师AOE群体PVE策略)
void DisciplinePriestAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师AOE群体PVP策略)
void DisciplinePriestAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师AOE群体PVP策略)
void DisciplinePriestAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师AOE群体团队副本策略)
void DisciplinePriestAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师AOE群体团队副本策略)
void DisciplinePriestAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师增益Buff策略)
void DisciplinePriestBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师增益Buff策略)
void DisciplinePriestBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师增益BuffPVE策略)
void DisciplinePriestBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师增益BuffPVE策略)
void DisciplinePriestBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师增益BuffPVP策略)
void DisciplinePriestBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师增益BuffPVP策略)
void DisciplinePriestBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师增益Buff团队副本策略)
void DisciplinePriestBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师增益Buff团队副本策略)
void DisciplinePriestBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师爆发增益策略)
void DisciplinePriestBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师爆发增益策略)
void DisciplinePriestBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师爆发增益PVE策略)
void DisciplinePriestBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师爆发增益PVE策略)
void DisciplinePriestBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师爆发增益PVP策略)
void DisciplinePriestBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师爆发增益PVP策略)
void DisciplinePriestBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师爆发增益团队副本策略)
void DisciplinePriestBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师爆发增益团队副本策略)
void DisciplinePriestBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师控制(CC)策略)
void DisciplinePriestCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师控制(CC)策略)
void DisciplinePriestCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师控制(CC)PVE策略)
void DisciplinePriestCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师控制(CC)PVE策略)
void DisciplinePriestCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师控制(CC)PVP策略)
void DisciplinePriestCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师控制(CC)PVP策略)
void DisciplinePriestCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师控制(CC)团队副本策略)
void DisciplinePriestCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师控制(CC)团队副本策略)
void DisciplinePriestCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师驱散净化策略)
void DisciplinePriestCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师驱散净化策略)
void DisciplinePriestCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师驱散净化PVE策略)
void DisciplinePriestCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师驱散净化PVE策略)
void DisciplinePriestCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师驱散净化PVP策略)
void DisciplinePriestCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师驱散净化PVP策略)
void DisciplinePriestCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师驱散净化团队副本策略)
void DisciplinePriestCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitCombatTriggers(triggers);
    PriestCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师驱散净化团队副本策略)
void DisciplinePriestCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (戒律牧师策略)
void DisciplinePriestStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "protect party member",
        NextAction::array(0, new NextAction("pain suppression on party", ACTION_EMERGENCY), NULL)));

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

// 初始化非战斗阶段触发器列表 (戒律牧师策略)
void DisciplinePriestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitNonCombatTriggers(triggers);

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

// 初始化反应阶段触发器列表 (戒律牧师策略)
void DisciplinePriestStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (戒律牧师策略)
void DisciplinePriestStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师PVE策略)
void DisciplinePriestPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitCombatTriggers(triggers);
    PriestPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师PVE策略)
void DisciplinePriestPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitNonCombatTriggers(triggers);
    PriestPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (戒律牧师PVE策略)
void DisciplinePriestPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitReactionTriggers(triggers);
    PriestPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (戒律牧师PVE策略)
void DisciplinePriestPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitDeadTriggers(triggers);
    PriestPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师PVP策略)
void DisciplinePriestPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitCombatTriggers(triggers);
    PriestPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师PVP策略)
void DisciplinePriestPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitNonCombatTriggers(triggers);
    PriestPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (戒律牧师PVP策略)
void DisciplinePriestPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitReactionTriggers(triggers);
    PriestPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (戒律牧师PVP策略)
void DisciplinePriestPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitDeadTriggers(triggers);
    PriestPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师团队副本策略)
void DisciplinePriestRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitCombatTriggers(triggers);
    PriestRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师团队副本策略)
void DisciplinePriestRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitNonCombatTriggers(triggers);
    PriestRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (戒律牧师团队副本策略)
void DisciplinePriestRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitReactionTriggers(triggers);
    PriestRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (戒律牧师团队副本策略)
void DisciplinePriestRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitDeadTriggers(triggers);
    PriestRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师AOE群体策略)
void DisciplinePriestAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("prayer of mending", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("prayer of healing", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (戒律牧师AOE群体策略)
void DisciplinePriestAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师AOE群体PVE策略)
void DisciplinePriestAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师AOE群体PVE策略)
void DisciplinePriestAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师AOE群体PVP策略)
void DisciplinePriestAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师AOE群体PVP策略)
void DisciplinePriestAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师AOE群体团队副本策略)
void DisciplinePriestAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师AOE群体团队副本策略)
void DisciplinePriestAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师增益Buff策略)
void DisciplinePriestBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师增益Buff策略)
void DisciplinePriestBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师增益BuffPVE策略)
void DisciplinePriestBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师增益BuffPVE策略)
void DisciplinePriestBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师增益BuffPVP策略)
void DisciplinePriestBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师增益BuffPVP策略)
void DisciplinePriestBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师增益Buff团队副本策略)
void DisciplinePriestBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师增益Buff团队副本策略)
void DisciplinePriestBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师爆发增益策略)
void DisciplinePriestBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师爆发增益策略)
void DisciplinePriestBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师爆发增益PVE策略)
void DisciplinePriestBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师爆发增益PVE策略)
void DisciplinePriestBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师爆发增益PVP策略)
void DisciplinePriestBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师爆发增益PVP策略)
void DisciplinePriestBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师爆发增益团队副本策略)
void DisciplinePriestBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师爆发增益团队副本策略)
void DisciplinePriestBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师控制(CC)策略)
void DisciplinePriestCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师控制(CC)策略)
void DisciplinePriestCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师控制(CC)PVE策略)
void DisciplinePriestCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师控制(CC)PVE策略)
void DisciplinePriestCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师控制(CC)PVP策略)
void DisciplinePriestCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师控制(CC)PVP策略)
void DisciplinePriestCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师控制(CC)团队副本策略)
void DisciplinePriestCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师控制(CC)团队副本策略)
void DisciplinePriestCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师驱散净化策略)
void DisciplinePriestCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师驱散净化策略)
void DisciplinePriestCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师驱散净化PVE策略)
void DisciplinePriestCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师驱散净化PVE策略)
void DisciplinePriestCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师驱散净化PVP策略)
void DisciplinePriestCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师驱散净化PVP策略)
void DisciplinePriestCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师驱散净化团队副本策略)
void DisciplinePriestCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitCombatTriggers(triggers);
    PriestCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师驱散净化团队副本策略)
void DisciplinePriestCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (戒律牧师策略)
void DisciplinePriestStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "protect party member",
        NextAction::array(0, new NextAction("pain suppression on party", ACTION_EMERGENCY), NULL)));

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

// 初始化非战斗阶段触发器列表 (戒律牧师策略)
void DisciplinePriestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitNonCombatTriggers(triggers);

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

// 初始化反应阶段触发器列表 (戒律牧师策略)
void DisciplinePriestStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (戒律牧师策略)
void DisciplinePriestStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师PVE策略)
void DisciplinePriestPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitCombatTriggers(triggers);
    PriestPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师PVE策略)
void DisciplinePriestPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitNonCombatTriggers(triggers);
    PriestPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (戒律牧师PVE策略)
void DisciplinePriestPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitReactionTriggers(triggers);
    PriestPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (戒律牧师PVE策略)
void DisciplinePriestPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitDeadTriggers(triggers);
    PriestPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师PVP策略)
void DisciplinePriestPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitCombatTriggers(triggers);
    PriestPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师PVP策略)
void DisciplinePriestPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitNonCombatTriggers(triggers);
    PriestPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (戒律牧师PVP策略)
void DisciplinePriestPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitReactionTriggers(triggers);
    PriestPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (戒律牧师PVP策略)
void DisciplinePriestPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitDeadTriggers(triggers);
    PriestPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师团队副本策略)
void DisciplinePriestRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitCombatTriggers(triggers);
    PriestRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师团队副本策略)
void DisciplinePriestRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitNonCombatTriggers(triggers);
    PriestRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (戒律牧师团队副本策略)
void DisciplinePriestRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitReactionTriggers(triggers);
    PriestRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (戒律牧师团队副本策略)
void DisciplinePriestRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestStrategy::InitDeadTriggers(triggers);
    PriestRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师AOE群体策略)
void DisciplinePriestAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("prayer of mending", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("prayer of healing", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (戒律牧师AOE群体策略)
void DisciplinePriestAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师AOE群体PVE策略)
void DisciplinePriestAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师AOE群体PVE策略)
void DisciplinePriestAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师AOE群体PVP策略)
void DisciplinePriestAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师AOE群体PVP策略)
void DisciplinePriestAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师AOE群体团队副本策略)
void DisciplinePriestAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师AOE群体团队副本策略)
void DisciplinePriestAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师增益Buff策略)
void DisciplinePriestBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师增益Buff策略)
void DisciplinePriestBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师增益BuffPVE策略)
void DisciplinePriestBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师增益BuffPVE策略)
void DisciplinePriestBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师增益BuffPVP策略)
void DisciplinePriestBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师增益BuffPVP策略)
void DisciplinePriestBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师增益Buff团队副本策略)
void DisciplinePriestBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师增益Buff团队副本策略)
void DisciplinePriestBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师爆发增益策略)
void DisciplinePriestBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师爆发增益策略)
void DisciplinePriestBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师爆发增益PVE策略)
void DisciplinePriestBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师爆发增益PVE策略)
void DisciplinePriestBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师爆发增益PVP策略)
void DisciplinePriestBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师爆发增益PVP策略)
void DisciplinePriestBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师爆发增益团队副本策略)
void DisciplinePriestBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师爆发增益团队副本策略)
void DisciplinePriestBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师控制(CC)策略)
void DisciplinePriestCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师控制(CC)策略)
void DisciplinePriestCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师控制(CC)PVE策略)
void DisciplinePriestCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师控制(CC)PVE策略)
void DisciplinePriestCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师控制(CC)PVP策略)
void DisciplinePriestCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师控制(CC)PVP策略)
void DisciplinePriestCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师控制(CC)团队副本策略)
void DisciplinePriestCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师控制(CC)团队副本策略)
void DisciplinePriestCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师驱散净化策略)
void DisciplinePriestCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师驱散净化策略)
void DisciplinePriestCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师驱散净化PVE策略)
void DisciplinePriestCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师驱散净化PVE策略)
void DisciplinePriestCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师驱散净化PVP策略)
void DisciplinePriestCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师驱散净化PVP策略)
void DisciplinePriestCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (戒律牧师驱散净化团队副本策略)
void DisciplinePriestCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitCombatTriggers(triggers);
    PriestCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (戒律牧师驱散净化团队副本策略)
void DisciplinePriestCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DisciplinePriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
