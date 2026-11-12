// 猎人 - 猎人策略实现文件 (HunterStrategy.cpp)

#include "playerbot/playerbot.h"
#include "HunterStrategy.h"
#include "HunterAiObjectContext.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class HunterStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    HunterStrategyActionNodeFactory()
    {
        creators["aimed shot"] = &aimed_shot;
        creators["rapid fire"] = &rapid_fire;
        creators["aspect of the pack"] = &aspect_of_the_pack;
        creators["aspect of the dragonhawk"] = &aspect_of_the_dragonhawk;
        creators["wing clip"] = &wing_clip;
        creators["intimidation"] = &intimidation;
        creators["scatter shot"] = &scatter_shot;
        creators["feign death threat"] = &feign_death_threat;
        creators["tame beast"] = &tame_beast;
    }

private:
    // 动作节点 aimed_shot：瞄准射击 -> 备选(A)动作：奥术射击
    ACTION_NODE_A(aimed_shot, "aimed shot", "arcane shot");

    // 动作节点 rapid_fire：急速射击 -> 备选(A)动作：准备就绪
    ACTION_NODE_A(rapid_fire, "rapid fire", "readiness");

    // 动作节点 aspect_of_the_pack：豹群守护 -> 备选(A)动作：猎豹守护
    ACTION_NODE_A(aspect_of_the_pack, "aspect of the pack", "aspect of the cheetah");

    // 动作节点 aspect_of_the_dragonhawk：龙鹰守护 -> 备选(A)动作：雄鹰守护
    ACTION_NODE_A(aspect_of_the_dragonhawk, "aspect of the dragonhawk", "aspect of the hawk");

    // 动作节点 wing_clip：摔绊 -> 备选(A)动作：猛禽一击
    ACTION_NODE_A(wing_clip, "wing clip", "raptor strike");

    // 动作节点 intimidation：胁迫 -> 备选(A)动作：摔绊
    ACTION_NODE_A(intimidation, "intimidation", "wing clip");

    // 动作节点 scatter_shot：驱散射击 -> 备选(A)动作：胁迫
    ACTION_NODE_A(scatter_shot, "scatter shot", "intimidation");

    // 动作节点 feign_death_threat：假死 -> 后续(C)动作：remove feign death
    ACTION_NODE_C(feign_death_threat, "feign death", "remove feign death");

    // 动作节点 tame_beast：驯服野兽 -> 后续(C)动作：召唤宠物
    ACTION_NODE_C(tame_beast, "tame beast", "call pet")
};

