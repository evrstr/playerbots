// 术士 - 痛苦术士策略头文件 (AfflictionWarlockStrategy.h)
#pragma once
#include "WarlockStrategy.h"

namespace ai
{
    // 痛苦术士专精占位策略：用于专精识别与占位的策略类
    class AfflictionWarlockPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        AfflictionWarlockPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "affliction"; }
    };

    // 痛苦术士策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockStrategy : public WarlockStrategy
    {
    public:
        AfflictionWarlockStrategy(PlayerbotAI* ai) : WarlockStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 痛苦术士PVE策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockPveStrategy : public AfflictionWarlockStrategy
    {
    public:
        AfflictionWarlockPveStrategy(PlayerbotAI* ai) : AfflictionWarlockStrategy(ai) {}
        std::string getName() override { return "affliction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士PVP策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockPvpStrategy : public AfflictionWarlockStrategy
    {
    public:
        AfflictionWarlockPvpStrategy(PlayerbotAI* ai) : AfflictionWarlockStrategy(ai) {}
        std::string getName() override { return "affliction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士团队副本策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockRaidStrategy : public AfflictionWarlockStrategy
    {
    public:
        AfflictionWarlockRaidStrategy(PlayerbotAI* ai) : AfflictionWarlockStrategy(ai) {}
        std::string getName() override { return "affliction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士AOE群体策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockAoeStrategy : public WarlockAoeStrategy
    {
    public:
        AfflictionWarlockAoeStrategy(PlayerbotAI* ai) : WarlockAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockAoePveStrategy : public AfflictionWarlockAoeStrategy
    {
    public:
        AfflictionWarlockAoePveStrategy(PlayerbotAI* ai) : AfflictionWarlockAoeStrategy(ai) {}
        std::string getName() override { return "aoe affliction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockAoePvpStrategy : public AfflictionWarlockAoeStrategy
    {
    public:
        AfflictionWarlockAoePvpStrategy(PlayerbotAI* ai) : AfflictionWarlockAoeStrategy(ai) {}
        std::string getName() override { return "aoe affliction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockAoeRaidStrategy : public AfflictionWarlockAoeStrategy
    {
    public:
        AfflictionWarlockAoeRaidStrategy(PlayerbotAI* ai) : AfflictionWarlockAoeStrategy(ai) {}
        std::string getName() override { return "aoe affliction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士增益Buff策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockBuffStrategy : public WarlockBuffStrategy
    {
    public:
        AfflictionWarlockBuffStrategy(PlayerbotAI* ai) : WarlockBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockBuffPveStrategy : public AfflictionWarlockBuffStrategy
    {
    public:
        AfflictionWarlockBuffPveStrategy(PlayerbotAI* ai) : AfflictionWarlockBuffStrategy(ai) {}
        std::string getName() override { return "buff affliction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockBuffPvpStrategy : public AfflictionWarlockBuffStrategy
    {
    public:
        AfflictionWarlockBuffPvpStrategy(PlayerbotAI* ai) : AfflictionWarlockBuffStrategy(ai) {}
        std::string getName() override { return "buff affliction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockBuffRaidStrategy : public AfflictionWarlockBuffStrategy
    {
    public:
        AfflictionWarlockBuffRaidStrategy(PlayerbotAI* ai) : AfflictionWarlockBuffStrategy(ai) {}
        std::string getName() override { return "buff affliction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士爆发增益策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockBoostStrategy : public WarlockBoostStrategy
    {
    public:
        AfflictionWarlockBoostStrategy(PlayerbotAI* ai) : WarlockBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockBoostPveStrategy : public AfflictionWarlockBoostStrategy
    {
    public:
        AfflictionWarlockBoostPveStrategy(PlayerbotAI* ai) : AfflictionWarlockBoostStrategy(ai) {}
        std::string getName() override { return "boost affliction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockBoostPvpStrategy : public AfflictionWarlockBoostStrategy
    {
    public:
        AfflictionWarlockBoostPvpStrategy(PlayerbotAI* ai) : AfflictionWarlockBoostStrategy(ai) {}
        std::string getName() override { return "boost affliction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockBoostRaidStrategy : public AfflictionWarlockBoostStrategy
    {
    public:
        AfflictionWarlockBoostRaidStrategy(PlayerbotAI* ai) : AfflictionWarlockBoostStrategy(ai) {}
        std::string getName() override { return "boost affliction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockCcStrategy : public WarlockCcStrategy
    {
    public:
        AfflictionWarlockCcStrategy(PlayerbotAI* ai) : WarlockCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockCcPveStrategy : public AfflictionWarlockCcStrategy
    {
    public:
        AfflictionWarlockCcPveStrategy(PlayerbotAI* ai) : AfflictionWarlockCcStrategy(ai) {}
        std::string getName() override { return "cc affliction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockCcPvpStrategy : public AfflictionWarlockCcStrategy
    {
    public:
        AfflictionWarlockCcPvpStrategy(PlayerbotAI* ai) : AfflictionWarlockCcStrategy(ai) {}
        std::string getName() override { return "cc affliction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockCcRaidStrategy : public AfflictionWarlockCcStrategy
    {
    public:
        AfflictionWarlockCcRaidStrategy(PlayerbotAI* ai) : AfflictionWarlockCcStrategy(ai) {}
        std::string getName() override { return "cc affliction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士宠物策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockPetStrategy : public WarlockPetStrategy
    {
    public:
        AfflictionWarlockPetStrategy(PlayerbotAI* ai) : WarlockPetStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士宠物PVE策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockPetPveStrategy : public AfflictionWarlockPetStrategy
    {
    public:
        AfflictionWarlockPetPveStrategy(PlayerbotAI* ai) : AfflictionWarlockPetStrategy(ai) {}
        std::string getName() override { return "pet affliction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士宠物PVP策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockPetPvpStrategy : public AfflictionWarlockPetStrategy
    {
    public:
        AfflictionWarlockPetPvpStrategy(PlayerbotAI* ai) : AfflictionWarlockPetStrategy(ai) {}
        std::string getName() override { return "pet affliction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士宠物团队副本策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockPetRaidStrategy : public AfflictionWarlockPetStrategy
    {
    public:
        AfflictionWarlockPetRaidStrategy(PlayerbotAI* ai) : AfflictionWarlockPetStrategy(ai) {}
        std::string getName() override { return "pet affliction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士诅咒策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockCursesStrategy : public WarlockCursesStrategy
    {
    public:
        AfflictionWarlockCursesStrategy(PlayerbotAI* ai) : WarlockCursesStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士诅咒PVE策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockCursesPveStrategy : public AfflictionWarlockCursesStrategy
    {
    public:
        AfflictionWarlockCursesPveStrategy(PlayerbotAI* ai) : AfflictionWarlockCursesStrategy(ai) {}
        std::string getName() override { return "curse affliction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士诅咒PVP策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockCursesPvpStrategy : public AfflictionWarlockCursesStrategy
    {
    public:
        AfflictionWarlockCursesPvpStrategy(PlayerbotAI* ai) : AfflictionWarlockCursesStrategy(ai) {}
        std::string getName() override { return "curse affliction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 痛苦术士诅咒团队副本策略：定义该专精/场景下的触发器与默认行为
    class AfflictionWarlockCursesRaidStrategy : public AfflictionWarlockCursesStrategy
    {
    public:
        AfflictionWarlockCursesRaidStrategy(PlayerbotAI* ai) : AfflictionWarlockCursesStrategy(ai) {}
        std::string getName() override { return "curse affliction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
