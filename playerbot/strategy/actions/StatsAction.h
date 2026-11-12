#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 状态统计指令动作：汇报机器人的金币、背包空间、耐久度、经验速率等状态信息
    class StatsAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化状态统计指令动作
        StatsAction(PlayerbotAI* ai) : ChatCommandAction(ai, "stats") {}
        /// 执行动作主逻辑（状态统计指令动作）
        virtual bool Execute(Event& event) override;

        /// 判断在被昏迷或控制状态下是否仍可执行该动作（状态统计指令动作）
        bool isUsefulWhenStunned() override { return true; }
    private:
        /// 详细列出背包与银行各个槽位中存放的物品
        void ListBagSlots(std::ostringstream &out);
        /// 汇报当前等级经验值进度与预计升级时间
        void ListXP(std::ostringstream &out);
        /// 汇报当前全部装备的修理费用明细
        void ListRepairCost(std::ostringstream &out);
        /// 汇报机器人当前拥有的金币数量
        void ListGold(std::ostringstream &out);
        /// 汇报机器人当前装备评分或战斗力统计
        void ListPower(std::ostringstream& out);
        /// 估算修理全部受损装备所需的金币费用
        uint32 EstRepair(uint16 pos);
        /// 计算当前全身装备的剩余耐久度百分比
        double RepairPercent(uint16 pos);
    };
}
