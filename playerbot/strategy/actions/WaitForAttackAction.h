#pragma once
#include "MovementActions.h"
#include "GenericActions.h"

namespace ai
{
   /// 等待开怪保持安全距离动作：在开怪倒计时期间保持与目标的安全距离避免提前引怪
   class WaitForAttackKeepSafeDistanceAction : public MovementAction
   {
   public:
       /// 构造函数：初始化等待开怪保持安全距离动作
       WaitForAttackKeepSafeDistanceAction(PlayerbotAI* ai) : MovementAction(ai, "wait for attack keep safe distance") {}
       /// 执行动作主逻辑（等待开怪保持安全距离动作）
       virtual bool Execute(Event& event) override;

   private:
       /// 从候选坐标集合中评估并挑选最安全的站位点
       const WorldPosition GetBestPoint(const WorldPosition& pos, float minDistance, float maxDistance) const;
       /// 判断附近指定半径内是否存在敌对单位
       bool IsEnemyClose(const WorldPosition& point, const std::list<ObjectGuid>& enemies) const;
       /// 判断当前状态下该动作是否可用/有效（等待开怪保持安全距离动作）
       bool isUseful() override;
       /// 判断在被昏迷或控制状态下是否仍可执行该动作（等待开怪保持安全距离动作）
       virtual bool isUsefulWhenStunned() override { return true; }
   };
}
