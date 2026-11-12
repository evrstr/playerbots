// 策略值头文件：LastMovementValue（上一次移动轨迹、停留时间、长途移动与炉石绑定点）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/TravelNode.h"

namespace ai
{
    // 移动记录数据结构：保存上次移动目标、路径点、飞行节点、上马状态及上次长途移动位置
    class LastMovement
    {
    public:
        LastMovement()
        {
            clear();
        }

        LastMovement(LastMovement& other)
        {
            taxiNodes = other.taxiNodes;
            taxiMaster = other.taxiMaster;
            lastFollow = other.lastFollow;
            lastAreaTrigger = other.lastAreaTrigger;
            lastTransportEntry = other.lastTransportEntry;
            lastPath = other.lastPath;
            lastMoveShort = other.lastMoveShort;
            nextTeleport = other.nextTeleport;
            moveEvent = Event();
        }

        void clear()
        {
            lastPath.clear();
            lastFollow = NULL;
            lastAreaTrigger = 0;
            lastTransportEntry = 0;
            lastFlee = 0;
            lastMoveShort = WorldPosition();
            lastFleeTo = WorldPosition();
            nextTeleport = 0;
            moveEvent = Event();
        }

        void Set(Unit* lastFollow)
        {
            setPath(TravelPath());
            this->lastFollow = lastFollow;
        }

        void setPath(TravelPath path) { lastPath = path; }
    public:
        std::vector<uint32> taxiNodes;
        ObjectGuid taxiMaster;
        Unit* lastFollow;
        uint32 lastAreaTrigger;
        uint32 lastTransportEntry;
        time_t lastFlee;
        WorldPosition lastFleeTo;
        TravelPath lastPath;
        WorldPosition lastMoveShort;
        time_t nextTeleport;
        Event moveEvent;
    };

    // 手动设置值：持有机器人的 LastMovement 移动状态缓存
    class LastMovementValue : public ManualSetValue<LastMovement&>
    {
    public:
        LastMovementValue(PlayerbotAI* ai) : ManualSetValue<LastMovement&>(ai, data) {}
    private:
        LastMovement data = LastMovement();
    };

    // 手动设置值：记录机器人开始原地停留的时间戳
    class StayTimeValue : public ManualSetValue<time_t>
    {
    public:
        StayTimeValue(PlayerbotAI* ai) : ManualSetValue<time_t>(ai, 0) {}
    };

    // 位置计算器：返回机器人在 100 码以上长途移动前保存的起始位置
    class LastLongMoveValue : public CalculatedValue<WorldPosition>
    {
    public:
        LastLongMoveValue(PlayerbotAI* ai) : CalculatedValue<WorldPosition>(ai, "last long move", 30) {}

        WorldPosition Calculate() override;
    };


    // 位置计算器：读取并格式化机器人炉石绑定的旅店世界坐标
    class HomeBindValue : public CalculatedValue<WorldPosition>
    {
    public:
        HomeBindValue(PlayerbotAI* ai) : CalculatedValue<WorldPosition>(ai, "home bind", 30) {}

        WorldPosition Calculate() override;

        virtual std::string Format() override;
    };
}
