// 策略值头文件：AoeValues（范围伤害位置、密度计数与区域减益检测）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 值计算器：计算最适合释放范围法术（AOE）的世界坐标位置
    class AoePositionValue : public CalculatedValue<WorldLocation>
    {
    public:
        AoePositionValue(PlayerbotAI* ai) : CalculatedValue<WorldLocation>(ai, "aoe position") {}

    public:
        // 返回 AOE 最佳释放中心点
        virtual WorldLocation Calculate();
    };

    // 值计算器：计算最大聚集敌人集群的单位数量
    class AoeCountValue : public CalculatedValue<uint8>
    {
    public:
        AoeCountValue(PlayerbotAI* ai) : CalculatedValue<uint8>(ai, "aoe count") {}

    public:
        // 在指定范围内查找互相距离不超过两倍 AOE 半径的最大敌对目标集合
        static std::list<ObjectGuid> FindMaxDensity(Player* bot, float range = 100.0f);
        // 返回最大密集敌群的单位数量
        virtual uint8 Calculate() override;
    };

    // 布尔值计算器：判断指定目标是否受到地面区域负面动态法术（如暴风雪、奉献等）影响
    class HasAreaDebuffValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HasAreaDebuffValue(PlayerbotAI* ai) : BoolCalculatedValue(ai), Qualified() {}

        // 根据限定符获取待检测的目标单位
        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;

            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }
        // 检测目标是否处于任意有害区域动态效果范围内
        virtual bool Calculate() override;
    };
}
