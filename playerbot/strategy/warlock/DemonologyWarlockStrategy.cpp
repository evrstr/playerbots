// 术士 - 恶魔学识术士策略实现文件 (DemonologyWarlockStrategy.cpp)

#include "playerbot/playerbot.h"
#include "WarlockTriggers.h"
#include "WarlockMultipliers.h"
#include "DemonologyWarlockStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class DemonologyWarlockStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DemonologyWarlockStrategyActionNodeFactory()
    {
        creators["demonic sacrifice raid"] = &demonic_sacrifice_raid;
    }

private:
    // 动作节点 demonic_sacrifice_raid：恶魔牺牲 -> 前置(P)动作：召唤魅魔
    ACTION_NODE_P(demonic_sacrifice_raid, "demonic sacrifice", "summon succubus");
};

// 构造函数：初始化恶魔学识术士策略并挂载动作节点工厂
DemonologyWarlockStrategy::DemonologyWarlockStrategy(PlayerbotAI* ai) : WarlockStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<DemonologyWarlockStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (恶魔学识术士策略)
ai::NextAction** DemonologyWarlockStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("shadow bolt", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士策略)
void DemonologyWarlockStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士策略)
void DemonologyWarlockStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恶魔学识术士策略)
void DemonologyWarlockStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恶魔学识术士策略)
void DemonologyWarlockStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士PVE策略)
void DemonologyWarlockPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士PVE策略)
void DemonologyWarlockPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恶魔学识术士PVE策略)
void DemonologyWarlockPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恶魔学识术士PVE策略)
void DemonologyWarlockPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士PVP策略)
void DemonologyWarlockPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士PVP策略)
void DemonologyWarlockPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恶魔学识术士PVP策略)
void DemonologyWarlockPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恶魔学识术士PVP策略)
void DemonologyWarlockPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士团队副本策略)
void DemonologyWarlockRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitCombatTriggers(triggers);
    WarlockRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士团队副本策略)
void DemonologyWarlockRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恶魔学识术士团队副本策略)
void DemonologyWarlockRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitReactionTriggers(triggers);
    WarlockRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恶魔学识术士团队副本策略)
void DemonologyWarlockRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitDeadTriggers(triggers);
    WarlockRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士AOE群体策略)
void DemonologyWarlockAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士AOE群体策略)
void DemonologyWarlockAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士AOE群体PVE策略)
void DemonologyWarlockAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士AOE群体PVE策略)
void DemonologyWarlockAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士AOE群体PVP策略)
void DemonologyWarlockAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士AOE群体PVP策略)
void DemonologyWarlockAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士AOE群体团队副本策略)
void DemonologyWarlockAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士AOE群体团队副本策略)
void DemonologyWarlockAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士增益Buff策略)
void DemonologyWarlockBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士增益Buff策略)
void DemonologyWarlockBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "soul link",
        NextAction::array(0, new NextAction("soul link", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (恶魔学识术士增益BuffPVE策略)
void DemonologyWarlockBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士增益BuffPVE策略)
void DemonologyWarlockBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士增益BuffPVP策略)
void DemonologyWarlockBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士增益BuffPVP策略)
void DemonologyWarlockBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士增益Buff团队副本策略)
void DemonologyWarlockBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士增益Buff团队副本策略)
void DemonologyWarlockBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "demonic sacrifice",
        NextAction::array(0, new NextAction("demonic sacrifice raid", ACTION_HIGH), NULL)));
}

