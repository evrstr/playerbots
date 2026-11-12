// 策略值头文件：StatsValues（血量、怒气、能量、法力、连击点、背包、耐久度、速度等基础属性计算值）
#pragma once
#include "playerbot/strategy/Value.h"

class Unit;

namespace ai
{
    // 百分比值计算器：获取指定单位当前生命值百分比（0-100）
    class HealthValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        HealthValue(PlayerbotAI* ai, std::string name = "health") : Uint8CalculatedValue(ai, name), Qualified() {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }

        virtual uint8 Calculate() override;
    };

    // 布尔值计算器：判断指定单位是否已死亡
    class IsDeadValue : public BoolCalculatedValue, public Qualified
    {
    public:
        IsDeadValue(PlayerbotAI* ai, std::string name = "dead") : BoolCalculatedValue(ai, name), Qualified() {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }

        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断猎人/术士当前宠物是否处于死亡状态
    class PetIsDeadValue : public BoolCalculatedValue
    {
    public:
        PetIsDeadValue(PlayerbotAI* ai, std::string name = "pet dead") : BoolCalculatedValue(ai, name) {}
        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断猎人宠物快乐度是否处于快乐（高兴）状态
    class PetIsHappyValue : public BoolCalculatedValue
    {
    public:
        PetIsHappyValue(PlayerbotAI* ai, std::string name = "pet happy") : BoolCalculatedValue(ai, name) {}
        virtual bool Calculate() override;
    };

    // 数值计算器：获取指定单位当前怒气值（已除以 10 换算为 0-100）
    class RageValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        RageValue(PlayerbotAI* ai, std::string name = "rage") : Uint8CalculatedValue(ai, name), Qualified() {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }

        virtual uint8 Calculate() override;
    };

    // 数值计算器：获取指定单位当前能量值
    class EnergyValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        EnergyValue(PlayerbotAI* ai, std::string name = "energy") : Uint8CalculatedValue(ai, name), Qualified() {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }

        virtual uint8 Calculate() override;
    };

    // 百分比值计算器：获取指定单位当前法力值百分比（0-100）
    class ManaValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        ManaValue(PlayerbotAI* ai, std::string name = "mana") : Uint8CalculatedValue(ai, name), Qualified() {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }

        virtual uint8 Calculate() override;
    };

    // 布尔值计算器：判断指定单位是否拥有法力条（最大法力大于 0）
    class HasManaValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HasManaValue(PlayerbotAI* ai, std::string name = "has mana") : BoolCalculatedValue(ai, name), Qualified() {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }

        virtual bool Calculate() override;
    };

    // 数值计算器：获取当前选定目标身上的连击点数
    class ComboPointsValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        ComboPointsValue(PlayerbotAI* ai, std::string name = "combo points") : Uint8CalculatedValue(ai, name), Qualified() {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }

        virtual uint8 Calculate() override;
    };

    // 布尔值计算器：判断指定单位当前是否处于骑乘状态（含飞行/水生）
    class IsMountedValue : public BoolCalculatedValue, public Qualified
    {
    public:
        IsMountedValue(PlayerbotAI* ai, std::string name = "mounted") : BoolCalculatedValue(ai, name), Qualified() {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }

        virtual bool Calculate() override;
    };

    // 记忆布尔值计算器：判断指定单位或机器人小队当前是否处于战斗中
    class IsInCombatValue : public MemoryCalculatedValue<bool>, public Qualified
    {
    public:
        IsInCombatValue(PlayerbotAI* ai, std::string name = "combat") : MemoryCalculatedValue(ai, name), Qualified() {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }

        virtual bool EqualToLast(bool value) override { return value == lastValue; }
        virtual bool Calculate() override;

        virtual std::string Format() override
        {
            return this->Calculate() ? "true" : "false";
        }
    };

    // 百分比值计算器：计算机器人当前背包已占用空间百分比（0-100）
    class BagSpaceValue : public Uint8CalculatedValue
    {
    public:
        BagSpaceValue(PlayerbotAI* ai, std::string name = "bag space") : Uint8CalculatedValue(ai, name) {}
        virtual uint8 Calculate() override;
    };

    // 百分比值计算器：计算机器人个人银行当前已占用空间百分比（0-100）
    class BankSpaceValue : public Uint8CalculatedValue
    {
    public:
        BankSpaceValue(PlayerbotAI* ai, std::string name = "bank space") : Uint8CalculatedValue(ai, name) {}
        virtual uint8 Calculate() override;
    };

    // 百分比值计算器：计算当前已穿戴装备的平均耐久度百分比
    class DurabilityValue : public Uint8CalculatedValue
    {
    public:
        DurabilityValue(PlayerbotAI* ai, std::string name = "durability") : Uint8CalculatedValue(ai, name) {}
        virtual uint8 Calculate() override;
    };

    // 百分比值计算器：计算全身装备与背包内所有可修理物品的平均耐久度百分比
    class DurabilityInventoryValue : public Uint8CalculatedValue
    {
    public:
        DurabilityInventoryValue(PlayerbotAI* ai, std::string name = "durability inventory") : Uint8CalculatedValue(ai, name) {}
        virtual uint8 Calculate() override;
    };

    // 百分比值计算器：计算全身装备中的最低单件耐久度百分比
    class LowestDurabilityValue : public Uint8CalculatedValue
    {
    public:
        LowestDurabilityValue(PlayerbotAI* ai, std::string name = "lowest durability") : Uint8CalculatedValue(ai, name) {}
        virtual uint8 Calculate() override;
    };

     // 百分比值计算器：获取指定单位当前地面移动速度百分比（相对于基础速度）
     class SpeedValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        SpeedValue(PlayerbotAI* ai, std::string name = "speed") : Uint8CalculatedValue(ai, name), Qualified() {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ai->GetUnit(ctx->GetValue<ObjectGuid>(qualifier)->Get());
        }

        virtual uint8 Calculate() override;
    };

    // 布尔值计算器：判断机器人当前是否已加入小队或团队
    class IsInGroupValue : public BoolCalculatedValue
    {
    public:
        IsInGroupValue(PlayerbotAI* ai, std::string name = "in group") : BoolCalculatedValue(ai, name) {}
        virtual bool Calculate() override { return bot->GetGroup(); }
    };

    // 手动设置值：累计记录机器人本次会话中的死亡次数
    class DeathCountValue : public ManualSetValue<uint32>
    {
    public:
        DeathCountValue(PlayerbotAI* ai, std::string name = "death count") : ManualSetValue<uint32>(ai, 0, name) {}

        virtual std::string Format() override
        {
            std::ostringstream out; out << (int)this->value;
            return out.str();
        }
    };


    // 记忆值计算器：读取并追踪当前经验值及上次变化间隔
    class ExperienceValue : public MemoryCalculatedValue<uint32>
    {
    public:
        ExperienceValue(PlayerbotAI* ai, std::string name = "experience", uint32 checkInterval = 60) : MemoryCalculatedValue<uint32>(ai, name, checkInterval) {}
        virtual bool EqualToLast(uint32 value) override { return value != lastValue; }
        virtual uint32 Calculate() override { return bot->GetUInt32Value(PLAYER_XP);}

        virtual std::string Format() override
        {
            std::ostringstream out; out << (int)this->Calculate() << " last change:" << LastChangeDelay() << "s";
            return out.str();
        }
    };

    // 记忆值计算器：读取并追踪角色生涯荣誉击杀数
    class HonorValue : public ExperienceValue
    {
    public:
        HonorValue(PlayerbotAI* ai, std::string name = "honor", uint32 checkInterval = 60) : ExperienceValue(ai, name, checkInterval) {}
        virtual bool EqualToLast(uint32 value) override { return value != lastValue; }
        virtual uint32 Calculate() override { return bot->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS); }        
    };
}
