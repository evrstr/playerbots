// 圣骑士 - 防护圣骑士策略实现文件 (ProtectionPaladinStrategy.cpp)

#include "playerbot/playerbot.h"
#include "PaladinMultipliers.h"
#include "ProtectionPaladinStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class ProtectionPaladinStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    ProtectionPaladinStrategyActionNodeFactory()
    {
        creators["seal of vengeance"] = &seal_of_vengeance;
        creators["hand of reckoning"] = &hand_of_reckoning;
        creators["righteous defense"] = &righteous_defense;
        creators["judgement"] = &judgement;
    }

private:
    // 动作节点 seal_of_vengeance：复仇圣印 -> 备选(A)动作：正义圣印
    ACTION_NODE_A(seal_of_vengeance, "seal of vengeance", "seal of righteousness");

    // 动作节点 hand_of_reckoning：清算之手 -> 备选(A)动作：正义防御
    ACTION_NODE_A(hand_of_reckoning, "hand of reckoning", "righteous defense");

    // 构建 正义防御 (righteous_defense) 动作节点
    static ActionNode* righteous_defense(PlayerbotAI* ai)
    {
        return new ActionNode("righteous defense",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("avenger's shield"), 
                                       new NextAction("judgement"), NULL));
    }

    // 动作节点 judgement：审判 -> 备选(A)动作：驱邪术
    ACTION_NODE_A(judgement, "judgement", "exorcism");
};

