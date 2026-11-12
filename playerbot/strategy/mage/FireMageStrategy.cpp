// 法师 - 火焰法师策略实现文件 (FireMageStrategy.cpp)

#include "playerbot/playerbot.h"
#include "MageMultipliers.h"
#include "FireMageStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class FireMageStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    FireMageStrategyActionNodeFactory()
    {
        creators["fire blast"] = &fire_blast;
    }
private:
    // 动作节点 fire_blast：火焰冲击 -> 备选(A)动作：灼烧
    ACTION_NODE_A(fire_blast, "fire blast", "scorch");
};

// 构造函数：初始化火焰法师策略并挂载动作节点工厂
FireMageStrategy::FireMageStrategy(PlayerbotAI* ai) : MageStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<FireMageStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (火焰法师策略)
NextAction** FireMageStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("fireball", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (火焰法师策略)
void FireMageStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no fire vulnerability",
        NextAction::array(0, new NextAction("scorch", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "pyroblast",
        NextAction::array(0, new NextAction("pyroblast", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "fire spells locked",
        NextAction::array(0, new NextAction("frostbolt", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (火焰法师策略)
void FireMageStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (火焰法师策略)
void FireMageStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (火焰法师策略)
void FireMageStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师PVE策略)
void FireMagePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitCombatTriggers(triggers);
    MagePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师PVE策略)
void FireMagePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitNonCombatTriggers(triggers);
    MagePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (火焰法师PVE策略)
void FireMagePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitReactionTriggers(triggers);
    MagePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (火焰法师PVE策略)
void FireMagePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitDeadTriggers(triggers);
    MagePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师PVP策略)
void FireMagePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitCombatTriggers(triggers);
    MagePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师PVP策略)
void FireMagePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitNonCombatTriggers(triggers);
    MagePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (火焰法师PVP策略)
void FireMagePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitReactionTriggers(triggers);
    MagePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (火焰法师PVP策略)
void FireMagePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitDeadTriggers(triggers);
    MagePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师团队副本策略)
void FireMageRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitCombatTriggers(triggers);
    MageRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师团队副本策略)
void FireMageRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitNonCombatTriggers(triggers);
    MageRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (火焰法师团队副本策略)
void FireMageRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitReactionTriggers(triggers);
    MageRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (火焰法师团队副本策略)
void FireMageRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitDeadTriggers(triggers);
    MageRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师AOE群体策略)
void FireMageAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("flamestrike", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "fire spells locked",
        NextAction::array(0, new NextAction("blizzard", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (火焰法师AOE群体策略)
void FireMageAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师AOE群体PVE策略)
void FireMageAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师AOE群体PVE策略)
void FireMageAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师AOE群体PVP策略)
void FireMageAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师AOE群体PVP策略)
void FireMageAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师AOE群体团队副本策略)
void FireMageAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师AOE群体团队副本策略)
void FireMageAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师增益Buff策略)
void FireMageBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师增益Buff策略)
void FireMageBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师增益BuffPVE策略)
void FireMageBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师增益BuffPVE策略)
void FireMageBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师增益BuffPVP策略)
void FireMageBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师增益BuffPVP策略)
void FireMageBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师增益Buff团队副本策略)
void FireMageBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师增益Buff团队副本策略)
void FireMageBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师爆发增益策略)
void FireMageBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "combustion",
        NextAction::array(0, new NextAction("combustion", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (火焰法师爆发增益策略)
void FireMageBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师爆发增益PVE策略)
void FireMageBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师爆发增益PVE策略)
void FireMageBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师爆发增益PVP策略)
void FireMageBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师爆发增益PVP策略)
void FireMageBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师爆发增益团队副本策略)
void FireMageBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师爆发增益团队副本策略)
void FireMageBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师控制(CC)策略)
void FireMageCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy ten yards",
        NextAction::array(0, new NextAction("blast wave", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (火焰法师控制(CC)策略)
void FireMageCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师控制(CC)PVE策略)
void FireMageCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师控制(CC)PVE策略)
void FireMageCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师控制(CC)PVP策略)
void FireMageCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师控制(CC)PVP策略)
void FireMageCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师控制(CC)团队副本策略)
void FireMageCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitCombatTriggers(triggers);
    MageCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师控制(CC)团队副本策略)
void FireMageCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师驱散净化策略)
void FireMageCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师驱散净化策略)
void FireMageCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师驱散净化PVE策略)
void FireMageCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师驱散净化PVE策略)
void FireMageCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师驱散净化PVP策略)
void FireMageCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师驱散净化PVP策略)
void FireMageCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师驱散净化团队副本策略)
void FireMageCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitCombatTriggers(triggers);
    MageCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师驱散净化团队副本策略)
void FireMageCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (火焰法师策略)
NextAction** FireMageStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("fireball", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (火焰法师策略)
void FireMageStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no fire vulnerability",
        NextAction::array(0, new NextAction("scorch", ACTION_NORMAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "living bomb",
        NextAction::array(0, new NextAction("living bomb", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "fire spells locked",
        NextAction::array(0, new NextAction("frostbolt", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (火焰法师策略)
void FireMageStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (火焰法师策略)
void FireMageStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (火焰法师策略)
void FireMageStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师PVE策略)
void FireMagePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitCombatTriggers(triggers);
    MagePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师PVE策略)
void FireMagePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitNonCombatTriggers(triggers);
    MagePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (火焰法师PVE策略)
void FireMagePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitReactionTriggers(triggers);
    MagePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (火焰法师PVE策略)
void FireMagePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitDeadTriggers(triggers);
    MagePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师PVP策略)
void FireMagePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitCombatTriggers(triggers);
    MagePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师PVP策略)
void FireMagePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitNonCombatTriggers(triggers);
    MagePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (火焰法师PVP策略)
void FireMagePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitReactionTriggers(triggers);
    MagePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (火焰法师PVP策略)
void FireMagePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitDeadTriggers(triggers);
    MagePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师团队副本策略)
void FireMageRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitCombatTriggers(triggers);
    MageRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师团队副本策略)
void FireMageRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitNonCombatTriggers(triggers);
    MageRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (火焰法师团队副本策略)
void FireMageRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitReactionTriggers(triggers);
    MageRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (火焰法师团队副本策略)
void FireMageRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitDeadTriggers(triggers);
    MageRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师AOE群体策略)
void FireMageAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "living bomb",
        NextAction::array(0, new NextAction("living bomb", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("flamestrike", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "fire spells locked",
        NextAction::array(0, new NextAction("blizzard", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (火焰法师AOE群体策略)
void FireMageAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师AOE群体PVE策略)
void FireMageAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师AOE群体PVE策略)
void FireMageAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师AOE群体PVP策略)
void FireMageAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师AOE群体PVP策略)
void FireMageAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师AOE群体团队副本策略)
void FireMageAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师AOE群体团队副本策略)
void FireMageAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师增益Buff策略)
void FireMageBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师增益Buff策略)
void FireMageBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师增益BuffPVE策略)
void FireMageBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "molten armor",
        NextAction::array(0, new NextAction("molten armor", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (火焰法师增益BuffPVE策略)
void FireMageBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "molten armor",
        NextAction::array(0, new NextAction("molten armor", ACTION_HIGH), NULL)));
}

// 初始化战斗阶段触发器列表 (火焰法师增益BuffPVP策略)
void FireMageBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师增益BuffPVP策略)
void FireMageBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师增益Buff团队副本策略)
void FireMageBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师增益Buff团队副本策略)
void FireMageBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师爆发增益策略)
void FireMageBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "combustion",
        NextAction::array(0, new NextAction("combustion", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (火焰法师爆发增益策略)
void FireMageBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师爆发增益PVE策略)
void FireMageBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师爆发增益PVE策略)
void FireMageBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师爆发增益PVP策略)
void FireMageBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师爆发增益PVP策略)
void FireMageBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师爆发增益团队副本策略)
void FireMageBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师爆发增益团队副本策略)
void FireMageBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师控制(CC)策略)
void FireMageCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("dragon's breath", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy ten yards",
        NextAction::array(0, new NextAction("blast wave", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (火焰法师控制(CC)策略)
void FireMageCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师控制(CC)PVE策略)
void FireMageCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师控制(CC)PVE策略)
void FireMageCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师控制(CC)PVP策略)
void FireMageCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师控制(CC)PVP策略)
void FireMageCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师控制(CC)团队副本策略)
void FireMageCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitCombatTriggers(triggers);
    MageCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师控制(CC)团队副本策略)
void FireMageCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师驱散净化策略)
void FireMageCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师驱散净化策略)
void FireMageCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师驱散净化PVE策略)
void FireMageCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师驱散净化PVE策略)
void FireMageCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师驱散净化PVP策略)
void FireMageCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师驱散净化PVP策略)
void FireMageCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师驱散净化团队副本策略)
void FireMageCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitCombatTriggers(triggers);
    MageCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师驱散净化团队副本策略)
void FireMageCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (火焰法师策略)
NextAction** FireMageStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("fireball", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (火焰法师策略)
void FireMageStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "living bomb",
        NextAction::array(0, new NextAction("living bomb", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "hot streak",
        NextAction::array(0, new NextAction("pyroblast", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "no improved scorch",
        NextAction::array(0, new NextAction("scorch", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "fire spells locked",
        NextAction::array(0, new NextAction("frostbolt", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (火焰法师策略)
void FireMageStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (火焰法师策略)
void FireMageStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (火焰法师策略)
void FireMageStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师PVE策略)
void FireMagePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitCombatTriggers(triggers);
    MagePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师PVE策略)
void FireMagePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitNonCombatTriggers(triggers);
    MagePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (火焰法师PVE策略)
void FireMagePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitReactionTriggers(triggers);
    MagePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (火焰法师PVE策略)
void FireMagePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitDeadTriggers(triggers);
    MagePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师PVP策略)
void FireMagePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitCombatTriggers(triggers);
    MagePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师PVP策略)
void FireMagePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitNonCombatTriggers(triggers);
    MagePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (火焰法师PVP策略)
void FireMagePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitReactionTriggers(triggers);
    MagePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (火焰法师PVP策略)
void FireMagePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitDeadTriggers(triggers);
    MagePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师团队副本策略)
void FireMageRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitCombatTriggers(triggers);
    MageRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师团队副本策略)
void FireMageRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitNonCombatTriggers(triggers);
    MageRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (火焰法师团队副本策略)
void FireMageRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitReactionTriggers(triggers);
    MageRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (火焰法师团队副本策略)
void FireMageRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageStrategy::InitDeadTriggers(triggers);
    MageRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师AOE群体策略)
void FireMageAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "living bomb",
        NextAction::array(0, new NextAction("living bomb", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("flamestrike", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "fire spells locked",
        NextAction::array(0, new NextAction("blizzard", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (火焰法师AOE群体策略)
void FireMageAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师AOE群体PVE策略)
void FireMageAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师AOE群体PVE策略)
void FireMageAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师AOE群体PVP策略)
void FireMageAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师AOE群体PVP策略)
void FireMageAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师AOE群体团队副本策略)
void FireMageAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师AOE群体团队副本策略)
void FireMageAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师增益Buff策略)
void FireMageBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师增益Buff策略)
void FireMageBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师增益BuffPVE策略)
void FireMageBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师增益BuffPVE策略)
void FireMageBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师增益BuffPVP策略)
void FireMageBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师增益BuffPVP策略)
void FireMageBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师增益Buff团队副本策略)
void FireMageBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师增益Buff团队副本策略)
void FireMageBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师爆发增益策略)
void FireMageBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "combustion",
        NextAction::array(0, new NextAction("combustion", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (火焰法师爆发增益策略)
void FireMageBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师爆发增益PVE策略)
void FireMageBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师爆发增益PVE策略)
void FireMageBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师爆发增益PVP策略)
void FireMageBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师爆发增益PVP策略)
void FireMageBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师爆发增益团队副本策略)
void FireMageBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师爆发增益团队副本策略)
void FireMageBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师控制(CC)策略)
void FireMageCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("dragon's breath", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy ten yards",
        NextAction::array(0, new NextAction("blast wave", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (火焰法师控制(CC)策略)
void FireMageCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师控制(CC)PVE策略)
void FireMageCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师控制(CC)PVE策略)
void FireMageCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师控制(CC)PVP策略)
void FireMageCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师控制(CC)PVP策略)
void FireMageCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师控制(CC)团队副本策略)
void FireMageCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitCombatTriggers(triggers);
    MageCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师控制(CC)团队副本策略)
void FireMageCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师驱散净化策略)
void FireMageCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师驱散净化策略)
void FireMageCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师驱散净化PVE策略)
void FireMageCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师驱散净化PVE策略)
void FireMageCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师驱散净化PVP策略)
void FireMageCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师驱散净化PVP策略)
void FireMageCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (火焰法师驱散净化团队副本策略)
void FireMageCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitCombatTriggers(triggers);
    MageCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (火焰法师驱散净化团队副本策略)
void FireMageCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    FireMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
