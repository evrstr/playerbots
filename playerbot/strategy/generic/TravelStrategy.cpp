/// 大世界智能旅行（Travel）策略与乘数实现

#include "playerbot/playerbot.h"
#include "TravelStrategy.h"
#include "playerbot/TravelMgr.h"

using namespace ai;

/// 乘数判定：已有激活旅行目标时屏蔽大部分新的目标请求，仅放行公会聚会/施法材料商/公会订单
float TravelActionMultiplier::GetValue(Action* action)
{
    if (action == NULL) return 1.0f;

    bool hasTarget = AI_VALUE(bool, "travel target active");
    std::string name = action->getName();

    if (hasTarget && name.find("request") == 0)
    {
        if (name.find("guild meeting") != std::string::npos)
            return 1.0f;
        if (name.find("reagent vendor") != std::string::npos)
            return 1.0f;
        if (name.find("guild order") != std::string::npos)
            return 1.0f;

        return 0.0f;
    }

    return 1.0f;
}

/// 初始化旅行非战斗乘数
void TravelStrategy::InitNonCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    multipliers.push_back(new TravelActionMultiplier(ai));
}

/// 获取非战斗默认动作：执行旅行状态推进
NextAction** TravelStrategy::GetDefaultNonCombatActions()
{
    return NextAction::array(0, new NextAction("travel", 1.0f), NULL);
}

/// 初始化旅行非战斗触发器：按优先级队列依次请求各目的旅行点、选择目标并赶路
void TravelStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    //The way these actions work: | 动作调度流程：
    //One of these request target actions will trigger and start fetching destinations. | 先触发请求目标动作异步/检索目的地；检索期间仅选择目标动作可用；
    //While fetching no other travel action will be usefull except choose travel target. | 若未找到目标则标记跳过并顺延至下一个请求动作；全部失败则重置从头开始。
    //Choose travel target will wait for the fetching to complete and then set a new target.
    //If no target was found the request action is marked as no targets found and can no longer trigger until reset.
    //The next request action will then trigger until a good target is found.
    //If no targets are found reset will clear all actions and start from the top.

    //All the standard choose travel target actions using either a specific val trigger or a generic purpose trigger. | 按旅行目的枚举组织的常规旅行目标请求表
    const std::vector<std::tuple<std::string, TravelDestinationPurpose, float>> PurposeActions =
    {        
        {"",TravelDestinationPurpose::AH, 6.95f},                                                //See isAllowed  90%
        {"",TravelDestinationPurpose::Vendor, 6.94f},                                                          // 90%
        {"",TravelDestinationPurpose::Repair, 6.93f},                                                          // 90%
        {"val::and::{should get money,can get mail,should get mail}", TravelDestinationPurpose::Mail, 6.79f},  //100%
        {"val::or::{should bank deposit,should bank withdraw}", TravelDestinationPurpose::Bank, 6.78f},    //100%
        {"val::should get money", TravelDestinationPurpose::Grind, 6.77f},                                     // 90%
        {"",TravelDestinationPurpose::Mail, 6.6f},                                                             // 30%
        {"",TravelDestinationPurpose::GatherMining, 6.5f},                                                     // 90%/40% in group
        {"",TravelDestinationPurpose::GatherSkinning, 6.5f},                                                   // 90%/40% in group
        {"",TravelDestinationPurpose::GatherHerbalism, 6.5f},                                                  // 90%/40% in group
        {"",TravelDestinationPurpose::GatherFishing, 6.5f},                                                    // 90%/40% in group
        {"",TravelDestinationPurpose::Boss, 6.4f},                                                             // 50%
        {"",TravelDestinationPurpose::Explore, 6.29f},                                                         // 10%
        {"",TravelDestinationPurpose::GenericRpg, 6.28f},                                                      // 50%
        {"",TravelDestinationPurpose::Grind, 6.27f},                                                           // 100%
    };

    for (auto& [condition, purpose, relevance] : PurposeActions)
    {
        std::string trigger = condition.empty() ? "val::need travel purpose::" + std::to_string((uint32)purpose) : condition;
        triggers.push_back(new TriggerNode(
            trigger,
            NextAction::array(0, new NextAction("request travel target::" + std::to_string((uint32)purpose), relevance), NULL)));
    }

    //Specific named exceptions | 特定命名旅行目标（职业/骑术/商业训练师、主城、任务、公会活动等）
    const std::vector<std::tuple<std::string, std::string, float>> StringActions =
    {
        {"val::should travel named::trainer class","request named travel target::trainer class", 6.89f},      // See isAllowed   25%
        //{"val::should travel named::trainer pet","request named travel target::trainer pet", 6.88f},        // 25%
        {"val::should travel named::trainer mount","request named travel target::trainer mount", 6.87f},      // 25%
        {"val::should travel named::mount","request named travel target::mount", 6.86f},                      // 25%
        {"val::should travel named::city","request named travel target::city", 6.85f},                        // 10%
        {"val::and::{has strategy::rpg quest,has focus travel target}","request quest travel target", 6.84f}, //100%
        {"val::should travel named::pvp","request named travel target::pvp", 6.83f},                          // 25%
        {"val::should travel named::guild meeting","request named travel target::guild meeting", 6.96f},      //100%
        {"val::should travel named::reagent vendor","request named travel target::reagent vendor", 6.955f},   //100%
        {"val::should travel named::guild order","request named travel target::guild order", 6.95f},          //100%
        {"val::and::{has strategy::rpg quest,should get money}", "request quest travel target", 6.78f},       // 90%
        {"val::not::travel target active","refresh travel target", 6.7f},                                     // 90%
        {"val::not::travel target active","choose group travel target", 6.65f},                               // 50%
        {"val::should travel named::trainer trade","request named travel target::trainer trade", 6.51f},      // 25%
        {"val::has strategy::rpg quest", "request quest travel target", 6.3f}                                 // 95%
    };

    for (auto& [trigger, action, relevance] : StringActions)
    {
        triggers.push_back(new TriggerNode(
            trigger,
            NextAction::array(0, new NextAction(action, relevance), NULL)));
    }

    triggers.push_back(new TriggerNode(
        "val::not::travel target active",
        NextAction::array(0, new NextAction("choose travel target", 6.98f), NULL)));

    triggers.push_back(new TriggerNode(
        "val::not::travel target active",
        NextAction::array(0, new NextAction("reset travel target", 6.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "has nearby quest taker",
        NextAction::array(0, new NextAction("reset travel target", 6.99f), NULL)));

    triggers.push_back(new TriggerNode(
        "val::travel target ready",
        NextAction::array(0, new NextAction("check mount state", 1), new NextAction("move to travel target", 1), NULL)));

    triggers.push_back(new TriggerNode(
        "val::travel target traveling",
        NextAction::array(0, new NextAction("check mount state", 1), new NextAction("move to travel target", 1), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("travel", 1), NULL)));
}

/// 初始化单次旅行策略触发器：仅沿既定旅行目标移动一次
void TravelOnceStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{   
    triggers.push_back(new TriggerNode(
        "val::travel target traveling",
        NextAction::array(0, new NextAction("check mount state", 1), new NextAction("move to travel target", 1), NULL)));
}