// 圣骑士 - 圣骑士策略实现文件 (PaladinStrategy.cpp)
#include "playerbot/playerbot.h"
#include "PaladinStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class PaladinStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    PaladinStrategyActionNodeFactory()
    {
        creators["cleanse poison"] = &cleanse_poison;
        creators["cleanse disease"] = &cleanse_disease;
        creators["cleanse poison on party"] = &cleanse_poison_on_party;
        creators["cleanse disease on party"] = &cleanse_disease_on_party;
        creators["judgement of wisdom"] = &judgement_of_wisdom;
        creators["divine shield"] = &divine_shield;
        creators["flash of light"] = &flash_of_light;
        creators["flash of light on party"] = &flash_of_light_on_party;
        creators["holy wrath"] = &holy_wrath;
        creators["lay on hands"] = &lay_on_hands;
        creators["lay on hands on party"] = &lay_on_hands_on_party;
        creators["greater blessing of might"] = &greater_blessing_of_might;
        creators["greater blessing of kings"] = &greater_blessing_of_kings;
        creators["greater blessing of wisdom"] = &greater_blessing_of_wisdom;
        creators["greater blessing of sanctuary"] = &greater_blessing_of_sanctuary;
        creators["greater blessing of might on party"] = &greater_blessing_of_might_on_party;
        creators["greater blessing of kings on party"] = &greater_blessing_of_kings_on_party;
        creators["greater blessing of wisdom on party"] = &greater_blessing_of_wisdom_on_party;
    }

private:
    // 动作节点 greater_blessing_of_might：强效力量祝福 -> 备选(A)动作：力量祝福
    ACTION_NODE_A(greater_blessing_of_might, "greater blessing of might", "blessing of might");

    // 动作节点 greater_blessing_of_kings：强效王者祝福 -> 备选(A)动作：王者祝福
    ACTION_NODE_A(greater_blessing_of_kings, "greater blessing of kings", "blessing of kings");

    // 动作节点 greater_blessing_of_wisdom：强效智慧祝福 -> 备选(A)动作：智慧祝福
    ACTION_NODE_A(greater_blessing_of_wisdom, "greater blessing of wisdom", "blessing of wisdom");

    // 动作节点 greater_blessing_of_sanctuary：强效庇护祝福 -> 备选(A)动作：庇护祝福
    ACTION_NODE_A(greater_blessing_of_sanctuary, "greater blessing of sanctuary", "blessing of sanctuary");

    // 动作节点 greater_blessing_of_might_on_party：对队友施放强效力量祝福 -> 备选(A)动作：力量祝福 (对队友)
    ACTION_NODE_A(greater_blessing_of_might_on_party, "greater blessing of might on party", "blessing of might on party");

    // 动作节点 greater_blessing_of_kings_on_party：对队友施放强效王者祝福 -> 备选(A)动作：王者祝福 (对队友)
    ACTION_NODE_A(greater_blessing_of_kings_on_party, "greater blessing of kings on party", "blessing of kings on party");

    // 动作节点 greater_blessing_of_wisdom_on_party：对队友施放强效智慧祝福 -> 备选(A)动作：智慧祝福 (对队友)
    ACTION_NODE_A(greater_blessing_of_wisdom_on_party, "greater blessing of wisdom on party", "blessing of wisdom on party");

    // 构建 圣疗术 (lay_on_hands) 动作节点
    static ActionNode* lay_on_hands(PlayerbotAI* ai)
    {
        return new ActionNode("lay on hands",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("divine shield"), 
                                       new NextAction("flash of light"), NULL),
            /*C*/ NULL);
    }

    // 动作节点 lay_on_hands_on_party：对队友施放圣疗术 -> 备选(A)动作：圣光术 (对队友)
    ACTION_NODE_A(lay_on_hands_on_party, "lay on hands on party", "holy light on party");

    // 动作节点 cleanse_poison：祛毒 -> 备选(A)动作：purify poison
    ACTION_NODE_A(cleanse_poison, "cleanse poison", "purify poison");

    // 动作节点 cleanse_disease：祛病 -> 备选(A)动作：purify disease
    ACTION_NODE_A(cleanse_disease, "cleanse disease", "purify disease");

    // 动作节点 cleanse_poison_on_party：对队友祛毒 -> 备选(A)动作：purify poison on party
    ACTION_NODE_A(cleanse_poison_on_party, "cleanse poison on party", "purify poison on party");

    // 动作节点 cleanse_disease_on_party：对队友祛病 -> 备选(A)动作：purify disease on party
    ACTION_NODE_A(cleanse_disease_on_party, "cleanse disease on party", "purify disease on party");

    // 动作节点 judgement_of_wisdom：智慧审判 -> 备选(A)动作：圣光审判
    ACTION_NODE_A(judgement_of_wisdom, "judgement of wisdom", "judgement of light");

    // 动作节点 divine_shield：圣盾术 -> 备选(A)动作：圣佑术
    ACTION_NODE_A(divine_shield, "divine shield", "divine protection");

    // 动作节点 flash_of_light：圣光闪现 -> 备选(A)动作：圣光术
    ACTION_NODE_A(flash_of_light, "flash of light", "holy light");

    // 动作节点 flash_of_light_on_party：对队友施放圣光闪现 -> 备选(A)动作：圣光术 (对队友)
    ACTION_NODE_A(flash_of_light_on_party, "flash of light on party", "holy light on party");

    // 动作节点 holy_wrath：神圣愤怒 -> 备选(A)动作：奉献
    ACTION_NODE_A(holy_wrath, "holy wrath", "consecration");
};

