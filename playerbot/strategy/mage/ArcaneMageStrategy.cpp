// 法师 - 奥术法师策略实现文件 (ArcaneMageStrategy.cpp)

#include "playerbot/playerbot.h"
#include "MageMultipliers.h"
#include "ArcaneMageStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class ArcaneMageStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    ArcaneMageStrategyActionNodeFactory()
    {
        creators["arcane blast"] = &arcane_blast;
        creators["arcane blast tbc"] = &arcane_blast_tbc;
        creators["arcane barrage"] = &arcane_barrage;
        creators["arcane missiles"] = &arcane_missiles;
    }

private:
    // 动作节点 arcane_blast：奥术冲击 -> 备选(A)动作：奥术飞弹
    ACTION_NODE_A(arcane_blast, "arcane blast", "arcane missiles");

    // 动作节点 arcane_blast_tbc：奥术冲击(TBC) -> 备选(A)动作：奥术飞弹
    ACTION_NODE_A(arcane_blast_tbc, "arcane blast tbc", "arcane missiles");

    // 动作节点 arcane_barrage：奥术弹幕 -> 备选(A)动作：奥术飞弹
    ACTION_NODE_A(arcane_barrage, "arcane barrage", "arcane missiles");

    // 动作节点 arcane_missiles：奥术飞弹 -> 备选(A)动作：shoot
    ACTION_NODE_A(arcane_missiles, "arcane missiles", "shoot");
};

// 构造函数：初始化奥术法师策略并挂载动作节点工厂
ArcaneMageStrategy::ArcaneMageStrategy(PlayerbotAI* ai) : MageStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<ArcaneMageStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (奥术法师策略)
NextAction** ArcaneMageStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("arcane missiles", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (奥术法师策略)
void ArcaneMageStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师策略)
void ArcaneMageStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (奥术法师策略)
void ArcaneMageStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (奥术法师策略)
void ArcaneMageStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师PVE策略)
void ArcaneMagePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitCombatTriggers(triggers);
    MagePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师PVE策略)
void ArcaneMagePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitNonCombatTriggers(triggers);
    MagePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (奥术法师PVE策略)
void ArcaneMagePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitReactionTriggers(triggers);
    MagePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (奥术法师PVE策略)
void ArcaneMagePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitDeadTriggers(triggers);
    MagePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师PVP策略)
void ArcaneMagePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitCombatTriggers(triggers);
    MagePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师PVP策略)
void ArcaneMagePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitNonCombatTriggers(triggers);
    MagePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (奥术法师PVP策略)
void ArcaneMagePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitReactionTriggers(triggers);
    MagePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (奥术法师PVP策略)
void ArcaneMagePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitDeadTriggers(triggers);
    MagePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师团队副本策略)
void ArcaneMageRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitCombatTriggers(triggers);
    MageRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师团队副本策略)
void ArcaneMageRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitNonCombatTriggers(triggers);
    MageRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (奥术法师团队副本策略)
void ArcaneMageRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitReactionTriggers(triggers);
    MageRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (奥术法师团队副本策略)
void ArcaneMageRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitDeadTriggers(triggers);
    MageRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师AOE群体策略)
void ArcaneMageAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("arcane explosion", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("flamestrike", ACTION_HIGH + 2), new NextAction("blizzard", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (奥术法师AOE群体策略)
void ArcaneMageAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师AOE群体PVE策略)
void ArcaneMageAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师AOE群体PVE策略)
void ArcaneMageAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师AOE群体PVP策略)
void ArcaneMageAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师AOE群体PVP策略)
void ArcaneMageAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师AOE群体团队副本策略)
void ArcaneMageAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师AOE群体团队副本策略)
void ArcaneMageAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师增益Buff策略)
void ArcaneMageBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师增益Buff策略)
void ArcaneMageBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师增益BuffPVE策略)
void ArcaneMageBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师增益BuffPVE策略)
void ArcaneMageBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师增益BuffPVP策略)
void ArcaneMageBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师增益BuffPVP策略)
void ArcaneMageBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师增益Buff团队副本策略)
void ArcaneMageBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师增益Buff团队副本策略)
void ArcaneMageBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师爆发增益策略)
void ArcaneMageBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "arcane power",
        NextAction::array(0, new NextAction("arcane power", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "presence of mind",
        NextAction::array(0, new NextAction("presence of mind", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (奥术法师爆发增益策略)
void ArcaneMageBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师爆发增益PVE策略)
void ArcaneMageBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师爆发增益PVE策略)
void ArcaneMageBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师爆发增益PVP策略)
void ArcaneMageBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师爆发增益PVP策略)
void ArcaneMageBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师爆发增益团队副本策略)
void ArcaneMageBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师爆发增益团队副本策略)
void ArcaneMageBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师控制(CC)策略)
void ArcaneMageCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师控制(CC)策略)
void ArcaneMageCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师控制(CC)PVE策略)
void ArcaneMageCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师控制(CC)PVE策略)
void ArcaneMageCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师控制(CC)PVP策略)
void ArcaneMageCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师控制(CC)PVP策略)
void ArcaneMageCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师控制(CC)团队副本策略)
void ArcaneMageCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitCombatTriggers(triggers);
    MageCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师控制(CC)团队副本策略)
void ArcaneMageCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师驱散净化策略)
void ArcaneMageCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师驱散净化策略)
void ArcaneMageCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师驱散净化PVE策略)
void ArcaneMageCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师驱散净化PVE策略)
void ArcaneMageCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师驱散净化PVP策略)
void ArcaneMageCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师驱散净化PVP策略)
void ArcaneMageCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师驱散净化团队副本策略)
void ArcaneMageCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitCombatTriggers(triggers);
    MageCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师驱散净化团队副本策略)
void ArcaneMageCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (奥术法师策略)
NextAction** ArcaneMageStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("arcane blast", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (奥术法师策略)
void ArcaneMageStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "arcane blast",
        NextAction::array(0, new NextAction("arcane blast tbc", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "arcane blast full",
        NextAction::array(0, new NextAction("frostbolt", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (奥术法师策略)
void ArcaneMageStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (奥术法师策略)
void ArcaneMageStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (奥术法师策略)
void ArcaneMageStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师PVE策略)
void ArcaneMagePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitCombatTriggers(triggers);
    MagePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师PVE策略)
void ArcaneMagePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitNonCombatTriggers(triggers);
    MagePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (奥术法师PVE策略)
void ArcaneMagePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitReactionTriggers(triggers);
    MagePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (奥术法师PVE策略)
void ArcaneMagePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitDeadTriggers(triggers);
    MagePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师PVP策略)
void ArcaneMagePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitCombatTriggers(triggers);
    MagePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师PVP策略)
void ArcaneMagePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitNonCombatTriggers(triggers);
    MagePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (奥术法师PVP策略)
void ArcaneMagePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitReactionTriggers(triggers);
    MagePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (奥术法师PVP策略)
void ArcaneMagePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitDeadTriggers(triggers);
    MagePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师团队副本策略)
void ArcaneMageRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitCombatTriggers(triggers);
    MageRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师团队副本策略)
void ArcaneMageRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitNonCombatTriggers(triggers);
    MageRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (奥术法师团队副本策略)
void ArcaneMageRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitReactionTriggers(triggers);
    MageRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (奥术法师团队副本策略)
void ArcaneMageRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitDeadTriggers(triggers);
    MageRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师AOE群体策略)
void ArcaneMageAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("arcane explosion", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "ranged high aoe",
        NextAction::array(0, new NextAction("flamestrike", ACTION_HIGH + 2), new NextAction("blizzard", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (奥术法师AOE群体策略)
void ArcaneMageAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师AOE群体PVE策略)
void ArcaneMageAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师AOE群体PVE策略)
void ArcaneMageAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师AOE群体PVP策略)
void ArcaneMageAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师AOE群体PVP策略)
void ArcaneMageAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师AOE群体团队副本策略)
void ArcaneMageAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师AOE群体团队副本策略)
void ArcaneMageAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师增益Buff策略)
void ArcaneMageBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师增益Buff策略)
void ArcaneMageBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师增益BuffPVE策略)
void ArcaneMageBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "mage armor",
        NextAction::array(0, new NextAction("mage armor", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (奥术法师增益BuffPVE策略)
void ArcaneMageBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "mage armor",
        NextAction::array(0, new NextAction("mage armor", ACTION_HIGH), NULL)));
}

// 初始化战斗阶段触发器列表 (奥术法师增益BuffPVP策略)
void ArcaneMageBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师增益BuffPVP策略)
void ArcaneMageBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师增益Buff团队副本策略)
void ArcaneMageBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师增益Buff团队副本策略)
void ArcaneMageBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师爆发增益策略)
void ArcaneMageBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "arcane power",
        NextAction::array(0, new NextAction("arcane power", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "presence of mind",
        NextAction::array(0, new NextAction("presence of mind", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (奥术法师爆发增益策略)
void ArcaneMageBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师爆发增益PVE策略)
void ArcaneMageBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师爆发增益PVE策略)
void ArcaneMageBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师爆发增益PVP策略)
void ArcaneMageBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师爆发增益PVP策略)
void ArcaneMageBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师爆发增益团队副本策略)
void ArcaneMageBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师爆发增益团队副本策略)
void ArcaneMageBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师控制(CC)策略)
void ArcaneMageCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师控制(CC)策略)
void ArcaneMageCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师控制(CC)PVE策略)
void ArcaneMageCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师控制(CC)PVE策略)
void ArcaneMageCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师控制(CC)PVP策略)
void ArcaneMageCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师控制(CC)PVP策略)
void ArcaneMageCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师控制(CC)团队副本策略)
void ArcaneMageCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitCombatTriggers(triggers);
    MageCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师控制(CC)团队副本策略)
void ArcaneMageCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师驱散净化策略)
void ArcaneMageCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师驱散净化策略)
void ArcaneMageCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师驱散净化PVE策略)
void ArcaneMageCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师驱散净化PVE策略)
void ArcaneMageCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师驱散净化PVP策略)
void ArcaneMageCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师驱散净化PVP策略)
void ArcaneMageCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师驱散净化团队副本策略)
void ArcaneMageCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitCombatTriggers(triggers);
    MageCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师驱散净化团队副本策略)
void ArcaneMageCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (奥术法师策略)
NextAction** ArcaneMageStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("arcane missiles", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (奥术法师策略)
void ArcaneMageStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "arcane blast",
        NextAction::array(0, new NextAction("arcane blast", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "missile barrage",
        NextAction::array(0, new NextAction("arcane missiles", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (奥术法师策略)
void ArcaneMageStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (奥术法师策略)
void ArcaneMageStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (奥术法师策略)
void ArcaneMageStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    MageStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师PVE策略)
void ArcaneMagePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitCombatTriggers(triggers);
    MagePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师PVE策略)
void ArcaneMagePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitNonCombatTriggers(triggers);
    MagePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (奥术法师PVE策略)
void ArcaneMagePveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitReactionTriggers(triggers);
    MagePveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (奥术法师PVE策略)
void ArcaneMagePveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitDeadTriggers(triggers);
    MagePveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师PVP策略)
void ArcaneMagePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitCombatTriggers(triggers);
    MagePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师PVP策略)
void ArcaneMagePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitNonCombatTriggers(triggers);
    MagePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (奥术法师PVP策略)
void ArcaneMagePvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitReactionTriggers(triggers);
    MagePvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (奥术法师PVP策略)
void ArcaneMagePvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitDeadTriggers(triggers);
    MagePvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师团队副本策略)
void ArcaneMageRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitCombatTriggers(triggers);
    MageRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师团队副本策略)
void ArcaneMageRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitNonCombatTriggers(triggers);
    MageRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (奥术法师团队副本策略)
void ArcaneMageRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitReactionTriggers(triggers);
    MageRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (奥术法师团队副本策略)
void ArcaneMageRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageStrategy::InitDeadTriggers(triggers);
    MageRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师AOE群体策略)
void ArcaneMageAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("arcane explosion", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (奥术法师AOE群体策略)
void ArcaneMageAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师AOE群体PVE策略)
void ArcaneMageAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师AOE群体PVE策略)
void ArcaneMageAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师AOE群体PVP策略)
void ArcaneMageAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师AOE群体PVP策略)
void ArcaneMageAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师AOE群体团队副本策略)
void ArcaneMageAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitCombatTriggers(triggers);
    MageAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师AOE群体团队副本策略)
void ArcaneMageAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageAoeStrategy::InitNonCombatTriggers(triggers);
    MageAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师增益Buff策略)
void ArcaneMageBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "arcane power",
        NextAction::array(0, new NextAction("arcane power", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "presence of mind",
        NextAction::array(0, new NextAction("presence of mind", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (奥术法师增益Buff策略)
void ArcaneMageBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师增益BuffPVE策略)
void ArcaneMageBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师增益BuffPVE策略)
void ArcaneMageBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师增益BuffPVP策略)
void ArcaneMageBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师增益BuffPVP策略)
void ArcaneMageBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师增益Buff团队副本策略)
void ArcaneMageBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitCombatTriggers(triggers);
    MageBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师增益Buff团队副本策略)
void ArcaneMageBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBuffStrategy::InitNonCombatTriggers(triggers);
    MageBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师爆发增益策略)
void ArcaneMageBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "arcane power",
        NextAction::array(0, new NextAction("arcane power", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "presence of mind",
        NextAction::array(0, new NextAction("presence of mind", ACTION_HIGH + 1), NULL)));
}

// 初始化非战斗阶段触发器列表 (奥术法师爆发增益策略)
void ArcaneMageBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师爆发增益PVE策略)
void ArcaneMageBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师爆发增益PVE策略)
void ArcaneMageBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师爆发增益PVP策略)
void ArcaneMageBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师爆发增益PVP策略)
void ArcaneMageBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师爆发增益团队副本策略)
void ArcaneMageBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitCombatTriggers(triggers);
    MageBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师爆发增益团队副本策略)
void ArcaneMageBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageBoostStrategy::InitNonCombatTriggers(triggers);
    MageBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师控制(CC)策略)
void ArcaneMageCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师控制(CC)策略)
void ArcaneMageCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师控制(CC)PVE策略)
void ArcaneMageCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师控制(CC)PVE策略)
void ArcaneMageCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师控制(CC)PVP策略)
void ArcaneMageCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitCombatTriggers(triggers);
    MageCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师控制(CC)PVP策略)
void ArcaneMageCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师控制(CC)团队副本策略)
void ArcaneMageCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitCombatTriggers(triggers);
    MageCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师控制(CC)团队副本策略)
void ArcaneMageCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCcStrategy::InitNonCombatTriggers(triggers);
    MageCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师驱散净化策略)
void ArcaneMageCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师驱散净化策略)
void ArcaneMageCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    MageCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师驱散净化PVE策略)
void ArcaneMageCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师驱散净化PVE策略)
void ArcaneMageCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师驱散净化PVP策略)
void ArcaneMageCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitCombatTriggers(triggers);
    MageCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师驱散净化PVP策略)
void ArcaneMageCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (奥术法师驱散净化团队副本策略)
void ArcaneMageCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitCombatTriggers(triggers);
    MageCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (奥术法师驱散净化团队副本策略)
void ArcaneMageCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ArcaneMageCureStrategy::InitNonCombatTriggers(triggers);
    MageCureRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
