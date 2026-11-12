#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"
#include "playerbot/strategy/values/LastMovementValue.h"

namespace ai
{
    /// 长途旅行动作：执行跨区域旅行移动、处理传送门及载具过渡
    class TravelAction : public MovementAction {
    public:
        /// 构造函数：初始化长途旅行动作
        TravelAction(PlayerbotAI* ai) : MovementAction(ai, "travel") {}

        /// 执行动作主逻辑（长途旅行动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（长途旅行动作）
        virtual bool isUseful() override;
    };

    /// 前往黑暗之门动作：引导机器人前往外域或艾泽拉斯侧的黑暗之门
    class MoveToDarkPortalAction : public MovementAction {
    public:
        /// 构造函数：初始化前往黑暗之门动作
        MoveToDarkPortalAction(PlayerbotAI* ai) : MovementAction(ai, "move to dark portal") {}

        /// 执行动作主逻辑（前往黑暗之门动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（前往黑暗之门动作）
        virtual bool isUseful() override;
    };

    /// 穿越黑暗之门（艾泽拉斯侧）动作：交互并穿过黑暗之门进入外域或返回艾泽拉斯
    class DarkPortalAzerothAction : public MovementAction {
    public:
        /// 构造函数：初始化穿越黑暗之门（艾泽拉斯侧）动作
        DarkPortalAzerothAction(PlayerbotAI* ai) : MovementAction(ai, "dark portal azeroth") {}

        /// 执行动作主逻辑（穿越黑暗之门（艾泽拉斯侧）动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（穿越黑暗之门（艾泽拉斯侧）动作）
        virtual bool isUseful() override;
    };

    /// 离开黑暗之门区域动作：穿过黑暗之门后向安全区域移动以防卡在门内
    class MoveFromDarkPortalAction : public MovementAction {
    public:
        /// 构造函数：初始化离开黑暗之门区域动作
        MoveFromDarkPortalAction(PlayerbotAI* ai) : MovementAction(ai, "move from dark portal") {}

        /// 执行动作主逻辑（离开黑暗之门区域动作）
        virtual bool Execute(Event& event) override;
    };

}
