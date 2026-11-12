// 潜行者 - 潜行者策略实现文件 (RogueStrategy.cpp)

#include "playerbot/playerbot.h"
#include "RogueMultipliers.h"
#include "RogueStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class RogueStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    RogueStrategyActionNodeFactory()
    {
        creators["sinister strike"] = &sinister_strike;
        creators["kick"] = &kick;
        creators["kidney shot"] = &kidney_shot;
        creators["slice and dice"] = &slice_and_dice;
        creators["eviscerate"] = &eviscerate;
        creators["sap"] = &sap;
    }

private:
    // 动作节点 sinister_strike：邪恶攻击 -> 备选(A)动作：melee
    ACTION_NODE_A(sinister_strike, "sinister strike", "melee");

    // 动作节点 kick：脚踢 -> 备选(A)动作：肾击
    ACTION_NODE_A(kick, "kick", "kidney shot");

    // 动作节点 kidney_shot：肾击 -> 备选(A)动作：凿击
    ACTION_NODE_A(kidney_shot, "kidney shot", "gouge");

    // 动作节点 eviscerate：刺骨 -> 备选(A)动作：割裂
    ACTION_NODE_A(eviscerate, "eviscerate", "rupture");

    // 动作节点 slice_and_dice：切割 -> 备选(A)动作：刺骨
    ACTION_NODE_A(slice_and_dice, "slice and dice", "eviscerate");

    // 动作节点 sap：闷棍 -> 备选(A)动作：致盲
    ACTION_NODE_A(sap, "sap", "blind");
};

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class RogueStealthStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    RogueStealthStrategyActionNodeFactory()
    {
        creators["ambush"] = &ambush;
        creators["backstab"] = &backstab;
        creators["cheap shot"] = &cheap_shot;
    }

private:
    // 动作节点 ambush：伏击 -> 备选(A)动作：背刺
    ACTION_NODE_A(ambush, "ambush", "backstab");

    // 动作节点 backstab：背刺 -> 备选(A)动作：偷袭
    ACTION_NODE_A(backstab, "backstab", "cheap shot");

    // 动作节点 cheap_shot：偷袭 -> 备选(A)动作：邪恶攻击
    ACTION_NODE_A(cheap_shot, "cheap shot", "sinister strike");
};

// 构造函数：初始化潜行者策略并挂载动作节点工厂
RogueStrategy::RogueStrategy(PlayerbotAI* ai) : ClassStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<RogueStrategyActionNodeFactory>());
}

// 构造函数：初始化潜行者潜行策略并挂载动作节点工厂
RogueStealthStrategy::RogueStealthStrategy(PlayerbotAI* ai) : StealthStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<RogueStealthStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (潜行者策略)
NextAction** RogueStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (潜行者策略)
void RogueStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("blind", ACTION_EMERGENCY + 2), 
                             new NextAction("vanish", ACTION_EMERGENCY + 1), 
                             new NextAction("vanish", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("evasion", ACTION_EMERGENCY), 
                             new NextAction("feint", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "sprint",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者策略)
void RogueStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (潜行者策略)
void RogueStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (潜行者策略)
void RogueStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者PVP策略)
void RoguePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者PVP策略)
void RoguePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH), NULL)));
}

