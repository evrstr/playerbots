/// 副本策略自动启停调度器实现

#include "playerbot/playerbot.h"
#include "DungeonStrategy.h"

using namespace ai;

/// 初始化战斗触发器：若机器人直接被拉进副本开战，也能自动激活对应副本专属策略
void DungeonStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    // Add this combat triggers in case the bot gets summoned into the dungeon and goes straight into combat | 在战斗中同样注册进入副本触发器，防止被直接召唤进副本开怪时漏掉策略加载
    triggers.push_back(new TriggerNode(
        "enter onyxias lair",
        NextAction::array(0, new NextAction("enable onyxias lair strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enter molten core",
        NextAction::array(0, new NextAction("enable molten core strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enter blackwing lair",
        NextAction::array(0, new NextAction("enable blackwing lair strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enter karazhan",
        NextAction::array(0, new NextAction("enable karazhan strategy", 100.0f), NULL)));
    
    triggers.push_back(new TriggerNode(
        "enter mechanar",
        NextAction::array(0, new NextAction("enable mechanar strategy", 100.0f), NULL)));
}

/// 初始化非战斗触发器：随进出奥妮克希亚/MC/BWL/卡拉赞/能源舰自动启停对应策略
void DungeonStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "enter onyxias lair",
        NextAction::array(0, new NextAction("enable onyxias lair strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "leave onyxias lair",
        NextAction::array(0, new NextAction("disable onyxias lair strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enter molten core",
        NextAction::array(0, new NextAction("enable molten core strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "leave molten core",
        NextAction::array(0, new NextAction("disable molten core strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enter blackwing lair",
        NextAction::array(0, new NextAction("enable blackwing lair strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "leave blackwing lair",
        NextAction::array(0, new NextAction("disable blackwing lair strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enter karazhan",
        NextAction::array(0, new NextAction("enable karazhan strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "leave karazhan",
        NextAction::array(0, new NextAction("disable karazhan strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enter mechanar",
        NextAction::array(0, new NextAction("enable mechanar strategy", 100.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "leave mechanar",
        NextAction::array(0, new NextAction("disable mechanar strategy", 100.0f), NULL)));
}