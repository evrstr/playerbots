#pragma once

#include "playerbot/strategy/Action.h"
#include "RpgAction.h"
#include "playerbot/strategy/values/LastMovementValue.h"

namespace ai
{
    /// 选择 RPG 目标动作：评估周围 NPC 与交互点相关性，挑选最适合的 RPG 交互目标
    class ChooseRpgTargetAction : public Action {
    public:
        /// 构造函数：初始化选择 RPG 目标动作
        ChooseRpgTargetAction(PlayerbotAI* ai, std::string name = "choose rpg target") : Action(ai, name) {}

        /// 执行动作主逻辑（选择 RPG 目标动作）
        virtual bool Execute(Event& event);
        /// 判断当前状态下该动作是否可用/有效（选择 RPG 目标动作）
        virtual bool isUseful();

        std::unordered_map<ObjectGuid, float> GetTargets(Player* requester, bool debug = false);

        /// 获取触发当前 RPG 交互动作的原因说明
        std::string GetRpgActionReason(ObjectGuid target) { auto reason = rgpActionReason.find(target); if (reason != rgpActionReason.end())  return reason->second; return ""; }
    private:        
        /// 评估指定 RPG 目标对机器人触发各类交互动作的最高相关性评分
        float getMaxRelevance(GuidPosition guidP);
        /// 判断两个单位是否正在攻击相同的目标
        bool HasSameTarget(ObjectGuid guid, uint32 max, std::list<ObjectGuid>& nearGuids);

        std::unordered_map <ObjectGuid, std::string> rgpActionReason;
    };

    /// 清除 RPG 目标动作：放弃当前 RPG 交互目标并将其加入临时忽略列表
    class ClearRpgTargetAction : public ChooseRpgTargetAction {
    public:
        /// 构造函数：初始化清除 RPG 目标动作
        ClearRpgTargetAction(PlayerbotAI* ai) : ChooseRpgTargetAction(ai, "clear rpg target") {}
    };

}
