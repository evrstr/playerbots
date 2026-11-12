// 牧师 - 牧师策略实现文件 (PriestStrategy.cpp)
#include "playerbot/playerbot.h"
#include "PriestStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class PriestStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    PriestStrategyActionNodeFactory()
    {
        creators["abolish disease"] = &abolish_disease;
        creators["abolish disease on party"] = &abolish_disease_on_party;
        creators["greater heal"] = &greater_heal;
        creators["greater heal on party"] = &greater_heal_on_party;
        creators["heal"] = &heal;
        creators["heal on party"] = &heal_on_party;
        creators["flash heal"] = &flash_heal;
        creators["flash heal on party"] = &flash_heal_on_party;
        creators["renew"] = &renew;
        creators["renew on party"] = &renew_on_party;
        creators["resurrection"] = &resurrection;
    }

private:
    // 动作节点 abolish_disease：驱除疾病 -> 备选(A)动作：祛病术
    ACTION_NODE_A(abolish_disease, "abolish disease", "cure disease");

    // 动作节点 abolish_disease_on_party：对队友驱除疾病 -> 备选(A)动作：祛病术 (对队友)
    ACTION_NODE_A(abolish_disease_on_party, "abolish disease on party", "cure disease on party");

    // 构建 强效治疗术 (greater_heal) 动作节点
    static ActionNode* greater_heal(PlayerbotAI* ai)
    {
        return new ActionNode("greater heal",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("heal"), NULL),
            /*C*/ NULL);
    }

    // 构建 强效治疗术 (对队友) (greater_heal_on_party) 动作节点
    static ActionNode* greater_heal_on_party(PlayerbotAI* ai)
    {
        return new ActionNode("greater heal on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("heal on party"), NULL),
            /*C*/ NULL);
    }

    // 构建 治疗术 (heal) 动作节点
    static ActionNode* heal(PlayerbotAI* ai)
    {
        return new ActionNode("heal",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lesser heal"), NULL),
            /*C*/ NULL);
    }

    // 构建 治疗术 (对队友) (heal_on_party) 动作节点
    static ActionNode* heal_on_party(PlayerbotAI* ai)
    {
        return new ActionNode("heal on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lesser heal on party"), NULL),
            /*C*/ NULL);
    }

    // 构建 快速治疗 (flash_heal) 动作节点
    static ActionNode* flash_heal(PlayerbotAI* ai)
    {
        return new ActionNode("flash heal",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("greater heal"), NULL),
            /*C*/ NULL);
    }

    // 构建 快速治疗 (对队友) (flash_heal_on_party) 动作节点
    static ActionNode* flash_heal_on_party(PlayerbotAI* ai)
    {
        return new ActionNode("flash heal on party",
            /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
            /*A*/ NextAction::array(0, new NextAction("greater heal on party"), NULL),
            /*C*/ NULL);
    }

    // 动作节点 renew：恢复 -> 前置(P)动作：取消暗影形态
    ACTION_NODE_P(renew, "renew", "remove shadowform");

    // 动作节点 renew_on_party：对队友施放恢复 -> 前置(P)动作：取消暗影形态
    ACTION_NODE_P(renew_on_party, "renew on party", "remove shadowform");

    // 动作节点 resurrection：复活术 -> 前置(P)动作：取消暗影形态
    ACTION_NODE_P(resurrection, "resurrection", "remove shadowform");
};

