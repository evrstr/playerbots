// 法师 - 法师策略实现文件 (MageStrategy.cpp)

#include "playerbot/playerbot.h"
#include "MageMultipliers.h"
#include "MageStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class MageStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    MageStrategyActionNodeFactory()
    {
        creators["frostbolt"] = &frostbolt;
        creators["frost nova"] = &frost_nova;
        creators["evocation"] = &evocation;
        creators["remove curse"] = &remove_curse;
        creators["remove curse on party"] = &remove_curse_on_party;
        creators["frostfire bolt"] = &frostfire_bolt;
        creators["dragon's breath"] = &dragons_breath;
        creators["blast wave"] = &blast_wave;
        creators["invisibility"] = &invisibility;
        creators["molten armor"] = &molten_armor;
        creators["mage armor"] = &mage_armor;
        creators["ice armor"] = &ice_armor;
    }

private:
    // 动作节点 frostbolt：寒冰箭 -> 备选(A)动作：shoot
    ACTION_NODE_A(frostbolt, "frostbolt", "shoot");

    // 动作节点 frost_nova：冰霜新星 -> 备选(A)动作：冰锥术
    ACTION_NODE_A(frost_nova, "frost nova", "cone of cold");

    // 动作节点 evocation：唤醒 -> 备选(A)动作：mana potion
    ACTION_NODE_A(evocation, "evocation", "mana potion");

    // 动作节点 remove_curse：解除诅咒 -> 备选(A)动作：解除次级诅咒
    ACTION_NODE_A(remove_curse, "remove curse", "remove lesser curse");

    // 动作节点 remove_curse_on_party：对队友解除诅咒 -> 备选(A)动作：解除次级诅咒 (对队友)
    ACTION_NODE_A(remove_curse_on_party, "remove curse on party", "remove lesser curse on party");

    // 动作节点 frostfire_bolt：霜火之箭 -> 备选(A)动作：火球术
    ACTION_NODE_A(frostfire_bolt, "frostfire bolt", "fireball");

    // 构建 dragons breath (dragons_breath) 动作节点
    static ActionNode* dragons_breath(PlayerbotAI* ai)
    {
        return new ActionNode("dragon's breath",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("blast wave"), NULL),
            /*C*/ NextAction::array(0, new NextAction("flamestrike", 71.0f), NULL));
    }

    // 构建 冲击波 (blast_wave) 动作节点
    static ActionNode* blast_wave(PlayerbotAI* ai)
    {
        return new ActionNode("blast wave",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("frost nova"), NULL),
            /*C*/ NextAction::array(0, new NextAction("flamestrike", 71.0f), NULL));
    }

    // 动作节点 invisibility：隐形术 -> 备选(A)动作：次级隐形术
    ACTION_NODE_A(invisibility, "invisibility", "lesser invisibility");

    // 动作节点 molten_armor：熔甲术 -> 备选(A)动作：魔甲术
    ACTION_NODE_A(molten_armor, "molten armor", "mage armor");

    // 动作节点 mage_armor：魔甲术 -> 备选(A)动作：冰甲术
    ACTION_NODE_A(mage_armor, "mage armor", "ice armor");

    // 动作节点 ice_armor：冰甲术 -> 备选(A)动作：霜甲术
    ACTION_NODE_A(ice_armor, "ice armor", "frost armor");
};

