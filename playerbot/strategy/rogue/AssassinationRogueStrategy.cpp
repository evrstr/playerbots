// 潜行者 - 刺杀潜行者策略实现文件 (AssassinationRogueStrategy.cpp)

#include "playerbot/playerbot.h"
#include "AssassinationRogueStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class AssassinationRogueStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    AssassinationRogueStrategyActionNodeFactory()
    {
        creators["mutilate front"] = &mutilate_front;
        creators["mutilate back"] = &mutilate_back;
        creators["mutilate"] = &mutilate;
        creators["backstab"] = &backstab;
    }

private:
    // 动作节点 mutilate_front：毁伤 -> 备选(A)动作：邪恶攻击
    ACTION_NODE_A(mutilate_front, "mutilate", "sinister strike");

    // 动作节点 mutilate_back：毁伤 -> 备选(A)动作：背刺
    ACTION_NODE_A(mutilate_back, "mutilate", "backstab");

    // 动作节点 mutilate：毁伤 -> 备选(A)动作：邪恶攻击
    ACTION_NODE_A(mutilate, "mutilate", "sinister strike");

    // 动作节点 backstab：背刺 -> 备选(A)动作：邪恶攻击
    ACTION_NODE_A(backstab, "backstab", "sinister strike");
};

// 构造函数：初始化刺杀潜行者策略并挂载动作节点工厂
AssassinationRogueStrategy::AssassinationRogueStrategy(PlayerbotAI* ai) : RogueStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<AssassinationRogueStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (刺杀潜行者策略)
void AssassinationRogueStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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
        "behind target",
        NextAction::array(0, new NextAction("mutilate back", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("mutilate front", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者策略)
void AssassinationRogueStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (刺杀潜行者策略)
void AssassinationRogueStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (刺杀潜行者策略)
void AssassinationRogueStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者PVE策略)
void AssassinationRoguePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitCombatTriggers(triggers);
    RoguePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者PVE策略)
void AssassinationRoguePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (刺杀潜行者PVE策略)
void AssassinationRoguePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitReactionTriggers(triggers);
    RoguePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (刺杀潜行者PVE策略)
void AssassinationRoguePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitDeadTriggers(triggers);
    RoguePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者PVP策略)
void AssassinationRoguePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitCombatTriggers(triggers);
    RoguePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者PVP策略)
void AssassinationRoguePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (刺杀潜行者PVP策略)
void AssassinationRoguePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitReactionTriggers(triggers);
    RoguePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (刺杀潜行者PVP策略)
void AssassinationRoguePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitDeadTriggers(triggers);
    RoguePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者团队副本策略)
void AssassinationRogueRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitCombatTriggers(triggers);
    RogueRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者团队副本策略)
void AssassinationRogueRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitNonCombatTriggers(triggers);
    RogueRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (刺杀潜行者团队副本策略)
void AssassinationRogueRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitReactionTriggers(triggers);
    RogueRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (刺杀潜行者团队副本策略)
void AssassinationRogueRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitDeadTriggers(triggers);
    RogueRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者AOE群体策略)
void AssassinationRogueAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者AOE群体策略)
void AssassinationRogueAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者AOE群体PVE策略)
void AssassinationRogueAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者AOE群体PVE策略)
void AssassinationRogueAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者AOE群体PVP策略)
void AssassinationRogueAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者AOE群体PVP策略)
void AssassinationRogueAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者AOE群体团队副本策略)
void AssassinationRogueAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者AOE群体团队副本策略)
void AssassinationRogueAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者增益Buff策略)
void AssassinationRogueBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者增益Buff策略)
void AssassinationRogueBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者增益BuffPVE策略)
void AssassinationRogueBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者增益BuffPVE策略)
void AssassinationRogueBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者增益BuffPVP策略)
void AssassinationRogueBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者增益BuffPVP策略)
void AssassinationRogueBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者增益Buff团队副本策略)
void AssassinationRogueBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者增益Buff团队副本策略)
void AssassinationRogueBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者爆发增益策略)
void AssassinationRogueBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("cold blood", ACTION_HIGH + 5), NULL)));
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者爆发增益策略)
void AssassinationRogueBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者爆发增益PVE策略)
void AssassinationRogueBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者爆发增益PVE策略)
void AssassinationRogueBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者爆发增益PVP策略)
void AssassinationRogueBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者爆发增益PVP策略)
void AssassinationRogueBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者爆发增益团队副本策略)
void AssassinationRogueBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者爆发增益团队副本策略)
void AssassinationRogueBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者控制(CC)策略)
void AssassinationRogueCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者控制(CC)策略)
void AssassinationRogueCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者控制(CC)PVE策略)
void AssassinationRogueCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者控制(CC)PVE策略)
void AssassinationRogueCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者控制(CC)PVP策略)
void AssassinationRogueCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者控制(CC)PVP策略)
void AssassinationRogueCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者控制(CC)团队副本策略)
void AssassinationRogueCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者控制(CC)团队副本策略)
void AssassinationRogueCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者潜行策略)
void AssassinationRogueStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者潜行策略)
void AssassinationRogueStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者潜行PVE策略)
void AssassinationRogueStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者潜行PVE策略)
void AssassinationRogueStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者潜行PVP策略)
void AssassinationRogueStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者潜行PVP策略)
void AssassinationRogueStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者潜行团队副本策略)
void AssassinationRogueStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者潜行团队副本策略)
void AssassinationRogueStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者毒药策略)
void AssassinationRoguePoisonsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者毒药策略)
void AssassinationRoguePoisonsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者毒药PVE策略)
void AssassinationRoguePoisonsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者毒药PVE策略)
void AssassinationRoguePoisonsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者毒药PVP策略)
void AssassinationRoguePoisonsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者毒药PVP策略)
void AssassinationRoguePoisonsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者毒药团队副本策略)
void AssassinationRoguePoisonsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者毒药团队副本策略)
void AssassinationRoguePoisonsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (刺杀潜行者策略)
void AssassinationRogueStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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
        "behind target",
        NextAction::array(0, new NextAction("mutilate back", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("mutilate front", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者策略)
void AssassinationRogueStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (刺杀潜行者策略)
void AssassinationRogueStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (刺杀潜行者策略)
void AssassinationRogueStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者PVE策略)
void AssassinationRoguePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitCombatTriggers(triggers);
    RoguePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者PVE策略)
void AssassinationRoguePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (刺杀潜行者PVE策略)
void AssassinationRoguePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitReactionTriggers(triggers);
    RoguePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (刺杀潜行者PVE策略)
void AssassinationRoguePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitDeadTriggers(triggers);
    RoguePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者PVP策略)
void AssassinationRoguePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitCombatTriggers(triggers);
    RoguePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者PVP策略)
void AssassinationRoguePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (刺杀潜行者PVP策略)
void AssassinationRoguePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitReactionTriggers(triggers);
    RoguePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (刺杀潜行者PVP策略)
void AssassinationRoguePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitDeadTriggers(triggers);
    RoguePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者团队副本策略)
void AssassinationRogueRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitCombatTriggers(triggers);
    RogueRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者团队副本策略)
void AssassinationRogueRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitNonCombatTriggers(triggers);
    RogueRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (刺杀潜行者团队副本策略)
void AssassinationRogueRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitReactionTriggers(triggers);
    RogueRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (刺杀潜行者团队副本策略)
void AssassinationRogueRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitDeadTriggers(triggers);
    RogueRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者AOE群体策略)
void AssassinationRogueAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者AOE群体策略)
void AssassinationRogueAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者AOE群体PVE策略)
void AssassinationRogueAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者AOE群体PVE策略)
void AssassinationRogueAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者AOE群体PVP策略)
void AssassinationRogueAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者AOE群体PVP策略)
void AssassinationRogueAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者AOE群体团队副本策略)
void AssassinationRogueAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者AOE群体团队副本策略)
void AssassinationRogueAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者增益Buff策略)
void AssassinationRogueBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者增益Buff策略)
void AssassinationRogueBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者增益BuffPVE策略)
void AssassinationRogueBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者增益BuffPVE策略)
void AssassinationRogueBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者增益BuffPVP策略)
void AssassinationRogueBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者增益BuffPVP策略)
void AssassinationRogueBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者增益Buff团队副本策略)
void AssassinationRogueBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者增益Buff团队副本策略)
void AssassinationRogueBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者爆发增益策略)
void AssassinationRogueBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("cold blood", ACTION_HIGH + 5), NULL)));
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者爆发增益策略)
void AssassinationRogueBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者爆发增益PVE策略)
void AssassinationRogueBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者爆发增益PVE策略)
void AssassinationRogueBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者爆发增益PVP策略)
void AssassinationRogueBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者爆发增益PVP策略)
void AssassinationRogueBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者爆发增益团队副本策略)
void AssassinationRogueBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者爆发增益团队副本策略)
void AssassinationRogueBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者控制(CC)策略)
void AssassinationRogueCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者控制(CC)策略)
void AssassinationRogueCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者控制(CC)PVE策略)
void AssassinationRogueCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者控制(CC)PVE策略)
void AssassinationRogueCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者控制(CC)PVP策略)
void AssassinationRogueCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者控制(CC)PVP策略)
void AssassinationRogueCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者控制(CC)团队副本策略)
void AssassinationRogueCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者控制(CC)团队副本策略)
void AssassinationRogueCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者潜行策略)
void AssassinationRogueStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者潜行策略)
void AssassinationRogueStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者潜行PVE策略)
void AssassinationRogueStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者潜行PVE策略)
void AssassinationRogueStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者潜行PVP策略)
void AssassinationRogueStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者潜行PVP策略)
void AssassinationRogueStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者潜行团队副本策略)
void AssassinationRogueStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者潜行团队副本策略)
void AssassinationRogueStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者毒药策略)
void AssassinationRoguePoisonsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者毒药策略)
void AssassinationRoguePoisonsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者毒药PVE策略)
void AssassinationRoguePoisonsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者毒药PVE策略)
void AssassinationRoguePoisonsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者毒药PVP策略)
void AssassinationRoguePoisonsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者毒药PVP策略)
void AssassinationRoguePoisonsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者毒药团队副本策略)
void AssassinationRoguePoisonsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者毒药团队副本策略)
void AssassinationRoguePoisonsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (刺杀潜行者策略)
void AssassinationRogueStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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
        "behind target",
        NextAction::array(0, new NextAction("mutilate back", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("mutilate front", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者策略)
void AssassinationRogueStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (刺杀潜行者策略)
void AssassinationRogueStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (刺杀潜行者策略)
void AssassinationRogueStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者PVE策略)
void AssassinationRoguePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitCombatTriggers(triggers);
    RoguePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者PVE策略)
void AssassinationRoguePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (刺杀潜行者PVE策略)
void AssassinationRoguePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitReactionTriggers(triggers);
    RoguePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (刺杀潜行者PVE策略)
void AssassinationRoguePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitDeadTriggers(triggers);
    RoguePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者PVP策略)
void AssassinationRoguePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitCombatTriggers(triggers);
    RoguePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者PVP策略)
void AssassinationRoguePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitNonCombatTriggers(triggers);
    RoguePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (刺杀潜行者PVP策略)
void AssassinationRoguePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitReactionTriggers(triggers);
    RoguePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (刺杀潜行者PVP策略)
void AssassinationRoguePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitDeadTriggers(triggers);
    RoguePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者团队副本策略)
void AssassinationRogueRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitCombatTriggers(triggers);
    RogueRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者团队副本策略)
void AssassinationRogueRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitNonCombatTriggers(triggers);
    RogueRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (刺杀潜行者团队副本策略)
void AssassinationRogueRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitReactionTriggers(triggers);
    RogueRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (刺杀潜行者团队副本策略)
void AssassinationRogueRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStrategy::InitDeadTriggers(triggers);
    RogueRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者AOE群体策略)
void AssassinationRogueAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者AOE群体策略)
void AssassinationRogueAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者AOE群体PVE策略)
void AssassinationRogueAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者AOE群体PVE策略)
void AssassinationRogueAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者AOE群体PVP策略)
void AssassinationRogueAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者AOE群体PVP策略)
void AssassinationRogueAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者AOE群体团队副本策略)
void AssassinationRogueAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者AOE群体团队副本策略)
void AssassinationRogueAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueAoeStrategy::InitNonCombatTriggers(triggers);
    RogueAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者增益Buff策略)
void AssassinationRogueBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者增益Buff策略)
void AssassinationRogueBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者增益BuffPVE策略)
void AssassinationRogueBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者增益BuffPVE策略)
void AssassinationRogueBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者增益BuffPVP策略)
void AssassinationRogueBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者增益BuffPVP策略)
void AssassinationRogueBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者增益Buff团队副本策略)
void AssassinationRogueBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者增益Buff团队副本策略)
void AssassinationRogueBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBuffStrategy::InitNonCombatTriggers(triggers);
    RogueBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者爆发增益策略)
void AssassinationRogueBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("cold blood", ACTION_HIGH + 5), NULL)));
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者爆发增益策略)
void AssassinationRogueBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者爆发增益PVE策略)
void AssassinationRogueBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者爆发增益PVE策略)
void AssassinationRogueBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者爆发增益PVP策略)
void AssassinationRogueBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者爆发增益PVP策略)
void AssassinationRogueBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者爆发增益团队副本策略)
void AssassinationRogueBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者爆发增益团队副本策略)
void AssassinationRogueBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueBoostStrategy::InitNonCombatTriggers(triggers);
    RogueBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者控制(CC)策略)
void AssassinationRogueCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者控制(CC)策略)
void AssassinationRogueCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者控制(CC)PVE策略)
void AssassinationRogueCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者控制(CC)PVE策略)
void AssassinationRogueCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者控制(CC)PVP策略)
void AssassinationRogueCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者控制(CC)PVP策略)
void AssassinationRogueCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者控制(CC)团队副本策略)
void AssassinationRogueCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitCombatTriggers(triggers);
    RogueCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者控制(CC)团队副本策略)
void AssassinationRogueCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueCcStrategy::InitNonCombatTriggers(triggers);
    RogueCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者潜行策略)
void AssassinationRogueStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者潜行策略)
void AssassinationRogueStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RogueStealthStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者潜行PVE策略)
void AssassinationRogueStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者潜行PVE策略)
void AssassinationRogueStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者潜行PVP策略)
void AssassinationRogueStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者潜行PVP策略)
void AssassinationRogueStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者潜行团队副本策略)
void AssassinationRogueStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者潜行团队副本策略)
void AssassinationRogueStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRogueStealthStrategy::InitNonCombatTriggers(triggers);
    RogueStealthRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者毒药策略)
void AssassinationRoguePoisonsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者毒药策略)
void AssassinationRoguePoisonsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RoguePoisonsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者毒药PVE策略)
void AssassinationRoguePoisonsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者毒药PVE策略)
void AssassinationRoguePoisonsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者毒药PVP策略)
void AssassinationRoguePoisonsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者毒药PVP策略)
void AssassinationRoguePoisonsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (刺杀潜行者毒药团队副本策略)
void AssassinationRoguePoisonsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (刺杀潜行者毒药团队副本策略)
void AssassinationRoguePoisonsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AssassinationRoguePoisonsStrategy::InitNonCombatTriggers(triggers);
    RoguePoisonsRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
