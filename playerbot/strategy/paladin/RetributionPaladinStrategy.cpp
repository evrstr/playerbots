// 圣骑士 - 惩戒圣骑士策略实现文件 (RetributionPaladinStrategy.cpp)
#include "playerbot/playerbot.h"
#include "PaladinMultipliers.h"
#include "RetributionPaladinStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class RetributionPaladinStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    RetributionPaladinStrategyActionNodeFactory()
    {
        creators["sanctity aura"] = &sanctity_aura;
        creators["retribution aura"] = &retribution_aura;
        creators["seal of vengeance"] = &seal_of_vengeance;
        creators["seal of command"] = &seal_of_command;
        creators["crusader strike"] = &crusader_strike;
        creators["repentance"] = &repentance;
        creators["repentance on enemy healer"] = &repentance_on_enemy_healer;
        creators["repentance on snare target"] = &repentance_on_snare_target;
        creators["repentance of shield"] = &repentance_or_shield;
        creators["judgement"] = &judgement;
    }

private:
    // 动作节点 seal_of_vengeance：复仇圣印 -> 备选(A)动作：命令圣印
    ACTION_NODE_A(seal_of_vengeance, "seal of vengeance", "seal of command");

#ifndef MANGOSBOT_ONE
    // 动作节点 seal_of_command：命令圣印 -> 备选(A)动作：正义圣印
    ACTION_NODE_A(seal_of_command, "seal of command", "seal of righteousness");
#else
    // 动作节点 seal_of_command：鲜血圣印 -> 备选(A)动作：命令圣印
    ACTION_NODE_A(seal_of_command, "seal of blood", "seal of command");
#endif
    // 动作节点 crusader_strike：十字军打击 -> 备选(A)动作：melee
    ACTION_NODE_A(crusader_strike, "crusader strike", "melee");

    // 动作节点 repentance：忏悔 -> 备选(A)动作：制裁之锤
    ACTION_NODE_A(repentance, "repentance", "hammer of justice");

    // 动作节点 repentance_on_enemy_healer：对敌方治疗者施放忏悔 -> 备选(A)动作：制裁之锤 (对敌方治疗)
    ACTION_NODE_A(repentance_on_enemy_healer, "repentance on enemy healer", "hammer of justice on enemy healer");

    // 动作节点 repentance_on_snare_target：对被减速目标施放忏悔 -> 备选(A)动作：制裁之锤 (对被减速目标)
    ACTION_NODE_A(repentance_on_snare_target, "repentance on snare target", "hammer of justice on snare target");

    // 动作节点 sanctity_aura：圣洁光环 -> 备选(A)动作：惩罚光环
    ACTION_NODE_A(sanctity_aura, "sanctity aura", "retribution aura");

    // 动作节点 retribution_aura：惩罚光环 -> 备选(A)动作：虔诚光环
    ACTION_NODE_A(retribution_aura, "retribution aura", "devotion aura");

    // 动作节点 repentance_or_shield：忏悔 -> 备选(A)动作：圣盾术
    ACTION_NODE_A(repentance_or_shield, "repentance", "divine shield");

    // 动作节点 judgement：审判 -> 备选(A)动作：驱邪术
    ACTION_NODE_A(judgement, "judgement", "exorcism");
};

