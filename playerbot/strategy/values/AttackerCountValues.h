// 策略值头文件：AttackerCountValues（攻击者数量、仇恨状态、战力平衡比与承受伤害）
#pragma once
#include "StatsValues.h"

namespace ai
{
    // 值计算器：统计与机器人或其队伍交战的攻击者总数
    class AttackersCountValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        AttackersCountValue(PlayerbotAI* ai, std::string name = "attackers count") : Uint8CalculatedValue(ai, name, 4), Qualified() {}
        virtual uint8 Calculate() override;
    };

    // 值计算器：统计附近可能作为攻击目标的单位总数
    class PossibleAttackTargetsCountValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        PossibleAttackTargetsCountValue(PlayerbotAI* ai, std::string name = "possible attack targets count") : Uint8CalculatedValue(ai, name, 4), Qualified() {}
        virtual uint8 Calculate() override;
    };

    // 布尔值计算器：判断当前是否存在正在交战的攻击者
    class HasAttackersValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HasAttackersValue(PlayerbotAI* ai, std::string name = "has attackers") : BoolCalculatedValue(ai, name, 4), Qualified() {}
        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断是否存在潜在可攻击目标
    class HasPossibleAttackTargetsValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HasPossibleAttackTargetsValue(PlayerbotAI* ai, std::string name = "has possible attack targets") : BoolCalculatedValue(ai, name, 4), Qualified() {}
        virtual bool Calculate() override;
    };

    // 值计算器：统计当前直接攻击机器人本体的敌人数量
    class MyAttackerCountValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        MyAttackerCountValue(PlayerbotAI* ai, std::string name = "my attackers count") : Uint8CalculatedValue(ai, name, 4), Qualified() {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }
        virtual uint8 Calculate() override;
    };

    // 布尔值计算器：判断机器人是否对指定目标拥有仇恨（Aggro）
    class HasAggroValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HasAggroValue(PlayerbotAI* ai, std::string name = "has agro") : BoolCalculatedValue(ai, name, 4), Qualified() {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }
        virtual bool Calculate() override;
    };

    // 值计算器：计算友方与敌方总等级战力对比百分比（最高 200%）
    class BalancePercentValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        BalancePercentValue(PlayerbotAI* ai, std::string name = "balance percentage") : Uint8CalculatedValue(ai, name, 4), Qualified() {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }
        virtual uint8 Calculate() override;
    };

    // 值计算器：估算指定目标当前承受的所有近战攻击者的平均单次伤害总和
    class IncomingDamageValue : public Uint32CalculatedValue, public Qualified
    {
    public:
        IncomingDamageValue(PlayerbotAI* ai) : Uint32CalculatedValue(ai), Qualified() {}

        virtual uint32 Calculate() override
        {
            Unit* target = ai->GetUnit(AI_VALUE(ObjectGuid, qualifier));
            if (!target)
                return 0;

            uint32 damage = 0;
            for (auto const& pAttacker : target->getAttackers())
                if (pAttacker->CanReachWithMeleeAttack(target))
                    damage += uint32((pAttacker->GetFloatValue(UNIT_FIELD_MINDAMAGE) + pAttacker->GetFloatValue(UNIT_FIELD_MAXDAMAGE)) / 2);

            return damage;
        }
    };
}
