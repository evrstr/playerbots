#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"

namespace ai
{
    /// RPG 交互动作：导航至并执行针对当前选定 RPG 目标的交互子动作
    class RpgAction : public MovementAction {
    public:
        /// 构造函数：初始化RPG 交互动作
        RpgAction(PlayerbotAI* ai, std::string name = "rpg") : MovementAction(ai, name) {}

        /// 执行动作主逻辑（RPG 交互动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（RPG 交互动作）
        virtual bool isUseful() override;

    protected:
        /// 根据评分选定并设置下一步要执行的 RPG 子动作
        virtual bool SetNextRpgAction();

        typedef void (RpgAction::* RpgElement) (ObjectGuid guid);
        /// 将指定 GUID 或目标加入临时忽略列表
        virtual bool AddIgnore(ObjectGuid guid);
        /// 从临时忽略列表中移除指定目标
        virtual bool RemIgnore(ObjectGuid guid);
        /// 检查指定目标是否处于临时忽略列表中
        virtual bool HasIgnore(ObjectGuid guid);   
    };

    /// 连续 RPG 交互动作：在完成一次 RPG 交互后继续评估并执行下一项交互
    class CRpgAction : public RpgAction {
    public:
        /// 构造函数：初始化连续 RPG 交互动作
        CRpgAction(PlayerbotAI* ai) : RpgAction(ai, "crpg") {}

        /// 判断当前状态下该动作是否可用/有效（连续 RPG 交互动作）
        virtual bool isUseful() override { RESET_AI_VALUE(GuidPosition,"rpg target"); return true; };
    };
}
