/// RPG 城镇拟真交互总控及各子模块策略实现

#include "playerbot/playerbot.h"
#include "RpgStrategy.h"
#include "playerbot/strategy/actions/RpgSubActions.h"

using namespace ai;

/// 乘数判定：强制执行 AI 选定的下一个 RPG 子动作，对非目标动作大幅降权
float RpgActionMultiplier::GetValue(Action* action)
{
    if (action == NULL) return 1.0f;

    std::string nextAction = AI_VALUE(std::string, "next rpg action");
    std::string name = action->getName();

    if (dynamic_cast<RpgEnabled*>(action))
    {
        if (!nextAction.empty() && name != nextAction)
            return 0.1f;
        else if(nextAction.empty() && name == "rpg cancel")
            return 0.1f;
        else
            return 1.0f - (0.1f * urand(0, 2));
    }

    return 1.0f;
}

/// 启用 RPG 总策略时联动加载任务、商人、探索、维护、玩家、战场、公会与银行子策略
void RpgStrategy::OnStrategyAdded(BotState state)
{
    ai->ChangeStrategy("+rpg quest,+rpg vendor,+rpg explore,+rpg maintenance,+rpg player,+rpg bg,+rpg guild,+rpg bank", state);
}
/// 关闭 RPG 总策略时联动卸载上述全部子策略
void RpgStrategy::OnStrategyRemoved(BotState state) 
{
    ai->ChangeStrategy("-rpg quest,-rpg vendor,-rpg explore,-rpg maintenance,-rpg player,-rpg bg,-rpg guild,-rpg bank", state);
}

