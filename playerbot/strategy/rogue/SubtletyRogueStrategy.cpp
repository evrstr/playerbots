// 潜行者 - 敏锐潜行者策略实现文件 (SubtletyRogueStrategy.cpp)

#include "playerbot/playerbot.h"
#include "SubtletyRogueStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class SubtletyRogueStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    SubtletyRogueStrategyActionNodeFactory()
    {
        creators["hemorrhage back"] = &hemorrhage_back;
        creators["hemorrhage front"] = &hemorrhage_front;
        creators["hemorrhage"] = &hemorrhage;
        creators["backstab"] = &backstab;
    }

private:
    // 动作节点 hemorrhage_back：背刺 -> 备选(A)动作：出血
    ACTION_NODE_A(hemorrhage_back, "backstab", "hemorrhage");

    // 动作节点 hemorrhage_front：出血 -> 备选(A)动作：邪恶攻击
    ACTION_NODE_A(hemorrhage_front, "hemorrhage", "sinister strike");

    // 动作节点 hemorrhage：出血 -> 备选(A)动作：邪恶攻击
    ACTION_NODE_A(hemorrhage, "hemorrhage", "sinister strike");

    // 动作节点 backstab：背刺 -> 备选(A)动作：邪恶攻击
    ACTION_NODE_A(backstab, "backstab", "sinister strike");
};