// 构造函数：初始化牧师策略并挂载动作节点工厂
PriestStrategy::PriestStrategy(PlayerbotAI* ai) : ClassStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<PriestStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (牧师策略)
void PriestStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("desperate prayer", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("flash heal", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("greater heal", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "target of attacker",
        NextAction::array(0, new NextAction("power word: shield", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师策略)
void PriestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member dead",
        NextAction::array(0, new NextAction("resurrection", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (牧师策略)
void PriestStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (牧师策略)
void PriestStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师PVP策略)
void PriestPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师PVP策略)
void PriestPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (牧师PVP策略)
void PriestPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (牧师PVP策略)
void PriestPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师PVE策略)
void PriestPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师PVE策略)
void PriestPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (牧师PVE策略)
void PriestPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (牧师PVE策略)
void PriestPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师团队副本策略)
void PriestRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("fade", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师团队副本策略)
void PriestRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (牧师团队副本策略)
void PriestRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (牧师团队副本策略)
void PriestRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师AOE群体策略)
void PriestAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师AOE群体策略)
void PriestAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师AOE群体PVP策略)
void PriestAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师AOE群体PVP策略)
void PriestAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师AOE群体PVE策略)
void PriestAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师AOE群体PVE策略)
void PriestAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师AOE群体团队副本策略)
void PriestAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师AOE群体团队副本策略)
void PriestAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师驱散净化策略)
void PriestCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "dispel magic",
        NextAction::array(0, new NextAction("dispel magic", ACTION_DISPEL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "dispel magic on party",
        NextAction::array(0, new NextAction("dispel magic on party", ACTION_DISPEL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("abolish disease", ACTION_DISPEL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("abolish disease on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师驱散净化策略)
void PriestCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "dispel magic",
        NextAction::array(0, new NextAction("dispel magic", ACTION_DISPEL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "dispel magic on party",
        NextAction::array(0, new NextAction("dispel magic on party", ACTION_DISPEL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("abolish disease", ACTION_DISPEL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("abolish disease on party", ACTION_DISPEL), NULL)));
}

// 初始化战斗阶段触发器列表 (牧师驱散净化PVP策略)
void PriestCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师驱散净化PVP策略)
void PriestCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师驱散净化PVE策略)
void PriestCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师驱散净化PVE策略)
void PriestCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师驱散净化团队副本策略)
void PriestCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师驱散净化团队副本策略)
void PriestCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师控制(CC)策略)
void PriestCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shackle undead",
        NextAction::array(0, new NextAction("shackle undead", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy five yards",
        NextAction::array(0, new NextAction("psychic scream", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师控制(CC)策略)
void PriestCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师控制(CC)PVP策略)
void PriestCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师控制(CC)PVP策略)
void PriestCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师控制(CC)PVE策略)
void PriestCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师控制(CC)PVE策略)
void PriestCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师控制(CC)团队副本策略)
void PriestCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师控制(CC)团队副本策略)
void PriestCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师增益Buff策略)
void PriestBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "fear ward",
        NextAction::array(0, new NextAction("fear ward", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "target of attacker",
        NextAction::array(0, new NextAction("elune's grace", ACTION_HIGH + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师增益Buff策略)
void PriestBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "prayer of fortitude on party",
        NextAction::array(0, new NextAction("prayer of fortitude on party", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "prayer of spirit on party",
        NextAction::array(0, new NextAction("prayer of spirit on party", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "prayer of shadow protection on party",
        NextAction::array(0, new NextAction("prayer of shadow protection on party", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "power word: fortitude on party",
        NextAction::array(0, new NextAction("power word: fortitude on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "divine spirit on party",
        NextAction::array(0, new NextAction("divine spirit on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow protection on party",
        NextAction::array(0, new NextAction("shadow protection on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "power word: fortitude",
        NextAction::array(0, new NextAction("power word: fortitude", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "divine spirit",
        NextAction::array(0, new NextAction("divine spirit", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow protection",
        NextAction::array(0, new NextAction("shadow protection", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "inner fire",
        NextAction::array(0, new NextAction("inner fire", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "fear ward",
        NextAction::array(0, new NextAction("fear ward", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "touch of weakness",
        NextAction::array(0, new NextAction("touch of weakness", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "shadowguard",
        NextAction::array(0, new NextAction("shadowguard", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));

    /*
    triggers.push_back(new TriggerNode(
        "swimming",
        NextAction::array(0, new NextAction("levitate", ACTION_NORMAL), NULL)));
    */
}

// 初始化战斗阶段触发器列表 (牧师增益BuffPVP策略)
void PriestBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师增益BuffPVP策略)
void PriestBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师增益BuffPVE策略)
void PriestBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师增益BuffPVE策略)
void PriestBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师增益Buff团队副本策略)
void PriestBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师增益Buff团队副本策略)
void PriestBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师爆发增益策略)
void PriestBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "power infusion",
        NextAction::array(0, new NextAction("power infusion", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "inner focus",
        NextAction::array(0, new NextAction("inner focus", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师爆发增益策略)
void PriestBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师爆发增益PVP策略)
void PriestBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师爆发增益PVP策略)
void PriestBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师爆发增益PVE策略)
void PriestBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师爆发增益PVE策略)
void PriestBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师爆发增益团队副本策略)
void PriestBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师爆发增益团队副本策略)
void PriestBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助治疗策略)
void PriestOffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("flash heal on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("renew on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师辅助治疗策略)
void PriestOffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化战斗阶段触发器列表 (牧师辅助治疗PVP策略)
void PriestOffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助治疗PVP策略)
void PriestOffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助治疗PVE策略)
void PriestOffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助治疗PVE策略)
void PriestOffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助治疗团队副本策略)
void PriestOffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitCombatTriggers(triggers);
    OffhealRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助治疗团队副本策略)
void PriestOffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助输出策略)
void PriestOffdpsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffdpsStrategy::InitCombatTriggers(triggers);

    if (ai->HasStrategy("aoe", BotState::BOT_STATE_COMBAT))
    {
        triggers.push_back(new TriggerNode(
            "shadow word: pain on attacker",
            NextAction::array(0, new NextAction("shadow word: pain on attacker", ACTION_HIGH + 1), NULL)));

        triggers.push_back(new TriggerNode(
            "melee medium aoe",
            NextAction::array(0, new NextAction("holy nova", ACTION_HIGH), NULL)));
    }

    triggers.push_back(new TriggerNode(
        "shadow word: pain",
        NextAction::array(0, new NextAction("shadow word: pain", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "holy fire",
        NextAction::array(0, new NextAction("holy fire", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("starshards", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "smite",
        NextAction::array(0, new NextAction("smite", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana",
        NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师辅助输出策略)
void PriestOffdpsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffdpsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助输出PVP策略)
void PriestOffdpsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitCombatTriggers(triggers);
    OffdpsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助输出PVP策略)
void PriestOffdpsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitNonCombatTriggers(triggers);
    OffdpsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助输出PVE策略)
void PriestOffdpsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitCombatTriggers(triggers);
    OffdpsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助输出PVE策略)
void PriestOffdpsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitNonCombatTriggers(triggers);
    OffdpsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助输出团队副本策略)
void PriestOffdpsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitCombatTriggers(triggers);
    OffdpsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助输出团队副本策略)
void PriestOffdpsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitNonCombatTriggers(triggers);
    OffdpsRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (牧师策略)
void PriestStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("desperate prayer", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("flash heal", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("greater heal", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "target of attacker",
        NextAction::array(0, new NextAction("power word: shield", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师策略)
void PriestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member dead",
        NextAction::array(0, new NextAction("resurrection", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (牧师策略)
void PriestStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (牧师策略)
void PriestStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师PVP策略)
void PriestPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师PVP策略)
void PriestPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (牧师PVP策略)
void PriestPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (牧师PVP策略)
void PriestPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师PVE策略)
void PriestPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师PVE策略)
void PriestPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (牧师PVE策略)
void PriestPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (牧师PVE策略)
void PriestPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师团队副本策略)
void PriestRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("fade", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师团队副本策略)
void PriestRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (牧师团队副本策略)
void PriestRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (牧师团队副本策略)
void PriestRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师AOE群体策略)
void PriestAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师AOE群体策略)
void PriestAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师AOE群体PVP策略)
void PriestAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师AOE群体PVP策略)
void PriestAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师AOE群体PVE策略)
void PriestAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师AOE群体PVE策略)
void PriestAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师AOE群体团队副本策略)
void PriestAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师AOE群体团队副本策略)
void PriestAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师驱散净化策略)
void PriestCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "dispel magic",
        NextAction::array(0, new NextAction("dispel magic", ACTION_DISPEL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "dispel magic on party",
        NextAction::array(0, new NextAction("dispel magic on party", ACTION_DISPEL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("abolish disease", ACTION_DISPEL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("abolish disease on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师驱散净化策略)
void PriestCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "dispel magic",
        NextAction::array(0, new NextAction("dispel magic", ACTION_DISPEL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "dispel magic on party",
        NextAction::array(0, new NextAction("dispel magic on party", ACTION_DISPEL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("abolish disease", ACTION_DISPEL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("abolish disease on party", ACTION_DISPEL), NULL)));
}

// 初始化战斗阶段触发器列表 (牧师驱散净化PVP策略)
void PriestCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师驱散净化PVP策略)
void PriestCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师驱散净化PVE策略)
void PriestCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师驱散净化PVE策略)
void PriestCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师驱散净化团队副本策略)
void PriestCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师驱散净化团队副本策略)
void PriestCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师控制(CC)策略)
void PriestCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "chastise",
        NextAction::array(0, new NextAction("chastise", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "shackle undead",
        NextAction::array(0, new NextAction("shackle undead", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy five yards",
        NextAction::array(0, new NextAction("psychic scream", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师控制(CC)策略)
void PriestCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师控制(CC)PVP策略)
void PriestCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师控制(CC)PVP策略)
void PriestCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师控制(CC)PVE策略)
void PriestCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师控制(CC)PVE策略)
void PriestCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师控制(CC)团队副本策略)
void PriestCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师控制(CC)团队副本策略)
void PriestCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师增益Buff策略)
void PriestBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "fear ward",
        NextAction::array(0, new NextAction("fear ward", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "target of attacker",
        NextAction::array(0, new NextAction("elune's grace", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "medium mana",
        NextAction::array(0, new NextAction("symbol of hope", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("shadowfiend", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师增益Buff策略)
void PriestBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "prayer of fortitude on party",
        NextAction::array(0, new NextAction("prayer of fortitude on party", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "prayer of spirit on party",
        NextAction::array(0, new NextAction("prayer of spirit on party", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "prayer of shadow protection on party",
        NextAction::array(0, new NextAction("prayer of shadow protection on party", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "power word: fortitude on party",
        NextAction::array(0, new NextAction("power word: fortitude on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "divine spirit on party",
        NextAction::array(0, new NextAction("divine spirit on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow protection on party",
        NextAction::array(0, new NextAction("shadow protection on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "power word: fortitude",
        NextAction::array(0, new NextAction("power word: fortitude", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "divine spirit",
        NextAction::array(0, new NextAction("divine spirit", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow protection",
        NextAction::array(0, new NextAction("shadow protection", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "inner fire",
        NextAction::array(0, new NextAction("inner fire", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "fear ward",
        NextAction::array(0, new NextAction("fear ward", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "touch of weakness",
        NextAction::array(0, new NextAction("touch of weakness", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "shadowguard",
        NextAction::array(0, new NextAction("shadowguard", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));

    /*
    triggers.push_back(new TriggerNode(
        "swimming",
        NextAction::array(0, new NextAction("levitate", ACTION_NORMAL), NULL)));
    */
}

// 初始化战斗阶段触发器列表 (牧师增益BuffPVP策略)
void PriestBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师增益BuffPVP策略)
void PriestBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师增益BuffPVE策略)
void PriestBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师增益BuffPVE策略)
void PriestBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师增益Buff团队副本策略)
void PriestBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师增益Buff团队副本策略)
void PriestBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师爆发增益策略)
void PriestBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "inner focus",
        NextAction::array(0, new NextAction("inner focus", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师爆发增益策略)
void PriestBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师爆发增益PVP策略)
void PriestBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师爆发增益PVP策略)
void PriestBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师爆发增益PVE策略)
void PriestBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师爆发增益PVE策略)
void PriestBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师爆发增益团队副本策略)
void PriestBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师爆发增益团队副本策略)
void PriestBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助治疗策略)
void PriestOffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("flash heal on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("renew on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师辅助治疗策略)
void PriestOffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化战斗阶段触发器列表 (牧师辅助治疗PVP策略)
void PriestOffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助治疗PVP策略)
void PriestOffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助治疗PVE策略)
void PriestOffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助治疗PVE策略)
void PriestOffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助治疗团队副本策略)
void PriestOffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitCombatTriggers(triggers);
    OffhealRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助治疗团队副本策略)
void PriestOffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助输出策略)
void PriestOffdpsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffdpsStrategy::InitCombatTriggers(triggers);

    if (ai->HasStrategy("aoe", BotState::BOT_STATE_COMBAT))
    {
        triggers.push_back(new TriggerNode(
            "shadow word: pain on attacker",
            NextAction::array(0, new NextAction("shadow word: pain on attacker", ACTION_HIGH + 1), NULL)));

        triggers.push_back(new TriggerNode(
            "melee medium aoe",
            NextAction::array(0, new NextAction("holy nova", ACTION_HIGH), NULL)));
    }

    triggers.push_back(new TriggerNode(
        "shadow word: pain",
        NextAction::array(0, new NextAction("shadow word: pain", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "holy fire",
        NextAction::array(0, new NextAction("holy fire", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("starshards", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "smite",
        NextAction::array(0, new NextAction("smite", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana",
        NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师辅助输出策略)
void PriestOffdpsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffdpsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助输出PVP策略)
void PriestOffdpsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitCombatTriggers(triggers);
    OffdpsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助输出PVP策略)
void PriestOffdpsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitNonCombatTriggers(triggers);
    OffdpsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助输出PVE策略)
void PriestOffdpsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitCombatTriggers(triggers);
    OffdpsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助输出PVE策略)
void PriestOffdpsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitNonCombatTriggers(triggers);
    OffdpsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助输出团队副本策略)
void PriestOffdpsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitCombatTriggers(triggers);
    OffdpsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助输出团队副本策略)
void PriestOffdpsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitNonCombatTriggers(triggers);
    OffdpsRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (牧师策略)
void PriestStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("desperate prayer", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("flash heal", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("greater heal", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "target of attacker",
        NextAction::array(0, new NextAction("power word: shield", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师策略)
void PriestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member dead",
        NextAction::array(0, new NextAction("resurrection", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (牧师策略)
void PriestStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (牧师策略)
void PriestStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师PVP策略)
void PriestPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师PVP策略)
void PriestPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (牧师PVP策略)
void PriestPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (牧师PVP策略)
void PriestPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师PVE策略)
void PriestPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师PVE策略)
void PriestPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (牧师PVE策略)
void PriestPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (牧师PVE策略)
void PriestPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师团队副本策略)
void PriestRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("fade", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师团队副本策略)
void PriestRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (牧师团队副本策略)
void PriestRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (牧师团队副本策略)
void PriestRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师AOE群体策略)
void PriestAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师AOE群体策略)
void PriestAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师AOE群体PVP策略)
void PriestAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师AOE群体PVP策略)
void PriestAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师AOE群体PVE策略)
void PriestAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师AOE群体PVE策略)
void PriestAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师AOE群体团队副本策略)
void PriestAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师AOE群体团队副本策略)
void PriestAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师驱散净化策略)
void PriestCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "dispel magic",
        NextAction::array(0, new NextAction("dispel magic", ACTION_DISPEL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "dispel magic on party",
        NextAction::array(0, new NextAction("dispel magic on party", ACTION_DISPEL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("abolish disease", ACTION_DISPEL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("abolish disease on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师驱散净化策略)
void PriestCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "dispel magic",
        NextAction::array(0, new NextAction("dispel magic", ACTION_DISPEL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "dispel magic on party",
        NextAction::array(0, new NextAction("dispel magic on party", ACTION_DISPEL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("abolish disease", ACTION_DISPEL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("abolish disease on party", ACTION_DISPEL), NULL)));
}

// 初始化战斗阶段触发器列表 (牧师驱散净化PVP策略)
void PriestCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师驱散净化PVP策略)
void PriestCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师驱散净化PVE策略)
void PriestCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师驱散净化PVE策略)
void PriestCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师驱散净化团队副本策略)
void PriestCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师驱散净化团队副本策略)
void PriestCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师控制(CC)策略)
void PriestCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shackle undead",
        NextAction::array(0, new NextAction("shackle undead", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy five yards",
        NextAction::array(0, new NextAction("psychic scream", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师控制(CC)策略)
void PriestCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师控制(CC)PVP策略)
void PriestCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师控制(CC)PVP策略)
void PriestCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师控制(CC)PVE策略)
void PriestCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师控制(CC)PVE策略)
void PriestCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师控制(CC)团队副本策略)
void PriestCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师控制(CC)团队副本策略)
void PriestCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师增益Buff策略)
void PriestBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "fear ward",
        NextAction::array(0, new NextAction("fear ward", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "target of attacker",
        NextAction::array(0, new NextAction("elune's grace", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("shadowfiend", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师增益Buff策略)
void PriestBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "prayer of fortitude on party",
        NextAction::array(0, new NextAction("prayer of fortitude on party", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "prayer of spirit on party",
        NextAction::array(0, new NextAction("prayer of spirit on party", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "prayer of shadow protection on party",
        NextAction::array(0, new NextAction("prayer of shadow protection on party", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "power word: fortitude on party",
        NextAction::array(0, new NextAction("power word: fortitude on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "divine spirit on party",
        NextAction::array(0, new NextAction("divine spirit on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow protection on party",
        NextAction::array(0, new NextAction("shadow protection on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "power word: fortitude",
        NextAction::array(0, new NextAction("power word: fortitude", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "divine spirit",
        NextAction::array(0, new NextAction("divine spirit", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow protection",
        NextAction::array(0, new NextAction("shadow protection", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "inner fire",
        NextAction::array(0, new NextAction("inner fire", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "fear ward",
        NextAction::array(0, new NextAction("fear ward", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "touch of weakness",
        NextAction::array(0, new NextAction("touch of weakness", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "shadowguard",
        NextAction::array(0, new NextAction("shadowguard", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));

    /*
    triggers.push_back(new TriggerNode(
        "swimming",
        NextAction::array(0, new NextAction("levitate", ACTION_NORMAL), NULL)));
    */
}

// 初始化战斗阶段触发器列表 (牧师增益BuffPVP策略)
void PriestBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师增益BuffPVP策略)
void PriestBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师增益BuffPVE策略)
void PriestBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师增益BuffPVE策略)
void PriestBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师增益Buff团队副本策略)
void PriestBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师增益Buff团队副本策略)
void PriestBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师爆发增益策略)
void PriestBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "inner focus",
        NextAction::array(0, new NextAction("inner focus", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师爆发增益策略)
void PriestBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师爆发增益PVP策略)
void PriestBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师爆发增益PVP策略)
void PriestBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师爆发增益PVE策略)
void PriestBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师爆发增益PVE策略)
void PriestBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师爆发增益团队副本策略)
void PriestBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师爆发增益团队副本策略)
void PriestBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助治疗策略)
void PriestOffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_CRITICAL_HEAL + 1),
                             new NextAction("flash heal on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("renew on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师辅助治疗策略)
void PriestOffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化战斗阶段触发器列表 (牧师辅助治疗PVP策略)
void PriestOffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助治疗PVP策略)
void PriestOffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助治疗PVE策略)
void PriestOffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助治疗PVE策略)
void PriestOffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助治疗团队副本策略)
void PriestOffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitCombatTriggers(triggers);
    OffhealRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助治疗团队副本策略)
void PriestOffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助输出策略)
void PriestOffdpsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffdpsStrategy::InitCombatTriggers(triggers);

    if (ai->HasStrategy("aoe", BotState::BOT_STATE_COMBAT))
    {
        triggers.push_back(new TriggerNode(
            "shadow word: pain on attacker",
            NextAction::array(0, new NextAction("shadow word: pain on attacker", ACTION_HIGH + 1), NULL)));

        triggers.push_back(new TriggerNode(
            "melee medium aoe",
            NextAction::array(0, new NextAction("holy nova", ACTION_HIGH), NULL)));
    }

    triggers.push_back(new TriggerNode(
        "shadow word: pain",
        NextAction::array(0, new NextAction("shadow word: pain", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "holy fire",
        NextAction::array(0, new NextAction("holy fire", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("starshards", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "smite",
        NextAction::array(0, new NextAction("smite", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana",
        NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (牧师辅助输出策略)
void PriestOffdpsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffdpsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助输出PVP策略)
void PriestOffdpsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitCombatTriggers(triggers);
    OffdpsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助输出PVP策略)
void PriestOffdpsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitNonCombatTriggers(triggers);
    OffdpsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助输出PVE策略)
void PriestOffdpsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitCombatTriggers(triggers);
    OffdpsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助输出PVE策略)
void PriestOffdpsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitNonCombatTriggers(triggers);
    OffdpsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (牧师辅助输出团队副本策略)
void PriestOffdpsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitCombatTriggers(triggers);
    OffdpsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (牧师辅助输出团队副本策略)
void PriestOffdpsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    PriestOffdpsStrategy::InitNonCombatTriggers(triggers);
    OffdpsRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
