/// 测试框架：Boss 焦点目标生命周期管理器头文件
#pragma once
#include "playerbot/PlayerbotAI.h"
#include "TestContext.h"
#include <ctime>

namespace ai
{
    /// 测试组件：管理测试过程中焦点怪物（Focus Mob）的查找、重生、拉怪及观测日志
    class BossFocusManager
    {
    public:
        BossFocusManager(Player* bot, PlayerbotAI* ai, TestContext& ctx)
            : bot(bot), ai(ai), ctx(ctx), lastFocusRespawnTime(0), lastObserveLogTime(0) {}

        /// 每帧更新焦点目标状态并触发重生或交战
        void Update();
        /// 重置管理器计时器状态
        void Reset() { lastFocusRespawnTime = 0; lastObserveLogTime = 0; }

    private:
        Creature* FindFocusMob();
        void RespawnFocusMob();
        void EngageFocusMob(Creature* focusMob);
        void LogObserveStatus();

        Player* bot;
        PlayerbotAI* ai;
        TestContext& ctx;
        uint32 lastFocusRespawnTime;
        uint32 lastObserveLogTime;
    };
}
