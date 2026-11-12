#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 查询任务指令动作：查看并汇报任务目标进度或指定任务详情
    class QueryQuestAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化查询任务指令动作
        QueryQuestAction(PlayerbotAI* ai) : ChatCommandAction(ai, "query quest") {}

    private:
        /// 执行动作主逻辑（查询任务指令动作）
        bool Execute(Event& event) override;
        /// 输出任务全部目标的详细进度清单
        void TellObjectives(Player* requester, uint32 questId);
        /// 输出单个任务目标或战术目标的完成进度
        void TellObjective(Player* requester, const std::string& name, int available, int required);
    };
}