// 构造函数：初始化惩戒圣骑士策略并挂载动作节点工厂
RetributionPaladinStrategy::RetributionPaladinStrategy(PlayerbotAI* ai) : PaladinStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<RetributionPaladinStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (惩戒圣骑士策略)
NextAction** RetributionPaladinStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士策略)
void RetributionPaladinStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("repentance or shield", ACTION_EMERGENCY + 1), 
                             new NextAction("holy light", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("divine shield", ACTION_EMERGENCY + 1), 
                             new NextAction("holy light", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("holy light", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("seal of wisdom", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("hammer of wrath", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "exorcism",
        NextAction::array(0, new NextAction("exorcism", ACTION_NORMAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "target no judgement",
        NextAction::array(0, new NextAction("seal of the crusader", ACTION_HIGH + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "seal",
        NextAction::array(0, new NextAction("seal of command", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "judgement",
        NextAction::array(0, new NextAction("judgement", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "crusader strike",
        NextAction::array(0, new NextAction("crusader strike", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士策略)
void RetributionPaladinStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("holy light", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (惩戒圣骑士策略)
void RetributionPaladinStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (惩戒圣骑士策略)
void RetributionPaladinStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士PVE策略)
void RetributionPaladinPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士PVE策略)
void RetributionPaladinPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (惩戒圣骑士PVE策略)
void RetributionPaladinPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (惩戒圣骑士PVE策略)
void RetributionPaladinPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士PVP策略)
void RetributionPaladinPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士PVP策略)
void RetributionPaladinPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (惩戒圣骑士PVP策略)
void RetributionPaladinPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (惩戒圣骑士PVP策略)
void RetributionPaladinPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士团队副本策略)
void RetributionPaladinRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士团队副本策略)
void RetributionPaladinRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (惩戒圣骑士团队副本策略)
void RetributionPaladinRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (惩戒圣骑士团队副本策略)
void RetributionPaladinRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士AOE群体策略)
void RetributionPaladinAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("consecration", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "consecration",
        NextAction::array(0, new NextAction("consecration", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士AOE群体策略)
void RetributionPaladinAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士AOE群体PVE策略)
void RetributionPaladinAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士AOE群体PVE策略)
void RetributionPaladinAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士AOE群体PVP策略)
void RetributionPaladinAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士AOE群体PVP策略)
void RetributionPaladinAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士AOE群体团队副本策略)
void RetributionPaladinAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士AOE群体团队副本策略)
void RetributionPaladinAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士增益Buff策略)
void RetributionPaladinBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士增益Buff策略)
void RetributionPaladinBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士增益BuffPVE策略)
void RetributionPaladinBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士增益BuffPVE策略)
void RetributionPaladinBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士增益BuffPVP策略)
void RetributionPaladinBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士增益BuffPVP策略)
void RetributionPaladinBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士增益Buff团队副本策略)
void RetributionPaladinBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士增益Buff团队副本策略)
void RetributionPaladinBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士爆发增益策略)
void RetributionPaladinBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士爆发增益策略)
void RetributionPaladinBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士爆发增益PVE策略)
void RetributionPaladinBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士爆发增益PVE策略)
void RetributionPaladinBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士爆发增益PVP策略)
void RetributionPaladinBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士爆发增益PVP策略)
void RetributionPaladinBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士爆发增益团队副本策略)
void RetributionPaladinBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士爆发增益团队副本策略)
void RetributionPaladinBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士控制(CC)策略)
void RetributionPaladinCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hammer of justice on enemy",
        NextAction::array(0, new NextAction("hammer of justice", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "repentance on enemy healer",
        NextAction::array(0, new NextAction("repentance on enemy healer", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "repentance on snare target",
        NextAction::array(0, new NextAction("repentance on snare target", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "repentance interrupt",
        NextAction::array(0, new NextAction("repentance", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士控制(CC)策略)
void RetributionPaladinCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士控制(CC)PVE策略)
void RetributionPaladinCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士控制(CC)PVE策略)
void RetributionPaladinCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士控制(CC)PVP策略)
void RetributionPaladinCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士控制(CC)PVP策略)
void RetributionPaladinCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士控制(CC)团队副本策略)
void RetributionPaladinCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士控制(CC)团队副本策略)
void RetributionPaladinCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士驱散净化策略)
void RetributionPaladinCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士驱散净化策略)
void RetributionPaladinCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士驱散净化PVE策略)
void RetributionPaladinCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士驱散净化PVE策略)
void RetributionPaladinCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士驱散净化PVP策略)
void RetributionPaladinCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士驱散净化PVP策略)
void RetributionPaladinCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士驱散净化团队副本策略)
void RetributionPaladinCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士驱散净化团队副本策略)
void RetributionPaladinCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士光环策略)
void RetributionPaladinAuraStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士光环策略)
void RetributionPaladinAuraStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no paladin aura",
        NextAction::array(0, new NextAction("sanctity aura", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士光环PVE策略)
void RetributionPaladinAuraPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士光环PVE策略)
void RetributionPaladinAuraPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士光环PVP策略)
void RetributionPaladinAuraPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士光环PVP策略)
void RetributionPaladinAuraPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士光环团队副本策略)
void RetributionPaladinAuraRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士光环团队副本策略)
void RetributionPaladinAuraRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士祝福策略)
void RetributionPaladinBlessingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士祝福策略)
void RetributionPaladinBlessingStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士祝福PVE策略)
void RetributionPaladinBlessingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士祝福PVE策略)
void RetributionPaladinBlessingPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士祝福PVP策略)
void RetributionPaladinBlessingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士祝福PVP策略)
void RetributionPaladinBlessingPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士祝福团队副本策略)
void RetributionPaladinBlessingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士祝福团队副本策略)
void RetributionPaladinBlessingRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (惩戒圣骑士策略)
NextAction** RetributionPaladinStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士策略)
void RetributionPaladinStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("repentance or shield", ACTION_EMERGENCY + 1),
                             new NextAction("holy light", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("seal of wisdom", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("hammer of wrath", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "exorcism",
        NextAction::array(0, new NextAction("exorcism", ACTION_NORMAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "target no judgement",
        NextAction::array(0, new NextAction("seal of the crusader", ACTION_HIGH + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "seal",
        NextAction::array(0, new NextAction("seal of command", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "judgement",
        NextAction::array(0, new NextAction("judgement", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "crusader strike",
        NextAction::array(0, new NextAction("crusader strike", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士策略)
void RetributionPaladinStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (惩戒圣骑士策略)
void RetributionPaladinStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (惩戒圣骑士策略)
void RetributionPaladinStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士PVE策略)
void RetributionPaladinPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士PVE策略)
void RetributionPaladinPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (惩戒圣骑士PVE策略)
void RetributionPaladinPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (惩戒圣骑士PVE策略)
void RetributionPaladinPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士PVP策略)
void RetributionPaladinPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士PVP策略)
void RetributionPaladinPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (惩戒圣骑士PVP策略)
void RetributionPaladinPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (惩戒圣骑士PVP策略)
void RetributionPaladinPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士团队副本策略)
void RetributionPaladinRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士团队副本策略)
void RetributionPaladinRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (惩戒圣骑士团队副本策略)
void RetributionPaladinRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (惩戒圣骑士团队副本策略)
void RetributionPaladinRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士AOE群体策略)
void RetributionPaladinAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("consecration", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "consecration",
        NextAction::array(0, new NextAction("consecration", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士AOE群体策略)
void RetributionPaladinAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士AOE群体PVE策略)
void RetributionPaladinAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士AOE群体PVE策略)
void RetributionPaladinAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士AOE群体PVP策略)
void RetributionPaladinAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士AOE群体PVP策略)
void RetributionPaladinAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士AOE群体团队副本策略)
void RetributionPaladinAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士AOE群体团队副本策略)
void RetributionPaladinAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士增益Buff策略)
void RetributionPaladinBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士增益Buff策略)
void RetributionPaladinBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士增益BuffPVE策略)
void RetributionPaladinBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士增益BuffPVE策略)
void RetributionPaladinBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士增益BuffPVP策略)
void RetributionPaladinBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士增益BuffPVP策略)
void RetributionPaladinBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士增益Buff团队副本策略)
void RetributionPaladinBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士增益Buff团队副本策略)
void RetributionPaladinBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士爆发增益策略)
void RetributionPaladinBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士爆发增益策略)
void RetributionPaladinBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士爆发增益PVE策略)
void RetributionPaladinBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士爆发增益PVE策略)
void RetributionPaladinBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士爆发增益PVP策略)
void RetributionPaladinBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士爆发增益PVP策略)
void RetributionPaladinBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士爆发增益团队副本策略)
void RetributionPaladinBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士爆发增益团队副本策略)
void RetributionPaladinBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士控制(CC)策略)
void RetributionPaladinCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hammer of justice on enemy",
        NextAction::array(0, new NextAction("hammer of justice", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "repentance on enemy healer",
        NextAction::array(0, new NextAction("repentance on enemy healer", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "repentance on snare target",
        NextAction::array(0, new NextAction("repentance on snare target", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "repentance interrupt",
        NextAction::array(0, new NextAction("repentance", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士控制(CC)策略)
void RetributionPaladinCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士控制(CC)PVE策略)
void RetributionPaladinCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士控制(CC)PVE策略)
void RetributionPaladinCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士控制(CC)PVP策略)
void RetributionPaladinCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士控制(CC)PVP策略)
void RetributionPaladinCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士控制(CC)团队副本策略)
void RetributionPaladinCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士控制(CC)团队副本策略)
void RetributionPaladinCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士驱散净化策略)
void RetributionPaladinCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士驱散净化策略)
void RetributionPaladinCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士驱散净化PVE策略)
void RetributionPaladinCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士驱散净化PVE策略)
void RetributionPaladinCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士驱散净化PVP策略)
void RetributionPaladinCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士驱散净化PVP策略)
void RetributionPaladinCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士驱散净化团队副本策略)
void RetributionPaladinCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士驱散净化团队副本策略)
void RetributionPaladinCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士光环策略)
void RetributionPaladinAuraStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士光环策略)
void RetributionPaladinAuraStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no paladin aura",
        NextAction::array(0, new NextAction("sanctity aura", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士光环PVE策略)
void RetributionPaladinAuraPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士光环PVE策略)
void RetributionPaladinAuraPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士光环PVP策略)
void RetributionPaladinAuraPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士光环PVP策略)
void RetributionPaladinAuraPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士光环团队副本策略)
void RetributionPaladinAuraRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士光环团队副本策略)
void RetributionPaladinAuraRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士祝福策略)
void RetributionPaladinBlessingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士祝福策略)
void RetributionPaladinBlessingStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士祝福PVE策略)
void RetributionPaladinBlessingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士祝福PVE策略)
void RetributionPaladinBlessingPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士祝福PVP策略)
void RetributionPaladinBlessingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士祝福PVP策略)
void RetributionPaladinBlessingPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士祝福团队副本策略)
void RetributionPaladinBlessingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士祝福团队副本策略)
void RetributionPaladinBlessingRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (惩戒圣骑士策略)
NextAction** RetributionPaladinStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士策略)
void RetributionPaladinStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("repentance or shield", ACTION_EMERGENCY + 1),
                             new NextAction("holy light", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("seal of wisdom", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("hammer of wrath", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "exorcism",
        NextAction::array(0, new NextAction("exorcism", ACTION_NORMAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "seal",
        NextAction::array(0, new NextAction("seal of command", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "judgement of wisdom",
        NextAction::array(0, new NextAction("judgement of wisdom", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "judgement of light",
        NextAction::array(0, new NextAction("judgement of light", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("divine storm", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "crusader strike",
        NextAction::array(0, new NextAction("crusader strike", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士策略)
void RetributionPaladinStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "set glyph::Judgement",
        NextAction::array(0, new NextAction("set glyph::Judgement", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "set glyph::Blessing of Might",
        NextAction::array(0, new NextAction("set glyph::Blessing of Might", ACTION_NORMAL + 1), NULL)));
}

// 初始化反应阶段触发器列表 (惩戒圣骑士策略)
void RetributionPaladinStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (惩戒圣骑士策略)
void RetributionPaladinStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士PVE策略)
void RetributionPaladinPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士PVE策略)
void RetributionPaladinPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (惩戒圣骑士PVE策略)
void RetributionPaladinPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (惩戒圣骑士PVE策略)
void RetributionPaladinPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士PVP策略)
void RetributionPaladinPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士PVP策略)
void RetributionPaladinPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (惩戒圣骑士PVP策略)
void RetributionPaladinPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (惩戒圣骑士PVP策略)
void RetributionPaladinPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士团队副本策略)
void RetributionPaladinRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士团队副本策略)
void RetributionPaladinRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (惩戒圣骑士团队副本策略)
void RetributionPaladinRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (惩戒圣骑士团队副本策略)
void RetributionPaladinRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士AOE群体策略)
void RetributionPaladinAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("consecration", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "consecration",
        NextAction::array(0, new NextAction("consecration", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士AOE群体策略)
void RetributionPaladinAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士AOE群体PVE策略)
void RetributionPaladinAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士AOE群体PVE策略)
void RetributionPaladinAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士AOE群体PVP策略)
void RetributionPaladinAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士AOE群体PVP策略)
void RetributionPaladinAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士AOE群体团队副本策略)
void RetributionPaladinAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士AOE群体团队副本策略)
void RetributionPaladinAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士增益Buff策略)
void RetributionPaladinBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士增益Buff策略)
void RetributionPaladinBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士增益BuffPVE策略)
void RetributionPaladinBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士增益BuffPVE策略)
void RetributionPaladinBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士增益BuffPVP策略)
void RetributionPaladinBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士增益BuffPVP策略)
void RetributionPaladinBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士增益Buff团队副本策略)
void RetributionPaladinBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士增益Buff团队副本策略)
void RetributionPaladinBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士爆发增益策略)
void RetributionPaladinBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士爆发增益策略)
void RetributionPaladinBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士爆发增益PVE策略)
void RetributionPaladinBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士爆发增益PVE策略)
void RetributionPaladinBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士爆发增益PVP策略)
void RetributionPaladinBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士爆发增益PVP策略)
void RetributionPaladinBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士爆发增益团队副本策略)
void RetributionPaladinBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士爆发增益团队副本策略)
void RetributionPaladinBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士控制(CC)策略)
void RetributionPaladinCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hammer of justice on enemy",
        NextAction::array(0, new NextAction("hammer of justice", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "repentance on enemy healer",
        NextAction::array(0, new NextAction("repentance on enemy healer", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "repentance on snare target",
        NextAction::array(0, new NextAction("repentance on snare target", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "repentance interrupt",
        NextAction::array(0, new NextAction("repentance", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士控制(CC)策略)
void RetributionPaladinCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士控制(CC)PVE策略)
void RetributionPaladinCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士控制(CC)PVE策略)
void RetributionPaladinCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士控制(CC)PVP策略)
void RetributionPaladinCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士控制(CC)PVP策略)
void RetributionPaladinCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士控制(CC)团队副本策略)
void RetributionPaladinCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士控制(CC)团队副本策略)
void RetributionPaladinCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士驱散净化策略)
void RetributionPaladinCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士驱散净化策略)
void RetributionPaladinCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士驱散净化PVE策略)
void RetributionPaladinCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士驱散净化PVE策略)
void RetributionPaladinCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士驱散净化PVP策略)
void RetributionPaladinCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士驱散净化PVP策略)
void RetributionPaladinCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士驱散净化团队副本策略)
void RetributionPaladinCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士驱散净化团队副本策略)
void RetributionPaladinCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士光环策略)
void RetributionPaladinAuraStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士光环策略)
void RetributionPaladinAuraStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no paladin aura",
        NextAction::array(0, new NextAction("sanctity aura", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士光环PVE策略)
void RetributionPaladinAuraPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士光环PVE策略)
void RetributionPaladinAuraPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士光环PVP策略)
void RetributionPaladinAuraPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士光环PVP策略)
void RetributionPaladinAuraPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士光环团队副本策略)
void RetributionPaladinAuraRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士光环团队副本策略)
void RetributionPaladinAuraRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士祝福策略)
void RetributionPaladinBlessingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士祝福策略)
void RetributionPaladinBlessingStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士祝福PVE策略)
void RetributionPaladinBlessingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士祝福PVE策略)
void RetributionPaladinBlessingPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士祝福PVP策略)
void RetributionPaladinBlessingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士祝福PVP策略)
void RetributionPaladinBlessingPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (惩戒圣骑士祝福团队副本策略)
void RetributionPaladinBlessingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (惩戒圣骑士祝福团队副本策略)
void RetributionPaladinBlessingRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RetributionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
