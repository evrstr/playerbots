#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 增益法术指令动作：手动触发机器人施放或切换增益法术策略
    class BuffAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化增益法术指令动作
        BuffAction(PlayerbotAI* ai) : ChatCommandAction(ai, "buff") {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "buff"; }
        virtual std::string GetHelpDescription()
        {
            return "This command list the items that provide some kind of buff when used\n"
                   "Included are things like flags, scrolls and food.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
        /// 执行动作主逻辑（增益法术指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（增益法术指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        /// 输出列表汇报的头部标题信息
        void TellHeader(uint32 subClass, Player* requester);
    };
}