// 构造函数：初始化猎人策略并挂载动作节点工厂
HunterStrategy::HunterStrategy(PlayerbotAI* ai) : ClassStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<HunterStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (猎人策略)
NextAction** HunterStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("auto shot", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (猎人策略)
void HunterStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "switch to ranged",
        NextAction::array(0, new NextAction("switch to ranged", ACTION_INTERRUPT + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "switch to melee",
        NextAction::array(0, new NextAction("switch to melee", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "counterattack",
        NextAction::array(0, new NextAction("counterattack", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "stealthed nearby",
        NextAction::array(0, new NextAction("flare", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "hunter's mark",
        NextAction::array(0, new NextAction("hunter's mark", ACTION_NORMAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "aimed shot",
        NextAction::array(0, new NextAction("aimed shot", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy is close",
        NextAction::array(0, new NextAction("raptor strike", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("tame beast", ACTION_EMERGENCY), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人策略)
void HunterStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "stealthed nearby",
        NextAction::array(0, new NextAction("flare", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "no ammo",
    NextAction::array(0,
        new NextAction("equip ammo", ACTION_EMERGENCY),
        new NextAction("say::no ammo", ACTION_NORMAL),
        NULL)));

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("tame beast", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (猎人策略)
void HunterStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "dispel enrage",
        NextAction::array(0, new NextAction("tranquilizing shot", ACTION_INTERRUPT), NULL)));
}

// 初始化死亡状态触发器列表 (猎人策略)
void HunterStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人PVP策略)
void HunterPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人PVP策略)
void HunterPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (猎人PVP策略)
void HunterPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (猎人PVP策略)
void HunterPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人PVE策略)
void HunterPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);

    // Traps must be on ACTION_INTERRUPT or higher due to its movements and chained actions
    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("immolation trap on target", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人PVE策略)
void HunterPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (猎人PVE策略)
void HunterPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (猎人PVE策略)
void HunterPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人团队副本策略)
void HunterRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "high threat",
        NextAction::array(0, new NextAction("feign death threat", ACTION_EMERGENCY), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人团队副本策略)
void HunterRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (猎人团队副本策略)
void HunterRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (猎人团队副本策略)
void HunterRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人AOE群体策略)
void HunterAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);

    // Traps must be on ACTION_INTERRUPT or higher due to its movements and chained actions
    triggers.push_back(new TriggerNode(
        "explosive trap",
        NextAction::array(0, new NextAction("explosive trap on target", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("volley", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "multi-shot",
        NextAction::array(0, new NextAction("multi-shot", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人AOE群体策略)
void HunterAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人AOE群体PVP策略)
void HunterAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人AOE群体PVP策略)
void HunterAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人AOE群体PVE策略)
void HunterAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人AOE群体PVE策略)
void HunterAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人AOE群体团队副本策略)
void HunterAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人AOE群体团队副本策略)
void HunterAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人增益Buff策略)
void HunterBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("deterrence", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "feign death",
        NextAction::array(0, new NextAction("remove feign death", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人增益Buff策略)
void HunterBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "feign death",
        NextAction::array(0, new NextAction("remove feign death", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人增益BuffPVP策略)
void HunterBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人增益BuffPVP策略)
void HunterBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人增益BuffPVE策略)
void HunterBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人增益BuffPVE策略)
void HunterBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人增益Buff团队副本策略)
void HunterBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人增益Buff团队副本策略)
void HunterBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人爆发增益策略)
void HunterBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rapid fire",
        NextAction::array(0, new NextAction("rapid fire", ACTION_HIGH + 5), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人爆发增益策略)
void HunterBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人爆发增益PVP策略)
void HunterBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人爆发增益PVP策略)
void HunterBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人爆发增益PVE策略)
void HunterBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人爆发增益PVE策略)
void HunterBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人爆发增益团队副本策略)
void HunterBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人爆发增益团队副本策略)
void HunterBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人控制(CC)策略)
void HunterCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    // Traps must be on ACTION_INTERRUPT or higher due to its movements and chained actions
    triggers.push_back(new TriggerNode(
        "freezing trap",
        NextAction::array(0, new NextAction("freezing trap on cc", ACTION_INTERRUPT + 1), NULL)));

    // Traps must be on ACTION_INTERRUPT or higher due to its movements and chained actions
    triggers.push_back(new TriggerNode(
        "frost trap",
        NextAction::array(0, new NextAction("frost trap on target", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "scare beast",
        NextAction::array(0, new NextAction("scare beast on cc", ACTION_HIGH + 2), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人控制(CC)策略)
void HunterCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人控制(CC)PVP策略)
void HunterCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    // Traps must be on ACTION_INTERRUPT or higher due to its movements and chained actions
    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("freezing trap in place", ACTION_INTERRUPT + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("scatter shot on closest attacker targeting me", ACTION_INTERRUPT + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy fifteen yards",
        NextAction::array(0, new NextAction("concussive shot", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人控制(CC)PVP策略)
void HunterCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人控制(CC)PVE策略)
void HunterCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("scatter shot on closest attacker targeting me", ACTION_INTERRUPT + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy fifteen yards",
        NextAction::array(0, new NextAction("concussive shot", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人控制(CC)PVE策略)
void HunterCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人控制(CC)团队副本策略)
void HunterCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人控制(CC)团队副本策略)
void HunterCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人钉刺策略)
void HunterStingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    if (ai->HasStrategy("aoe", BotState::BOT_STATE_COMBAT))
    {
        triggers.push_back(new TriggerNode(
            "serpent sting on attacker",
            NextAction::array(0, new NextAction("serpent sting on attacker", ACTION_HIGH + 2), NULL)));

        triggers.push_back(new TriggerNode(
            "viper sting on attacker",
            NextAction::array(0, new NextAction("viper sting on attacker", ACTION_HIGH + 1), NULL)));
    }

    triggers.push_back(new TriggerNode(
        "no stings",
        NextAction::array(0, new NextAction("viper sting", ACTION_NORMAL + 5), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人钉刺PVP策略)
void HunterStingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no stings",
        NextAction::array(0, new NextAction("serpent sting", ACTION_NORMAL + 4), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人钉刺PVE策略)
void HunterStingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no stings",
        NextAction::array(0, new NextAction("serpent sting", ACTION_NORMAL + 4), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人钉刺团队副本策略)
void HunterStingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (猎人守护策略)
void HunterAspectStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "aspect of the hawk",
        NextAction::array(0, new NextAction("aspect of the hawk", ACTION_HIGH + 5), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人守护策略)
void HunterAspectStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "aspect of the hawk",
        NextAction::array(0, new NextAction("aspect of the hawk", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人守护PVP策略)
void HunterAspectPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "target of attacker",
        NextAction::array(0, new NextAction("remove aspect of the cheetah", ACTION_HIGH + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("aspect of the cheetah", ACTION_HIGH + 6), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人守护PVP策略)
void HunterAspectPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "target of attacker",
        NextAction::array(0, new NextAction("remove aspect of the cheetah", ACTION_HIGH + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("aspect of the cheetah", ACTION_HIGH + 6), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人守护PVE策略)
void HunterAspectPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (猎人守护PVE策略)
void HunterAspectPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (猎人守护团队副本策略)
void HunterAspectRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (猎人守护团队副本策略)
void HunterAspectRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (猎人策略)
NextAction** HunterStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("auto shot", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (猎人策略)
void HunterStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "switch to ranged",
        NextAction::array(0, new NextAction("switch to ranged", ACTION_INTERRUPT + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "switch to melee",
        NextAction::array(0, new NextAction("switch to melee", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "counterattack",
        NextAction::array(0, new NextAction("counterattack", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "stealthed nearby",
        NextAction::array(0, new NextAction("flare", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "hunter's mark",
        NextAction::array(0, new NextAction("hunter's mark", ACTION_NORMAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "arcane shot",
        NextAction::array(0, new NextAction("arcane shot", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "kill command",
        NextAction::array(0, new NextAction("kill command", ACTION_NORMAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "steady shot",
        NextAction::array(0, new NextAction("steady shot", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy is close",
        NextAction::array(0, new NextAction("raptor strike", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("tame beast", ACTION_EMERGENCY), NULL)));    
}

// 初始化非战斗阶段触发器列表 (猎人策略)
void HunterStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "stealthed nearby",
        NextAction::array(0, new NextAction("flare", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "no ammo",
    NextAction::array(0,
        new NextAction("equip ammo", ACTION_EMERGENCY),
        new NextAction("say::no ammo", ACTION_NORMAL),
        NULL)));

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("tame beast", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (猎人策略)
void HunterStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "dispel enrage",
        NextAction::array(0, new NextAction("tranquilizing shot", ACTION_INTERRUPT), NULL)));
}

// 初始化死亡状态触发器列表 (猎人策略)
void HunterStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人PVP策略)
void HunterPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人PVP策略)
void HunterPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (猎人PVP策略)
void HunterPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (猎人PVP策略)
void HunterPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人PVE策略)
void HunterPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);

    // Traps must be on ACTION_INTERRUPT or higher due to its movements and chained actions
    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("immolation trap on target", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人PVE策略)
void HunterPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (猎人PVE策略)
void HunterPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (猎人PVE策略)
void HunterPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人团队副本策略)
void HunterRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "high threat",
        NextAction::array(0, new NextAction("feign death threat", ACTION_EMERGENCY), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人团队副本策略)
void HunterRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (猎人团队副本策略)
void HunterRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (猎人团队副本策略)
void HunterRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人AOE群体策略)
void HunterAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);

    // Traps must be on ACTION_INTERRUPT or higher due to its movements and chained actions
    triggers.push_back(new TriggerNode(
        "explosive trap",
        NextAction::array(0, new NextAction("explosive trap on target", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("volley", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "multi-shot",
        NextAction::array(0, new NextAction("multi-shot", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人AOE群体策略)
void HunterAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人AOE群体PVP策略)
void HunterAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人AOE群体PVP策略)
void HunterAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人AOE群体PVE策略)
void HunterAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人AOE群体PVE策略)
void HunterAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人AOE群体团队副本策略)
void HunterAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人AOE群体团队副本策略)
void HunterAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人增益Buff策略)
void HunterBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("deterrence", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "feign death",
        NextAction::array(0, new NextAction("remove feign death", ACTION_HIGH), NULL)));    
}

// 初始化非战斗阶段触发器列表 (猎人增益Buff策略)
void HunterBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "feign death",
        NextAction::array(0, new NextAction("remove feign death", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人增益BuffPVP策略)
void HunterBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人增益BuffPVP策略)
void HunterBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人增益BuffPVE策略)
void HunterBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人增益BuffPVE策略)
void HunterBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人增益Buff团队副本策略)
void HunterBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人增益Buff团队副本策略)
void HunterBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人爆发增益策略)
void HunterBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rapid fire",
        NextAction::array(0, new NextAction("rapid fire", ACTION_HIGH + 5), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人爆发增益策略)
void HunterBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人爆发增益PVP策略)
void HunterBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人爆发增益PVP策略)
void HunterBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人爆发增益PVE策略)
void HunterBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人爆发增益PVE策略)
void HunterBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人爆发增益团队副本策略)
void HunterBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人爆发增益团队副本策略)
void HunterBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人控制(CC)策略)
void HunterCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("scatter shot on closest attacker targeting me", ACTION_INTERRUPT + 2), NULL)));

    // Traps must be on ACTION_INTERRUPT or higher due to its movements and chained actions
    triggers.push_back(new TriggerNode(
        "freezing trap",
        NextAction::array(0, new NextAction("freezing trap on cc", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "frost trap",
        NextAction::array(0, new NextAction("frost trap on target", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "scare beast",
        NextAction::array(0, new NextAction("scare beast on cc", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy fifteen yards",
        NextAction::array(0, new NextAction("concussive shot", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人控制(CC)策略)
void HunterCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人控制(CC)PVP策略)
void HunterCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("freezing trap in place", ACTION_INTERRUPT + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人控制(CC)PVP策略)
void HunterCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人控制(CC)PVE策略)
void HunterCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人控制(CC)PVE策略)
void HunterCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人控制(CC)团队副本策略)
void HunterCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人控制(CC)团队副本策略)
void HunterCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人钉刺策略)
void HunterStingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    if (ai->HasStrategy("aoe", BotState::BOT_STATE_COMBAT))
    {
        triggers.push_back(new TriggerNode(
            "serpent sting on attacker",
            NextAction::array(0, new NextAction("serpent sting on attacker", ACTION_HIGH + 2), NULL)));

        triggers.push_back(new TriggerNode(
            "viper sting on attacker",
            NextAction::array(0, new NextAction("viper sting on attacker", ACTION_HIGH + 1), NULL)));
    }

    triggers.push_back(new TriggerNode(
        "no stings",
        NextAction::array(0, new NextAction("viper sting", ACTION_NORMAL + 5), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人钉刺PVP策略)
void HunterStingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no stings",
        NextAction::array(0, new NextAction("serpent sting", ACTION_NORMAL + 4), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人钉刺PVE策略)
void HunterStingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no stings",
        NextAction::array(0, new NextAction("serpent sting", ACTION_NORMAL + 4), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人钉刺团队副本策略)
void HunterStingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (猎人守护策略)
void HunterAspectStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "aspect of the hawk",
        NextAction::array(0, new NextAction("aspect of the hawk", ACTION_HIGH + 5), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人守护策略)
void HunterAspectStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "aspect of the hawk",
        NextAction::array(0, new NextAction("aspect of the hawk", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人守护PVP策略)
void HunterAspectPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    // TO DO: This needs to be done better, currently it spams unnecessarily
    /*
    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("aspect of the monkey", ACTION_EMERGENCY), NULL)));
    */

    triggers.push_back(new TriggerNode(
        "target of attacker",
        NextAction::array(0, new NextAction("remove aspect of the cheetah", ACTION_HIGH + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("aspect of the cheetah", ACTION_HIGH + 6), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人守护PVP策略)
void HunterAspectPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "target of attacker",
        NextAction::array(0, new NextAction("remove aspect of the cheetah", ACTION_HIGH + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("aspect of the cheetah", ACTION_HIGH + 6), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人守护PVE策略)
void HunterAspectPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (猎人守护PVE策略)
void HunterAspectPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (猎人守护团队副本策略)
void HunterAspectRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (猎人守护团队副本策略)
void HunterAspectRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (猎人策略)
NextAction** HunterStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("auto shot", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (猎人策略)
void HunterStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "switch to ranged",
        NextAction::array(0, new NextAction("switch to ranged", ACTION_INTERRUPT + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "switch to melee",
        NextAction::array(0, new NextAction("switch to melee", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "counterattack",
        NextAction::array(0, new NextAction("counterattack", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "stealthed nearby",
        NextAction::array(0, new NextAction("flare", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "hunter's mark",
        NextAction::array(0, new NextAction("hunter's mark", ACTION_NORMAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "kill command",
        NextAction::array(0, new NextAction("kill command", ACTION_NORMAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "aimed shot",
        NextAction::array(0, new NextAction("aimed shot", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy is close",
        NextAction::array(0, new NextAction("raptor strike", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("tame beast", ACTION_EMERGENCY), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人策略)
void HunterStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "stealthed nearby",
        NextAction::array(0, new NextAction("flare", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "no ammo",
    NextAction::array(0,
        new NextAction("equip ammo", ACTION_EMERGENCY),
        new NextAction("say::no ammo", ACTION_NORMAL),
        NULL)));

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("tame beast", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (猎人策略)
void HunterStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "dispel enrage",
        NextAction::array(0, new NextAction("tranquilizing shot", ACTION_INTERRUPT), NULL)));
}

// 初始化死亡状态触发器列表 (猎人策略)
void HunterStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人PVP策略)
void HunterPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人PVP策略)
void HunterPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (猎人PVP策略)
void HunterPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (猎人PVP策略)
void HunterPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人PVE策略)
void HunterPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);

    // Traps must be on ACTION_INTERRUPT or higher due to its movements and chained actions
    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("immolation trap on target", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人PVE策略)
void HunterPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (猎人PVE策略)
void HunterPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (猎人PVE策略)
void HunterPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人团队副本策略)
void HunterRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "high threat",
        NextAction::array(0, new NextAction("feign death threat", ACTION_EMERGENCY), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人团队副本策略)
void HunterRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (猎人团队副本策略)
void HunterRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (猎人团队副本策略)
void HunterRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人AOE群体策略)
void HunterAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);

    // Traps must be on ACTION_INTERRUPT or higher due to its movements and chained actions
    triggers.push_back(new TriggerNode(
        "explosive trap",
        NextAction::array(0, new NextAction("explosive trap on target", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("volley", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "multi-shot",
        NextAction::array(0, new NextAction("multi-shot", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人AOE群体策略)
void HunterAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人AOE群体PVP策略)
void HunterAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人AOE群体PVP策略)
void HunterAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人AOE群体PVE策略)
void HunterAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人AOE群体PVE策略)
void HunterAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人AOE群体团队副本策略)
void HunterAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人AOE群体团队副本策略)
void HunterAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人增益Buff策略)
void HunterBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("deterrence", ACTION_HIGH + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "feign death",
        NextAction::array(0, new NextAction("remove feign death", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人增益Buff策略)
void HunterBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "feign death",
        NextAction::array(0, new NextAction("remove feign death", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人增益BuffPVP策略)
void HunterBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人增益BuffPVP策略)
void HunterBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人增益BuffPVE策略)
void HunterBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人增益BuffPVE策略)
void HunterBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人增益Buff团队副本策略)
void HunterBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人增益Buff团队副本策略)
void HunterBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人爆发增益策略)
void HunterBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "rapid fire",
        NextAction::array(0, new NextAction("rapid fire", ACTION_HIGH + 5), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人爆发增益策略)
void HunterBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人爆发增益PVP策略)
void HunterBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人爆发增益PVP策略)
void HunterBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人爆发增益PVE策略)
void HunterBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人爆发增益PVE策略)
void HunterBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人爆发增益团队副本策略)
void HunterBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人爆发增益团队副本策略)
void HunterBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人控制(CC)策略)
void HunterCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("scatter shot on closest attacker targeting me", ACTION_INTERRUPT + 2), NULL)));

    // Traps must be on ACTION_INTERRUPT or higher due to its movements and chained actions
    triggers.push_back(new TriggerNode(
        "freezing trap",
        NextAction::array(0, new NextAction("freezing trap on cc", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "frost trap",
        NextAction::array(0, new NextAction("frost trap on target", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "scare beast",
        NextAction::array(0, new NextAction("scare beast on cc", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy fifteen yards",
        NextAction::array(0, new NextAction("concussive shot", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人控制(CC)策略)
void HunterCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人控制(CC)PVP策略)
void HunterCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("freezing trap in place", ACTION_INTERRUPT + 3), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人控制(CC)PVP策略)
void HunterCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人控制(CC)PVE策略)
void HunterCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人控制(CC)PVE策略)
void HunterCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人控制(CC)团队副本策略)
void HunterCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (猎人控制(CC)团队副本策略)
void HunterCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人钉刺策略)
void HunterStingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    if (ai->HasStrategy("aoe", BotState::BOT_STATE_COMBAT))
    {
        triggers.push_back(new TriggerNode(
            "serpent sting on attacker",
            NextAction::array(0, new NextAction("serpent sting on attacker", ACTION_HIGH + 2), NULL)));

        triggers.push_back(new TriggerNode(
            "viper sting on attacker",
            NextAction::array(0, new NextAction("viper sting on attacker", ACTION_HIGH + 1), NULL)));
    }

    triggers.push_back(new TriggerNode(
        "no stings",
        NextAction::array(0, new NextAction("viper sting", ACTION_NORMAL + 5), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人钉刺PVP策略)
void HunterStingPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no stings",
        NextAction::array(0, new NextAction("serpent sting", ACTION_NORMAL + 4), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人钉刺PVE策略)
void HunterStingPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no stings",
        NextAction::array(0, new NextAction("serpent sting", ACTION_NORMAL + 4), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人钉刺团队副本策略)
void HunterStingRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (猎人守护策略)
void HunterAspectStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "aspect of the dragonhawk",
        NextAction::array(0, new NextAction("aspect of the dragonhawk", ACTION_HIGH + 5), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人守护策略)
void HunterAspectStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "aspect of the dragonhawk",
        NextAction::array(0, new NextAction("aspect of the dragonhawk", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人守护PVP策略)
void HunterAspectPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    // TO DO: This needs to be done better, currently it spams unnecessarily
    /*
    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("aspect of the monkey", ACTION_EMERGENCY), NULL)));
    */

    triggers.push_back(new TriggerNode(
        "target of attacker",
        NextAction::array(0, new NextAction("remove aspect of the cheetah", ACTION_HIGH + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("aspect of the cheetah", ACTION_HIGH + 6), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人守护PVP策略)
void HunterAspectPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "target of attacker",
        NextAction::array(0, new NextAction("remove aspect of the cheetah", ACTION_HIGH + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("aspect of the cheetah", ACTION_HIGH + 6), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人守护PVE策略)
void HunterAspectPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (猎人守护PVE策略)
void HunterAspectPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (猎人守护团队副本策略)
void HunterAspectRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (猎人守护团队副本策略)
void HunterAspectRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

#endif

// 初始化战斗阶段触发器列表 (猎人手动钉刺策略)
void HunterManualStingStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    if (ai->HasStrategy("aoe", BotState::BOT_STATE_COMBAT))
    {
        triggers.push_back(new TriggerNode(
            triggerName + " on attacker",
            NextAction::array(0, new NextAction(actionName + " on attacker", ACTION_HIGH + 1), NULL)));
    }

    triggers.push_back(new TriggerNode(
        "no stings",
        NextAction::array(0, new NextAction(actionName, ACTION_HIGH), NULL)));
}

// 初始化战斗阶段触发器列表 (猎人手动守护策略)
void HunterManualAspectStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        triggerName,
        NextAction::array(0, new NextAction(actionName, ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人手动守护策略)
void HunterManualAspectStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (猎人宠物策略)
void HunterPetStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "hunters pet low health",
        NextAction::array(0, new NextAction("mend pet", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (猎人宠物策略)
void HunterPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("call pet", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "pet not happy",
        NextAction::array(0, new NextAction("feed pet", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "hunters pet low health",
        NextAction::array(0, new NextAction("mend pet", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "hunters pet dead",
        NextAction::array(0, new NextAction("revive pet", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("initialize pet", ACTION_NORMAL + 1), NULL)));
}
