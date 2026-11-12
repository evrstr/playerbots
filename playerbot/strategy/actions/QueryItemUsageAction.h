#pragma once
#include "GenericActions.h"

namespace ai
{
    class ItemQualifier;

    /// 查询物品用途动作：分析并汇报某件物品对当前机器人的用途（装备/任务/配方/材料）
    class QueryItemUsageAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化查询物品用途动作
        QueryItemUsageAction(PlayerbotAI* ai, std::string name = "query item usage") : ChatCommandAction(ai, name) {}
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（查询物品用途动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    protected:
        /// 执行动作主逻辑（查询物品用途动作）
        virtual bool Execute(Event& event) override;
        /// 统计符合条件的目标或物品数量
        uint32 GetCount(ItemQualifier& qualifier);
        /// 查询指定物品的基本属性与背包持有情况
        std::string QueryItem(ItemQualifier& qualifier, uint32 count, uint32 total, bool reason = false);
        /// 分析并输出物品对当前机器人的综合用途评估
        std::string QueryItemUsage(ItemQualifier& qualifier, bool reason = false);
        /// 查询物品的商人收购价、购买价或拍卖行估值
        std::string QueryItemPrice(ItemQualifier& qualifier);
        /// 查询任务相关物品在任务目标中的需求与用途
        std::string QueryQuestItem(uint32 itemId, const Quest *questTemplate, const QuestStatusData *questStatus);
        /// 查询任务相关物品在任务目标中的需求与用途
        std::string QueryQuestItem(uint32 itemId);
        /// 计算并对比物品的装等评分与属性提升幅度
        std::string QueryItemPower(ItemQualifier& qualifier);

    private:
        std::ostringstream out;
    };
}
