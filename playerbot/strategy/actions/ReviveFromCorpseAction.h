#pragma once
#include "MovementActions.h"

namespace ai
{
    /// 跑尸复活动作：在灵魂状态下移动回自己尸体附近并点击复活
    class ReviveFromCorpseAction : public MovementAction 
    {
    public:
        /// 构造函数：初始化跑尸复活动作
        ReviveFromCorpseAction(PlayerbotAI* ai) : MovementAction(ai, "revive from corpse") {}
        /// 执行动作主逻辑（跑尸复活动作）
        virtual bool Execute(Event& event) override;
    };

    /// 寻找尸体动作：规划灵魂状态下返回自己尸体所在位置的路径
    class FindCorpseAction : public MovementAction 
    {
    public:
        /// 构造函数：初始化寻找尸体动作
        FindCorpseAction(PlayerbotAI* ai) : MovementAction(ai, "find corpse") {}
        /// 执行动作主逻辑（寻找尸体动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（寻找尸体动作）
        virtual bool isUseful() override;
    };

    /// 灵魂医者复活动作：向最近灵魂医者移动并执行虚弱复活
    class SpiritHealerAction : public MovementAction 
    {
    public:
        /// 构造函数：初始化灵魂医者复活动作
        SpiritHealerAction(PlayerbotAI* ai, std::string name = "spirit healer") : MovementAction(ai,name) {}
        /// 执行动作主逻辑（灵魂医者复活动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（灵魂医者复活动作）
        virtual bool isUseful() override;
    };
}