// 构造函数：初始化圣骑士策略并挂载动作节点工厂
PaladinStrategy::PaladinStrategy(PlayerbotAI* ai) : ClassStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<PaladinStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (圣骑士策略)
void PaladinStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("lay on hands", ACTION_EMERGENCY + 2), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士策略)
void PaladinStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member dead",
        NextAction::array(0, new NextAction("redemption", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (圣骑士策略)
void PaladinStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (圣骑士策略)
void PaladinStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士PVP策略)
void PaladinPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士PVP策略)
void PaladinPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (圣骑士PVP策略)
void PaladinPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (圣骑士PVP策略)
void PaladinPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士PVE策略)
void PaladinPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士PVE策略)
void PaladinPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (圣骑士PVE策略)
void PaladinPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (圣骑士PVE策略)
void PaladinPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士团队副本策略)
void PaladinRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士团队副本策略)
void PaladinRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (圣骑士团队副本策略)
void PaladinRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (圣骑士团队副本策略)
void PaladinRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士AOE群体策略)
void PaladinAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士AOE群体策略)
void PaladinAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士AOE群体PVP策略)
void PaladinAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士AOE群体PVP策略)
void PaladinAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士AOE群体PVE策略)
void PaladinAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士AOE群体PVE策略)
void PaladinAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士AOE群体团队副本策略)
void PaladinAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士AOE群体团队副本策略)
void PaladinAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士驱散净化策略)
void PaladinCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rooted",
        NextAction::array(0, new NextAction("blessing of freedom", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member rooted",
        NextAction::array(0, new NextAction("blessing of freedom on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure disease",
        NextAction::array(0, new NextAction("cleanse disease", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure disease",
        NextAction::array(0, new NextAction("cleanse disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure poison",
        NextAction::array(0, new NextAction("cleanse poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure poison",
        NextAction::array(0, new NextAction("cleanse poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure magic",
        NextAction::array(0, new NextAction("cleanse magic", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure magic",
        NextAction::array(0, new NextAction("cleanse magic on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士驱散净化策略)
void PaladinCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rooted",
        NextAction::array(0, new NextAction("blessing of freedom", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member rooted",
        NextAction::array(0, new NextAction("blessing of freedom on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure disease",
        NextAction::array(0, new NextAction("cleanse disease", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure disease",
        NextAction::array(0, new NextAction("cleanse disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure poison",
        NextAction::array(0, new NextAction("cleanse poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure poison",
        NextAction::array(0, new NextAction("cleanse poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure magic",
        NextAction::array(0, new NextAction("cleanse magic", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure magic",
        NextAction::array(0, new NextAction("cleanse magic on party", ACTION_DISPEL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士驱散净化PVP策略)
void PaladinCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士驱散净化PVP策略)
void PaladinCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士驱散净化PVE策略)
void PaladinCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士驱散净化PVE策略)
void PaladinCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士驱散净化团队副本策略)
void PaladinCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士驱散净化团队副本策略)
void PaladinCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士控制(CC)策略)
void PaladinCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hammer of justice interrupt",
        NextAction::array(0, new NextAction("hammer of justice", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "hammer of justice on enemy healer",
        NextAction::array(0, new NextAction("hammer of justice on enemy healer", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "hammer of justice on snare target",
        NextAction::array(0, new NextAction("hammer of justice on snare target", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "turn undead",
        NextAction::array(0, new NextAction("turn undead", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士控制(CC)策略)
void PaladinCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士控制(CC)PVP策略)
void PaladinCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士控制(CC)PVP策略)
void PaladinCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士控制(CC)PVE策略)
void PaladinCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士控制(CC)PVE策略)
void PaladinCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士控制(CC)团队副本策略)
void PaladinCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士控制(CC)团队副本策略)
void PaladinCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士增益Buff策略)
void PaladinBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士增益Buff策略)
void PaladinBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士增益BuffPVP策略)
void PaladinBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士增益BuffPVP策略)
void PaladinBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士增益BuffPVE策略)
void PaladinBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士增益BuffPVE策略)
void PaladinBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士增益Buff团队副本策略)
void PaladinBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士增益Buff团队副本策略)
void PaladinBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士爆发增益策略)
void PaladinBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士爆发增益策略)
void PaladinBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士爆发增益PVP策略)
void PaladinBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士爆发增益PVP策略)
void PaladinBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士爆发增益PVE策略)
void PaladinBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士爆发增益PVE策略)
void PaladinBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士爆发增益团队副本策略)
void PaladinBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士爆发增益团队副本策略)
void PaladinBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士辅助治疗策略)
void PaladinOffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("lay on hands on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "protect party member",
        NextAction::array(0, new NextAction("blessing of protection on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士辅助治疗策略)
void PaladinOffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士辅助治疗PVP策略)
void PaladinOffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士辅助治疗PVP策略)
void PaladinOffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士辅助治疗PVE策略)
void PaladinOffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士辅助治疗PVE策略)
void PaladinOffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士辅助治疗团队副本策略)
void PaladinOffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitCombatTriggers(triggers);
    OffhealRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士辅助治疗团队副本策略)
void PaladinOffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士光环策略)
void PaladinAuraStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    
}

// 初始化非战斗阶段触发器列表 (圣骑士光环策略)
void PaladinAuraStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no paladin aura",
        NextAction::array(0, new NextAction("paladin aura", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士光环PVP策略)
void PaladinAuraPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士光环PVP策略)
void PaladinAuraPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (圣骑士光环PVE策略)
void PaladinAuraPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士光环PVE策略)
void PaladinAuraPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (圣骑士光环团队副本策略)
void PaladinAuraRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士光环团队副本策略)
void PaladinAuraRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (圣骑士祝福策略)
void PaladinBlessingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士祝福策略)
void PaladinBlessingStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (圣骑士祝福PVP策略)
void PaladinBlessingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "greater blessing on party",
        NextAction::array(0, new NextAction("pvp greater blessing on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing on party",
        NextAction::array(0, new NextAction("pvp blessing on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "greater blessing",
        NextAction::array(0, new NextAction("pvp greater blessing", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("pvp blessing", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士祝福PVP策略)
void PaladinBlessingPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "greater blessing on party",
        NextAction::array(0, new NextAction("pvp greater blessing on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing on party",
        NextAction::array(0, new NextAction("pvp blessing on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "greater blessing",
        NextAction::array(0, new NextAction("pvp greater blessing", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("pvp blessing", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士祝福PVE策略)
void PaladinBlessingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "greater blessing on party",
        NextAction::array(0, new NextAction("pvp greater blessing on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing on party",
        NextAction::array(0, new NextAction("pvp blessing on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "greater blessing",
        NextAction::array(0, new NextAction("pvp greater blessing", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("pvp blessing", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士祝福PVE策略)
void PaladinBlessingPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "greater blessing on party",
        NextAction::array(0, new NextAction("pve greater blessing on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing on party",
        NextAction::array(0, new NextAction("pve blessing on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "greater blessing",
        NextAction::array(0, new NextAction("pve greater blessing", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("pve blessing", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士祝福团队副本策略)
void PaladinBlessingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "greater blessing on party",
        NextAction::array(0, new NextAction("pve greater blessing on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing on party",
        NextAction::array(0, new NextAction("pve blessing on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "greater blessing",
        NextAction::array(0, new NextAction("pve greater blessing", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("pve blessing", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士祝福团队副本策略)
void PaladinBlessingRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "greater blessing on party",
        NextAction::array(0, new NextAction("raid greater blessing on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing on party",
        NextAction::array(0, new NextAction("raid blessing on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "greater blessing",
        NextAction::array(0, new NextAction("raid greater blessing", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("raid blessing", ACTION_NORMAL), NULL)));
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (圣骑士策略)
void PaladinStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("lay on hands", ACTION_EMERGENCY + 2), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士策略)
void PaladinStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member dead",
        NextAction::array(0, new NextAction("redemption", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (圣骑士策略)
void PaladinStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (圣骑士策略)
void PaladinStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士PVP策略)
void PaladinPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士PVP策略)
void PaladinPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (圣骑士PVP策略)
void PaladinPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (圣骑士PVP策略)
void PaladinPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士PVE策略)
void PaladinPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士PVE策略)
void PaladinPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (圣骑士PVE策略)
void PaladinPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (圣骑士PVE策略)
void PaladinPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士团队副本策略)
void PaladinRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士团队副本策略)
void PaladinRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (圣骑士团队副本策略)
void PaladinRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (圣骑士团队副本策略)
void PaladinRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士AOE群体策略)
void PaladinAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士AOE群体策略)
void PaladinAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士AOE群体PVP策略)
void PaladinAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士AOE群体PVP策略)
void PaladinAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士AOE群体PVE策略)
void PaladinAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士AOE群体PVE策略)
void PaladinAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士AOE群体团队副本策略)
void PaladinAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士AOE群体团队副本策略)
void PaladinAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士驱散净化策略)
void PaladinCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rooted",
        NextAction::array(0, new NextAction("blessing of freedom", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member rooted",
        NextAction::array(0, new NextAction("blessing of freedom on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure disease",
        NextAction::array(0, new NextAction("cleanse disease", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure disease",
        NextAction::array(0, new NextAction("cleanse disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure poison",
        NextAction::array(0, new NextAction("cleanse poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure poison",
        NextAction::array(0, new NextAction("cleanse poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure magic",
        NextAction::array(0, new NextAction("cleanse magic", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure magic",
        NextAction::array(0, new NextAction("cleanse magic on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士驱散净化策略)
void PaladinCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rooted",
        NextAction::array(0, new NextAction("blessing of freedom", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member rooted",
        NextAction::array(0, new NextAction("blessing of freedom on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure disease",
        NextAction::array(0, new NextAction("cleanse disease", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure disease",
        NextAction::array(0, new NextAction("cleanse disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure poison",
        NextAction::array(0, new NextAction("cleanse poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure poison",
        NextAction::array(0, new NextAction("cleanse poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure magic",
        NextAction::array(0, new NextAction("cleanse magic", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure magic",
        NextAction::array(0, new NextAction("cleanse magic on party", ACTION_DISPEL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士驱散净化PVP策略)
void PaladinCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士驱散净化PVP策略)
void PaladinCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士驱散净化PVE策略)
void PaladinCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士驱散净化PVE策略)
void PaladinCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士驱散净化团队副本策略)
void PaladinCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士驱散净化团队副本策略)
void PaladinCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士控制(CC)策略)
void PaladinCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hammer of justice interrupt",
        NextAction::array(0, new NextAction("hammer of justice", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "hammer of justice on enemy healer",
        NextAction::array(0, new NextAction("hammer of justice on enemy healer", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "hammer of justice on snare target",
        NextAction::array(0, new NextAction("hammer of justice on snare target", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "turn undead",
        NextAction::array(0, new NextAction("turn undead", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士控制(CC)策略)
void PaladinCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士控制(CC)PVP策略)
void PaladinCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士控制(CC)PVP策略)
void PaladinCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士控制(CC)PVE策略)
void PaladinCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士控制(CC)PVE策略)
void PaladinCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士控制(CC)团队副本策略)
void PaladinCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士控制(CC)团队副本策略)
void PaladinCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士增益Buff策略)
void PaladinBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("avenging wrath", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士增益Buff策略)
void PaladinBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士增益BuffPVP策略)
void PaladinBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士增益BuffPVP策略)
void PaladinBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士增益BuffPVE策略)
void PaladinBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士增益BuffPVE策略)
void PaladinBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士增益Buff团队副本策略)
void PaladinBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士增益Buff团队副本策略)
void PaladinBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士爆发增益策略)
void PaladinBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士爆发增益策略)
void PaladinBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士爆发增益PVP策略)
void PaladinBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士爆发增益PVP策略)
void PaladinBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士爆发增益PVE策略)
void PaladinBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士爆发增益PVE策略)
void PaladinBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士爆发增益团队副本策略)
void PaladinBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士爆发增益团队副本策略)
void PaladinBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士辅助治疗策略)
void PaladinOffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("lay on hands on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "protect party member",
        NextAction::array(0, new NextAction("blessing of protection on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士辅助治疗策略)
void PaladinOffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士辅助治疗PVP策略)
void PaladinOffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士辅助治疗PVP策略)
void PaladinOffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士辅助治疗PVE策略)
void PaladinOffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士辅助治疗PVE策略)
void PaladinOffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士辅助治疗团队副本策略)
void PaladinOffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitCombatTriggers(triggers);
    OffhealRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士辅助治疗团队副本策略)
void PaladinOffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士光环策略)
void PaladinAuraStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士光环策略)
void PaladinAuraStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no paladin aura",
        NextAction::array(0, new NextAction("paladin aura", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士光环PVP策略)
void PaladinAuraPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士光环PVP策略)
void PaladinAuraPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (圣骑士光环PVE策略)
void PaladinAuraPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士光环PVE策略)
void PaladinAuraPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (圣骑士光环团队副本策略)
void PaladinAuraRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士光环团队副本策略)
void PaladinAuraRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (圣骑士祝福策略)
void PaladinBlessingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士祝福策略)
void PaladinBlessingStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (圣骑士祝福PVP策略)
void PaladinBlessingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士祝福PVP策略)
void PaladinBlessingPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "greater blessing on party",
        NextAction::array(0, new NextAction("pvp greater blessing on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing on party",
        NextAction::array(0, new NextAction("pvp blessing on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "greater blessing",
        NextAction::array(0, new NextAction("pvp greater blessing", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("pvp blessing", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士祝福PVE策略)
void PaladinBlessingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士祝福PVE策略)
void PaladinBlessingPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "greater blessing on party",
        NextAction::array(0, new NextAction("pve greater blessing on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing on party",
        NextAction::array(0, new NextAction("pve blessing on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "greater blessing",
        NextAction::array(0, new NextAction("pve greater blessing", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("pve blessing", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士祝福团队副本策略)
void PaladinBlessingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士祝福团队副本策略)
void PaladinBlessingRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "greater blessing on party",
        NextAction::array(0, new NextAction("raid greater blessing on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing on party",
        NextAction::array(0, new NextAction("raid blessing on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "greater blessing",
        NextAction::array(0, new NextAction("raid greater blessing", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("raid blessing", ACTION_NORMAL), NULL)));
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (圣骑士策略)
void PaladinStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("lay on hands", ACTION_EMERGENCY + 2), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士策略)
void PaladinStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member dead",
        NextAction::array(0, new NextAction("redemption", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (圣骑士策略)
void PaladinStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (圣骑士策略)
void PaladinStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士PVP策略)
void PaladinPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士PVP策略)
void PaladinPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (圣骑士PVP策略)
void PaladinPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (圣骑士PVP策略)
void PaladinPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士PVE策略)
void PaladinPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士PVE策略)
void PaladinPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (圣骑士PVE策略)
void PaladinPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (圣骑士PVE策略)
void PaladinPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士团队副本策略)
void PaladinRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士团队副本策略)
void PaladinRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (圣骑士团队副本策略)
void PaladinRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (圣骑士团队副本策略)
void PaladinRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士AOE群体策略)
void PaladinAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士AOE群体策略)
void PaladinAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士AOE群体PVP策略)
void PaladinAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士AOE群体PVP策略)
void PaladinAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士AOE群体PVE策略)
void PaladinAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士AOE群体PVE策略)
void PaladinAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士AOE群体团队副本策略)
void PaladinAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士AOE群体团队副本策略)
void PaladinAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士驱散净化策略)
void PaladinCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rooted",
        NextAction::array(0, new NextAction("blessing of freedom", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member rooted",
        NextAction::array(0, new NextAction("blessing of freedom on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure disease",
        NextAction::array(0, new NextAction("cleanse disease", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure disease",
        NextAction::array(0, new NextAction("cleanse disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure poison",
        NextAction::array(0, new NextAction("cleanse poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure poison",
        NextAction::array(0, new NextAction("cleanse poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure magic",
        NextAction::array(0, new NextAction("cleanse magic", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure magic",
        NextAction::array(0, new NextAction("cleanse magic on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士驱散净化策略)
void PaladinCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rooted",
        NextAction::array(0, new NextAction("blessing of freedom", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member rooted",
        NextAction::array(0, new NextAction("blessing of freedom on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure disease",
        NextAction::array(0, new NextAction("cleanse disease", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure disease",
        NextAction::array(0, new NextAction("cleanse disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure poison",
        NextAction::array(0, new NextAction("cleanse poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure poison",
        NextAction::array(0, new NextAction("cleanse poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure magic",
        NextAction::array(0, new NextAction("cleanse magic", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure magic",
        NextAction::array(0, new NextAction("cleanse magic on party", ACTION_DISPEL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士驱散净化PVP策略)
void PaladinCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士驱散净化PVP策略)
void PaladinCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士驱散净化PVE策略)
void PaladinCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士驱散净化PVE策略)
void PaladinCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士驱散净化团队副本策略)
void PaladinCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士驱散净化团队副本策略)
void PaladinCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士控制(CC)策略)
void PaladinCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "hammer of justice interrupt",
        NextAction::array(0, new NextAction("hammer of justice", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "hammer of justice on enemy healer",
        NextAction::array(0, new NextAction("hammer of justice on enemy healer", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "hammer of justice on snare target",
        NextAction::array(0, new NextAction("hammer of justice on snare target", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "turn undead",
        NextAction::array(0, new NextAction("turn undead", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士控制(CC)策略)
void PaladinCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士控制(CC)PVP策略)
void PaladinCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士控制(CC)PVP策略)
void PaladinCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士控制(CC)PVE策略)
void PaladinCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士控制(CC)PVE策略)
void PaladinCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士控制(CC)团队副本策略)
void PaladinCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士控制(CC)团队副本策略)
void PaladinCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士增益Buff策略)
void PaladinBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("avenging wrath", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士增益Buff策略)
void PaladinBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply stone", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士增益BuffPVP策略)
void PaladinBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士增益BuffPVP策略)
void PaladinBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士增益BuffPVE策略)
void PaladinBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士增益BuffPVE策略)
void PaladinBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士增益Buff团队副本策略)
void PaladinBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士增益Buff团队副本策略)
void PaladinBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士爆发增益策略)
void PaladinBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士爆发增益策略)
void PaladinBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士爆发增益PVP策略)
void PaladinBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士爆发增益PVP策略)
void PaladinBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士爆发增益PVE策略)
void PaladinBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士爆发增益PVE策略)
void PaladinBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士爆发增益团队副本策略)
void PaladinBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士爆发增益团队副本策略)
void PaladinBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士辅助治疗策略)
void PaladinOffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("lay on hands on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "protect party member",
        NextAction::array(0, new NextAction("blessing of protection on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士辅助治疗策略)
void PaladinOffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士辅助治疗PVP策略)
void PaladinOffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士辅助治疗PVP策略)
void PaladinOffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士辅助治疗PVE策略)
void PaladinOffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士辅助治疗PVE策略)
void PaladinOffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士辅助治疗团队副本策略)
void PaladinOffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitCombatTriggers(triggers);
    OffhealRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (圣骑士辅助治疗团队副本策略)
void PaladinOffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PaladinOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (圣骑士光环策略)
void PaladinAuraStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士光环策略)
void PaladinAuraStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no paladin aura",
        NextAction::array(0, new NextAction("paladin aura", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士光环PVP策略)
void PaladinAuraPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士光环PVP策略)
void PaladinAuraPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (圣骑士光环PVE策略)
void PaladinAuraPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士光环PVE策略)
void PaladinAuraPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (圣骑士光环团队副本策略)
void PaladinAuraRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士光环团队副本策略)
void PaladinAuraRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (圣骑士祝福策略)
void PaladinBlessingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士祝福策略)
void PaladinBlessingStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (圣骑士祝福PVP策略)
void PaladinBlessingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士祝福PVP策略)
void PaladinBlessingPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "greater blessing on party",
        NextAction::array(0, new NextAction("pvp greater blessing on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing on party",
        NextAction::array(0, new NextAction("pvp blessing on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "greater blessing",
        NextAction::array(0, new NextAction("pvp greater blessing", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("pvp blessing", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士祝福PVE策略)
void PaladinBlessingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士祝福PVE策略)
void PaladinBlessingPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "greater blessing on party",
        NextAction::array(0, new NextAction("pve greater blessing on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing on party",
        NextAction::array(0, new NextAction("pve blessing on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "greater blessing",
        NextAction::array(0, new NextAction("pve greater blessing", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("pve blessing", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (圣骑士祝福团队副本策略)
void PaladinBlessingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (圣骑士祝福团队副本策略)
void PaladinBlessingRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "greater blessing on party",
        NextAction::array(0, new NextAction("raid greater blessing on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing on party",
        NextAction::array(0, new NextAction("raid blessing on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "greater blessing",
        NextAction::array(0, new NextAction("raid greater blessing", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("raid blessing", ACTION_NORMAL), NULL)));
}

#endif

// 初始化非战斗阶段触发器列表 (圣骑士手动光环策略)
void PaladinManualAuraStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        triggerName,
        NextAction::array(0, new NextAction(actionName, ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (圣骑士手动祝福策略)
void PaladinManualBlessingStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "greater " + triggerName + " on party",
        NextAction::array(0, new NextAction("greater " + actionName + " on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        triggerName + " on party",
        NextAction::array(0, new NextAction(actionName + " on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "greater " + triggerName,
        NextAction::array(0, new NextAction("greater " + actionName, ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        triggerName,
        NextAction::array(0, new NextAction(actionName, ACTION_NORMAL), NULL)));
}
