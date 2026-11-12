
#include "playerbot/strategy/Action.h"
#include "playerbot/strategy/values/GuildValues.h"

namespace ai
{
    // Accepts the specific quest from a guild QuestReward order when near a quest giver. (在任务发布者附近时，接受来自公会任务奖励委托的指定任务。)
    class GuildAcceptQuestOrderAction : public Action
    {
    public:
        /// 构造函数：初始化接受公会任务委托动作
        GuildAcceptQuestOrderAction(PlayerbotAI* ai) : Action(ai, "guild accept quest order") {}

        /// 执行动作主逻辑（接受公会任务委托动作）
        bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（接受公会任务委托动作）
        bool isUseful() override;
    };
}
