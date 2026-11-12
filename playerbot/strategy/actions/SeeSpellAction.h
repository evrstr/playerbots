#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"
#include "playerbot/strategy/values/LastMovementValue.h"
#include "playerbot/strategy/values/RTSCValues.h"

namespace ai
{
    /// 观察法术视觉辅助动作：辅助调试与追踪法术释放位置及路径点
    class SeeSpellAction : public MovementAction
    {
    public:
        /// 构造函数：初始化观察法术视觉辅助动作
        SeeSpellAction(PlayerbotAI* ai, std::string name = "see spell") : MovementAction(ai, name) {}
        /// 执行动作主逻辑（观察法术视觉辅助动作）
        virtual bool Execute(Event& event) override;

        /// 判断执行该动作的前置条件是否满足（观察法术视觉辅助动作）
        virtual bool isPossible() override { return true; }
        /// 判断当前状态下该动作是否可用/有效（观察法术视觉辅助动作）
        virtual bool isUseful() override;

        /// 从候选法术列表中选择当前最适合施放的法术
        bool SelectSpell(Player* requester, WorldPosition& spellPosition);

        /// 移动至满足指定法术施法距离与视野的位置
        virtual bool MoveToSpell(Player* requester, WorldPosition& spellPosition, bool inFormation = true);
        /// 设置机器人相对队伍基准点的自定义阵型偏移位置
        void SetFormationOffset(Player* requester, WorldPosition& spellPosition);
    private:
        /// 沿完整路径点序列批量生成可视化路标点
        Creature* CreateWps(Player* wpOwner, float x, float y, float z, float o, uint32 entry, Creature* lastWp, bool important = false);
    };
}