// 构造函数：初始化防护圣骑士策略并挂载动作节点工厂
ProtectionPaladinStrategy::ProtectionPaladinStrategy(PlayerbotAI* ai) : PaladinStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<ProtectionPaladinStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (防护圣骑士策略)
NextAction** ProtectionPaladinStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (防护圣骑士策略)
void ProtectionPaladinStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("hand of reckoning", ACTION_PASSTROUGH), NULL)));

    triggers.push_back(new TriggerNode(
        "protect party member",
        NextAction::array(0, new NextAction("blessing of protection on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "holy shield",
        NextAction::array(0, new NextAction("holy shield", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "medium mana",
        NextAction::array(0, new NextAction("seal of wisdom", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "exorcism",
        NextAction::array(0, new NextAction("exorcism", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "seal",
        NextAction::array(0, new NextAction("seal of vengeance", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "judgement",
        NextAction::array(0, new NextAction("judgement", ACTION_NORMAL + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士策略)
void ProtectionPaladinStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (防护圣骑士策略)
void ProtectionPaladinStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护圣骑士策略)
void ProtectionPaladinStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士PVE策略)
void ProtectionPaladinPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("hammer of wrath", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士PVE策略)
void ProtectionPaladinPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护圣骑士PVE策略)
void ProtectionPaladinPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护圣骑士PVE策略)
void ProtectionPaladinPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士PVP策略)
void ProtectionPaladinPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("hammer of wrath", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士PVP策略)
void ProtectionPaladinPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护圣骑士PVP策略)
void ProtectionPaladinPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护圣骑士PVP策略)
void ProtectionPaladinPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士团队副本策略)
void ProtectionPaladinRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士团队副本策略)
void ProtectionPaladinRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护圣骑士团队副本策略)
void ProtectionPaladinRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护圣骑士团队副本策略)
void ProtectionPaladinRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士AOE群体策略)
void ProtectionPaladinAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("consecration", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "consecration",
        NextAction::array(0, new NextAction("consecration", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士AOE群体策略)
void ProtectionPaladinAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士AOE群体PVE策略)
void ProtectionPaladinAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士AOE群体PVE策略)
void ProtectionPaladinAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士AOE群体PVP策略)
void ProtectionPaladinAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士AOE群体PVP策略)
void ProtectionPaladinAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士AOE群体团队副本策略)
void ProtectionPaladinAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士AOE群体团队副本策略)
void ProtectionPaladinAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士增益Buff策略)
void ProtectionPaladinBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士增益Buff策略)
void ProtectionPaladinBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "righteous fury",
        NextAction::array(0, new NextAction("righteous fury", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士增益BuffPVE策略)
void ProtectionPaladinBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士增益BuffPVE策略)
void ProtectionPaladinBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士增益BuffPVP策略)
void ProtectionPaladinBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士增益BuffPVP策略)
void ProtectionPaladinBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士增益Buff团队副本策略)
void ProtectionPaladinBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("stoneshield potion", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士增益Buff团队副本策略)
void ProtectionPaladinBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士爆发增益策略)
void ProtectionPaladinBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士爆发增益策略)
void ProtectionPaladinBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士爆发增益PVE策略)
void ProtectionPaladinBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士爆发增益PVE策略)
void ProtectionPaladinBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士爆发增益PVP策略)
void ProtectionPaladinBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士爆发增益PVP策略)
void ProtectionPaladinBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士爆发增益团队副本策略)
void ProtectionPaladinBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士爆发增益团队副本策略)
void ProtectionPaladinBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士控制(CC)策略)
void ProtectionPaladinCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hammer of justice on enemy",
        NextAction::array(0, new NextAction("hammer of justice", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士控制(CC)策略)
void ProtectionPaladinCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士控制(CC)PVE策略)
void ProtectionPaladinCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士控制(CC)PVE策略)
void ProtectionPaladinCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士控制(CC)PVP策略)
void ProtectionPaladinCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士控制(CC)PVP策略)
void ProtectionPaladinCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士控制(CC)团队副本策略)
void ProtectionPaladinCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士控制(CC)团队副本策略)
void ProtectionPaladinCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士驱散净化策略)
void ProtectionPaladinCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士驱散净化策略)
void ProtectionPaladinCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士驱散净化PVE策略)
void ProtectionPaladinCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士驱散净化PVE策略)
void ProtectionPaladinCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士驱散净化PVP策略)
void ProtectionPaladinCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士驱散净化PVP策略)
void ProtectionPaladinCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士驱散净化团队副本策略)
void ProtectionPaladinCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士驱散净化团队副本策略)
void ProtectionPaladinCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士光环策略)
void ProtectionPaladinAuraStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士光环策略)
void ProtectionPaladinAuraStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no paladin aura",
        NextAction::array(0, new NextAction("retribution aura", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士光环PVE策略)
void ProtectionPaladinAuraPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士光环PVE策略)
void ProtectionPaladinAuraPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士光环PVP策略)
void ProtectionPaladinAuraPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士光环PVP策略)
void ProtectionPaladinAuraPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士光环团队副本策略)
void ProtectionPaladinAuraRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士光环团队副本策略)
void ProtectionPaladinAuraRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士祝福策略)
void ProtectionPaladinBlessingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士祝福策略)
void ProtectionPaladinBlessingStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士祝福PVE策略)
void ProtectionPaladinBlessingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士祝福PVE策略)
void ProtectionPaladinBlessingPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士祝福PVP策略)
void ProtectionPaladinBlessingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士祝福PVP策略)
void ProtectionPaladinBlessingPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士祝福团队副本策略)
void ProtectionPaladinBlessingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士祝福团队副本策略)
void ProtectionPaladinBlessingRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (防护圣骑士策略)
NextAction** ProtectionPaladinStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (防护圣骑士策略)
void ProtectionPaladinStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitCombatTriggers(triggers);  

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("righteous defense", ACTION_PASSTROUGH), NULL)));

    triggers.push_back(new TriggerNode(
        "protect party member",
        NextAction::array(0, new NextAction("blessing of protection on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "holy shield",
        NextAction::array(0, new NextAction("holy shield", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("seal of wisdom", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "exorcism",
        NextAction::array(0, new NextAction("exorcism", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "seal",
        NextAction::array(0, new NextAction("prot seal", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "judgement",
        NextAction::array(0, new NextAction("judgement", ACTION_NORMAL + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士策略)
void ProtectionPaladinStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (防护圣骑士策略)
void ProtectionPaladinStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护圣骑士策略)
void ProtectionPaladinStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士PVE策略)
void ProtectionPaladinPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("hammer of wrath", ACTION_HIGH), NULL)));
    
}

// 初始化非战斗阶段触发器列表 (防护圣骑士PVE策略)
void ProtectionPaladinPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护圣骑士PVE策略)
void ProtectionPaladinPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护圣骑士PVE策略)
void ProtectionPaladinPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士PVP策略)
void ProtectionPaladinPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("hammer of wrath", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士PVP策略)
void ProtectionPaladinPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护圣骑士PVP策略)
void ProtectionPaladinPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护圣骑士PVP策略)
void ProtectionPaladinPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士团队副本策略)
void ProtectionPaladinRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士团队副本策略)
void ProtectionPaladinRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护圣骑士团队副本策略)
void ProtectionPaladinRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护圣骑士团队副本策略)
void ProtectionPaladinRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士AOE群体策略)
void ProtectionPaladinAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitCombatTriggers(triggers);
    triggers.push_back(new TriggerNode(
        "consecration",
        NextAction::array(0, new NextAction("consecration", ACTION_HIGH + 4), NULL)));

    /*triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH), NULL)));
    */
    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("consecration", ACTION_HIGH + 1), NULL)));

    /*triggers.push_back(new TriggerNode(
        "avenger's shield",
        NextAction::array(0, new NextAction("avenger's shield", ACTION_HIGH), NULL)));
    */
}

