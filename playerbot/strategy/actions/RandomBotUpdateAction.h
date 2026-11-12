#pragma once

#include "playerbot/RandomPlayerbotMgr.h"
#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 随机机器人更新动作：定期更新随机机器人的等级、装备、区域与策略
    class RandomBotUpdateAction : public Action
    {
    public:
        /// 构造函数：初始化随机机器人更新动作
        RandomBotUpdateAction(PlayerbotAI* ai) : Action(ai, "random bot update")
        {}

        /// 执行动作主逻辑（随机机器人更新动作）
        virtual bool Execute(Event& event) override
        {
            if (!sRandomPlayerbotMgr.IsRandomBot(bot))
                return false;

            if (bot->GetGroup() && ai->GetGroupMaster() && (!ai->GetGroupMaster()->GetPlayerbotAI() || ai->GetGroupMaster()->GetPlayerbotAI()->IsRealPlayer()))
                return true;

            if (ai->HasPlayerNearby())
                return true;

            return sRandomPlayerbotMgr.ProcessBot(bot);
        }

        /// 判断当前状态下该动作是否可用/有效（随机机器人更新动作）
        virtual bool isUseful() override
        {
            return AI_VALUE(bool, "random bot update");
        }
    };

}
