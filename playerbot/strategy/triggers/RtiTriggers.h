/// 团队目标标记（RTI）触发器定义
#pragma once
#include "playerbot/strategy/Trigger.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/strategy/values/RtiTargetValue.h"

namespace ai
{
    /// 触发器：当前不存在有效的主攻团队标记目标（或默认骷髅标记）
    class NoRtiTrigger : public Trigger
    {
    public:
        NoRtiTrigger(PlayerbotAI* ai) : Trigger(ai, "no rti target") {}

        virtual bool IsActive() override
        {
            if (ai->GetUnit(AI_VALUE(ObjectGuid, "rti target")))
            {
                return false;
            }
            else
            {
                // Check for the default rti if the bot is setup to ignore rti targets | 若机器人配置为忽略团队标记，则检查默认的骷髅标记
                std::string rti = AI_VALUE(std::string, "rti");
                if (rti == "none")
                {
                    Group* group = bot->GetGroup();
                    if (group)
                    {
                        const ObjectGuid guid = group->GetTargetIcon(RtiTargetValue::GetRtiIndex("skull"));
                        if (!guid.IsEmpty())
                        {
                            Unit* unit = ai->GetUnit(ObjectGuid(guid));
                            if (unit && !sServerFacade.UnitIsDead(unit) && bot->IsWithinDistInMap(unit, sPlayerbotAIConfig.sightDistance, false))
                            {
                                return false;
                            }
                        }
                    }
                }
            }

            return true;
        }
    };

    /// 触发器：当前不存在有效的控制（CC）团队标记目标
    class NoRtiCCTrigger : public Trigger
    {
    public:
        NoRtiCCTrigger(PlayerbotAI* ai) : Trigger(ai, "no rti cc target") {}

        virtual bool IsActive() override
        {
            if (ai->GetUnit(AI_VALUE(ObjectGuid, "rti cc target")))
            {
                return false;
            }
            else
            {
                // Check for the default rti cc if the bot is setup to ignore rti cc targets | 若机器人配置为忽略控制标记，则检查默认控制标记
                std::string rti = AI_VALUE(std::string, "rti cc");
                int index = RtiTargetValue::GetRtiIndex(rti);
                if (index == -1)
                {
                    // If we have cc enabled, but no mark set, then we're open to ccing stuff at random | 若开启了控制策略但未指定标记，则允许随机对目标施放控制
                    if (ai->HasStrategy("cc", BotState::BOT_STATE_COMBAT))
                        return true;
                }

                return false;
            }
        }
    };
}