// 初始化非战斗阶段触发器列表 (防护圣骑士AOE群体策略)
void ProtectionPaladinAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士AOE群体PVE策略)
void ProtectionPaladinAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士AOE群体PVE策略)
void ProtectionPaladinAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士AOE群体PVP策略)
void ProtectionPaladinAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士AOE群体PVP策略)
void ProtectionPaladinAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士AOE群体团队副本策略)
void ProtectionPaladinAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士AOE群体团队副本策略)
void ProtectionPaladinAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士增益Buff策略)
void ProtectionPaladinBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士增益Buff策略)
void ProtectionPaladinBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "righteous fury",
        NextAction::array(0, new NextAction("righteous fury", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士增益BuffPVE策略)
void ProtectionPaladinBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士增益BuffPVE策略)
void ProtectionPaladinBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士增益BuffPVP策略)
void ProtectionPaladinBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士增益BuffPVP策略)
void ProtectionPaladinBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士增益Buff团队副本策略)
void ProtectionPaladinBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士增益Buff团队副本策略)
void ProtectionPaladinBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士爆发增益策略)
void ProtectionPaladinBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士爆发增益策略)
void ProtectionPaladinBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士爆发增益PVE策略)
void ProtectionPaladinBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士爆发增益PVE策略)
void ProtectionPaladinBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士爆发增益PVP策略)
void ProtectionPaladinBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士爆发增益PVP策略)
void ProtectionPaladinBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士爆发增益团队副本策略)
void ProtectionPaladinBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士爆发增益团队副本策略)
void ProtectionPaladinBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士控制(CC)策略)
void ProtectionPaladinCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hammer of justice on enemy",
        NextAction::array(0, new NextAction("hammer of justice", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士控制(CC)策略)
void ProtectionPaladinCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士控制(CC)PVE策略)
void ProtectionPaladinCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士控制(CC)PVE策略)
void ProtectionPaladinCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士控制(CC)PVP策略)
void ProtectionPaladinCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士控制(CC)PVP策略)
void ProtectionPaladinCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士控制(CC)团队副本策略)
void ProtectionPaladinCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士控制(CC)团队副本策略)
void ProtectionPaladinCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士驱散净化策略)
void ProtectionPaladinCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士驱散净化策略)
void ProtectionPaladinCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士驱散净化PVE策略)
void ProtectionPaladinCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士驱散净化PVE策略)
void ProtectionPaladinCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士驱散净化PVP策略)
void ProtectionPaladinCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士驱散净化PVP策略)
void ProtectionPaladinCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士驱散净化团队副本策略)
void ProtectionPaladinCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士驱散净化团队副本策略)
void ProtectionPaladinCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士光环策略)
void ProtectionPaladinAuraStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士光环策略)
void ProtectionPaladinAuraStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no paladin aura",
        NextAction::array(0, new NextAction("retribution aura", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士光环PVE策略)
void ProtectionPaladinAuraPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士光环PVE策略)
void ProtectionPaladinAuraPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士光环PVP策略)
void ProtectionPaladinAuraPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士光环PVP策略)
void ProtectionPaladinAuraPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士光环团队副本策略)
void ProtectionPaladinAuraRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士光环团队副本策略)
void ProtectionPaladinAuraRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士祝福策略)
void ProtectionPaladinBlessingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士祝福策略)
void ProtectionPaladinBlessingStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士祝福PVE策略)
void ProtectionPaladinBlessingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士祝福PVE策略)
void ProtectionPaladinBlessingPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士祝福PVP策略)
void ProtectionPaladinBlessingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士祝福PVP策略)
void ProtectionPaladinBlessingPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士祝福团队副本策略)
void ProtectionPaladinBlessingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士祝福团队副本策略)
void ProtectionPaladinBlessingRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (防护圣骑士策略)
NextAction** ProtectionPaladinStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (防护圣骑士策略)
void ProtectionPaladinStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("hand of reckoning", ACTION_PASSTROUGH), NULL)));

    triggers.push_back(new TriggerNode(
        "protect party member",
        NextAction::array(0, new NextAction("blessing of protection on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "holy shield",
        NextAction::array(0, new NextAction("holy shield", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "medium mana",
        NextAction::array(0, new NextAction("judgement of wisdom", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("seal of wisdom", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "exorcism",
        NextAction::array(0, new NextAction("exorcism", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "seal",
        NextAction::array(0, new NextAction("seal of vengeance", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "judgement of light",
        NextAction::array(0, new NextAction("judgement of light", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士策略)
void ProtectionPaladinStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "set glyph::Hammer of Justice",
        NextAction::array(0, new NextAction("set glyph::Hammer of Justice", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "set glyph::the Wise",
        NextAction::array(0, new NextAction("set glyph::the Wise", ACTION_NORMAL + 1), NULL)));
}

// 初始化反应阶段触发器列表 (防护圣骑士策略)
void ProtectionPaladinStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护圣骑士策略)
void ProtectionPaladinStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士PVE策略)
void ProtectionPaladinPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("hammer of wrath", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士PVE策略)
void ProtectionPaladinPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护圣骑士PVE策略)
void ProtectionPaladinPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护圣骑士PVE策略)
void ProtectionPaladinPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士PVP策略)
void ProtectionPaladinPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("hammer of wrath", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士PVP策略)
void ProtectionPaladinPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护圣骑士PVP策略)
void ProtectionPaladinPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护圣骑士PVP策略)
void ProtectionPaladinPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士团队副本策略)
void ProtectionPaladinRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitCombatTriggers(triggers);
    PaladinRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士团队副本策略)
void ProtectionPaladinRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitNonCombatTriggers(triggers);
    PaladinRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护圣骑士团队副本策略)
void ProtectionPaladinRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitReactionTriggers(triggers);
    PaladinRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护圣骑士团队副本策略)
void ProtectionPaladinRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinStrategy::InitDeadTriggers(triggers);
    PaladinRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士AOE群体策略)
void ProtectionPaladinAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitCombatTriggers(triggers);

    //triggers.push_back(new TriggerNode(
        //"melee light aoe",
        //NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("hammer of the righteous", ACTION_HIGH + 3),
                             new NextAction("avenger's shield", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("consecration", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "consecration",
        NextAction::array(0, new NextAction("consecration", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "avenger's shield",
        NextAction::array(0, new NextAction("avenger's shield", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士AOE群体策略)
void ProtectionPaladinAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士AOE群体PVE策略)
void ProtectionPaladinAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士AOE群体PVE策略)
void ProtectionPaladinAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士AOE群体PVP策略)
void ProtectionPaladinAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士AOE群体PVP策略)
void ProtectionPaladinAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士AOE群体团队副本策略)
void ProtectionPaladinAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士AOE群体团队副本策略)
void ProtectionPaladinAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAoeStrategy::InitNonCombatTriggers(triggers);
    PaladinAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士增益Buff策略)
void ProtectionPaladinBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士增益Buff策略)
void ProtectionPaladinBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "righteous fury",
        NextAction::array(0, new NextAction("righteous fury", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士增益BuffPVE策略)
void ProtectionPaladinBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士增益BuffPVE策略)
void ProtectionPaladinBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士增益BuffPVP策略)
void ProtectionPaladinBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士增益BuffPVP策略)
void ProtectionPaladinBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士增益Buff团队副本策略)
void ProtectionPaladinBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士增益Buff团队副本策略)
void ProtectionPaladinBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBuffStrategy::InitNonCombatTriggers(triggers);
    PaladinBuffRaidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士爆发增益策略)
void ProtectionPaladinBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士爆发增益策略)
void ProtectionPaladinBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士爆发增益PVE策略)
void ProtectionPaladinBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士爆发增益PVE策略)
void ProtectionPaladinBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士爆发增益PVP策略)
void ProtectionPaladinBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士爆发增益PVP策略)
void ProtectionPaladinBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士爆发增益团队副本策略)
void ProtectionPaladinBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士爆发增益团队副本策略)
void ProtectionPaladinBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBoostStrategy::InitNonCombatTriggers(triggers);
    PaladinBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士控制(CC)策略)
void ProtectionPaladinCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hammer of justice on enemy",
        NextAction::array(0, new NextAction("hammer of justice", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士控制(CC)策略)
void ProtectionPaladinCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士控制(CC)PVE策略)
void ProtectionPaladinCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士控制(CC)PVE策略)
void ProtectionPaladinCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士控制(CC)PVP策略)
void ProtectionPaladinCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护圣骑士控制(CC)PVP策略)
void ProtectionPaladinCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士控制(CC)团队副本策略)
void ProtectionPaladinCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士控制(CC)团队副本策略)
void ProtectionPaladinCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCcStrategy::InitNonCombatTriggers(triggers);
    PaladinCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士驱散净化策略)
void ProtectionPaladinCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士驱散净化策略)
void ProtectionPaladinCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士驱散净化PVE策略)
void ProtectionPaladinCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士驱散净化PVE策略)
void ProtectionPaladinCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士驱散净化PVP策略)
void ProtectionPaladinCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士驱散净化PVP策略)
void ProtectionPaladinCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士驱散净化团队副本策略)
void ProtectionPaladinCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士驱散净化团队副本策略)
void ProtectionPaladinCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinCureStrategy::InitNonCombatTriggers(triggers);
    PaladinCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士光环策略)
void ProtectionPaladinAuraStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士光环策略)
void ProtectionPaladinAuraStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinAuraStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no paladin aura",
        NextAction::array(0, new NextAction("retribution aura", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (防护圣骑士光环PVE策略)
void ProtectionPaladinAuraPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士光环PVE策略)
void ProtectionPaladinAuraPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士光环PVP策略)
void ProtectionPaladinAuraPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士光环PVP策略)
void ProtectionPaladinAuraPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士光环团队副本策略)
void ProtectionPaladinAuraRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士光环团队副本策略)
void ProtectionPaladinAuraRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinAuraStrategy::InitNonCombatTriggers(triggers);
    PaladinAuraRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士祝福策略)
void ProtectionPaladinBlessingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士祝福策略)
void ProtectionPaladinBlessingStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinBlessingStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士祝福PVE策略)
void ProtectionPaladinBlessingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士祝福PVE策略)
void ProtectionPaladinBlessingPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士祝福PVP策略)
void ProtectionPaladinBlessingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士祝福PVP策略)
void ProtectionPaladinBlessingPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护圣骑士祝福团队副本策略)
void ProtectionPaladinBlessingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护圣骑士祝福团队副本策略)
void ProtectionPaladinBlessingRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionPaladinBlessingStrategy::InitNonCombatTriggers(triggers);
    PaladinBlessingRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
