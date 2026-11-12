/// 卡拉赞（Karazhan）团队副本及各首领机制策略实现

#include "playerbot/playerbot.h"
#include "KarazhanDungeonStrategies.h"
#include "DungeonMultipliers.h"

using namespace ai;

/// 初始化卡拉赞副本触发器：根据交战 Boss 自动切换对应首领专项策略
void KarazhanDungeonStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "start netherspite fight",
        NextAction::array(0, new NextAction("enable netherspite fight strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "start shade of aran fight",
        NextAction::array(0, new NextAction("enable shade of aran fight strategy", 100.0f), NULL)));

triggers.push_back(new TriggerNode(
        "start big bad wolf fight",
        NextAction::array(0, new NextAction("enable big bad wolf fight strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "start prince malchezaar fight",
        NextAction::array(0, new NextAction("enable prince malchezaar fight strategy", 100.0f), NULL)));
}

/// 初始化虚空幽龙战斗触发器：躲避虚空地带与团队轮流挡线机制处理
void NetherspiteFightStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "void zone too close",
        NextAction::array(0, new NextAction("move away from void zone", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "add nether portal - perseverence for tank",
        NextAction::array(0, new NextAction("add nether portal - perseverence for tank", 101.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "remove nether portal buffs from netherspite",
        NextAction::array(0, new NextAction("remove nether portal buffs from netherspite", 101.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "remove nether portal - perseverence",
        NextAction::array(0, new NextAction("remove nether portal - perseverence", 101.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "remove nether portal - serenity",
        NextAction::array(0, new NextAction("remove nether portal - serenity", 101.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "remove nether portal - dominance",
        NextAction::array(0, new NextAction("remove nether portal - dominance", 101.0f), NULL)));
}

/// 初始化虚空幽龙非战斗触发器：脱战后卸载策略
void NetherspiteFightStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end netherspite fight",
        NextAction::array(0, new NextAction("disable netherspite fight strategy", 100.0f), NULL)));
}

/// 初始化虚空幽龙死亡触发器
void NetherspiteFightStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end netherspite fight",
        NextAction::array(0, new NextAction("disable netherspite fight strategy", 100.0f), NULL)));
}

/// 启用虚空幽龙策略时查找并缓存 Boss GUID
void NetherspiteFightStrategy::OnStrategyAdded(BotState state)
{
    if (!Get(ai)->GetBossGuid())
    {
        // Find Netherspite and store him | 查找虚空幽龙（15689）并记录 GUID
        std::list<Unit*> creatures;
        MaNGOS::AllCreaturesOfEntryInRangeCheck u_check(ai->GetBot(), 15689, 100);
        MaNGOS::UnitListSearcher<MaNGOS::AllCreaturesOfEntryInRangeCheck> searcher(creatures, u_check);
        Cell::VisitAllObjects(ai->GetBot(), searcher, 100);

        if (creatures.empty())
            return;

        Unit* target = creatures.front();

        NetherspiteFightStrategy* strategy = NetherspiteFightStrategy::Get(ai);
        if (strategy)
        {
            if (target && target->GetEntry() == 15689)
            {
                strategy->SetBossGuid(target->GetObjectGuid());
            }
        }
    }
}

/// 获取机器人当前的虚空幽龙战斗策略实例
NetherspiteFightStrategy* NetherspiteFightStrategy::Get(PlayerbotAI* ai)
{
    return ai ? ai->GetStrategy<NetherspiteFightStrategy>("netherspite", BotState::BOT_STATE_COMBAT) : nullptr;
}

/// 初始化埃兰之影战斗触发器：烈焰花环、魔爆术与召唤水元素阶段切换
void ShadeOfAranFightStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "shade of aran casting flame wreath",
        NextAction::array(0, new NextAction("start aran fire phase", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "shade of aran casting arcane explosion",
        NextAction::array(0, new NextAction("start aran arcane phase", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "shade of aran elementals out",
        NextAction::array(0, new NextAction("start aran elementals", 100.0f), NULL)));
}

/// 初始化埃兰之影非战斗触发器：脱战后卸载策略
void ShadeOfAranFightStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end shade of aran fight",
        NextAction::array(0, new NextAction("disable shade of aran fight strategy", 100.0f), NULL)));
}

