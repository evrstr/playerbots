
#include "playerbot/playerbot.h"
#include "playerbot/RandomPlayerbotMgr.h"
#include "SecurityCheckAction.h"

using namespace ai;

/// 判断当前状态下该动作是否可用/有效（安全权限校验动作）
bool SecurityCheckAction::isUseful()
{
    return sRandomPlayerbotMgr.IsRandomBot(bot) && ai->GetMaster() && ai->GetMaster()->GetSession()->GetSecurity() < SEC_GAMEMASTER && !ai->GetMaster()->GetPlayerbotAI();
}

/// 执行动作主逻辑（安全权限校验动作）
bool SecurityCheckAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    Group* group = bot->GetGroup();
    if (group)
    {
        LootMethod method = group->GetLootMethod();
        ItemQualities threshold = group->GetLootThreshold();
        if (method == MASTER_LOOT || method == FREE_FOR_ALL || threshold > ITEM_QUALITY_UNCOMMON)
        {
            if ((ai->GetGroupMaster()->GetSession()->GetSecurity() == SEC_PLAYER) && (!bot->GetGuildId() || bot->GetGuildId() != ai->GetGroupMaster()->GetGuildId()))
            {
                ai->TellError(requester, "I will play with this loot type only if I'm in your guild :/");
                ai->ChangeStrategy("+passive,+stay", BotState::BOT_STATE_NON_COMBAT);
                ai->ChangeStrategy("+passive,+stay", BotState::BOT_STATE_COMBAT);
            }
            return true;
        }
    }
    return false;
}
