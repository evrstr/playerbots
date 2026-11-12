#pragma once
#include "UseItemAction.h"

namespace ai
{
    /// 使用饰品动作：检测已装备的主动饰品冷却并在合适时机激活饰品特效
    class UseTrinketAction : public UseAction 
    {
    public:

        /// 构造函数：初始化使用饰品动作
        UseTrinketAction(PlayerbotAI* ai) : UseAction(ai, "use trinket") {}
        /// 执行动作主逻辑（使用饰品动作）
        virtual bool Execute(Event& event) override;
        /// 判断执行该动作的前置条件是否满足（使用饰品动作）
        virtual bool isPossible() override;
        /// 判断当前状态下该动作是否可用/有效（使用饰品动作）
        virtual bool isUseful() override { return UseAction::isUseful() && !bot->HasStealthAura(); }
    };
}