// 构造函数：初始化法师策略并挂载动作节点工厂
MageStrategy::MageStrategy(PlayerbotAI* ai) : ClassStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<MageStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (法师策略)
void MageStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("ice block", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blink",
        NextAction::array(0, new NextAction("blink", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("mana gem", ACTION_HIGH + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("evocation", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("fire blast", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "presence of mind aura",
        NextAction::array(0, new NextAction("pyroblast", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "presence of mind aura",
        NextAction::array(0, new NextAction("frostbolt", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana",
        NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师策略)
void MageStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no drink",
        NextAction::array(0, new NextAction("conjure water", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no food",
        NextAction::array(0, new NextAction("conjure food", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana gem",
        NextAction::array(0, new NextAction("conjure mana gem", ACTION_NORMAL), NULL)));
}

// 初始化反应阶段触发器列表 (法师策略)
void MageStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (法师策略)
void MageStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师PVP策略)
void MagePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("fire blast", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师PVP策略)
void MagePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (法师PVP策略)
void MagePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (法师PVP策略)
void MagePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师PVE策略)
void MagePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师PVE策略)
void MagePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (法师PVE策略)
void MagePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (法师PVE策略)
void MagePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师团队副本策略)
void MageRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "high threat",
        NextAction::array(0, new NextAction("invisibility", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "multiple attackers",
        NextAction::array(0, new NextAction("invisibility", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "has aggro",
        NextAction::array(0, new NextAction("shoot", ACTION_HIGH + 9), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师团队副本策略)
void MageRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (法师团队副本策略)
void MageRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (法师团队副本策略)
void MageRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师AOE群体策略)
void MageAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师AOE群体策略)
void MageAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师AOE群体PVP策略)
void MageAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师AOE群体PVP策略)
void MageAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师AOE群体PVE策略)
void MageAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师AOE群体PVE策略)
void MageAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师AOE群体团队副本策略)
void MageAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师AOE群体团队副本策略)
void MageAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师增益Buff策略)
void MageBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "fire ward",
        NextAction::array(0, new NextAction("fire ward", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "frost ward",
        NextAction::array(0, new NextAction("frost ward", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("mana shield", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师增益Buff策略)
void MageBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "arcane intellect on party",
        NextAction::array(0, new NextAction("arcane intellect on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "arcane brilliance on party",
        NextAction::array(0, new NextAction("arcane brilliance on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "arcane intellect",
        NextAction::array(0, new NextAction("arcane intellect", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "give water",
        NextAction::array(0, new NextAction("give water", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "give food",
        NextAction::array(0, new NextAction("give food", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (法师增益BuffPVP策略)
void MageBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ice armor",
        NextAction::array(0, new NextAction("ice armor", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师增益BuffPVP策略)
void MageBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ice armor",
        NextAction::array(0, new NextAction("ice armor", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (法师增益BuffPVE策略)
void MageBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "mage armor",
        NextAction::array(0, new NextAction("mage armor", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师增益BuffPVE策略)
void MageBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "mage armor",
        NextAction::array(0, new NextAction("mage armor", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (法师增益Buff团队副本策略)
void MageBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师增益Buff团队副本策略)
void MageBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师爆发增益策略)
void MageBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师爆发增益策略)
void MageBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师爆发增益PVP策略)
void MageBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师爆发增益PVP策略)
void MageBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师爆发增益PVE策略)
void MageBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师爆发增益PVE策略)
void MageBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师爆发增益团队副本策略)
void MageBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师爆发增益团队副本策略)
void MageBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师控制(CC)策略)
void MageCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy ten yards",
        NextAction::array(0, new NextAction("frost nova", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "counterspell on enemy healer",
        NextAction::array(0, new NextAction("counterspell on enemy healer", ACTION_INTERRUPT + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "counterspell",
        NextAction::array(0, new NextAction("counterspell", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "polymorph",
        NextAction::array(0, new NextAction("polymorph",  ACTION_INTERRUPT + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师控制(CC)策略)
void MageCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师控制(CC)PVP策略)
void MageCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "counterspell",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师控制(CC)PVP策略)
void MageCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师控制(CC)PVE策略)
void MageCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师控制(CC)PVE策略)
void MageCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师控制(CC)团队副本策略)
void MageCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师控制(CC)团队副本策略)
void MageCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师驱散净化策略)
void MageCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", ACTION_DISPEL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse on party",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师驱散净化策略)
void MageCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse on party",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (法师驱散净化PVP策略)
void MageCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师驱散净化PVP策略)
void MageCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师驱散净化PVE策略)
void MageCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师驱散净化PVE策略)
void MageCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师驱散净化团队副本策略)
void MageCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师驱散净化团队副本策略)
void MageCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (法师策略)
void MageStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("ice block", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blink",
        NextAction::array(0, new NextAction("blink", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "spellsteal",
        NextAction::array(0, new NextAction("spellsteal", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("fire blast", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("mana gem", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("evocation", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana",
        NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师策略)
void MageStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no drink",
        NextAction::array(0, new NextAction("conjure water", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no food",
        NextAction::array(0, new NextAction("conjure food", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana gem",
        NextAction::array(0, new NextAction("conjure mana gem", ACTION_NORMAL), NULL)));
}

// 初始化反应阶段触发器列表 (法师策略)
void MageStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (法师策略)
void MageStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师PVP策略)
void MagePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("fire blast", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师PVP策略)
void MagePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (法师PVP策略)
void MagePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (法师PVP策略)
void MagePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师PVE策略)
void MagePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师PVE策略)
void MagePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (法师PVE策略)
void MagePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (法师PVE策略)
void MagePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师团队副本策略)
void MageRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "high threat",
        NextAction::array(0, new NextAction("invisibility", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "multiple attackers",
        NextAction::array(0, new NextAction("invisibility", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "has aggro",
        NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师团队副本策略)
void MageRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (法师团队副本策略)
void MageRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (法师团队副本策略)
void MageRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师AOE群体策略)
void MageAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师AOE群体策略)
void MageAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师AOE群体PVP策略)
void MageAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师AOE群体PVP策略)
void MageAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师AOE群体PVE策略)
void MageAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师AOE群体PVE策略)
void MageAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师AOE群体团队副本策略)
void MageAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师AOE群体团队副本策略)
void MageAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师增益Buff策略)
void MageBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "fire ward",
        NextAction::array(0, new NextAction("fire ward", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "frost ward",
        NextAction::array(0, new NextAction("frost ward", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师增益Buff策略)
void MageBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "arcane intellect on party",
        NextAction::array(0, new NextAction("arcane intellect on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "arcane brilliance on party",
        NextAction::array(0, new NextAction("arcane brilliance on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "arcane intellect",
        NextAction::array(0, new NextAction("arcane intellect", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "give water",
        NextAction::array(0, new NextAction("give water", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "give food",
        NextAction::array(0, new NextAction("give food", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (法师增益BuffPVP策略)
void MageBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ice armor",
        NextAction::array(0, new NextAction("ice armor", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师增益BuffPVP策略)
void MageBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ice armor",
        NextAction::array(0, new NextAction("ice armor", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (法师增益BuffPVE策略)
void MageBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师增益BuffPVE策略)
void MageBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师增益Buff团队副本策略)
void MageBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师增益Buff团队副本策略)
void MageBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师爆发增益策略)
void MageBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师爆发增益策略)
void MageBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师爆发增益PVP策略)
void MageBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师爆发增益PVP策略)
void MageBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师爆发增益PVE策略)
void MageBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师爆发增益PVE策略)
void MageBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师爆发增益团队副本策略)
void MageBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师爆发增益团队副本策略)
void MageBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师控制(CC)策略)
void MageCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy ten yards",
        NextAction::array(0, new NextAction("frost nova", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "counterspell on enemy healer",
        NextAction::array(0, new NextAction("counterspell on enemy healer", ACTION_INTERRUPT + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "counterspell",
        NextAction::array(0, new NextAction("counterspell", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "polymorph",
        NextAction::array(0, new NextAction("polymorph",  ACTION_INTERRUPT + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师控制(CC)策略)
void MageCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师控制(CC)PVP策略)
void MageCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "counterspell",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师控制(CC)PVP策略)
void MageCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师控制(CC)PVE策略)
void MageCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师控制(CC)PVE策略)
void MageCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师控制(CC)团队副本策略)
void MageCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师控制(CC)团队副本策略)
void MageCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师驱散净化策略)
void MageCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", ACTION_DISPEL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse on party",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师驱散净化策略)
void MageCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse on party",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (法师驱散净化PVP策略)
void MageCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师驱散净化PVP策略)
void MageCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师驱散净化PVE策略)
void MageCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师驱散净化PVE策略)
void MageCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师驱散净化团队副本策略)
void MageCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师驱散净化团队副本策略)
void MageCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (法师策略)
void MageStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("ice block", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "blink",
        NextAction::array(0, new NextAction("blink", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "spellsteal",
        NextAction::array(0, new NextAction("spellsteal", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("fire blast", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("mana gem", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("evocation", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana",
        NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师策略)
void MageStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no drink",
        NextAction::array(0, new NextAction("conjure water", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no food",
        NextAction::array(0, new NextAction("conjure food", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "no mana gem",
        NextAction::array(0, new NextAction("conjure mana gem", ACTION_NORMAL), NULL)));
}

// 初始化反应阶段触发器列表 (法师策略)
void MageStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (法师策略)
void MageStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师PVP策略)
void MagePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("fire blast", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师PVP策略)
void MagePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (法师PVP策略)
void MagePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (法师PVP策略)
void MagePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师PVE策略)
void MagePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师PVE策略)
void MagePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (法师PVE策略)
void MagePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (法师PVE策略)
void MagePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师团队副本策略)
void MageRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "high threat",
        NextAction::array(0, new NextAction("invisibility", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "multiple attackers",
        NextAction::array(0, new NextAction("invisibility", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "has aggro",
        NextAction::array(0, new NextAction("shoot", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师团队副本策略)
void MageRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (法师团队副本策略)
void MageRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (法师团队副本策略)
void MageRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师AOE群体策略)
void MageAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师AOE群体策略)
void MageAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师AOE群体PVP策略)
void MageAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师AOE群体PVP策略)
void MageAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师AOE群体PVE策略)
void MageAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师AOE群体PVE策略)
void MageAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师AOE群体团队副本策略)
void MageAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师AOE群体团队副本策略)
void MageAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师增益Buff策略)
void MageBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "mirror image",
        NextAction::array(0, new NextAction("mirror image", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "fire ward",
        NextAction::array(0, new NextAction("fire ward", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "frost ward",
        NextAction::array(0, new NextAction("frost ward", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师增益Buff策略)
void MageBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "arcane intellect on party",
        NextAction::array(0, new NextAction("arcane intellect on party", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "arcane brilliance on party",
        NextAction::array(0, new NextAction("arcane brilliance on party", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "give water",
        NextAction::array(0, new NextAction("give water", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "give food",
        NextAction::array(0, new NextAction("give food", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "arcane intellect",
        NextAction::array(0, new NextAction("arcane intellect", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (法师增益BuffPVP策略)
void MageBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ice armor",
        NextAction::array(0, new NextAction("ice armor", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师增益BuffPVP策略)
void MageBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ice armor",
        NextAction::array(0, new NextAction("ice armor", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (法师增益BuffPVE策略)
void MageBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "molten armor",
        NextAction::array(0, new NextAction("molten armor", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师增益BuffPVE策略)
void MageBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "molten armor",
        NextAction::array(0, new NextAction("molten armor", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (法师增益Buff团队副本策略)
void MageBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师增益Buff团队副本策略)
void MageBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师爆发增益策略)
void MageBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师爆发增益策略)
void MageBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师爆发增益PVP策略)
void MageBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师爆发增益PVP策略)
void MageBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师爆发增益PVE策略)
void MageBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师爆发增益PVE策略)
void MageBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师爆发增益团队副本策略)
void MageBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师爆发增益团队副本策略)
void MageBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师控制(CC)策略)
void MageCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy ten yards",
        NextAction::array(0, new NextAction("frost nova", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "counterspell on enemy healer",
        NextAction::array(0, new NextAction("counterspell on enemy healer", ACTION_INTERRUPT + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "counterspell",
        NextAction::array(0, new NextAction("counterspell", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "polymorph",
        NextAction::array(0, new NextAction("polymorph",  ACTION_INTERRUPT + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师控制(CC)策略)
void MageCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师控制(CC)PVP策略)
void MageCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "counterspell",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师控制(CC)PVP策略)
void MageCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师控制(CC)PVE策略)
void MageCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师控制(CC)PVE策略)
void MageCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师控制(CC)团队副本策略)
void MageCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师控制(CC)团队副本策略)
void MageCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师驱散净化策略)
void MageCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", ACTION_DISPEL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse on party",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (法师驱散净化策略)
void MageCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse on party",
        NextAction::array(0, new NextAction("remove curse on party", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (法师驱散净化PVP策略)
void MageCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师驱散净化PVP策略)
void MageCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师驱散净化PVE策略)
void MageCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师驱散净化PVE策略)
void MageCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (法师驱散净化团队副本策略)
void MageCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (法师驱散净化团队副本策略)
void MageCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
