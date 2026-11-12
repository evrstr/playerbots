/// 角色日常维护（Maintenance）策略实现

#include "playerbot/playerbot.h"
#include "MaintenanceStrategy.h"

using namespace ai;

/// 初始化非战斗触发器：清理任务日志、学习配方、开箱拆解附魔、清包及脱困
void MaintenanceStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("clean quest log", 6.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("use random recipe", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("open random item", 0.9f), NULL)));

    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("disenchant random item", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("enchant random item", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("smart destroy item", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "move stuck",
        NextAction::array(0, new NextAction("unstuck", 0.7f), NULL)));

    triggers.push_back(new TriggerNode(
        "move long stuck",
        NextAction::array(0, new NextAction("unstuck", 0.9f), NULL)));

    triggers.push_back(new TriggerNode(
        "movement loop stuck",
        NextAction::array(0, new NextAction("release stuck movement", 101.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("use random quest item", 0.9f), NULL)));

    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("auto share quest", 0.9f), NULL)));

    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("auto complete quest", 1.0f), NULL)));
}
