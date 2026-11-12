#pragma once
#include "MovementActions.h"

namespace ai
{
    /// 集合石/术士召唤移动动作：向待召唤成员位置或集合石移动以准备执行召唤
    class SummonAction : public MovementAction
    {
    public:
        /// 构造函数：初始化集合石/术士召唤移动动作
        SummonAction(PlayerbotAI* ai, std::string name = "summon") : MovementAction(ai, name) {}
        /// 判断执行该动作的前置条件是否满足（集合石/术士召唤移动动作）
        bool isPossible() override { return true; }
        /// 判断当前状态下该动作是否可用/有效（集合石/术士召唤移动动作）
        bool isUseful() override { return true; }
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（集合石/术士召唤移动动作）
        bool isUsefulWhenStunned() override { return true; }
        /// 执行动作主逻辑（集合石/术士召唤移动动作）
        virtual bool Execute(Event& event) override;

    protected:
        /// 执行传送法术或安全坐标传送操作
        bool Teleport(Player* requester, Player *summoner, Player *player);
        /// 利用附近的集合石等游戏对象执行召唤队友操作
        bool SummonUsingGos(Player* requester, Player *summoner, Player *player);
        /// 利用相关 NPC 执行召唤队友操作
        bool SummonUsingNpcs(Player* requester, Player *summoner, Player *player);
    };

    /// 使用集合石动作：利用副本门口的集合石召唤尚未到场的队友
    class UseMeetingStoneAction : public SummonAction
    {
    public:
        /// 构造函数：初始化使用集合石动作
        UseMeetingStoneAction(PlayerbotAI* ai) : SummonAction(ai, "use meeting stone") {}
        /// 执行动作主逻辑（使用集合石动作）
        virtual bool Execute(Event& event) override;
    };

    /// 接受召唤动作：收到术士或集合石召唤请求时自动确认并传送
    class AcceptSummonAction : public Action
    {
    public:
        /// 构造函数：初始化接受召唤动作
        AcceptSummonAction(PlayerbotAI* ai) : Action(ai, "accept summon") {}
        /// 执行动作主逻辑（接受召唤动作）
        virtual bool Execute(Event& event) override;
    };
}
