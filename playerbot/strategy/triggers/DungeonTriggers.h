/// 副本与首领战斗通用触发器基类定义
#pragma once
#include "playerbot/strategy/Trigger.h"

namespace ai
{
    /// 触发器：进入指定地图 ID 的地下城或团队副本
    class EnterDungeonTrigger : public Trigger
    {
    public:
        // You can get the mapID from worlddb > instance_template > map column | 可在 worlddb > instance_template > map 列查询地图 ID
        // or from here https://wow.tools/dbc/?dbc=map&build=1.12.1.5875 | 或参考 https://wow.tools/dbc/?dbc=map&build=1.12.1.5875
        EnterDungeonTrigger(PlayerbotAI* ai, std::string name, std::string dungeonStrategy, uint32 mapID)
        : Trigger(ai, name, 5)
        , dungeonStrategy(dungeonStrategy)
        , mapID(mapID) {}

        bool IsActive() override;

    private:
        std::string dungeonStrategy;
        uint32 mapID;
    };

    /// 触发器：离开指定地图 ID 的地下城或团队副本
    class LeaveDungeonTrigger : public Trigger
    {
    public:
        // You can get the mapID from worlddb > instance_template > map column | 可在 worlddb > instance_template > map 列查询地图 ID
        // or from here https://wow.tools/dbc/?dbc=map&build=1.12.1.5875 | 或参考 https://wow.tools/dbc/?dbc=map&build=1.12.1.5875
        LeaveDungeonTrigger(PlayerbotAI* ai, std::string name, std::string dungeonStrategy, uint32 mapID)
        : Trigger(ai, name, 5)
        , dungeonStrategy(dungeonStrategy)
        , mapID(mapID) {}

        bool IsActive() override;

    private:
        std::string dungeonStrategy;
        uint32 mapID;
    };

    /// 触发器：检测到指定 Boss 进入战斗，开启对应首领策略
    class StartBossFightTrigger : public Trigger
    {
    public:
        StartBossFightTrigger(PlayerbotAI* ai, std::string name, std::string bossStrategy, uint64 bossID)
        : Trigger(ai, name, 1)
        , bossStrategy(bossStrategy)
        , bossID(bossID) {}

        bool IsActive() override;

    private:
        std::string bossStrategy;
        uint64 bossID;
    };

    /// 触发器：脱离战斗后结束对应首领策略
    class EndBossFightTrigger : public Trigger
    {
    public:
        EndBossFightTrigger(PlayerbotAI* ai, std::string name, std::string bossStrategy, uint64 bossID)
        : Trigger(ai, name, 5)
        , bossStrategy(bossStrategy)
        , bossID(bossID) {}

        bool IsActive() override;

    private:
        std::string bossStrategy;
        uint64 bossID;
    };

    /// 触发器基类：检测机器人是否靠近持续性危险区域（地面AoE/陷阱等）
    class CloseToHazardTrigger : public Trigger
    {
    public:
        CloseToHazardTrigger(PlayerbotAI* ai, std::string name, int checkInterval, float hazardRadius, time_t hazardDuration)
        : Trigger(ai, name, checkInterval)
        , hazardRadius(hazardRadius)
        , hazardDuration(hazardDuration) {}

        bool IsActive() override final;

    protected:
        virtual std::list<ObjectGuid> GetPossibleHazards() = 0;
        virtual bool IsHazardValid(const ObjectGuid& hazzardGuid);

    private:
        float GetDistanceToHazard(const ObjectGuid& hazzardGuid);

    protected:
        float hazardRadius;
        time_t hazardDuration;
    };

    /// 触发器：靠近特定游戏对象（GameObject）类型的危险区域
    class CloseToGameObjectHazardTrigger : public CloseToHazardTrigger
    {
    public:
        CloseToGameObjectHazardTrigger(PlayerbotAI* ai, std::string name, uint32 gameObjectID, float radius, time_t expirationTime)
        : CloseToHazardTrigger(ai, name, 1, radius, expirationTime)
        , gameObjectID(gameObjectID) {}

    private:
        std::list<ObjectGuid> GetPossibleHazards() override;

    private:
        uint32 gameObjectID;
    };

    /// 触发器：靠近特定生物（Creature）类型的危险区域
    class CloseToCreatureHazardTrigger : public CloseToHazardTrigger
    {
    public:
        CloseToCreatureHazardTrigger(PlayerbotAI* ai, std::string name, uint32 creatureID, float radius, time_t expirationTime)
        : CloseToHazardTrigger(ai, name, 1, radius, expirationTime)
        , creatureID(creatureID) {}

    private:
        std::list<ObjectGuid> GetPossibleHazards() override;
        bool IsHazardValid(const ObjectGuid& hazzardGuid) override;

    protected:
        uint32 creatureID;
    };

    /// 触发器：靠近正在攻击的敌对生物危险区域
    class CloseToHostileCreatureHazardTrigger : public CloseToCreatureHazardTrigger
    {
    public:
        CloseToHostileCreatureHazardTrigger(PlayerbotAI* ai, std::string name, uint32 creatureID, float radius, time_t expirationTime)
        : CloseToCreatureHazardTrigger(ai, name, creatureID, radius, expirationTime) {}

    private:
        std::list<ObjectGuid> GetPossibleHazards() override;
    };

    /// 触发器：特定生物距离机器人过近
    class CloseToCreatureTrigger : public Trigger
    {
    public:
        CloseToCreatureTrigger(PlayerbotAI* ai, std::string name, uint32 creatureID, float range, bool ignoreVictim = false, uint32 timeInterval = 1)
        : Trigger(ai, name, timeInterval)
        , creatureID(creatureID)
        , range(range)
        , ignoreVictim(ignoreVictim) {}

        bool IsActive() override;

    private:
        uint32 creatureID;
        float range;
        bool ignoreVictim;
    };

    /// 触发器：规避列表中的指定生物距离机器人过近
    class CloseToSpecificCreaturesTrigger : public Trigger
    {
    public:
        CloseToSpecificCreaturesTrigger(PlayerbotAI* ai, std::string name = "specific creature too close", bool ignoreVictim = true)
        : Trigger(ai, name, 1)
        , ignoreVictim(ignoreVictim) {}

        bool IsActive() override;

    private:
        bool ignoreVictim;
    };

    /// 触发器：检查背包中指定物品是否冷却就绪
    class ItemReadyTrigger : public Trigger
    {
    public:
        ItemReadyTrigger(PlayerbotAI* ai, std::string name, uint32 itemID)
        : Trigger(ai, name, 1)
        , itemID(itemID) {}

        virtual bool IsActive() override;

    protected:
        uint32 itemID;
    };

    /// 触发器：检查指定增益物品就绪且自身尚未拥有该增益
    class ItemBuffReadyTrigger : public ItemReadyTrigger
    {
    public:
        ItemBuffReadyTrigger(PlayerbotAI* ai, std::string name, uint32 itemID, uint32 buffID)
        : ItemReadyTrigger(ai, name, itemID)
        , buffID(buffID) {}

        bool IsActive() override;

    private:
        uint32 buffID;
    };
}