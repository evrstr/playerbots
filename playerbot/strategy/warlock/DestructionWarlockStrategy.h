// 术士 - 毁灭术士策略头文件 (DestructionWarlockStrategy.h)
#pragma once
#include "WarlockStrategy.h"

namespace ai
{
    // 毁灭术士专精占位策略：用于专精识别与占位的策略类
    class DestructionWarlockPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        DestructionWarlockPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "destruction"; }
    };

    // 毁灭术士策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockStrategy : public WarlockStrategy
    {
    public:
        DestructionWarlockStrategy(PlayerbotAI* ai) : WarlockStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 毁灭术士PVE策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockPveStrategy : public DestructionWarlockStrategy
    {
    public:
        DestructionWarlockPveStrategy(PlayerbotAI* ai) : DestructionWarlockStrategy(ai) {}
        std::string getName() override { return "destruction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士PVP策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockPvpStrategy : public DestructionWarlockStrategy
    {
    public:
        DestructionWarlockPvpStrategy(PlayerbotAI* ai) : DestructionWarlockStrategy(ai) {}
        std::string getName() override { return "destruction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士团队副本策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockRaidStrategy : public DestructionWarlockStrategy
    {
    public:
        DestructionWarlockRaidStrategy(PlayerbotAI* ai) : DestructionWarlockStrategy(ai) {}
        std::string getName() override { return "destruction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士AOE群体策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockAoeStrategy : public WarlockAoeStrategy
    {
    public:
        DestructionWarlockAoeStrategy(PlayerbotAI* ai) : WarlockAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockAoePveStrategy : public DestructionWarlockAoeStrategy
    {
    public:
        DestructionWarlockAoePveStrategy(PlayerbotAI* ai) : DestructionWarlockAoeStrategy(ai) {}
        std::string getName() override { return "aoe destruction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockAoePvpStrategy : public DestructionWarlockAoeStrategy
    {
    public:
        DestructionWarlockAoePvpStrategy(PlayerbotAI* ai) : DestructionWarlockAoeStrategy(ai) {}
        std::string getName() override { return "aoe destruction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockAoeRaidStrategy : public DestructionWarlockAoeStrategy
    {
    public:
        DestructionWarlockAoeRaidStrategy(PlayerbotAI* ai) : DestructionWarlockAoeStrategy(ai) {}
        std::string getName() override { return "aoe destruction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士增益Buff策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockBuffStrategy : public WarlockBuffStrategy
    {
    public:
        DestructionWarlockBuffStrategy(PlayerbotAI* ai) : WarlockBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockBuffPveStrategy : public DestructionWarlockBuffStrategy
    {
    public:
        DestructionWarlockBuffPveStrategy(PlayerbotAI* ai) : DestructionWarlockBuffStrategy(ai) {}
        std::string getName() override { return "buff destruction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockBuffPvpStrategy : public DestructionWarlockBuffStrategy
    {
    public:
        DestructionWarlockBuffPvpStrategy(PlayerbotAI* ai) : DestructionWarlockBuffStrategy(ai) {}
        std::string getName() override { return "buff destruction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockBuffRaidStrategy : public DestructionWarlockBuffStrategy
    {
    public:
        DestructionWarlockBuffRaidStrategy(PlayerbotAI* ai) : DestructionWarlockBuffStrategy(ai) {}
        std::string getName() override { return "buff destruction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士爆发增益策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockBoostStrategy : public WarlockBoostStrategy
    {
    public:
        DestructionWarlockBoostStrategy(PlayerbotAI* ai) : WarlockBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockBoostPveStrategy : public DestructionWarlockBoostStrategy
    {
    public:
        DestructionWarlockBoostPveStrategy(PlayerbotAI* ai) : DestructionWarlockBoostStrategy(ai) {}
        std::string getName() override { return "boost destruction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockBoostPvpStrategy : public DestructionWarlockBoostStrategy
    {
    public:
        DestructionWarlockBoostPvpStrategy(PlayerbotAI* ai) : DestructionWarlockBoostStrategy(ai) {}
        std::string getName() override { return "boost destruction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockBoostRaidStrategy : public DestructionWarlockBoostStrategy
    {
    public:
        DestructionWarlockBoostRaidStrategy(PlayerbotAI* ai) : DestructionWarlockBoostStrategy(ai) {}
        std::string getName() override { return "boost destruction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockCcStrategy : public WarlockCcStrategy
    {
    public:
        DestructionWarlockCcStrategy(PlayerbotAI* ai) : WarlockCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockCcPveStrategy : public DestructionWarlockCcStrategy
    {
    public:
        DestructionWarlockCcPveStrategy(PlayerbotAI* ai) : DestructionWarlockCcStrategy(ai) {}
        std::string getName() override { return "cc destruction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockCcPvpStrategy : public DestructionWarlockCcStrategy
    {
    public:
        DestructionWarlockCcPvpStrategy(PlayerbotAI* ai) : DestructionWarlockCcStrategy(ai) {}
        std::string getName() override { return "cc destruction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockCcRaidStrategy : public DestructionWarlockCcStrategy
    {
    public:
        DestructionWarlockCcRaidStrategy(PlayerbotAI* ai) : DestructionWarlockCcStrategy(ai) {}
        std::string getName() override { return "cc destruction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士宠物策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockPetStrategy : public WarlockPetStrategy
    {
    public:
        DestructionWarlockPetStrategy(PlayerbotAI* ai) : WarlockPetStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士宠物PVE策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockPetPveStrategy : public DestructionWarlockPetStrategy
    {
    public:
        DestructionWarlockPetPveStrategy(PlayerbotAI* ai) : DestructionWarlockPetStrategy(ai) {}
        std::string getName() override { return "pet destruction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士宠物PVP策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockPetPvpStrategy : public DestructionWarlockPetStrategy
    {
    public:
        DestructionWarlockPetPvpStrategy(PlayerbotAI* ai) : DestructionWarlockPetStrategy(ai) {}
        std::string getName() override { return "pet destruction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士宠物团队副本策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockPetRaidStrategy : public DestructionWarlockPetStrategy
    {
    public:
        DestructionWarlockPetRaidStrategy(PlayerbotAI* ai) : DestructionWarlockPetStrategy(ai) {}
        std::string getName() override { return "pet destruction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士诅咒策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockCursesStrategy : public WarlockCursesStrategy
    {
    public:
        DestructionWarlockCursesStrategy(PlayerbotAI* ai) : WarlockCursesStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士诅咒PVE策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockCursesPveStrategy : public DestructionWarlockCursesStrategy
    {
    public:
        DestructionWarlockCursesPveStrategy(PlayerbotAI* ai) : DestructionWarlockCursesStrategy(ai) {}
        std::string getName() override { return "curse destruction pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士诅咒PVP策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockCursesPvpStrategy : public DestructionWarlockCursesStrategy
    {
    public:
        DestructionWarlockCursesPvpStrategy(PlayerbotAI* ai) : DestructionWarlockCursesStrategy(ai) {}
        std::string getName() override { return "curse destruction pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 毁灭术士诅咒团队副本策略：定义该专精/场景下的触发器与默认行为
    class DestructionWarlockCursesRaidStrategy : public DestructionWarlockCursesStrategy
    {
    public:
        DestructionWarlockCursesRaidStrategy(PlayerbotAI* ai) : DestructionWarlockCursesStrategy(ai) {}
        std::string getName() override { return "curse destruction raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
