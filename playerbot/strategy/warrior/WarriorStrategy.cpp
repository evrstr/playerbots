// 战士 - 战士策略实现文件 (WarriorStrategy.cpp)

#include "playerbot/playerbot.h"
#include "WarriorStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class WarriorStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    WarriorStrategyActionNodeFactory()
    {
        /*
        // Stance requirements
        // battle only
        creators["charge"] = &charge;
        creators["mocking blow"] = &mocking_blow;
        creators["overpower"] = &overpower;
        creators["sweeping strikes"] = &sweeping strikes;

        // berserker only
        creators["whirlwind"] = &whirlwind;
        creators["berserker rage"] = &berserker_rage;
        creators["recklessness"] = &recklessness;
        creators["pummel"] = &pummel;
        creators["intercept"] = &intercept;

        // defensive only
        creators["taunt"] = &taunt;
        creators["revenge"] = &revenge;
        creators["shield block"] = &shield_block;
        creators["disarm"] = &disarm;
        creators["shield wall"] = &shield_wall;
        creators["intervene"] = &intervene;
        */

        creators["berserker rage"] = &berserker_rage;
    }

private:
    /*
    // Stance requirements
    ACTION_NODE_P(charge, "charge", "battle stance");

    ACTION_NODE_P(mocking_blow, "mocking blow", "battle stance");

    ACTION_NODE_P(overpower, "overpower", "battle stance");

    ACTION_NODE_P(sweeping strikes, "sweeping strikes", "battle stance");

    ACTION_NODE_P(whirlwind, "whirlwind", "berserker stance");

    ACTION_NODE_P(berserker_rage, "berserker rage", "berserker stance");

    ACTION_NODE_P(recklessness, "recklessness", "berserker stance");

    ACTION_NODE_P(pummel, "pummel", "berserker stance");

    ACTION_NODE_P(intercept, "intercept", "berserker stance");

    ACTION_NODE_P(taunt, "taunt", "defensive stance");

    ACTION_NODE_P(revenge, "revenge", "defensive stance");

    ACTION_NODE_P(shield_block, "shield block", "defensive stance");

    ACTION_NODE_P(disarm, "disarm", "defensive stance");

    ACTION_NODE_P(shield_wall, "shield wall", "defensive stance");

    ACTION_NODE_P(intervene, "intervene", "defensive stance");

    */

    // 动作节点 berserker_rage：狂暴之怒 -> 前置(P)动作：狂暴姿态
    ACTION_NODE_P(berserker_rage, "berserker rage", "berserker stance");
};