// 初始化战斗阶段触发器列表 (恶魔学识术士爆发增益策略)
void DemonologyWarlockBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士爆发增益策略)
void DemonologyWarlockBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士爆发增益PVE策略)
void DemonologyWarlockBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士爆发增益PVE策略)
void DemonologyWarlockBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士爆发增益PVP策略)
void DemonologyWarlockBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士爆发增益PVP策略)
void DemonologyWarlockBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士爆发增益团队副本策略)
void DemonologyWarlockBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士爆发增益团队副本策略)
void DemonologyWarlockBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士控制(CC)策略)
void DemonologyWarlockCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士控制(CC)策略)
void DemonologyWarlockCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士控制(CC)PVE策略)
void DemonologyWarlockCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士控制(CC)PVE策略)
void DemonologyWarlockCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士控制(CC)PVP策略)
void DemonologyWarlockCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士控制(CC)PVP策略)
void DemonologyWarlockCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士控制(CC)团队副本策略)
void DemonologyWarlockCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士控制(CC)团队副本策略)
void DemonologyWarlockCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士宠物策略)
void DemonologyWarlockPetStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士宠物策略)
void DemonologyWarlockPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士宠物PVE策略)
void DemonologyWarlockPetPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士宠物PVE策略)
void DemonologyWarlockPetPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士宠物PVP策略)
void DemonologyWarlockPetPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士宠物PVP策略)
void DemonologyWarlockPetPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士宠物团队副本策略)
void DemonologyWarlockPetRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士宠物团队副本策略)
void DemonologyWarlockPetRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    /* NO PET BECAUSE OF DEMONIC SACRIFICE
    DemonologyWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitNonCombatTriggers(triggers);
    */
}

// 初始化战斗阶段触发器列表 (恶魔学识术士诅咒策略)
void DemonologyWarlockCursesStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCursesStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士诅咒PVE策略)
void DemonologyWarlockCursesPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士诅咒PVP策略)
void DemonologyWarlockCursesPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士诅咒团队副本策略)
void DemonologyWarlockCursesRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesRaidStrategy::InitCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (恶魔学识术士策略)
ai::NextAction** DemonologyWarlockStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("shadow bolt", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士策略)
void DemonologyWarlockStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士策略)
void DemonologyWarlockStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恶魔学识术士策略)
void DemonologyWarlockStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恶魔学识术士策略)
void DemonologyWarlockStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士PVE策略)
void DemonologyWarlockPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士PVE策略)
void DemonologyWarlockPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恶魔学识术士PVE策略)
void DemonologyWarlockPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恶魔学识术士PVE策略)
void DemonologyWarlockPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士PVP策略)
void DemonologyWarlockPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士PVP策略)
void DemonologyWarlockPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恶魔学识术士PVP策略)
void DemonologyWarlockPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恶魔学识术士PVP策略)
void DemonologyWarlockPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士团队副本策略)
void DemonologyWarlockRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitCombatTriggers(triggers);
    WarlockRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士团队副本策略)
void DemonologyWarlockRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恶魔学识术士团队副本策略)
void DemonologyWarlockRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitReactionTriggers(triggers);
    WarlockRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恶魔学识术士团队副本策略)
void DemonologyWarlockRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitDeadTriggers(triggers);
    WarlockRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士AOE群体策略)
void DemonologyWarlockAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士AOE群体策略)
void DemonologyWarlockAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士AOE群体PVE策略)
void DemonologyWarlockAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士AOE群体PVE策略)
void DemonologyWarlockAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士AOE群体PVP策略)
void DemonologyWarlockAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士AOE群体PVP策略)
void DemonologyWarlockAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士AOE群体团队副本策略)
void DemonologyWarlockAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士AOE群体团队副本策略)
void DemonologyWarlockAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士增益Buff策略)
void DemonologyWarlockBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士增益Buff策略)
void DemonologyWarlockBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitNonCombatTriggers(triggers);
    triggers.push_back(new TriggerNode(
        "soul link",
        NextAction::array(0, new NextAction("soul link", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (恶魔学识术士增益BuffPVE策略)
void DemonologyWarlockBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士增益BuffPVE策略)
void DemonologyWarlockBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitNonCombatTriggers(triggers);
    triggers.push_back(new TriggerNode(
        "soul link",
        NextAction::array(0, new NextAction("soul link", ACTION_NORMAL + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (恶魔学识术士增益BuffPVP策略)
void DemonologyWarlockBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士增益BuffPVP策略)
void DemonologyWarlockBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士增益Buff团队副本策略)
void DemonologyWarlockBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士增益Buff团队副本策略)
void DemonologyWarlockBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "demonic sacrifice",
        NextAction::array(0, new NextAction("demonic sacrifice raid", ACTION_HIGH), NULL)));
}

// 初始化战斗阶段触发器列表 (恶魔学识术士爆发增益策略)
void DemonologyWarlockBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士爆发增益策略)
void DemonologyWarlockBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士爆发增益PVE策略)
void DemonologyWarlockBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士爆发增益PVE策略)
void DemonologyWarlockBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士爆发增益PVP策略)
void DemonologyWarlockBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士爆发增益PVP策略)
void DemonologyWarlockBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士爆发增益团队副本策略)
void DemonologyWarlockBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士爆发增益团队副本策略)
void DemonologyWarlockBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士控制(CC)策略)
void DemonologyWarlockCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士控制(CC)策略)
void DemonologyWarlockCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士控制(CC)PVE策略)
void DemonologyWarlockCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士控制(CC)PVE策略)
void DemonologyWarlockCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士控制(CC)PVP策略)
void DemonologyWarlockCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士控制(CC)PVP策略)
void DemonologyWarlockCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士控制(CC)团队副本策略)
void DemonologyWarlockCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士控制(CC)团队副本策略)
void DemonologyWarlockCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士宠物策略)
void DemonologyWarlockPetStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士宠物策略)
void DemonologyWarlockPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士宠物PVE策略)
void DemonologyWarlockPetPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士宠物PVE策略)
void DemonologyWarlockPetPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon felguard", ACTION_NORMAL + 2), NULL)));
}

// 初始化战斗阶段触发器列表 (恶魔学识术士宠物PVP策略)
void DemonologyWarlockPetPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士宠物PVP策略)
void DemonologyWarlockPetPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon felguard", ACTION_NORMAL + 2), NULL)));
}

// 初始化战斗阶段触发器列表 (恶魔学识术士宠物团队副本策略)
void DemonologyWarlockPetRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士宠物团队副本策略)
void DemonologyWarlockPetRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    /* NO PET BECAUSE OF DEMONIC SACRIFICE
    DemonologyWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitNonCombatTriggers(triggers);
    */
}

// 初始化战斗阶段触发器列表 (恶魔学识术士诅咒策略)
void DemonologyWarlockCursesStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCursesStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士诅咒PVE策略)
void DemonologyWarlockCursesPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士诅咒PVP策略)
void DemonologyWarlockCursesPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士诅咒团队副本策略)
void DemonologyWarlockCursesRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesRaidStrategy::InitCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (恶魔学识术士策略)
ai::NextAction** DemonologyWarlockStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("shadow bolt", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士策略)
void DemonologyWarlockStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士策略)
void DemonologyWarlockStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恶魔学识术士策略)
void DemonologyWarlockStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恶魔学识术士策略)
void DemonologyWarlockStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士PVE策略)
void DemonologyWarlockPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士PVE策略)
void DemonologyWarlockPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恶魔学识术士PVE策略)
void DemonologyWarlockPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恶魔学识术士PVE策略)
void DemonologyWarlockPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士PVP策略)
void DemonologyWarlockPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitCombatTriggers(triggers);
    WarlockPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士PVP策略)
void DemonologyWarlockPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恶魔学识术士PVP策略)
void DemonologyWarlockPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitReactionTriggers(triggers);
    WarlockPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恶魔学识术士PVP策略)
void DemonologyWarlockPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitDeadTriggers(triggers);
    WarlockPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士团队副本策略)
void DemonologyWarlockRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitCombatTriggers(triggers);
    WarlockRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士团队副本策略)
void DemonologyWarlockRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitNonCombatTriggers(triggers);
    WarlockRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恶魔学识术士团队副本策略)
void DemonologyWarlockRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitReactionTriggers(triggers);
    WarlockRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恶魔学识术士团队副本策略)
void DemonologyWarlockRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockStrategy::InitDeadTriggers(triggers);
    WarlockRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士AOE群体策略)
void DemonologyWarlockAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士AOE群体策略)
void DemonologyWarlockAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士AOE群体PVE策略)
void DemonologyWarlockAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士AOE群体PVE策略)
void DemonologyWarlockAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士AOE群体PVP策略)
void DemonologyWarlockAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士AOE群体PVP策略)
void DemonologyWarlockAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士AOE群体团队副本策略)
void DemonologyWarlockAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士AOE群体团队副本策略)
void DemonologyWarlockAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockAoeStrategy::InitNonCombatTriggers(triggers);
    WarlockAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士增益Buff策略)
void DemonologyWarlockBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士增益Buff策略)
void DemonologyWarlockBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士增益BuffPVE策略)
void DemonologyWarlockBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士增益BuffPVE策略)
void DemonologyWarlockBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士增益BuffPVP策略)
void DemonologyWarlockBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士增益BuffPVP策略)
void DemonologyWarlockBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士增益Buff团队副本策略)
void DemonologyWarlockBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士增益Buff团队副本策略)
void DemonologyWarlockBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBuffStrategy::InitNonCombatTriggers(triggers);
    WarlockBuffRaidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "demonic sacrifice",
        NextAction::array(0, new NextAction("demonic sacrifice raid", ACTION_HIGH), NULL)));
}

// 初始化战斗阶段触发器列表 (恶魔学识术士爆发增益策略)
void DemonologyWarlockBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士爆发增益策略)
void DemonologyWarlockBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士爆发增益PVE策略)
void DemonologyWarlockBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士爆发增益PVE策略)
void DemonologyWarlockBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士爆发增益PVP策略)
void DemonologyWarlockBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士爆发增益PVP策略)
void DemonologyWarlockBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士爆发增益团队副本策略)
void DemonologyWarlockBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士爆发增益团队副本策略)
void DemonologyWarlockBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockBoostStrategy::InitNonCombatTriggers(triggers);
    WarlockBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士控制(CC)策略)
void DemonologyWarlockCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士控制(CC)策略)
void DemonologyWarlockCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士控制(CC)PVE策略)
void DemonologyWarlockCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士控制(CC)PVE策略)
void DemonologyWarlockCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士控制(CC)PVP策略)
void DemonologyWarlockCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士控制(CC)PVP策略)
void DemonologyWarlockCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士控制(CC)团队副本策略)
void DemonologyWarlockCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士控制(CC)团队副本策略)
void DemonologyWarlockCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCcStrategy::InitNonCombatTriggers(triggers);
    WarlockCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士宠物策略)
void DemonologyWarlockPetStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士宠物策略)
void DemonologyWarlockPetStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockPetStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士宠物PVE策略)
void DemonologyWarlockPetPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士宠物PVE策略)
void DemonologyWarlockPetPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon felguard", ACTION_NORMAL + 2), NULL)));
}

// 初始化战斗阶段触发器列表 (恶魔学识术士宠物PVP策略)
void DemonologyWarlockPetPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士宠物PVP策略)
void DemonologyWarlockPetPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon felguard", ACTION_NORMAL + 2), NULL)));
}

// 初始化战斗阶段触发器列表 (恶魔学识术士宠物团队副本策略)
void DemonologyWarlockPetRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockPetStrategy::InitCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恶魔学识术士宠物团队副本策略)
void DemonologyWarlockPetRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    /* NO PET BECAUSE OF DEMONIC SACRIFICE
    DemonologyWarlockPetStrategy::InitNonCombatTriggers(triggers);
    WarlockPetRaidStrategy::InitNonCombatTriggers(triggers);
    */
}

// 初始化战斗阶段触发器列表 (恶魔学识术士诅咒策略)
void DemonologyWarlockCursesStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarlockCursesStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士诅咒PVE策略)
void DemonologyWarlockCursesPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPveStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士诅咒PVP策略)
void DemonologyWarlockCursesPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恶魔学识术士诅咒团队副本策略)
void DemonologyWarlockCursesRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    DemonologyWarlockCursesStrategy::InitCombatTriggers(triggers);
    WarlockCursesRaidStrategy::InitCombatTriggers(triggers);
}

#endif