// 初始化反应阶段触发器列表 (潜行者PVP策略)
void RoguePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (潜行者PVP策略)
void RoguePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者PVE策略)
void RoguePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者PVE策略)
void RoguePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (潜行者PVE策略)
void RoguePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (潜行者PVE策略)
void RoguePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者团队副本策略)
void RogueRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("feint", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "high threat",
        NextAction::array(0, new NextAction("vanish", ACTION_EMERGENCY), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者团队副本策略)
void RogueRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (潜行者团队副本策略)
void RogueRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (潜行者团队副本策略)
void RogueRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者AOE群体策略)
void RogueAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者AOE群体策略)
void RogueAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者AOE群体PVP策略)
void RogueAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者AOE群体PVP策略)
void RogueAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者AOE群体PVE策略)
void RogueAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者AOE群体PVE策略)
void RogueAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者AOE群体团队副本策略)
void RogueAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者AOE群体团队副本策略)
void RogueAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者增益Buff策略)
void RogueBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者增益Buff策略)
void RogueBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者增益BuffPVP策略)
void RogueBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者增益BuffPVP策略)
void RogueBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者增益BuffPVE策略)
void RogueBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者增益BuffPVE策略)
void RogueBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者增益Buff团队副本策略)
void RogueBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者增益Buff团队副本策略)
void RogueBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者爆发增益策略)
void RogueBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者爆发增益策略)
void RogueBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者爆发增益PVP策略)
void RogueBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者爆发增益PVP策略)
void RogueBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者爆发增益PVE策略)
void RogueBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者爆发增益PVE策略)
void RogueBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者爆发增益团队副本策略)
void RogueBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者爆发增益团队副本策略)
void RogueBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者控制(CC)策略)
void RogueCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "kick on enemy healer",
        NextAction::array(0, new NextAction("kick on enemy healer", ACTION_INTERRUPT + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "kick",
        NextAction::array(0, new NextAction("kick", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "sap",
        NextAction::array(0, new NextAction("sap", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("gouge", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者控制(CC)策略)
void RogueCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者控制(CC)PVP策略)
void RogueCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "kick",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者控制(CC)PVP策略)
void RogueCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者控制(CC)PVE策略)
void RogueCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者控制(CC)PVE策略)
void RogueCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者控制(CC)团队副本策略)
void RogueCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者控制(CC)团队副本策略)
void RogueCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者潜行策略)
void RogueStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "stealth",
        NextAction::array(0, new NextAction("stealth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "no stealth",
        NextAction::array(0, new NextAction("check stealth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("ambush", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("cheap shot", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "kick",
        NextAction::array(0, new NextAction("cheap shot", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "unstealth",
        NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者潜行策略)
void RogueStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no stealth",
        NextAction::array(0, new NextAction("check stealth", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "unstealth",
        NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (潜行者潜行PVP策略)
void RogueStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH), 
                             new NextAction("unstealth", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者潜行PVP策略)
void RogueStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者潜行PVE策略)
void RogueStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者潜行PVE策略)
void RogueStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者潜行团队副本策略)
void RogueStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者潜行团队副本策略)
void RogueStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    StealthRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者毒药策略)
void RoguePoisonsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者毒药策略)
void RoguePoisonsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (潜行者毒药PVP策略)
void RoguePoisonsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者毒药PVP策略)
void RoguePoisonsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "apply mind poison main hand",
        NextAction::array(0, new NextAction("apply mind poison main hand", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "apply crippling poison off hand",
        NextAction::array(0, new NextAction("apply crippling poison off hand", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (潜行者毒药PVE策略)
void RoguePoisonsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者毒药PVE策略)
void RoguePoisonsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "apply instant poison main hand",
        NextAction::array(0, new NextAction("apply instant poison main hand", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "apply instant poison off hand",
        NextAction::array(0, new NextAction("apply instant poison off hand", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (潜行者毒药团队副本策略)
void RoguePoisonsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    
}

// 初始化非战斗阶段触发器列表 (潜行者毒药团队副本策略)
void RoguePoisonsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "apply instant poison main hand",
        NextAction::array(0, new NextAction("apply instant poison main hand", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "apply deadly poison off hand",
        NextAction::array(0, new NextAction("apply deadly poison off hand", ACTION_NORMAL), NULL)));
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (潜行者策略)
NextAction** RogueStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_NORMAL), NULL);
}

// 初始化战斗阶段触发器列表 (潜行者策略)
void RogueStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("blind", ACTION_EMERGENCY + 2), 
                             new NextAction("vanish", ACTION_EMERGENCY + 1), 
                             new NextAction("vanish", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("evasion", ACTION_EMERGENCY), 
                             new NextAction("feint", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "sprint",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者策略)
void RogueStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (潜行者策略)
void RogueStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (潜行者策略)
void RogueStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者PVP策略)
void RoguePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者PVP策略)
void RoguePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH), NULL)));
}

