#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 在线查询指令动作：模拟 /who 查询并汇报机器人所在区域、等级与职业信息
    class WhoAction : public ChatCommandAction 
    {
    public:
        /// 构造函数：初始化在线查询指令动作
        WhoAction(PlayerbotAI* ai) : ChatCommandAction(ai, "who") {}
        /// 执行动作主逻辑（在线查询指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（在线查询指令动作）
        bool isUsefulWhenStunned() override { return true; }
    private:
        /// 查询当前交易请求或目标的可交易状态
        std::string QueryTrade(std::string text);
        /// 查询并输出机器人已学习的专业与武器技能等级
        std::string QuerySkill(std::string text);
        /// 查询并汇报机器人当前的天赋专精分配情况
        std::string QuerySpec(std::string text);
    };
}
