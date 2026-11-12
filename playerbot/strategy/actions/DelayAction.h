#pragma once

#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/RandomPlayerbotMgr.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 延迟等待动作：按配置反应延迟暂停机器人行动以模拟真实玩家节奏
    class DelayAction : public Action
    {
    public:
        /// 构造函数：初始化延迟等待动作
        DelayAction(PlayerbotAI* ai) : Action(ai, "delay")
        {}

        /// 执行动作主逻辑（延迟等待动作）
        virtual bool Execute(Event& event) override
        {
            SetDuration(sPlayerbotAIConfig.passiveDelay + sPlayerbotAIConfig.globalCoolDown);
            return true;
        }

        /// 判断当前状态下该动作是否可用/有效（延迟等待动作）
        virtual bool isUseful() override
        {
            return !ai->AllowActivity(ALL_ACTIVITY);
        }
    };
}
