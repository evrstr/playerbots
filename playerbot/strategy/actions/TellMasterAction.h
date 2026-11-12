#pragma once
#include "MovementActions.h"

namespace ai
{
    /// 通知主人动作：向主人发送自定义文本提示消息
    class TellMasterAction : public Action 
    {
    public:
        /// 构造函数：初始化通知主人动作
        TellMasterAction(PlayerbotAI* ai, std::string text) : Action(ai, "tell master"), text(text) {}

        /// 执行动作主逻辑（通知主人动作）
        virtual bool Execute(Event& event)
        {
            ai->TellPlayer(GetMaster(), text);
            return true;
        }

        /// 判断在被昏迷或控制状态下是否仍可执行该动作（通知主人动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        std::string text;
    };

    /// 超出反应范围通知动作：在机器人距离主人过远时移动靠近并汇报
    class OutOfReactRangeAction : public MovementAction 
    {
    public:
        /// 构造函数：初始化超出反应范围通知动作
        OutOfReactRangeAction(PlayerbotAI* ai) : MovementAction(ai, "tell out of react range") {}

        /// 执行动作主逻辑（超出反应范围通知动作）
        virtual bool Execute(Event& event) override
        {
            Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
            ai->TellPlayer(requester, BOT_TEXT("wait_travel_close"));
            return true;
        }

        /// 判断当前状态下该动作是否可用/有效（超出反应范围通知动作）
        virtual bool isUseful() override
        {
            bool canFollow = Follow(ai->GetUnit(AI_VALUE(ObjectGuid, "master target")));
            if (!canFollow)
                return false;

            return true;
        }

        /// 判断在被昏迷或控制状态下是否仍可执行该动作（超出反应范围通知动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
