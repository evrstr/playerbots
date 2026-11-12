// 策略值头文件：NewPlayerNearbyValue（新遇见的附近玩家检测与已见过玩家缓存）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 目标值计算器：从附近友方玩家中找出尚未记录的新玩家 GUID
    class NewPlayerNearbyValue : public CalculatedValue<ObjectGuid>
    {
    public:
        NewPlayerNearbyValue(PlayerbotAI* ai) : CalculatedValue<ObjectGuid>(ai, "new player nearby") {}
        virtual ObjectGuid Calculate() override;
    };

    // 手动设置值：保存机器人已经打过招呼或记录过的玩家 GUID 集合
    class AlreadySeenPlayersValue : public ManualSetValue<std::set<ObjectGuid>& >
    {
    public:
        AlreadySeenPlayersValue(PlayerbotAI* ai) : ManualSetValue<std::set<ObjectGuid>& >(ai, data, "already seen players") {}

    private:
        std::set<ObjectGuid> data;
    };
}