/// 初始化埃兰之影死亡触发器
void ShadeOfAranFightStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end shade of aran fight",
        NextAction::array(0, new NextAction("disable shade of aran fight strategy", 100.0f), NULL)));
}

/// 初始化埃兰之影反应触发器：暴风雪躲避与魔爆术跑开/结束复位
void ShadeOfAranFightStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "shade of aran casting blizzard",
        NextAction::array(0, new NextAction("start aran frost phase", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "shade of aran done casting arcane explosion",
        NextAction::array(0, new NextAction("end aran arcane phase", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "shade of aran casting arcane explosion",
        NextAction::array(0, new NextAction("move away from shade of aran", 100.0f), NULL)));
}

/// 获取机器人当前的埃兰之影战斗策略实例
ShadeOfAranFightStrategy* ShadeOfAranFightStrategy::Get(PlayerbotAI* ai)
{
    return ai ? ai->GetStrategy<ShadeOfAranFightStrategy>("shade of aran", BotState::BOT_STATE_COMBAT) : nullptr;
}

/// 启用埃兰之影策略时缓存 Boss GUID 并初始化阶段与逃跑距离参数
void ShadeOfAranFightStrategy::OnStrategyAdded(BotState state)
{
    if (!Get(ai)->GetBossGuid())
    {
        // Find Shade of aran and store him | 查找埃兰之影（16524）并记录 GUID
        std::list<Unit*> creatures;
        MaNGOS::AllCreaturesOfEntryInRangeCheck u_check(ai->GetBot(), 16524, 100);
        MaNGOS::UnitListSearcher<MaNGOS::AllCreaturesOfEntryInRangeCheck> searcher(creatures, u_check);
        Cell::VisitAllObjects(ai->GetBot(), searcher, 100);

        if (creatures.empty())
            return;

        Unit* target = creatures.front();

        ShadeOfAranFightStrategy* strategy = ShadeOfAranFightStrategy::Get(ai);
        if (strategy)
        {
            if (target && target->GetEntry() == 16524)
            {
                strategy->SetBossGuid(target->GetObjectGuid());
                // fight starts with unknown phase | 战斗开始时初始化为未知阶段
                strategy->SetPhase(AranPhase::PHASE_NONE);
                strategy->SetRangedBot(ai->IsRanged(ai->GetBot()));
                if (target->GetHealthPercent() <= 40.0f && !strategy->GetElementals())
                    strategy->SetElementals(true);
                else
                    strategy->SetElementals(false);
                if (ai->GetRange("flee") < 5.0f)
                    ai->GetAiObjectContext()->GetValue<float>("range", "flee")->Set(20.0f);
                
            }
        }
    }
}

/// 初始化大灰狼战斗触发器：被点名变小红帽时远离大灰狼风筝
void BigBadWolfFightStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "big bad wolf too close",
        NextAction::array(0, new NextAction("move away from big bad wolf", 100.0f), NULL)));
}

/// 初始化大灰狼非战斗触发器：脱战后卸载策略
void BigBadWolfFightStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end big bad wolf fight",
        NextAction::array(0, new NextAction("disable big bad wolf fight strategy", 100.0f), NULL)));
}

/// 初始化大灰狼死亡触发器
void BigBadWolfFightStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end big bad wolf fight",
        NextAction::array(0, new NextAction("disable big bad wolf fight strategy", 100.0f), NULL)));
}

/// 初始化玛克扎尔王子战斗触发器：远离地狱火
void PrinceMalchezaarFightStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "netherspite infernal too close",
        NextAction::array(0, new NextAction("move away from netherspite infernal", 100.0f), NULL)));
}

/// 初始化玛克扎尔王子非战斗触发器：脱战后卸载策略
void PrinceMalchezaarFightStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end prince malchezaar fight",
        NextAction::array(0, new NextAction("disable prince malchezaar fight strategy", 100.0f), NULL)));
}

/// 初始化玛克扎尔王子死亡触发器
void PrinceMalchezaarFightStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "end prince malchezaar fight",
        NextAction::array(0, new NextAction("disable prince malchezaar fight strategy", 100.0f), NULL)));
}

/// 初始化玛克扎尔王子反应触发器：虚弱或暗影新星阶段立即远离 Boss
void PrinceMalchezaarFightStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "prince malchezaar too close",
        NextAction::array(0, new NextAction("move away from prince malchezaar", 100.0f), NULL)));
}
