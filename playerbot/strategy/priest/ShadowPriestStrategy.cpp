// 牧师 - 暗影牧师策略实现文件 (ShadowPriestStrategy.cpp)
#include "playerbot/playerbot.h"
#include "PriestMultipliers.h"
#include "ShadowPriestStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class ShadowPriestStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    ShadowPriestStrategyActionNodeFactory()
    {
        creators["dispersion"] = &dispersion;
    }

private:
    // 动作节点 dispersion：消散 -> 备选(A)动作：mana potion
    ACTION_NODE_A(dispersion, "dispersion", "mana potion");
};

// 构造函数：初始化暗影牧师策略并挂载动作节点工厂
ShadowPriestStrategy::ShadowPriestStrategy(PlayerbotAI* ai) : PriestStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<ShadowPriestStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (暗影牧师策略)
NextAction** ShadowPriestStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("mind flay", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (暗影牧师策略)
void ShadowPriestStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "mind blast",
        NextAction::array(0, new NextAction("mind blast", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "vampiric embrace",
        NextAction::array(0, new NextAction("vampiric embrace", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow word: pain",
        NextAction::array(0, new NextAction("shadow word: pain", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "devouring plague",
        NextAction::array(0, new NextAction("devouring plague", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "hex of weakness",
        NextAction::array(0, new NextAction("hex of weakness", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana",
        NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (暗影牧师策略)
void ShadowPriestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (暗影牧师策略)
void ShadowPriestStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (暗影牧师策略)
void ShadowPriestStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师PVE策略)
void ShadowPriestPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitCombatTriggers(triggers);
    PriestPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师PVE策略)
void ShadowPriestPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitNonCombatTriggers(triggers);
    PriestPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (暗影牧师PVE策略)
void ShadowPriestPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitReactionTriggers(triggers);
    PriestPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (暗影牧师PVE策略)
void ShadowPriestPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitDeadTriggers(triggers);
    PriestPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师PVP策略)
void ShadowPriestPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitCombatTriggers(triggers);
    PriestPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师PVP策略)
void ShadowPriestPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitNonCombatTriggers(triggers);
    PriestPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (暗影牧师PVP策略)
void ShadowPriestPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitReactionTriggers(triggers);
    PriestPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (暗影牧师PVP策略)
void ShadowPriestPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitDeadTriggers(triggers);
    PriestPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师团队副本策略)
void ShadowPriestRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitCombatTriggers(triggers);
    PriestRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师团队副本策略)
void ShadowPriestRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitNonCombatTriggers(triggers);
    PriestRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (暗影牧师团队副本策略)
void ShadowPriestRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitReactionTriggers(triggers);
    PriestRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (暗影牧师团队副本策略)
void ShadowPriestRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitDeadTriggers(triggers);
    PriestRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师AOE群体策略)
void ShadowPriestAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shadow word: pain on attacker",
        NextAction::array(0, new NextAction("shadow word: pain on attacker", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (暗影牧师AOE群体策略)
void ShadowPriestAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师AOE群体PVE策略)
void ShadowPriestAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师AOE群体PVE策略)
void ShadowPriestAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师AOE群体PVP策略)
void ShadowPriestAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师AOE群体PVP策略)
void ShadowPriestAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师AOE群体团队副本策略)
void ShadowPriestAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师AOE群体团队副本策略)
void ShadowPriestAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师增益Buff策略)
void ShadowPriestBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shadowform",
        NextAction::array(0, new NextAction("shadowform", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "feedback",
        NextAction::array(0, new NextAction("feedback", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (暗影牧师增益Buff策略)
void ShadowPriestBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师增益BuffPVE策略)
void ShadowPriestBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师增益BuffPVE策略)
void ShadowPriestBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师增益BuffPVP策略)
void ShadowPriestBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师增益BuffPVP策略)
void ShadowPriestBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师增益Buff团队副本策略)
void ShadowPriestBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师增益Buff团队副本策略)
void ShadowPriestBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师爆发增益策略)
void ShadowPriestBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师爆发增益策略)
void ShadowPriestBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师爆发增益PVE策略)
void ShadowPriestBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师爆发增益PVE策略)
void ShadowPriestBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师爆发增益PVP策略)
void ShadowPriestBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师爆发增益PVP策略)
void ShadowPriestBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师爆发增益团队副本策略)
void ShadowPriestBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师爆发增益团队副本策略)
void ShadowPriestBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师控制(CC)策略)
void ShadowPriestCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "silence",
        NextAction::array(0, new NextAction("silence", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "silence on enemy healer",
        NextAction::array(0, new NextAction("silence on enemy healer", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (暗影牧师控制(CC)策略)
void ShadowPriestCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师控制(CC)PVE策略)
void ShadowPriestCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师控制(CC)PVE策略)
void ShadowPriestCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师控制(CC)PVP策略)
void ShadowPriestCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师控制(CC)PVP策略)
void ShadowPriestCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师控制(CC)团队副本策略)
void ShadowPriestCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师控制(CC)团队副本策略)
void ShadowPriestCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师驱散净化策略)
void ShadowPriestCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师驱散净化策略)
void ShadowPriestCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师驱散净化PVE策略)
void ShadowPriestCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师驱散净化PVE策略)
void ShadowPriestCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师驱散净化PVP策略)
void ShadowPriestCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师驱散净化PVP策略)
void ShadowPriestCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师驱散净化团队副本策略)
void ShadowPriestCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师驱散净化团队副本策略)
void ShadowPriestCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (暗影牧师策略)
NextAction** ShadowPriestStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("mind flay", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (暗影牧师策略)
void ShadowPriestStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("shadow word: death", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "mind blast",
        NextAction::array(0, new NextAction("mind blast", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "vampiric embrace",
        NextAction::array(0, new NextAction("vampiric embrace", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow word: pain",
        NextAction::array(0, new NextAction("shadow word: pain", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "devouring plague",
        NextAction::array(0, new NextAction("devouring plague", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "hex of weakness",
        NextAction::array(0, new NextAction("hex of weakness", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "vampiric touch",
        NextAction::array(0, new NextAction("vampiric touch", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana",
        NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (暗影牧师策略)
void ShadowPriestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (暗影牧师策略)
void ShadowPriestStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (暗影牧师策略)
void ShadowPriestStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师PVE策略)
void ShadowPriestPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitCombatTriggers(triggers);
    PriestPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师PVE策略)
void ShadowPriestPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitNonCombatTriggers(triggers);
    PriestPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (暗影牧师PVE策略)
void ShadowPriestPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitReactionTriggers(triggers);
    PriestPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (暗影牧师PVE策略)
void ShadowPriestPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitDeadTriggers(triggers);
    PriestPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师PVP策略)
void ShadowPriestPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitCombatTriggers(triggers);
    PriestPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师PVP策略)
void ShadowPriestPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitNonCombatTriggers(triggers);
    PriestPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (暗影牧师PVP策略)
void ShadowPriestPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitReactionTriggers(triggers);
    PriestPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (暗影牧师PVP策略)
void ShadowPriestPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitDeadTriggers(triggers);
    PriestPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师团队副本策略)
void ShadowPriestRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitCombatTriggers(triggers);
    PriestRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师团队副本策略)
void ShadowPriestRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitNonCombatTriggers(triggers);
    PriestRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (暗影牧师团队副本策略)
void ShadowPriestRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitReactionTriggers(triggers);
    PriestRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (暗影牧师团队副本策略)
void ShadowPriestRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitDeadTriggers(triggers);
    PriestRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师AOE群体策略)
void ShadowPriestAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shadow word: pain on attacker",
        NextAction::array(0, new NextAction("shadow word: pain on attacker", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "vampiric touch on attacker",
        NextAction::array(0, new NextAction("vampiric touch on attacker", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (暗影牧师AOE群体策略)
void ShadowPriestAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师AOE群体PVE策略)
void ShadowPriestAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师AOE群体PVE策略)
void ShadowPriestAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师AOE群体PVP策略)
void ShadowPriestAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师AOE群体PVP策略)
void ShadowPriestAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师AOE群体团队副本策略)
void ShadowPriestAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师AOE群体团队副本策略)
void ShadowPriestAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师增益Buff策略)
void ShadowPriestBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shadowform",
        NextAction::array(0, new NextAction("shadowform", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "feedback",
        NextAction::array(0, new NextAction("feedback", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (暗影牧师增益Buff策略)
void ShadowPriestBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师增益BuffPVE策略)
void ShadowPriestBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师增益BuffPVE策略)
void ShadowPriestBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师增益BuffPVP策略)
void ShadowPriestBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师增益BuffPVP策略)
void ShadowPriestBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师增益Buff团队副本策略)
void ShadowPriestBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师增益Buff团队副本策略)
void ShadowPriestBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师爆发增益策略)
void ShadowPriestBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师爆发增益策略)
void ShadowPriestBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师爆发增益PVE策略)
void ShadowPriestBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师爆发增益PVE策略)
void ShadowPriestBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师爆发增益PVP策略)
void ShadowPriestBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师爆发增益PVP策略)
void ShadowPriestBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师爆发增益团队副本策略)
void ShadowPriestBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师爆发增益团队副本策略)
void ShadowPriestBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师控制(CC)策略)
void ShadowPriestCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "silence",
        NextAction::array(0, new NextAction("silence", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "silence on enemy healer",
        NextAction::array(0, new NextAction("silence on enemy healer", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (暗影牧师控制(CC)策略)
void ShadowPriestCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师控制(CC)PVE策略)
void ShadowPriestCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师控制(CC)PVE策略)
void ShadowPriestCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师控制(CC)PVP策略)
void ShadowPriestCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师控制(CC)PVP策略)
void ShadowPriestCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师控制(CC)团队副本策略)
void ShadowPriestCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师控制(CC)团队副本策略)
void ShadowPriestCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师驱散净化策略)
void ShadowPriestCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师驱散净化策略)
void ShadowPriestCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师驱散净化PVE策略)
void ShadowPriestCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师驱散净化PVE策略)
void ShadowPriestCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师驱散净化PVP策略)
void ShadowPriestCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师驱散净化PVP策略)
void ShadowPriestCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师驱散净化团队副本策略)
void ShadowPriestCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师驱散净化团队副本策略)
void ShadowPriestCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (暗影牧师策略)
NextAction** ShadowPriestStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("mind flay", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (暗影牧师策略)
void ShadowPriestStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("shadow word: death", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "mind blast",
        NextAction::array(0, new NextAction("mind blast", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "vampiric embrace",
        NextAction::array(0, new NextAction("vampiric embrace", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow word: pain",
        NextAction::array(0, new NextAction("shadow word: pain", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "devouring plague",
        NextAction::array(0, new NextAction("devouring plague", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "hex of weakness",
        NextAction::array(0, new NextAction("hex of weakness", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "vampiric touch",
        NextAction::array(0, new NextAction("vampiric touch", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana",
        NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (暗影牧师策略)
void ShadowPriestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (暗影牧师策略)
void ShadowPriestStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (暗影牧师策略)
void ShadowPriestStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PriestStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师PVE策略)
void ShadowPriestPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitCombatTriggers(triggers);
    PriestPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师PVE策略)
void ShadowPriestPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitNonCombatTriggers(triggers);
    PriestPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (暗影牧师PVE策略)
void ShadowPriestPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitReactionTriggers(triggers);
    PriestPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (暗影牧师PVE策略)
void ShadowPriestPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitDeadTriggers(triggers);
    PriestPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师PVP策略)
void ShadowPriestPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitCombatTriggers(triggers);
    PriestPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师PVP策略)
void ShadowPriestPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitNonCombatTriggers(triggers);
    PriestPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (暗影牧师PVP策略)
void ShadowPriestPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitReactionTriggers(triggers);
    PriestPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (暗影牧师PVP策略)
void ShadowPriestPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitDeadTriggers(triggers);
    PriestPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师团队副本策略)
void ShadowPriestRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitCombatTriggers(triggers);
    PriestRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师团队副本策略)
void ShadowPriestRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitNonCombatTriggers(triggers);
    PriestRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (暗影牧师团队副本策略)
void ShadowPriestRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitReactionTriggers(triggers);
    PriestRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (暗影牧师团队副本策略)
void ShadowPriestRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestStrategy::InitDeadTriggers(triggers);
    PriestRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师AOE群体策略)
void ShadowPriestAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shadow word: pain on attacker",
        NextAction::array(0, new NextAction("shadow word: pain on attacker", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "vampiric touch on attacker",
        NextAction::array(0, new NextAction("vampiric touch on attacker", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (暗影牧师AOE群体策略)
void ShadowPriestAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师AOE群体PVE策略)
void ShadowPriestAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师AOE群体PVE策略)
void ShadowPriestAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师AOE群体PVP策略)
void ShadowPriestAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师AOE群体PVP策略)
void ShadowPriestAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师AOE群体团队副本策略)
void ShadowPriestAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师AOE群体团队副本策略)
void ShadowPriestAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestAoeStrategy::InitNonCombatTriggers(triggers);
    PriestAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师增益Buff策略)
void ShadowPriestBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shadowform",
        NextAction::array(0, new NextAction("shadowform", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "feedback",
        NextAction::array(0, new NextAction("feedback", ACTION_HIGH), NULL)));

    /*
    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("dispersion", ACTION_EMERGENCY + 5), NULL)));
    */
}

// 初始化非战斗阶段触发器列表 (暗影牧师增益Buff策略)
void ShadowPriestBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师增益BuffPVE策略)
void ShadowPriestBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师增益BuffPVE策略)
void ShadowPriestBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师增益BuffPVP策略)
void ShadowPriestBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师增益BuffPVP策略)
void ShadowPriestBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师增益Buff团队副本策略)
void ShadowPriestBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师增益Buff团队副本策略)
void ShadowPriestBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBuffStrategy::InitNonCombatTriggers(triggers);
    PriestBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师爆发增益策略)
void ShadowPriestBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师爆发增益策略)
void ShadowPriestBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师爆发增益PVE策略)
void ShadowPriestBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师爆发增益PVE策略)
void ShadowPriestBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师爆发增益PVP策略)
void ShadowPriestBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师爆发增益PVP策略)
void ShadowPriestBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师爆发增益团队副本策略)
void ShadowPriestBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师爆发增益团队副本策略)
void ShadowPriestBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestBoostStrategy::InitNonCombatTriggers(triggers);
    PriestBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师控制(CC)策略)
void ShadowPriestCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "silence",
        NextAction::array(0, new NextAction("silence", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "silence on enemy healer",
        NextAction::array(0, new NextAction("silence on enemy healer", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (暗影牧师控制(CC)策略)
void ShadowPriestCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师控制(CC)PVE策略)
void ShadowPriestCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师控制(CC)PVE策略)
void ShadowPriestCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师控制(CC)PVP策略)
void ShadowPriestCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师控制(CC)PVP策略)
void ShadowPriestCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师控制(CC)团队副本策略)
void ShadowPriestCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitCombatTriggers(triggers);
    PriestCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师控制(CC)团队副本策略)
void ShadowPriestCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCcStrategy::InitNonCombatTriggers(triggers);
    PriestCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师驱散净化策略)
void ShadowPriestCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师驱散净化策略)
void ShadowPriestCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师驱散净化PVE策略)
void ShadowPriestCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师驱散净化PVE策略)
void ShadowPriestCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师驱散净化PVP策略)
void ShadowPriestCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师驱散净化PVP策略)
void ShadowPriestCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (暗影牧师驱散净化团队副本策略)
void ShadowPriestCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitCombatTriggers(triggers);
    PriestCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (暗影牧师驱散净化团队副本策略)
void ShadowPriestCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShadowPriestCureStrategy::InitNonCombatTriggers(triggers);
    PriestCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
