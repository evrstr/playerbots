// 术士 - 恶魔学识术士策略头文件 (DemonologyWarlockStrategy.h)
#pragma once
#include "WarlockStrategy.h"

namespace ai
{
    // 恶魔学识术士专精占位策略：用于专精识别与占位的策略类
    class DemonologyWarlockPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        DemonologyWarlockPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "demonology"; }
    };

    // 恶魔学识术士策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockStrategy : public WarlockStrategy
    {
    public:
        DemonologyWarlockStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 恶魔学识术士PVE策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockPveStrategy : public DemonologyWarlockStrategy
    {
    public:
        DemonologyWarlockPveStrategy(PlayerbotAI* ai) : DemonologyWarlockStrategy(ai) {}
        std::string getName() override { return "demonology pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士PVP策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockPvpStrategy : public DemonologyWarlockStrategy
    {
    public:
        DemonologyWarlockPvpStrategy(PlayerbotAI* ai) : DemonologyWarlockStrategy(ai) {}
        std::string getName() override { return "demonology pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士团队副本策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockRaidStrategy : public DemonologyWarlockStrategy
    {
    public:
        DemonologyWarlockRaidStrategy(PlayerbotAI* ai) : DemonologyWarlockStrategy(ai) {}
        std::string getName() override { return "demonology raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士AOE群体策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockAoeStrategy : public WarlockAoeStrategy
    {
    public:
        DemonologyWarlockAoeStrategy(PlayerbotAI* ai) : WarlockAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockAoePveStrategy : public DemonologyWarlockAoeStrategy
    {
    public:
        DemonologyWarlockAoePveStrategy(PlayerbotAI* ai) : DemonologyWarlockAoeStrategy(ai) {}
        std::string getName() override { return "aoe demonology pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockAoePvpStrategy : public DemonologyWarlockAoeStrategy
    {
    public:
        DemonologyWarlockAoePvpStrategy(PlayerbotAI* ai) : DemonologyWarlockAoeStrategy(ai) {}
        std::string getName() override { return "aoe demonology pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockAoeRaidStrategy : public DemonologyWarlockAoeStrategy
    {
    public:
        DemonologyWarlockAoeRaidStrategy(PlayerbotAI* ai) : DemonologyWarlockAoeStrategy(ai) {}
        std::string getName() override { return "aoe demonology raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士增益Buff策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockBuffStrategy : public WarlockBuffStrategy
    {
    public:
        DemonologyWarlockBuffStrategy(PlayerbotAI* ai) : WarlockBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockBuffPveStrategy : public DemonologyWarlockBuffStrategy
    {
    public:
        DemonologyWarlockBuffPveStrategy(PlayerbotAI* ai) : DemonologyWarlockBuffStrategy(ai) {}
        std::string getName() override { return "buff demonology pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockBuffPvpStrategy : public DemonologyWarlockBuffStrategy
    {
    public:
        DemonologyWarlockBuffPvpStrategy(PlayerbotAI* ai) : DemonologyWarlockBuffStrategy(ai) {}
        std::string getName() override { return "buff demonology pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockBuffRaidStrategy : public DemonologyWarlockBuffStrategy
    {
    public:
        DemonologyWarlockBuffRaidStrategy(PlayerbotAI* ai) : DemonologyWarlockBuffStrategy(ai) {}
        std::string getName() override { return "buff demonology raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士爆发增益策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockBoostStrategy : public WarlockBoostStrategy
    {
    public:
        DemonologyWarlockBoostStrategy(PlayerbotAI* ai) : WarlockBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockBoostPveStrategy : public DemonologyWarlockBoostStrategy
    {
    public:
        DemonologyWarlockBoostPveStrategy(PlayerbotAI* ai) : DemonologyWarlockBoostStrategy(ai) {}
        std::string getName() override { return "boost demonology pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockBoostPvpStrategy : public DemonologyWarlockBoostStrategy
    {
    public:
        DemonologyWarlockBoostPvpStrategy(PlayerbotAI* ai) : DemonologyWarlockBoostStrategy(ai) {}
        std::string getName() override { return "boost demonology pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockBoostRaidStrategy : public DemonologyWarlockBoostStrategy
    {
    public:
        DemonologyWarlockBoostRaidStrategy(PlayerbotAI* ai) : DemonologyWarlockBoostStrategy(ai) {}
        std::string getName() override { return "boost demonology raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockCcStrategy : public WarlockCcStrategy
    {
    public:
        DemonologyWarlockCcStrategy(PlayerbotAI* ai) : WarlockCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockCcPveStrategy : public DemonologyWarlockCcStrategy
    {
    public:
        DemonologyWarlockCcPveStrategy(PlayerbotAI* ai) : DemonologyWarlockCcStrategy(ai) {}
        std::string getName() override { return "cc demonology pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockCcPvpStrategy : public DemonologyWarlockCcStrategy
    {
    public:
        DemonologyWarlockCcPvpStrategy(PlayerbotAI* ai) : DemonologyWarlockCcStrategy(ai) {}
        std::string getName() override { return "cc demonology pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockCcRaidStrategy : public DemonologyWarlockCcStrategy
    {
    public:
        DemonologyWarlockCcRaidStrategy(PlayerbotAI* ai) : DemonologyWarlockCcStrategy(ai) {}
        std::string getName() override { return "cc demonology raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士宠物策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockPetStrategy : public WarlockPetStrategy
    {
    public:
        DemonologyWarlockPetStrategy(PlayerbotAI* ai) : WarlockPetStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士宠物PVE策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockPetPveStrategy : public DemonologyWarlockPetStrategy
    {
    public:
        DemonologyWarlockPetPveStrategy(PlayerbotAI* ai) : DemonologyWarlockPetStrategy(ai) {}
        std::string getName() override { return "pet demonology pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士宠物PVP策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockPetPvpStrategy : public DemonologyWarlockPetStrategy
    {
    public:
        DemonologyWarlockPetPvpStrategy(PlayerbotAI* ai) : DemonologyWarlockPetStrategy(ai) {}
        std::string getName() override { return "pet demonology pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士宠物团队副本策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockPetRaidStrategy : public DemonologyWarlockPetStrategy
    {
    public:
        DemonologyWarlockPetRaidStrategy(PlayerbotAI* ai) : DemonologyWarlockPetStrategy(ai) {}
        std::string getName() override { return "pet demonology raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士诅咒策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockCursesStrategy : public WarlockCursesStrategy
    {
    public:
        DemonologyWarlockCursesStrategy(PlayerbotAI* ai) : WarlockCursesStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士诅咒PVE策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockCursesPveStrategy : public DemonologyWarlockCursesStrategy
    {
    public:
        DemonologyWarlockCursesPveStrategy(PlayerbotAI* ai) : DemonologyWarlockCursesStrategy(ai) {}
        std::string getName() override { return "curse demonology pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士诅咒PVP策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockCursesPvpStrategy : public DemonologyWarlockCursesStrategy
    {
    public:
        DemonologyWarlockCursesPvpStrategy(PlayerbotAI* ai) : DemonologyWarlockCursesStrategy(ai) {}
        std::string getName() override { return "curse demonology pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恶魔学识术士诅咒团队副本策略：定义该专精/场景下的触发器与默认行为
    class DemonologyWarlockCursesRaidStrategy : public DemonologyWarlockCursesStrategy
    {
    public:
        DemonologyWarlockCursesRaidStrategy(PlayerbotAI* ai) : DemonologyWarlockCursesStrategy(ai) {}
        std::string getName() override { return "curse demonology raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