// 构造函数：初始化战士策略并挂载动作节点工厂
WarriorStrategy::WarriorStrategy(PlayerbotAI* ai) : ClassStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<WarriorStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (战士策略)
void WarriorStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士策略)
void WarriorStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战士策略)
void WarriorStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战士策略)
void WarriorStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士PVP策略)
void WarriorPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士PVP策略)
void WarriorPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战士PVP策略)
void WarriorPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战士PVP策略)
void WarriorPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士PVE策略)
void WarriorPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士PVE策略)
void WarriorPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战士PVE策略)
void WarriorPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战士PVE策略)
void WarriorPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士团队副本策略)
void WarriorRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士团队副本策略)
void WarriorRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战士团队副本策略)
void WarriorRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战士团队副本策略)
void WarriorRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士AOE群体策略)
void WarriorAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("cleave", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "thunder clap",
        NextAction::array(0, new NextAction("thunder clap", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "thunder clap on snare target",
        NextAction::array(0, new NextAction("thunder clap on snare target", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (战士AOE群体策略)
void WarriorAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士AOE群体PVP策略)
void WarriorAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士AOE群体PVP策略)
void WarriorAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士AOE群体PVE策略)
void WarriorAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士AOE群体PVE策略)
void WarriorAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士AOE群体团队副本策略)
void WarriorAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士AOE群体团队副本策略)
void WarriorAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士控制(CC)策略)
void WarriorCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士控制(CC)策略)
void WarriorCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士控制(CC)PVP策略)
void WarriorCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "shield bash",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (战士控制(CC)PVP策略)
void WarriorCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士控制(CC)PVE策略)
void WarriorCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士控制(CC)PVE策略)
void WarriorCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士控制(CC)团队副本策略)
void WarriorCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士控制(CC)团队副本策略)
void WarriorCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士增益Buff策略)
void WarriorBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "berserker rage",
        NextAction::array(0, new NextAction("berserker rage", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "battle shout",
        NextAction::array(0, new NextAction("battle shout", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "bloodrage",
        NextAction::array(0, new NextAction("bloodrage", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (战士增益Buff策略)
void WarriorBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "battle stance",
        NextAction::array(0, new NextAction("battle stance", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (战士增益BuffPVP策略)
void WarriorBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士增益BuffPVP策略)
void WarriorBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士增益BuffPVE策略)
void WarriorBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士增益BuffPVE策略)
void WarriorBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士增益Buff团队副本策略)
void WarriorBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士增益Buff团队副本策略)
void WarriorBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士爆发增益策略)
void WarriorBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士爆发增益策略)
void WarriorBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士爆发增益PVP策略)
void WarriorBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士爆发增益PVP策略)
void WarriorBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士爆发增益PVE策略)
void WarriorBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士爆发增益PVE策略)
void WarriorBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士爆发增益团队副本策略)
void WarriorBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士爆发增益团队副本策略)
void WarriorBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (战士策略)
void WarriorStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "victory rush",
        NextAction::array(0, new NextAction("victory rush", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (战士策略)
void WarriorStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战士策略)
void WarriorStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战士策略)
void WarriorStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士PVP策略)
void WarriorPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士PVP策略)
void WarriorPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战士PVP策略)
void WarriorPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战士PVP策略)
void WarriorPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士PVE策略)
void WarriorPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士PVE策略)
void WarriorPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战士PVE策略)
void WarriorPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战士PVE策略)
void WarriorPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士团队副本策略)
void WarriorRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士团队副本策略)
void WarriorRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战士团队副本策略)
void WarriorRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战士团队副本策略)
void WarriorRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士AOE群体策略)
void WarriorAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("cleave", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "thunder clap",
        NextAction::array(0, new NextAction("thunder clap", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "thunder clap on snare target",
        NextAction::array(0, new NextAction("thunder clap on snare target", ACTION_HIGH + 1), NULL)));

    //triggers.push_back(new TriggerNode(
        //"melee light aoe",
        //NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (战士AOE群体策略)
void WarriorAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士AOE群体PVP策略)
void WarriorAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士AOE群体PVP策略)
void WarriorAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士AOE群体PVE策略)
void WarriorAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士AOE群体PVE策略)
void WarriorAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士AOE群体团队副本策略)
void WarriorAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士AOE群体团队副本策略)
void WarriorAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士控制(CC)策略)
void WarriorCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士控制(CC)策略)
void WarriorCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士控制(CC)PVP策略)
void WarriorCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "shield bash",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (战士控制(CC)PVP策略)
void WarriorCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士控制(CC)PVE策略)
void WarriorCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士控制(CC)PVE策略)
void WarriorCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士控制(CC)团队副本策略)
void WarriorCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士控制(CC)团队副本策略)
void WarriorCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士增益Buff策略)
void WarriorBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "battle shout",
        NextAction::array(0, new NextAction("battle shout", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "bloodrage",
        NextAction::array(0, new NextAction("bloodrage", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (战士增益Buff策略)
void WarriorBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "battle stance",
        NextAction::array(0, new NextAction("battle stance", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (战士增益BuffPVP策略)
void WarriorBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士增益BuffPVP策略)
void WarriorBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士增益BuffPVE策略)
void WarriorBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士增益BuffPVE策略)
void WarriorBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士增益Buff团队副本策略)
void WarriorBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士增益Buff团队副本策略)
void WarriorBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士爆发增益策略)
void WarriorBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士爆发增益策略)
void WarriorBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士爆发增益PVP策略)
void WarriorBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士爆发增益PVP策略)
void WarriorBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士爆发增益PVE策略)
void WarriorBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士爆发增益PVE策略)
void WarriorBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士爆发增益团队副本策略)
void WarriorBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士爆发增益团队副本策略)
void WarriorBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (战士策略)
void WarriorStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "victory rush",
        NextAction::array(0, new NextAction("victory rush", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (战士策略)
void WarriorStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战士策略)
void WarriorStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战士策略)
void WarriorStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士PVP策略)
void WarriorPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士PVP策略)
void WarriorPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战士PVP策略)
void WarriorPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战士PVP策略)
void WarriorPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士PVE策略)
void WarriorPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士PVE策略)
void WarriorPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战士PVE策略)
void WarriorPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战士PVE策略)
void WarriorPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士团队副本策略)
void WarriorRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士团队副本策略)
void WarriorRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (战士团队副本策略)
void WarriorRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (战士团队副本策略)
void WarriorRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士AOE群体策略)
void WarriorAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("cleave", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "thunder clap",
        NextAction::array(0, new NextAction("thunder clap", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "thunder clap on snare target",
        NextAction::array(0, new NextAction("thunder clap on snare target", ACTION_HIGH + 1), NULL)));

    //triggers.push_back(new TriggerNode(
        //"melee light aoe",
        //NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (战士AOE群体策略)
void WarriorAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士AOE群体PVP策略)
void WarriorAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士AOE群体PVP策略)
void WarriorAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士AOE群体PVE策略)
void WarriorAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士AOE群体PVE策略)
void WarriorAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士AOE群体团队副本策略)
void WarriorAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士AOE群体团队副本策略)
void WarriorAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士控制(CC)策略)
void WarriorCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士控制(CC)策略)
void WarriorCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士控制(CC)PVP策略)
void WarriorCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "shield bash",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (战士控制(CC)PVP策略)
void WarriorCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士控制(CC)PVE策略)
void WarriorCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士控制(CC)PVE策略)
void WarriorCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士控制(CC)团队副本策略)
void WarriorCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士控制(CC)团队副本策略)
void WarriorCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士增益Buff策略)
void WarriorBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "feared",
        NextAction::array(0, new NextAction("berserker rage", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "stunned",
        NextAction::array(0, new NextAction("berserker rage", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "battle shout",
        NextAction::array(0, new NextAction("battle shout", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "bloodrage",
        NextAction::array(0, new NextAction("bloodrage", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (战士增益Buff策略)
void WarriorBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "battle stance",
        NextAction::array(0, new NextAction("battle stance", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (战士增益BuffPVP策略)
void WarriorBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士增益BuffPVP策略)
void WarriorBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士增益BuffPVE策略)
void WarriorBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士增益BuffPVE策略)
void WarriorBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士增益Buff团队副本策略)
void WarriorBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士增益Buff团队副本策略)
void WarriorBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士爆发增益策略)
void WarriorBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士爆发增益策略)
void WarriorBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士爆发增益PVP策略)
void WarriorBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士爆发增益PVP策略)
void WarriorBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士爆发增益PVE策略)
void WarriorBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士爆发增益PVE策略)
void WarriorBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (战士爆发增益团队副本策略)
void WarriorBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (战士爆发增益团队副本策略)
void WarriorBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
