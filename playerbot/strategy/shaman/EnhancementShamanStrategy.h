// 萨满祭司 - 增强萨满祭司策略头文件 (EnhancementShamanStrategy.h)
#pragma once
#include "ShamanStrategy.h"

namespace ai
{
    // 增强萨满祭司专精占位策略：用于专精识别与占位的策略类
    class EnhancementShamanPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        EnhancementShamanPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
        std::string getName() override { return "enhancement"; }
    };

    // 增强萨满祭司策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanStrategy : public ShamanStrategy
    {
    public:
        EnhancementShamanStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 增强萨满祭司PVE策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanPveStrategy : public EnhancementShamanStrategy
    {
    public:
        EnhancementShamanPveStrategy(PlayerbotAI* ai) : EnhancementShamanStrategy(ai) {}
        std::string getName() override { return "enhancement pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司PVP策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanPvpStrategy : public EnhancementShamanStrategy
    {
    public:
        EnhancementShamanPvpStrategy(PlayerbotAI* ai) : EnhancementShamanStrategy(ai) {}
        std::string getName() override { return "enhancement pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司团队副本策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanRaidStrategy : public EnhancementShamanStrategy
    {
    public:
        EnhancementShamanRaidStrategy(PlayerbotAI* ai) : EnhancementShamanStrategy(ai) {}
        std::string getName() override { return "enhancement raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司AOE群体策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanAoeStrategy : public ShamanAoeStrategy
    {
    public:
        EnhancementShamanAoeStrategy(PlayerbotAI* ai) : ShamanAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanAoePveStrategy : public EnhancementShamanAoeStrategy
    {
    public:
        EnhancementShamanAoePveStrategy(PlayerbotAI* ai) : EnhancementShamanAoeStrategy(ai) {}
        std::string getName() override { return "aoe enhancement pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanAoePvpStrategy : public EnhancementShamanAoeStrategy
    {
    public:
        EnhancementShamanAoePvpStrategy(PlayerbotAI* ai) : EnhancementShamanAoeStrategy(ai) {}
        std::string getName() override { return "aoe enhancement pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanAoeRaidStrategy : public EnhancementShamanAoeStrategy
    {
    public:
        EnhancementShamanAoeRaidStrategy(PlayerbotAI* ai) : EnhancementShamanAoeStrategy(ai) {}
        std::string getName() override { return "aoe enhancement raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanCcStrategy : public ShamanCcStrategy
    {
    public:
        EnhancementShamanCcStrategy(PlayerbotAI* ai) : ShamanCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanCcPveStrategy : public EnhancementShamanCcStrategy
    {
    public:
        EnhancementShamanCcPveStrategy(PlayerbotAI* ai) : EnhancementShamanCcStrategy(ai) {}
        std::string getName() override { return "cc enhancement pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanCcPvpStrategy : public EnhancementShamanCcStrategy
    {
    public:
        EnhancementShamanCcPvpStrategy(PlayerbotAI* ai) : EnhancementShamanCcStrategy(ai) {}
        std::string getName() override { return "cc enhancement pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanCcRaidStrategy : public EnhancementShamanCcStrategy
    {
    public:
        EnhancementShamanCcRaidStrategy(PlayerbotAI* ai) : EnhancementShamanCcStrategy(ai) {}
        std::string getName() override { return "cc enhancement raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司驱散净化策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanCureStrategy : public ShamanCureStrategy
    {
    public:
        EnhancementShamanCureStrategy(PlayerbotAI* ai) : ShamanCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanCurePveStrategy : public EnhancementShamanCureStrategy
    {
    public:
        EnhancementShamanCurePveStrategy(PlayerbotAI* ai) : EnhancementShamanCureStrategy(ai) {}
        std::string getName() override { return "cure enhancement pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanCurePvpStrategy : public EnhancementShamanCureStrategy
    {
    public:
        EnhancementShamanCurePvpStrategy(PlayerbotAI* ai) : EnhancementShamanCureStrategy(ai) {}
        std::string getName() override { return "cure enhancement pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanCureRaidStrategy : public EnhancementShamanCureStrategy
    {
    public:
        EnhancementShamanCureRaidStrategy(PlayerbotAI* ai) : EnhancementShamanCureStrategy(ai) {}
        std::string getName() override { return "cure enhancement raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司图腾策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanTotemsStrategy : public ShamanTotemsStrategy
    {
    public:
        EnhancementShamanTotemsStrategy(PlayerbotAI* ai) : ShamanTotemsStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司图腾PVE策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanTotemsPveStrategy : public EnhancementShamanTotemsStrategy
    {
    public:
        EnhancementShamanTotemsPveStrategy(PlayerbotAI* ai) : EnhancementShamanTotemsStrategy(ai) {}
        std::string getName() override { return "totems enhancement pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司图腾PVP策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanTotemsPvpStrategy : public EnhancementShamanTotemsStrategy
    {
    public:
        EnhancementShamanTotemsPvpStrategy(PlayerbotAI* ai) : EnhancementShamanTotemsStrategy(ai) {}
        std::string getName() override { return "totems enhancement pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司图腾团队副本策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanTotemsRaidStrategy : public EnhancementShamanTotemsStrategy
    {
    public:
        EnhancementShamanTotemsRaidStrategy(PlayerbotAI* ai) : EnhancementShamanTotemsStrategy(ai) {}
        std::string getName() override { return "totems enhancement raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司增益Buff策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanBuffStrategy : public ShamanBuffStrategy
    {
    public:
        EnhancementShamanBuffStrategy(PlayerbotAI* ai) : ShamanBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanBuffPveStrategy : public EnhancementShamanBuffStrategy
    {
    public:
        EnhancementShamanBuffPveStrategy(PlayerbotAI* ai) : EnhancementShamanBuffStrategy(ai) {}
        std::string getName() override { return "buff enhancement pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanBuffPvpStrategy : public EnhancementShamanBuffStrategy
    {
    public:
        EnhancementShamanBuffPvpStrategy(PlayerbotAI* ai) : EnhancementShamanBuffStrategy(ai) {}
        std::string getName() override { return "buff enhancement pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanBuffRaidStrategy : public EnhancementShamanBuffStrategy
    {
    public:
        EnhancementShamanBuffRaidStrategy(PlayerbotAI* ai) : EnhancementShamanBuffStrategy(ai) {}
        std::string getName() override { return "buff enhancement raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司爆发增益策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanBoostStrategy : public ShamanBoostStrategy
    {
    public:
        EnhancementShamanBoostStrategy(PlayerbotAI* ai) : ShamanBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanBoostPveStrategy : public EnhancementShamanBoostStrategy
    {
    public:
        EnhancementShamanBoostPveStrategy(PlayerbotAI* ai) : EnhancementShamanBoostStrategy(ai) {}
        std::string getName() override { return "boost enhancement pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanBoostPvpStrategy : public EnhancementShamanBoostStrategy
    {
    public:
        EnhancementShamanBoostPvpStrategy(PlayerbotAI* ai) : EnhancementShamanBoostStrategy(ai) {}
        std::string getName() override { return "boost enhancement pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 增强萨满祭司爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class EnhancementShamanBoostRaidStrategy : public EnhancementShamanBoostStrategy
    {
    public:
        EnhancementShamanBoostRaidStrategy(PlayerbotAI* ai) : EnhancementShamanBoostStrategy(ai) {}
        std::string getName() override { return "boost enhancement raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