// 构造函数：初始化敏锐潜行者策略并挂载动作节点工厂
SubtletyRogueStrategy::SubtletyRogueStrategy(PlayerbotAI* ai) : RogueStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<SubtletyRogueStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (敏锐潜行者策略)
void SubtletyRogueStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "eviscerate",
        NextAction::array(0, new NextAction("eviscerate", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "slice and dice",
        NextAction::array(0, new NextAction("slice and dice", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "3 combo",
        NextAction::array(0, new NextAction("rupture", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("ghostly strike", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("hemorrhage back", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("hemorrhage front", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者策略)
void SubtletyRogueStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (敏锐潜行者策略)
void SubtletyRogueStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (敏锐潜行者策略)
void SubtletyRogueStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者PVE策略)
void SubtletyRoguePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitCombatTriggers(triggers);
    RoguePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者PVE策略)
void SubtletyRoguePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (敏锐潜行者PVE策略)
void SubtletyRoguePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitReactionTriggers(triggers);
    RoguePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (敏锐潜行者PVE策略)
void SubtletyRoguePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitDeadTriggers(triggers);
    RoguePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者PVP策略)
void SubtletyRoguePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitCombatTriggers(triggers);
    RoguePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者PVP策略)
void SubtletyRoguePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (敏锐潜行者PVP策略)
void SubtletyRoguePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitReactionTriggers(triggers);
    RoguePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (敏锐潜行者PVP策略)
void SubtletyRoguePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitDeadTriggers(triggers);
    RoguePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者团队副本策略)
void SubtletyRogueRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitCombatTriggers(triggers);
    RogueRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者团队副本策略)
void SubtletyRogueRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitNonCombatTriggers(triggers);
    RogueRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (敏锐潜行者团队副本策略)
void SubtletyRogueRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitReactionTriggers(triggers);
    RogueRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (敏锐潜行者团队副本策略)
void SubtletyRogueRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitDeadTriggers(triggers);
    RogueRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者AOE群体策略)
void SubtletyRogueAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者AOE群体策略)
void SubtletyRogueAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者AOE群体PVE策略)
void SubtletyRogueAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者AOE群体PVE策略)
void SubtletyRogueAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者AOE群体PVP策略)
void SubtletyRogueAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者AOE群体PVP策略)
void SubtletyRogueAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者AOE群体团队副本策略)
void SubtletyRogueAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者AOE群体团队副本策略)
void SubtletyRogueAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者增益Buff策略)
void SubtletyRogueBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者增益Buff策略)
void SubtletyRogueBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者增益BuffPVE策略)
void SubtletyRogueBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者增益BuffPVE策略)
void SubtletyRogueBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者增益BuffPVP策略)
void SubtletyRogueBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者增益BuffPVP策略)
void SubtletyRogueBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者增益Buff团队副本策略)
void SubtletyRogueBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者增益Buff团队副本策略)
void SubtletyRogueBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者爆发增益策略)
void SubtletyRogueBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("preparation", ACTION_HIGH + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者爆发增益策略)
void SubtletyRogueBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者爆发增益PVE策略)
void SubtletyRogueBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者爆发增益PVE策略)
void SubtletyRogueBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者爆发增益PVP策略)
void SubtletyRogueBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者爆发增益PVP策略)
void SubtletyRogueBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者爆发增益团队副本策略)
void SubtletyRogueBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者爆发增益团队副本策略)
void SubtletyRogueBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者控制(CC)策略)
void SubtletyRogueCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者控制(CC)策略)
void SubtletyRogueCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者控制(CC)PVE策略)
void SubtletyRogueCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者控制(CC)PVE策略)
void SubtletyRogueCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者控制(CC)PVP策略)
void SubtletyRogueCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者控制(CC)PVP策略)
void SubtletyRogueCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者控制(CC)团队副本策略)
void SubtletyRogueCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者控制(CC)团队副本策略)
void SubtletyRogueCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者潜行策略)
void SubtletyRogueStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("premeditation", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者潜行策略)
void SubtletyRogueStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者潜行PVE策略)
void SubtletyRogueStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者潜行PVE策略)
void SubtletyRogueStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者潜行PVP策略)
void SubtletyRogueStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者潜行PVP策略)
void SubtletyRogueStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者潜行团队副本策略)
void SubtletyRogueStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者潜行团队副本策略)
void SubtletyRogueStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者毒药策略)
void SubtletyRoguePoisonsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者毒药策略)
void SubtletyRoguePoisonsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者毒药PVE策略)
void SubtletyRoguePoisonsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者毒药PVE策略)
void SubtletyRoguePoisonsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者毒药PVP策略)
void SubtletyRoguePoisonsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者毒药PVP策略)
void SubtletyRoguePoisonsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者毒药团队副本策略)
void SubtletyRoguePoisonsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者毒药团队副本策略)
void SubtletyRoguePoisonsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (敏锐潜行者策略)
void SubtletyRogueStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("shadowstep", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "eviscerate",
        NextAction::array(0, new NextAction("eviscerate", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "slice and dice",
        NextAction::array(0, new NextAction("slice and dice", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "3 combo",
        NextAction::array(0, new NextAction("rupture", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("ghostly strike", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("hemorrhage back", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("hemorrhage front", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者策略)
void SubtletyRogueStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (敏锐潜行者策略)
void SubtletyRogueStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (敏锐潜行者策略)
void SubtletyRogueStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者PVE策略)
void SubtletyRoguePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitCombatTriggers(triggers);
    RoguePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者PVE策略)
void SubtletyRoguePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (敏锐潜行者PVE策略)
void SubtletyRoguePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitReactionTriggers(triggers);
    RoguePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (敏锐潜行者PVE策略)
void SubtletyRoguePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitDeadTriggers(triggers);
    RoguePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者PVP策略)
void SubtletyRoguePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitCombatTriggers(triggers);
    RoguePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者PVP策略)
void SubtletyRoguePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (敏锐潜行者PVP策略)
void SubtletyRoguePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitReactionTriggers(triggers);
    RoguePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (敏锐潜行者PVP策略)
void SubtletyRoguePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitDeadTriggers(triggers);
    RoguePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者团队副本策略)
void SubtletyRogueRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitCombatTriggers(triggers);
    RogueRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者团队副本策略)
void SubtletyRogueRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitNonCombatTriggers(triggers);
    RogueRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (敏锐潜行者团队副本策略)
void SubtletyRogueRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitReactionTriggers(triggers);
    RogueRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (敏锐潜行者团队副本策略)
void SubtletyRogueRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitDeadTriggers(triggers);
    RogueRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者AOE群体策略)
void SubtletyRogueAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者AOE群体策略)
void SubtletyRogueAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者AOE群体PVE策略)
void SubtletyRogueAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者AOE群体PVE策略)
void SubtletyRogueAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者AOE群体PVP策略)
void SubtletyRogueAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者AOE群体PVP策略)
void SubtletyRogueAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者AOE群体团队副本策略)
void SubtletyRogueAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者AOE群体团队副本策略)
void SubtletyRogueAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者增益Buff策略)
void SubtletyRogueBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者增益Buff策略)
void SubtletyRogueBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者增益BuffPVE策略)
void SubtletyRogueBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者增益BuffPVE策略)
void SubtletyRogueBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者增益BuffPVP策略)
void SubtletyRogueBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者增益BuffPVP策略)
void SubtletyRogueBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者增益Buff团队副本策略)
void SubtletyRogueBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者增益Buff团队副本策略)
void SubtletyRogueBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者爆发增益策略)
void SubtletyRogueBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("preparation", ACTION_HIGH + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者爆发增益策略)
void SubtletyRogueBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者爆发增益PVE策略)
void SubtletyRogueBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者爆发增益PVE策略)
void SubtletyRogueBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者爆发增益PVP策略)
void SubtletyRogueBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者爆发增益PVP策略)
void SubtletyRogueBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者爆发增益团队副本策略)
void SubtletyRogueBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者爆发增益团队副本策略)
void SubtletyRogueBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者控制(CC)策略)
void SubtletyRogueCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者控制(CC)策略)
void SubtletyRogueCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者控制(CC)PVE策略)
void SubtletyRogueCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者控制(CC)PVE策略)
void SubtletyRogueCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者控制(CC)PVP策略)
void SubtletyRogueCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者控制(CC)PVP策略)
void SubtletyRogueCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者控制(CC)团队副本策略)
void SubtletyRogueCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者控制(CC)团队副本策略)
void SubtletyRogueCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者潜行策略)
void SubtletyRogueStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("shadowstep", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("premeditation", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者潜行策略)
void SubtletyRogueStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者潜行PVE策略)
void SubtletyRogueStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者潜行PVE策略)
void SubtletyRogueStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者潜行PVP策略)
void SubtletyRogueStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者潜行PVP策略)
void SubtletyRogueStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者潜行团队副本策略)
void SubtletyRogueStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者潜行团队副本策略)
void SubtletyRogueStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者毒药策略)
void SubtletyRoguePoisonsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者毒药策略)
void SubtletyRoguePoisonsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者毒药PVE策略)
void SubtletyRoguePoisonsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者毒药PVE策略)
void SubtletyRoguePoisonsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者毒药PVP策略)
void SubtletyRoguePoisonsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者毒药PVP策略)
void SubtletyRoguePoisonsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者毒药团队副本策略)
void SubtletyRoguePoisonsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者毒药团队副本策略)
void SubtletyRoguePoisonsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (敏锐潜行者策略)
void SubtletyRogueStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("shadowstep", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "eviscerate",
        NextAction::array(0, new NextAction("eviscerate", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "slice and dice",
        NextAction::array(0, new NextAction("slice and dice", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "3 combo",
        NextAction::array(0, new NextAction("rupture", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("ghostly strike", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("hemorrhage back", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("hemorrhage front", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者策略)
void SubtletyRogueStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (敏锐潜行者策略)
void SubtletyRogueStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (敏锐潜行者策略)
void SubtletyRogueStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者PVE策略)
void SubtletyRoguePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitCombatTriggers(triggers);
    RoguePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者PVE策略)
void SubtletyRoguePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (敏锐潜行者PVE策略)
void SubtletyRoguePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitReactionTriggers(triggers);
    RoguePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (敏锐潜行者PVE策略)
void SubtletyRoguePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitDeadTriggers(triggers);
    RoguePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者PVP策略)
void SubtletyRoguePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitCombatTriggers(triggers);
    RoguePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者PVP策略)
void SubtletyRoguePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (敏锐潜行者PVP策略)
void SubtletyRoguePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitReactionTriggers(triggers);
    RoguePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (敏锐潜行者PVP策略)
void SubtletyRoguePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitDeadTriggers(triggers);
    RoguePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者团队副本策略)
void SubtletyRogueRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitCombatTriggers(triggers);
    RogueRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者团队副本策略)
void SubtletyRogueRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitNonCombatTriggers(triggers);
    RogueRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (敏锐潜行者团队副本策略)
void SubtletyRogueRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitReactionTriggers(triggers);
    RogueRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (敏锐潜行者团队副本策略)
void SubtletyRogueRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStrategy::InitDeadTriggers(triggers);
    RogueRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者AOE群体策略)
void SubtletyRogueAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者AOE群体策略)
void SubtletyRogueAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者AOE群体PVE策略)
void SubtletyRogueAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者AOE群体PVE策略)
void SubtletyRogueAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者AOE群体PVP策略)
void SubtletyRogueAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者AOE群体PVP策略)
void SubtletyRogueAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者AOE群体团队副本策略)
void SubtletyRogueAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者AOE群体团队副本策略)
void SubtletyRogueAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者增益Buff策略)
void SubtletyRogueBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者增益Buff策略)
void SubtletyRogueBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者增益BuffPVE策略)
void SubtletyRogueBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者增益BuffPVE策略)
void SubtletyRogueBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者增益BuffPVP策略)
void SubtletyRogueBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者增益BuffPVP策略)
void SubtletyRogueBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者增益Buff团队副本策略)
void SubtletyRogueBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者增益Buff团队副本策略)
void SubtletyRogueBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者爆发增益策略)
void SubtletyRogueBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("preparation", ACTION_HIGH + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者爆发增益策略)
void SubtletyRogueBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者爆发增益PVE策略)
void SubtletyRogueBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者爆发增益PVE策略)
void SubtletyRogueBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者爆发增益PVP策略)
void SubtletyRogueBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者爆发增益PVP策略)
void SubtletyRogueBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者爆发增益团队副本策略)
void SubtletyRogueBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者爆发增益团队副本策略)
void SubtletyRogueBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者控制(CC)策略)
void SubtletyRogueCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者控制(CC)策略)
void SubtletyRogueCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者控制(CC)PVE策略)
void SubtletyRogueCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者控制(CC)PVE策略)
void SubtletyRogueCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者控制(CC)PVP策略)
void SubtletyRogueCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者控制(CC)PVP策略)
void SubtletyRogueCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者控制(CC)团队副本策略)
void SubtletyRogueCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者控制(CC)团队副本策略)
void SubtletyRogueCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者潜行策略)
void SubtletyRogueStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("shadowstep", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("premeditation", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者潜行策略)
void SubtletyRogueStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者潜行PVE策略)
void SubtletyRogueStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者潜行PVE策略)
void SubtletyRogueStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者潜行PVP策略)
void SubtletyRogueStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者潜行PVP策略)
void SubtletyRogueStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者潜行团队副本策略)
void SubtletyRogueStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者潜行团队副本策略)
void SubtletyRogueStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者毒药策略)
void SubtletyRoguePoisonsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者毒药策略)
void SubtletyRoguePoisonsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者毒药PVE策略)
void SubtletyRoguePoisonsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者毒药PVE策略)
void SubtletyRoguePoisonsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者毒药PVP策略)
void SubtletyRoguePoisonsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者毒药PVP策略)
void SubtletyRoguePoisonsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (敏锐潜行者毒药团队副本策略)
void SubtletyRoguePoisonsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (敏锐潜行者毒药团队副本策略)
void SubtletyRoguePoisonsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    SubtletyRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
