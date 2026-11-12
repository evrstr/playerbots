// 术士 - 术士策略实现文件 (WarlockStrategy.cpp)

#include "playerbot/playerbot.h"
#include "WarlockMultipliers.h"
#include "WarlockStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class WarlockStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    WarlockStrategyActionNodeFactory()
    {
        creators["banish"] = &banish;
        creators["fel armor"] = &fel_armor;
        creators["demon armor"] = &demon_armor;
    }

private:
    // 动作节点 banish：放逐术 -> 备选(A)动作：恐惧术
    ACTION_NODE_A(banish, "banish", "fear");

    // 动作节点 fel_armor：邪甲术 -> 备选(A)动作：魔甲术
    ACTION_NODE_A(fel_armor, "fel armor", "demon armor");

    // 动作节点 demon_armor：魔甲术 -> 备选(A)动作：恶魔皮肤
    ACTION_NODE_A(demon_armor, "demon armor", "demon skin");
};

// 构造函数：初始化术士策略并挂载动作节点工厂
WarlockStrategy::WarlockStrategy(PlayerbotAI* ai) : ClassStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<WarlockStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (术士策略)
void WarlockStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("sacrifice", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "life tap",
        NextAction::array(0, new NextAction("life tap", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow trance",
        NextAction::array(0, new NextAction("shadow bolt", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "drain soul",
        NextAction::array(0, new NextAction("drain soul", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("shadowburn", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "corruption",
        NextAction::array(0, new NextAction("corruption", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana",
        NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士策略)
void WarlockStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("initialize pet", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no healthstone",
        NextAction::array(0, new NextAction("create healthstone", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no soulstone",
        NextAction::array(0, new NextAction("create soulstone", ACTION_NORMAL), NULL)));

    /*
    triggers.push_back(new TriggerNode(
        "no firestone",
        NextAction::array(0, new NextAction("create firestone", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no spellstone",
        NextAction::array(0, new NextAction("create spellstone", ACTION_NORMAL), NULL)));
    */
}

// 初始化反应阶段触发器列表 (术士策略)
void WarlockStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (术士策略)
void WarlockStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士PVP策略)
void WarlockPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("drain life", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("shadowburn", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士PVP策略)
void WarlockPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (术士PVP策略)
void WarlockPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (术士PVP策略)
void WarlockPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士PVE策略)
void WarlockPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("drain life", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士PVE策略)
void WarlockPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (术士PVE策略)
void WarlockPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (术士PVE策略)
void WarlockPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士团队副本策略)
void WarlockRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "has aggro",
        NextAction::array(0, new NextAction("shoot", ACTION_HIGH + 9), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士团队副本策略)
void WarlockRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (术士团队副本策略)
void WarlockRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (术士团队副本策略)
void WarlockRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士AOE群体策略)
void WarlockAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "corruption on attacker",
        NextAction::array(0, new NextAction("corruption on attacker", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("rain of fire", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士AOE群体策略)
void WarlockAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士AOE群体PVP策略)
void WarlockAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士AOE群体PVP策略)
void WarlockAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士AOE群体PVE策略)
void WarlockAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士AOE群体PVE策略)
void WarlockAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士AOE群体团队副本策略)
void WarlockAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士AOE群体团队副本策略)
void WarlockAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士增益Buff策略)
void WarlockBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shadow ward",
        NextAction::array(0, new NextAction("shadow ward", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士增益Buff策略)
void WarlockBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "demon armor",
        NextAction::array(0, new NextAction("fel armor", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "soulstone",
        NextAction::array(0, new NextAction("soulstone", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (术士增益BuffPVP策略)
void WarlockBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士增益BuffPVP策略)
void WarlockBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士增益BuffPVE策略)
void WarlockBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士增益BuffPVE策略)
void WarlockBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士增益Buff团队副本策略)
void WarlockBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士增益Buff团队副本策略)
void WarlockBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士爆发增益策略)
void WarlockBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "amplify curse",
        NextAction::array(0, new NextAction("amplify curse", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "inferno",
        NextAction::array(0, new NextAction("inferno", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士爆发增益策略)
void WarlockBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士爆发增益PVP策略)
void WarlockBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士爆发增益PVP策略)
void WarlockBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士爆发增益PVE策略)
void WarlockBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士爆发增益PVE策略)
void WarlockBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士爆发增益团队副本策略)
void WarlockBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士爆发增益团队副本策略)
void WarlockBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士控制(CC)策略)
void WarlockCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "spell lock on enemy healer",
        NextAction::array(0, new NextAction("spell lock on enemy healer", ACTION_INTERRUPT + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "spell lock",
        NextAction::array(0, new NextAction("spell lock", ACTION_INTERRUPT + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "death coil interrupt",
        NextAction::array(0, new NextAction("death coil", ACTION_INTERRUPT + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "death coil on enemy healer",
        NextAction::array(0, new NextAction("death coil on enemy healer", ACTION_INTERRUPT + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "death coil on snare target",
        NextAction::array(0, new NextAction("death coil on snare target", ACTION_INTERRUPT + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "banish",
        NextAction::array(0, new NextAction("banish on cc", ACTION_INTERRUPT + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "fear",
        NextAction::array(0, new NextAction("fear on cc",  ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy ten yards",
        NextAction::array(0, new NextAction("howl of terror", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士控制(CC)策略)
void WarlockCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士控制(CC)PVP策略)
void WarlockCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "fear pvp",
        NextAction::array(0, new NextAction("fear", ACTION_INTERRUPT + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士控制(CC)PVP策略)
void WarlockCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士控制(CC)PVE策略)
void WarlockCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士控制(CC)PVE策略)
void WarlockCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士控制(CC)团队副本策略)
void WarlockCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士控制(CC)团队副本策略)
void WarlockCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士宠物策略)
void WarlockPetStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (术士宠物策略)
void WarlockPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (术士宠物PVP策略)
void WarlockPetPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (术士宠物PVP策略)
void WarlockPetPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon succubus", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon felhunter", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (术士宠物PVE策略)
void WarlockPetPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (术士宠物PVE策略)
void WarlockPetPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon voidwalker", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon imp", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (术士宠物团队副本策略)
void WarlockPetRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (术士宠物团队副本策略)
void WarlockPetRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon imp", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (术士诅咒策略)
void WarlockCursesStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    if (ai->HasStrategy("aoe", BotState::BOT_STATE_COMBAT))
    {
        triggers.push_back(new TriggerNode(
            "no curse on attacker",
            NextAction::array(0, new NextAction("curse of agony on attacker", ACTION_HIGH + 1), NULL)));
    }

    triggers.push_back(new TriggerNode(
        "no curse",
        NextAction::array(0, new NextAction("curse of agony", ACTION_NORMAL + 2), NULL)));
}

// 初始化战斗阶段触发器列表 (术士诅咒PVP策略)
void WarlockCursesPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (术士诅咒PVE策略)
void WarlockCursesPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (术士诅咒团队副本策略)
void WarlockCursesRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (术士策略)
void WarlockStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("sacrifice", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "medium mana",
        NextAction::array(0, new NextAction("life tap", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow trance",
        NextAction::array(0, new NextAction("shadow bolt", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "drain soul",
        NextAction::array(0, new NextAction("drain soul", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("shadowburn", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "corruption",
        NextAction::array(0, new NextAction("corruption", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana",
        NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士策略)
void WarlockStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no healthstone",
        NextAction::array(0, new NextAction("create healthstone", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no soulstone",
        NextAction::array(0, new NextAction("create soulstone", ACTION_NORMAL), NULL)));

    /*
    triggers.push_back(new TriggerNode(
        "no firestone",
        NextAction::array(0, new NextAction("create firestone", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no spellstone",
        NextAction::array(0, new NextAction("create spellstone", ACTION_NORMAL), NULL)));
    */
}

// 初始化反应阶段触发器列表 (术士策略)
void WarlockStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (术士策略)
void WarlockStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士PVP策略)
void WarlockPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("drain life", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("shadowburn", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士PVP策略)
void WarlockPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (术士PVP策略)
void WarlockPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (术士PVP策略)
void WarlockPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士PVE策略)
void WarlockPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("drain life", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士PVE策略)
void WarlockPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (术士PVE策略)
void WarlockPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (术士PVE策略)
void WarlockPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士团队副本策略)
void WarlockRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("soulshatter", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "has aggro",
        NextAction::array(0, new NextAction("shoot", ACTION_HIGH + 9), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士团队副本策略)
void WarlockRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (术士团队副本策略)
void WarlockRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (术士团队副本策略)
void WarlockRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士AOE群体策略)
void WarlockAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "seed of corruption on attacker",
        NextAction::array(0, new NextAction("seed of corruption on attacker", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "corruption on attacker",
        NextAction::array(0, new NextAction("corruption on attacker", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("rain of fire", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士AOE群体策略)
void WarlockAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士AOE群体PVP策略)
void WarlockAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士AOE群体PVP策略)
void WarlockAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士AOE群体PVE策略)
void WarlockAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士AOE群体PVE策略)
void WarlockAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士AOE群体团队副本策略)
void WarlockAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士AOE群体团队副本策略)
void WarlockAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士增益Buff策略)
void WarlockBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shadow ward",
        NextAction::array(0, new NextAction("shadow ward", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士增益Buff策略)
void WarlockBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "demon armor",
        NextAction::array(0, new NextAction("fel armor", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "soulstone",
        NextAction::array(0, new NextAction("soulstone", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (术士增益BuffPVP策略)
void WarlockBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士增益BuffPVP策略)
void WarlockBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士增益BuffPVE策略)
void WarlockBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士增益BuffPVE策略)
void WarlockBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士增益Buff团队副本策略)
void WarlockBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士增益Buff团队副本策略)
void WarlockBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士爆发增益策略)
void WarlockBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "amplify curse",
        NextAction::array(0, new NextAction("amplify curse", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "inferno",
        NextAction::array(0, new NextAction("inferno", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士爆发增益策略)
void WarlockBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士爆发增益PVP策略)
void WarlockBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士爆发增益PVP策略)
void WarlockBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士爆发增益PVE策略)
void WarlockBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士爆发增益PVE策略)
void WarlockBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士爆发增益团队副本策略)
void WarlockBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士爆发增益团队副本策略)
void WarlockBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士控制(CC)策略)
void WarlockCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "spell lock on enemy healer",
        NextAction::array(0, new NextAction("spell lock on enemy healer", ACTION_INTERRUPT + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "spell lock",
        NextAction::array(0, new NextAction("spell lock", ACTION_INTERRUPT + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "death coil interrupt",
        NextAction::array(0, new NextAction("death coil", ACTION_INTERRUPT + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "death coil on enemy healer",
        NextAction::array(0, new NextAction("death coil on enemy healer", ACTION_INTERRUPT + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "death coil on snare target",
        NextAction::array(0, new NextAction("death coil on snare target", ACTION_INTERRUPT + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "banish",
        NextAction::array(0, new NextAction("banish on cc", ACTION_INTERRUPT + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "fear",
        NextAction::array(0, new NextAction("fear on cc",  ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy ten yards",
        NextAction::array(0, new NextAction("howl of terror", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士控制(CC)策略)
void WarlockCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士控制(CC)PVP策略)
void WarlockCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "fear pvp",
        NextAction::array(0, new NextAction("fear", ACTION_INTERRUPT + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士控制(CC)PVP策略)
void WarlockCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士控制(CC)PVE策略)
void WarlockCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士控制(CC)PVE策略)
void WarlockCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士控制(CC)团队副本策略)
void WarlockCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士控制(CC)团队副本策略)
void WarlockCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士宠物策略)
void WarlockPetStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (术士宠物策略)
void WarlockPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("initialize pet", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (术士宠物PVP策略)
void WarlockPetPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (术士宠物PVP策略)
void WarlockPetPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon succubus", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon felhunter", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (术士宠物PVE策略)
void WarlockPetPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (术士宠物PVE策略)
void WarlockPetPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon voidwalker", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon imp", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (术士宠物团队副本策略)
void WarlockPetRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (术士宠物团队副本策略)
void WarlockPetRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon imp", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (术士诅咒策略)
void WarlockCursesStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    if (ai->HasStrategy("aoe", BotState::BOT_STATE_COMBAT))
    {
        triggers.push_back(new TriggerNode(
            "no curse on attacker",
            NextAction::array(0, new NextAction("curse of agony on attacker", ACTION_HIGH + 1), NULL)));
    }

    triggers.push_back(new TriggerNode(
        "no curse",
        NextAction::array(0, new NextAction("curse of agony", ACTION_NORMAL + 2), NULL)));
}

// 初始化战斗阶段触发器列表 (术士诅咒PVP策略)
void WarlockCursesPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (术士诅咒PVE策略)
void WarlockCursesPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (术士诅咒团队副本策略)
void WarlockCursesRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (术士策略)
void WarlockStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("sacrifice", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "life tap",
        NextAction::array(0, new NextAction("life tap", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow trance",
        NextAction::array(0, new NextAction("shadow bolt", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "drain soul",
        NextAction::array(0, new NextAction("drain soul", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("shadowburn", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "corruption",
        NextAction::array(0, new NextAction("corruption", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana",
        NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士策略)
void WarlockStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no healthstone",
        NextAction::array(0, new NextAction("create healthstone", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no soulstone",
        NextAction::array(0, new NextAction("create soulstone", ACTION_NORMAL), NULL)));

    /*
    triggers.push_back(new TriggerNode(
        "no firestone",
        NextAction::array(0, new NextAction("create firestone", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no spellstone",
        NextAction::array(0, new NextAction("create spellstone", ACTION_NORMAL), NULL)));
    */
}

// 初始化反应阶段触发器列表 (术士策略)
void WarlockStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (术士策略)
void WarlockStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士PVP策略)
void WarlockPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("drain life", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("shadowburn", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士PVP策略)
void WarlockPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (术士PVP策略)
void WarlockPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (术士PVP策略)
void WarlockPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士PVE策略)
void WarlockPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("drain life", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士PVE策略)
void WarlockPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (术士PVE策略)
void WarlockPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (术士PVE策略)
void WarlockPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士团队副本策略)
void WarlockRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("soulshatter", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "has aggro",
        NextAction::array(0, new NextAction("shoot", ACTION_HIGH + 9), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士团队副本策略)
void WarlockRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (术士团队副本策略)
void WarlockRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (术士团队副本策略)
void WarlockRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士AOE群体策略)
void WarlockAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "seed of corruption on attacker",
        NextAction::array(0, new NextAction("seed of corruption on attacker", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "corruption on attacker",
        NextAction::array(0, new NextAction("corruption on attacker", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("rain of fire", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士AOE群体策略)
void WarlockAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士AOE群体PVP策略)
void WarlockAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士AOE群体PVP策略)
void WarlockAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士AOE群体PVE策略)
void WarlockAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士AOE群体PVE策略)
void WarlockAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士AOE群体团队副本策略)
void WarlockAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士AOE群体团队副本策略)
void WarlockAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士增益Buff策略)
void WarlockBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shadow ward",
        NextAction::array(0, new NextAction("shadow ward", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士增益Buff策略)
void WarlockBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "demon armor",
        NextAction::array(0, new NextAction("fel armor", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "soulstone",
        NextAction::array(0, new NextAction("soulstone", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (术士增益BuffPVP策略)
void WarlockBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士增益BuffPVP策略)
void WarlockBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士增益BuffPVE策略)
void WarlockBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士增益BuffPVE策略)
void WarlockBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士增益Buff团队副本策略)
void WarlockBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士增益Buff团队副本策略)
void WarlockBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士爆发增益策略)
void WarlockBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "amplify curse",
        NextAction::array(0, new NextAction("amplify curse", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "inferno",
        NextAction::array(0, new NextAction("inferno", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士爆发增益策略)
void WarlockBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士爆发增益PVP策略)
void WarlockBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士爆发增益PVP策略)
void WarlockBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士爆发增益PVE策略)
void WarlockBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士爆发增益PVE策略)
void WarlockBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士爆发增益团队副本策略)
void WarlockBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士爆发增益团队副本策略)
void WarlockBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士控制(CC)策略)
void WarlockCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "spell lock on enemy healer",
        NextAction::array(0, new NextAction("spell lock on enemy healer", ACTION_INTERRUPT + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "spell lock",
        NextAction::array(0, new NextAction("spell lock", ACTION_INTERRUPT + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "death coil interrupt",
        NextAction::array(0, new NextAction("death coil", ACTION_INTERRUPT + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "death coil on enemy healer",
        NextAction::array(0, new NextAction("death coil on enemy healer", ACTION_INTERRUPT + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "death coil on snare target",
        NextAction::array(0, new NextAction("death coil on snare target", ACTION_INTERRUPT + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "banish",
        NextAction::array(0, new NextAction("banish on cc", ACTION_INTERRUPT + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "fear",
        NextAction::array(0, new NextAction("fear on cc",  ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy ten yards",
        NextAction::array(0, new NextAction("howl of terror", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士控制(CC)策略)
void WarlockCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士控制(CC)PVP策略)
void WarlockCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "fear pvp",
        NextAction::array(0, new NextAction("fear", ACTION_INTERRUPT + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (术士控制(CC)PVP策略)
void WarlockCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士控制(CC)PVE策略)
void WarlockCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士控制(CC)PVE策略)
void WarlockCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士控制(CC)团队副本策略)
void WarlockCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (术士控制(CC)团队副本策略)
void WarlockCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (术士宠物策略)
void WarlockPetStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (术士宠物策略)
void WarlockPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (术士宠物PVP策略)
void WarlockPetPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (术士宠物PVP策略)
void WarlockPetPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon succubus", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon felhunter", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (术士宠物PVE策略)
void WarlockPetPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (术士宠物PVE策略)
void WarlockPetPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon voidwalker", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon imp", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (术士宠物团队副本策略)
void WarlockPetRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (术士宠物团队副本策略)
void WarlockPetRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon imp", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (术士诅咒策略)
void WarlockCursesStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    if (ai->HasStrategy("aoe", BotState::BOT_STATE_COMBAT))
    {
        triggers.push_back(new TriggerNode(
            "no curse on attacker",
            NextAction::array(0, new NextAction("curse of agony on attacker", ACTION_HIGH + 1), NULL)));
    }

    triggers.push_back(new TriggerNode(
        "no curse",
        NextAction::array(0, new NextAction("curse of agony", ACTION_NORMAL + 2), NULL)));
}

// 初始化战斗阶段触发器列表 (术士诅咒PVP策略)
void WarlockCursesPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (术士诅咒PVE策略)
void WarlockCursesPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (术士诅咒团队副本策略)
void WarlockCursesRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

#endif

// 初始化非战斗阶段触发器列表 (术士手动宠物策略)
void WarlockManualPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        triggerName,
        NextAction::array(0, new NextAction(actionName, ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("initialize pet", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (术士手动诅咒策略)
void WarlockManualCurseStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    if (ai->HasStrategy("aoe", BotState::BOT_STATE_COMBAT))
    {
        triggers.push_back(new TriggerNode(
            triggerName + " on attacker",
            NextAction::array(0, new NextAction(actionName + " on attacker", ACTION_HIGH + 1), NULL)));
    }

    triggers.push_back(new TriggerNode(
        triggerName,
        NextAction::array(0, new NextAction(actionName, ACTION_HIGH), NULL)));
}
