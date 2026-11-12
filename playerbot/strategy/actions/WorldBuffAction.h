#pragma once

#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 世界增益施加动作：为机器人或玩家施加预设的世界级强力增益效果
    class WorldBuffAction : public Action {
    public:
        /// 构造函数：初始化世界增益施加动作
        WorldBuffAction(PlayerbotAI* ai) : Action(ai, "world buff") {}
        /// 执行动作主逻辑（世界增益施加动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（世界增益施加动作）
        virtual bool isUsefulWhenStunned() override { return true; }
        /// 判断机器人当前是否仍缺少并需要收集世界增益
        static std::vector<uint32> NeedWorldBuffs(Unit* unit);
        //static bool AddAura(Unit* unit, uint32 spellId);
    private:
    };

}
