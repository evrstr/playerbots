
#include "playerbot/strategy/Action.h"
#include "playerbot/strategy/values/GuildValues.h"

namespace ai
{
    /// 公会共享拍卖购入动作：查找并从拍卖行购入公会成员需要或高性价比的物品
    class GuildShareAhBuyAction : public Action
    {
    public:
        /// 构造函数：初始化公会共享拍卖购入动作
        GuildShareAhBuyAction(PlayerbotAI* ai) : Action(ai, "guild ah buy") {}

        /// 执行动作主逻辑（公会共享拍卖购入动作）
        bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（公会共享拍卖购入动作）
        bool isUseful() override;

    private:
        /// 查找距离机器人最近的拍卖师单位
        Unit* FindNearbyAuctioneer();
        std::map<uint32, uint32> GetNeededItems();
        /// 判断机器人是否已学会并有材料制作指定物品
        bool CanBotCraftItem(uint32 itemId);
        /// 判断指定材料是否可用于机器人当前专业制造
        bool CanBotUseReagent(ItemPrototype const* reagentProto);
        /// 统计机器人邮箱中的邮件或附件物品总数
        uint32 CountMailboxItems(uint32 itemId);
    };
}
