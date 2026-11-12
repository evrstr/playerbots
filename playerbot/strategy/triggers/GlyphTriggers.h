/// 雕文应用触发器定义
#pragma once

#include "playerbot/playerbot.h"
#include "playerbot/strategy/Trigger.h"
#include "playerbot/strategy/triggers/GenericTriggers.h"

namespace ai
{
    /// 触发器：15级及以上机器人随机触发检查并镶嵌雕文
    class ApplyGlyphTrigger : public RandomTrigger
    {
    public:
        ApplyGlyphTrigger(PlayerbotAI* ai, std::string triggerName = "apply glyphs") : RandomTrigger(ai, triggerName, 60) {}
        virtual bool IsActive() override
        {
            if (bot->GetLevel() < 15)
                return false;

            return RandomTrigger::IsActive();
        }
    };   
}