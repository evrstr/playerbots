#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"
#include "playerbot/strategy/values/LastMovementValue.h"
#include "UseItemAction.h"

namespace ai
{
    /// 检查坐骑状态动作：根据移动距离、战斗状态和骑术自动上马或下马
    class CheckMountStateAction : public UseAction 
    {
    public:
        /// 构造函数：初始化检查坐骑状态动作
        CheckMountStateAction(PlayerbotAI* ai) : UseAction(ai, "check mount state") {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "check mount state"; }
        virtual std::string GetHelpDescription()
        {
            return "This action automatically mouts up or unmounts a bot based on:\n"
                   "- Location (outdoors only, battleground restrictions)\n"
                   "- Combat status (dismounts when in combat)\n"
                   "- Travel distance (mounts for long distances)\n"
                   "- Group coordination (matches master's mount state)\n"
                   "- Level requirements (minimum level 20/30/40 depending on expansion)";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {"mount list", "current mount speed"}; }
#endif 

        /// 执行动作主逻辑（检查坐骑状态动作）
        virtual bool Execute(Event& event) override;
        /// 判断执行该动作的前置条件是否满足（检查坐骑状态动作）
        virtual bool isPossible() override { return true; }
        /// 判断当前状态下该动作是否可用/有效（检查坐骑状态动作）
        virtual bool isUseful() override;

    private:
        /// 判断机器人当前区域及坐骑状态是否支持飞行移动
        virtual bool CanFly() const;
        /// 判断当前战场规则与携带旗帜状态是否允许上马
        bool CanMountInBg() const;
        /// 根据职业与策略获取对目标的期望攻击距离
        float GetAttackDistance() const;

    private:
        /// 召唤并骑乘适合当前区域的陆地或飞行坐骑
        bool Mount(Player* requester, bool limitSpeedToGroup = false);
        /// 下马并取消当前的坐骑光环
        bool UnMount() const;
    };
}
