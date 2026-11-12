#pragma once

#include "WorldPosition.h"

class Player;

namespace ai
{
    class Engine;

    

    /// 候选逃跑安全点，记录三维坐标与周围敌对单位的距离统计
        class FleePoint {
    public:
        FleePoint(PlayerbotAI* ai, float x, float y, float z) : ai(ai), sumDistance(0.0f), minDistance(0.0f) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

    public:
        float x;
        float y;
        float z;

        float sumDistance;
        float minDistance;

    private:
        PlayerbotAI* ai;
    };

    /// 逃跑路径评估管理器，在周围采样无阻挡、非水域、远离敌人的最佳撤离目标点
        class FleeManager
    {
    public:
        FleeManager(Player* bot, float maxAllowedDistance, float followAngle, bool forceMaxDistance = false, WorldPosition startPosition = WorldPosition()) {
            this->bot = bot;
            this->maxAllowedDistance = maxAllowedDistance;
            this->followAngle = followAngle;
            this->forceMaxDistance = forceMaxDistance;
            this->startPosition = startPosition ? startPosition : WorldPosition(bot);
        }

    public:
        bool CalculateDestination(float* rx, float* ry, float* rz);
        bool isUseful();

    private:
        void calculatePossibleDestinations(std::list<FleePoint*> &points);
        void calculateDistanceToCreatures(FleePoint *point);
        void cleanup(std::list<FleePoint*> &points);
        FleePoint* selectOptimalDestination(std::list<FleePoint*> &points);
        bool isBetterThan(FleePoint* point, FleePoint* other);
        bool isTooCloseToEdge(float x, float y, float z, float angle);

    private:
        Player* bot;
        float maxAllowedDistance;
        float followAngle;
        bool forceMaxDistance;
        WorldPosition startPosition;
    };

};