/// 初始化 RPG 主策略非战斗触发器：寻敌移动、原地发呆、工作、表情、治疗友方及 LLM 闲聊
void RpgStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "no rpg target",
        NextAction::array(0, new NextAction("choose rpg target", 5.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "far from rpg target",
        NextAction::array(0, new NextAction("move to rpg target", 5.0f), NULL)));

    //triggers.push_back(new TriggerNode(
    //    "near rpg target",
    //    NextAction::array(0, new NextAction("rpg", 1.1f), NULL)));

    //Sub actions | RPG 子动作调度
    triggers.push_back(new TriggerNode(
        "rpg wander",
        NextAction::array(0, new NextAction("rpg cancel", 1.001f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg",
        NextAction::array(0, new NextAction("rpg stay", 1.001f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg",
        NextAction::array(0, new NextAction("rpg work", 1.001f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg",
        NextAction::array(0, new NextAction("rpg emote", 1.001f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg",
        NextAction::array(0, new NextAction("rpg cancel", 1.001f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg heal",
        NextAction::array(0, new NextAction("rpg heal", 1.025f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg use",
        NextAction::array(0, new NextAction("rpg use", 1.001f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg ai chat",
        NextAction::array(0, new NextAction("rpg ai chat", 1.003f), NULL)));   
}

/// 注册 RPG 动作序列化乘数
void RpgStrategy::InitNonCombatMultipliers(std::list<Multiplier*>& multipliers)
{
    multipliers.push_back(new RpgActionMultiplier(ai));
}

/// 初始化 RPG 任务子策略：接任务、交任务、重复任务、法术点击与任务物品交互
void RpgQuestStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "rpg start quest",
        NextAction::array(0, new NextAction("rpg start quest", 1.080f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg end quest",
        NextAction::array(0, new NextAction("rpg end quest", 1.090f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg repeat quest",
        NextAction::array(0, new NextAction("rpg start quest", 1.030f), new NextAction("rpg end quest", 1.030f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg spell click",
        NextAction::array(0, new NextAction("rpg spell click", 1.003f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg gossip talk",
        NextAction::array(0, new NextAction("rpg gossip talk", 1.003f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg quest use",
        NextAction::array(0, new NextAction("rpg use", 1.003f), NULL)));
}

/// 初始化 RPG 商人子策略：买卖物品、拍卖行买卖与收发邮件
void RpgVendorStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "rpg buy",
        NextAction::array(0, new NextAction("rpg buy", 1.030f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg ah sell",
        NextAction::array(0, new NextAction("rpg ah sell", 1.110f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg ah buy",
        NextAction::array(0, new NextAction("rpg ah buy", 1.035f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg get mail",
        NextAction::array(0, new NextAction("rpg get mail", 1.070f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg sell",
        NextAction::array(0, new NextAction("rpg sell", 1.100f), NULL)));
}

/// 初始化 RPG 探索子策略：搭乘飞行航线、解锁鸟点与绑定炉石
void RpgExploreStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "rpg taxi",
        NextAction::array(0, new NextAction("rpg taxi", 1.005f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg discover",
        NextAction::array(0, new NextAction("rpg discover", 1.110f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg home bind",
        NextAction::array(0, new NextAction("rpg home bind", 1.060f), NULL)));
}

/// 初始化 RPG 维护子策略：找商贩修装备与找训练师学技能
void RpgMaintenanceStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "rpg repair",
        NextAction::array(0, new NextAction("rpg repair", 1.095f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg train",
        NextAction::array(0, new NextAction("rpg train", 1.080f), NULL)));
}

/// 初始化 RPG 公会子策略：购买公会签名表与公会银行存取
void RpgGuildStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "rpg buy petition",
        NextAction::array(0, new NextAction("rpg buy petition", 1.040f), NULL)));

#ifndef MANGOSBOT_ZERO
    triggers.push_back(new TriggerNode(
        "rpg guild bank deposit",
        NextAction::array(0, new NextAction("rpg guild bank deposit", 1.050f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg guild bank withdraw",
        NextAction::array(0, new NextAction("rpg guild bank withdraw", 1.045f), NULL)));
#endif
}

/// 初始化 RPG 银行子策略：个人银行物品存取
void RpgBankStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "rpg bank deposit",
        NextAction::array(0, new NextAction("rpg bank deposit", 1.080f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg bank withdraw",
        NextAction::array(0, new NextAction("rpg bank withdraw", 1.075f), NULL)));
}

/// 初始化 RPG 战场子策略：与军官排队加入战场
void RpgBgStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "rpg queue bg",
        NextAction::array(0, new NextAction("rpg queue bg", 1.085f), NULL)));
}

/// 初始化 RPG 玩家互动子策略：交易有用装备、附魔与发起决斗
void RpgPlayerStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "rpg trade useful",
        NextAction::array(0, new NextAction("rpg trade useful", 1.030f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg enchant",
        NextAction::array(0, new NextAction("rpg enchant", 1.029f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg duel",
        NextAction::array(0, new NextAction("rpg duel", 1.010f), NULL)));
}

/// 初始化 RPG 制造子策略：制造商业技能物品与闲暇施放娱乐法术
void RpgCraftStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "rpg spell",
        NextAction::array(0, new NextAction("rpg spell", 1.001f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg craft",
        NextAction::array(0, new NextAction("rpg craft", ai->HasCheat(BotCheatMask::item) ? 1.001f : 1.010f), NULL)));

    triggers.push_back(new TriggerNode(
        "rpg item",
        NextAction::array(0, new NextAction("rpg item", 1.003f), NULL)));
}

/// 初始化 RPG 随机跳跃非战斗触发器
void RpgJumpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "random jump",
        NextAction::array(0, new NextAction("jump::random", ACTION_PASSTROUGH), NULL)));
}

/// 初始化 RPG 随机跳跃战斗触发器
void RpgJumpStrategy::InitCombatTriggers(std::list<TriggerNode *> &triggers)
{
    InitNonCombatTriggers(triggers);
}

/// 初始化 RPG 随机跳跃反应触发器
void RpgJumpStrategy::InitReactionTriggers(std::list<TriggerNode *> &triggers)
{
    InitNonCombatTriggers(triggers);
}