// 初始化反应阶段触发器列表 (潜行者PVP策略)
void RoguePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (潜行者PVP策略)
void RoguePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者PVE策略)
void RoguePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者PVE策略)
void RoguePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (潜行者PVE策略)
void RoguePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (潜行者PVE策略)
void RoguePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者团队副本策略)
void RogueRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("feint", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者团队副本策略)
void RogueRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (潜行者团队副本策略)
void RogueRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (潜行者团队副本策略)
void RogueRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者AOE群体策略)
void RogueAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者AOE群体策略)
void RogueAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者AOE群体PVP策略)
void RogueAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者AOE群体PVP策略)
void RogueAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者AOE群体PVE策略)
void RogueAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者AOE群体PVE策略)
void RogueAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者AOE群体团队副本策略)
void RogueAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者AOE群体团队副本策略)
void RogueAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者增益Buff策略)
void RogueBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者增益Buff策略)
void RogueBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者增益BuffPVP策略)
void RogueBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者增益BuffPVP策略)
void RogueBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者增益BuffPVE策略)
void RogueBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者增益BuffPVE策略)
void RogueBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者增益Buff团队副本策略)
void RogueBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者增益Buff团队副本策略)
void RogueBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者爆发增益策略)
void RogueBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者爆发增益策略)
void RogueBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者爆发增益PVP策略)
void RogueBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者爆发增益PVP策略)
void RogueBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者爆发增益PVE策略)
void RogueBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者爆发增益PVE策略)
void RogueBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者爆发增益团队副本策略)
void RogueBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者爆发增益团队副本策略)
void RogueBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者控制(CC)策略)
void RogueCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "kick on enemy healer",
        NextAction::array(0, new NextAction("kick on enemy healer", ACTION_INTERRUPT + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "kick",
        NextAction::array(0, new NextAction("kick", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "sap",
        NextAction::array(0, new NextAction("sap", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("gouge", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者控制(CC)策略)
void RogueCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者控制(CC)PVP策略)
void RogueCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "kick",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者控制(CC)PVP策略)
void RogueCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者控制(CC)PVE策略)
void RogueCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者控制(CC)PVE策略)
void RogueCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者控制(CC)团队副本策略)
void RogueCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者控制(CC)团队副本策略)
void RogueCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者潜行策略)
void RogueStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "stealth",
        NextAction::array(0, new NextAction("stealth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "no stealth",
        NextAction::array(0, new NextAction("check stealth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("ambush", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("cheap shot", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "kick",
        NextAction::array(0, new NextAction("cheap shot", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "unstealth",
        NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者潜行策略)
void RogueStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no stealth",
        NextAction::array(0, new NextAction("check stealth", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "unstealth",
        NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (潜行者潜行PVP策略)
void RogueStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH),
                             new NextAction("unstealth", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者潜行PVP策略)
void RogueStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (潜行者潜行PVE策略)
void RogueStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者潜行PVE策略)
void RogueStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (潜行者潜行团队副本策略)
void RogueStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者潜行团队副本策略)
void RogueStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (潜行者毒药策略)
void RoguePoisonsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者毒药策略)
void RoguePoisonsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (潜行者毒药PVP策略)
void RoguePoisonsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者毒药PVP策略)
void RoguePoisonsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "apply mind poison main hand",
        NextAction::array(0, new NextAction("apply mind poison main hand", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "apply crippling poison off hand",
        NextAction::array(0, new NextAction("apply crippling poison off hand", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (潜行者毒药PVE策略)
void RoguePoisonsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者毒药PVE策略)
void RoguePoisonsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "apply instant poison main hand",
        NextAction::array(0, new NextAction("apply instant poison main hand", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "apply instant poison off hand",
        NextAction::array(0, new NextAction("apply instant poison off hand", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (潜行者毒药团队副本策略)
void RoguePoisonsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者毒药团队副本策略)
void RoguePoisonsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "apply instant poison main hand",
        NextAction::array(0, new NextAction("apply instant poison main hand", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "apply deadly poison off hand",
        NextAction::array(0, new NextAction("apply deadly poison off hand", ACTION_NORMAL), NULL)));
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (潜行者策略)
NextAction** RogueStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_NORMAL), NULL);
}

// 初始化战斗阶段触发器列表 (潜行者策略)
void RogueStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

        triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("blind", ACTION_EMERGENCY + 2), 
                             new NextAction("vanish", ACTION_EMERGENCY + 1), 
                             new NextAction("vanish", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("evasion", ACTION_EMERGENCY), 
                             new NextAction("feint", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "cloak of shadows",
        NextAction::array(0, new NextAction("cloak of shadows", ACTION_INTERRUPT + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "sprint",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者策略)
void RogueStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (潜行者策略)
void RogueStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (潜行者策略)
void RogueStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者PVP策略)
void RoguePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者PVP策略)
void RoguePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH), NULL)));
}

// 初始化反应阶段触发器列表 (潜行者PVP策略)
void RoguePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (潜行者PVP策略)
void RoguePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者PVE策略)
void RoguePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者PVE策略)
void RoguePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (潜行者PVE策略)
void RoguePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (潜行者PVE策略)
void RoguePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者团队副本策略)
void RogueRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("feint", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者团队副本策略)
void RogueRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (潜行者团队副本策略)
void RogueRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (潜行者团队副本策略)
void RogueRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者AOE群体策略)
void RogueAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者AOE群体策略)
void RogueAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者AOE群体PVP策略)
void RogueAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者AOE群体PVP策略)
void RogueAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者AOE群体PVE策略)
void RogueAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者AOE群体PVE策略)
void RogueAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者AOE群体团队副本策略)
void RogueAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者AOE群体团队副本策略)
void RogueAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者增益Buff策略)
void RogueBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者增益Buff策略)
void RogueBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者增益BuffPVP策略)
void RogueBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者增益BuffPVP策略)
void RogueBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者增益BuffPVE策略)
void RogueBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者增益BuffPVE策略)
void RogueBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者增益Buff团队副本策略)
void RogueBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者增益Buff团队副本策略)
void RogueBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者爆发增益策略)
void RogueBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者爆发增益策略)
void RogueBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者爆发增益PVP策略)
void RogueBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者爆发增益PVP策略)
void RogueBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者爆发增益PVE策略)
void RogueBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者爆发增益PVE策略)
void RogueBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者爆发增益团队副本策略)
void RogueBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者爆发增益团队副本策略)
void RogueBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者控制(CC)策略)
void RogueCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "kick on enemy healer",
        NextAction::array(0, new NextAction("kick on enemy healer", ACTION_INTERRUPT + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "kick",
        NextAction::array(0, new NextAction("kick", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "sap",
        NextAction::array(0, new NextAction("sap", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("gouge", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者控制(CC)策略)
void RogueCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者控制(CC)PVP策略)
void RogueCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "kick",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者控制(CC)PVP策略)
void RogueCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者控制(CC)PVE策略)
void RogueCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者控制(CC)PVE策略)
void RogueCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者控制(CC)团队副本策略)
void RogueCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (潜行者控制(CC)团队副本策略)
void RogueCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (潜行者潜行策略)
void RogueStealthStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "stealth",
        NextAction::array(0, new NextAction("stealth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "no stealth",
        NextAction::array(0, new NextAction("check stealth", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("ambush", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "not behind target",
        NextAction::array(0, new NextAction("cheap shot", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "kick",
        NextAction::array(0, new NextAction("cheap shot", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "unstealth",
        NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者潜行策略)
void RogueStealthStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no stealth",
        NextAction::array(0, new NextAction("check stealth", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "unstealth",
        NextAction::array(0, new NextAction("unstealth", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (潜行者潜行PVP策略)
void RogueStealthPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "enemy flagcarrier near",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH),
                             new NextAction("unstealth", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (潜行者潜行PVP策略)
void RogueStealthPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (潜行者潜行PVE策略)
void RogueStealthPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者潜行PVE策略)
void RogueStealthPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (潜行者潜行团队副本策略)
void RogueStealthRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者潜行团队副本策略)
void RogueStealthRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (潜行者毒药策略)
void RoguePoisonsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者毒药策略)
void RoguePoisonsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (潜行者毒药PVP策略)
void RoguePoisonsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者毒药PVP策略)
void RoguePoisonsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "apply mind poison main hand",
        NextAction::array(0, new NextAction("apply mind poison main hand", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "apply crippling poison off hand",
        NextAction::array(0, new NextAction("apply crippling poison off hand", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (潜行者毒药PVE策略)
void RoguePoisonsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者毒药PVE策略)
void RoguePoisonsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "apply instant poison main hand",
        NextAction::array(0, new NextAction("apply instant poison main hand", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "apply instant poison off hand",
        NextAction::array(0, new NextAction("apply instant poison off hand", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (潜行者毒药团队副本策略)
void RoguePoisonsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (潜行者毒药团队副本策略)
void RoguePoisonsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "apply instant poison main hand",
        NextAction::array(0, new NextAction("apply instant poison main hand", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "apply deadly poison off hand",
        NextAction::array(0, new NextAction("apply deadly poison off hand", ACTION_NORMAL), NULL)));
}

#endif

// 初始化非战斗阶段触发器列表 (潜行者手动毒药策略)
void RogueManualPoisonStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        triggerName,
        NextAction::array(0, new NextAction(actionName, ACTION_NORMAL), NULL)));
}

// 乘数修饰器 (RogueStealthedStrategyMultiplier)：动态调整特定状态下的动作权重
class RogueStealthedStrategyMultiplier : public Multiplier
{
public:
    RogueStealthedStrategyMultiplier(PlayerbotAI* ai) : Multiplier(ai, "stealthed") {}

    float GetValue(Action* action) override
    {
        // Only allow stealth actions
        const std::string& actionName = action->getName();
        if ((actionName == "unstealth") ||
            (actionName == "check stealth") ||
            (actionName == "cold blood") ||
            (actionName == "preparation") ||
            (actionName == "premeditation") ||
            (actionName == "shadowstep") ||
            (actionName == "sprint") ||
            (actionName == "ambush") ||
            (actionName == "cheap shot") ||
            (actionName == "sap") ||
            (actionName == "garrote") ||
            (actionName == "food") ||
            (actionName == "backstab") ||
            (actionName == "sinister strike") ||
            (actionName == "dps assist") ||
            (actionName == "select new target") ||
            (actionName == "follow") ||
            (actionName == "reach melee") ||
            (actionName == "set behind") ||
            (actionName == "set combat state") ||
            (actionName == "set non combat state") ||
            (actionName == "set dead state") ||
            (actionName == "update pvp strats") ||
            (actionName == "update pve strats") ||
            (actionName == "update raid strats") ||
            (actionName == "accept invitation") ||
            (actionName == "bg status") ||
            (actionName == "bg leave") ||
            (actionName == "check mount state") ||
            (actionName == "loot roll") ||
            (actionName == "auto loot roll") ||
            (actionName == "attack anything") ||
            (actionName == "choose rpg target") ||
            (actionName == "move to rpg target") ||
            (actionName == "move to travel target") ||
            (actionName == "choose travel target") ||
            (actionName == "reset travel target") ||
            (actionName == "bg move to start") ||
            (actionName == "bg move to objective") ||
            (actionName == "bg check objective") ||
            (actionName == "bg check flag") ||
            (actionName == "attack enemy flag carrier") ||
            (actionName == "travel") ||
            (actionName == "move to suppression device") ||
            (actionName == "disarm suppression device"))
        {
            return 1.0f;
        }

        return 0.0f;
    }
};

// 初始化战斗阶段乘数修饰器 (潜行者潜行状态策略)
void RogueStealthedStrategy::InitCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    multipliers.push_back(new RogueStealthedStrategyMultiplier(ai));
}

// 初始化非战斗阶段乘数修饰器 (潜行者潜行状态策略)
void RogueStealthedStrategy::InitNonCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    RogueStealthedStrategy::InitCombatMultipliers(multipliers);
}
