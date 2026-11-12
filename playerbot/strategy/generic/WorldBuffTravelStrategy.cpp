/// 世界增益自动旅行（World Buff Travel）策略实现
#include "playerbot/playerbot.h"
#include "WorldBuffTravelStrategy.h"
#include "playerbot/TravelMgr.h"

using namespace ai;

/// 乘数判定：世界增益旅行期间屏蔽常规旅行目标选择、RPG 与野外刷怪动作
float WorldBuffTravelMultiplier::GetValue(Action* action)
{
    if (!action)
        return 1.0f;

    std::string name = action->getName();

    if (name == "choose travel target" || name == "request travel target" ||
        name == "request named travel target" || name == "request quest travel target" ||
        name == "choose group travel target" || name == "refresh travel target" ||
        name == "reset travel target" ||
        name == "rpg" || name == "choose rpg target" ||
        name == "grind" || name == "attack anything")
    {
        return 0.0f;
    }

    return 1.0f;
}

/// 初始化非战斗乘数：挂载 WorldBuffTravelMultiplier
void WorldBuffTravelStrategy::InitNonCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    multipliers.push_back(new WorldBuffTravelMultiplier(ai));
}

/// 初始化非战斗触发器：驱动各节点到达判定、移动设置、厄运出本及法师开门步骤
void WorldBuffTravelStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "world buff travel zone reached",
        NextAction::array(0, new NextAction("world buff travel apply", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "world buff travel need move",
        NextAction::array(0, new NextAction("world buff travel set target", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "world buff travel dm buffed",
        NextAction::array(0, new NextAction("world buff travel dm buffed", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "world buff travel dm exited",
        NextAction::array(0, new NextAction("world buff travel dm exited", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "world buff travel dm portal cast",
        NextAction::array(0, new NextAction("world buff travel dm cast portal", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "world buff travel dm portal use",
        NextAction::array(0, new NextAction("world buff travel dm take portal", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "val::travel target traveling",
        NextAction::array(0, new NextAction("check mount state", 1), new NextAction("move to travel target", 3), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("travel", 3), NULL)));

    triggers.push_back(new TriggerNode(
        "world buff travel portal step",
        NextAction::array(0, new NextAction("world buff travel cast portal", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "world buff travel use portal",
        NextAction::array(0, new NextAction("world buff travel take portal", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "world buff travel done",
        NextAction::array(0, new NextAction("world buff travel finish", 20.0f), NULL)));
}

/// 启用策略时根据机器人当前缺少的 Buff 自动计算起始步骤
void WorldBuffTravelStrategy::OnStrategyAdded(BotState state)
{
    WorldBuffTravelStep startStep = GetFirstNeededStep(ai->GetBot());

    ai->GetAiObjectContext()->GetValue<uint8>("world buff travel step")->Set(
        static_cast<uint8>(startStep));
}

/// 移除策略时将旅行步骤置为完成状态
void WorldBuffTravelStrategy::OnStrategyRemoved(BotState state)
{
    ai->GetAiObjectContext()->GetValue<uint8>("world buff travel step")->Set(
        static_cast<uint8>(WorldBuffTravelStep::STEP_DONE));
}