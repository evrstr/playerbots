#pragma once

#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 经验获取处理动作：监听击杀或任务获得的经验值变化并触发升级/统计播报
    class XpGainAction : public Action
    {
    public:
        /// 构造函数：初始化经验获取处理动作
        XpGainAction(PlayerbotAI* ai) : Action(ai, "xp gain") {}
        /// 执行动作主逻辑（经验获取处理动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（经验获取处理动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    private:
        /// 处理经验获取事件并计算经验速率
        void GiveXP(int32 xp, Unit* victim);
    };
}
