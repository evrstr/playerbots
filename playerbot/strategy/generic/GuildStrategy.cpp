/// 公会社交与自动管理策略实现
#include "playerbot/playerbot.h"
#include "GuildStrategy.h"

using namespace ai;

/// 初始化非战斗触发器：递交签名表、购买战袍、退出超大公会、公会银行及制造/任务订单
void GuildStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("offer petition nearby", 4.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("guild manage nearby", 4.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "petition signed",
        NextAction::array(0, new NextAction("turn in petition", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "buy tabard",
        NextAction::array(0, new NextAction("buy tabard", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "leave large guild",
        NextAction::array(0, new NextAction("guild leave", 4.0f), NULL)));

#ifndef MANGOSBOT_ZERO
    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("buy guild bank tab", 4.0f), NULL)));
#endif

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("guild craft order", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("guild share item", 9.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("guild ah buy", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("guild accept quest order", 11.0f), NULL)));
}
