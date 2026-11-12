// 萨满祭司 - 恢复萨满祭司策略头文件 (RestorationShamanStrategy.h)
#pragma once
#include "ShamanStrategy.h"

namespace ai
{
    // 恢复萨满祭司专精占位策略：用于专精识别与占位的策略类
    class RestorationShamanPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        RestorationShamanPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_HEAL | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "restoration"; }
    };

    // 恢复萨满祭司策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanStrategy : public ShamanStrategy
    {
    public:
        RestorationShamanStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司PVE策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanPveStrategy : public RestorationShamanStrategy
    {
    public:
        RestorationShamanPveStrategy(PlayerbotAI* ai) : RestorationShamanStrategy(ai) {}
        std::string getName() override { return "restoration pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司PVP策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanPvpStrategy : public RestorationShamanStrategy
    {
    public:
        RestorationShamanPvpStrategy(PlayerbotAI* ai) : RestorationShamanStrategy(ai) {}
        std::string getName() override { return "restoration pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司团队副本策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanRaidStrategy : public RestorationShamanStrategy
    {
    public:
        RestorationShamanRaidStrategy(PlayerbotAI* ai) : RestorationShamanStrategy(ai) {}
        std::string getName() override { return "restoration raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司AOE群体策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanAoeStrategy : public ShamanAoeStrategy
    {
    public:
        RestorationShamanAoeStrategy(PlayerbotAI* ai) : ShamanAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanAoePveStrategy : public RestorationShamanAoeStrategy
    {
    public:
        RestorationShamanAoePveStrategy(PlayerbotAI* ai) : RestorationShamanAoeStrategy(ai) {}
        std::string getName() override { return "aoe restoration pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanAoePvpStrategy : public RestorationShamanAoeStrategy
    {
    public:
        RestorationShamanAoePvpStrategy(PlayerbotAI* ai) : RestorationShamanAoeStrategy(ai) {}
        std::string getName() override { return "aoe restoration pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanAoeRaidStrategy : public RestorationShamanAoeStrategy
    {
    public:
        RestorationShamanAoeRaidStrategy(PlayerbotAI* ai) : RestorationShamanAoeStrategy(ai) {}
        std::string getName() override { return "aoe restoration raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanCcStrategy : public ShamanCcStrategy
    {
    public:
        RestorationShamanCcStrategy(PlayerbotAI* ai) : ShamanCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanCcPveStrategy : public RestorationShamanCcStrategy
    {
    public:
        RestorationShamanCcPveStrategy(PlayerbotAI* ai) : RestorationShamanCcStrategy(ai) {}
        std::string getName() override { return "cc restoration pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanCcPvpStrategy : public RestorationShamanCcStrategy
    {
    public:
        RestorationShamanCcPvpStrategy(PlayerbotAI* ai) : RestorationShamanCcStrategy(ai) {}
        std::string getName() override { return "cc restoration pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanCcRaidStrategy : public RestorationShamanCcStrategy
    {
    public:
        RestorationShamanCcRaidStrategy(PlayerbotAI* ai) : RestorationShamanCcStrategy(ai) {}
        std::string getName() override { return "cc restoration raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司驱散净化策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanCureStrategy : public ShamanCureStrategy
    {
    public:
        RestorationShamanCureStrategy(PlayerbotAI* ai) : ShamanCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanCurePveStrategy : public RestorationShamanCureStrategy
    {
    public:
        RestorationShamanCurePveStrategy(PlayerbotAI* ai) : RestorationShamanCureStrategy(ai) {}
        std::string getName() override { return "cure restoration pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanCurePvpStrategy : public RestorationShamanCureStrategy
    {
    public:
        RestorationShamanCurePvpStrategy(PlayerbotAI* ai) : RestorationShamanCureStrategy(ai) {}
        std::string getName() override { return "cure restoration pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanCureRaidStrategy : public RestorationShamanCureStrategy
    {
    public:
        RestorationShamanCureRaidStrategy(PlayerbotAI* ai) : RestorationShamanCureStrategy(ai) {}
        std::string getName() override { return "cure restoration raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司图腾策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanTotemsStrategy : public ShamanTotemsStrategy
    {
    public:
        RestorationShamanTotemsStrategy(PlayerbotAI* ai) : ShamanTotemsStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司图腾PVE策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanTotemsPveStrategy : public RestorationShamanTotemsStrategy
    {
    public:
        RestorationShamanTotemsPveStrategy(PlayerbotAI* ai) : RestorationShamanTotemsStrategy(ai) {}
        std::string getName() override { return "totems restoration pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司图腾PVP策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanTotemsPvpStrategy : public RestorationShamanTotemsStrategy
    {
    public:
        RestorationShamanTotemsPvpStrategy(PlayerbotAI* ai) : RestorationShamanTotemsStrategy(ai) {}
        std::string getName() override { return "totems restoration pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司图腾团队副本策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanTotemsRaidStrategy : public RestorationShamanTotemsStrategy
    {
    public:
        RestorationShamanTotemsRaidStrategy(PlayerbotAI* ai) : RestorationShamanTotemsStrategy(ai) {}
        std::string getName() override { return "totems restoration raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司增益Buff策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanBuffStrategy : public ShamanBuffStrategy
    {
    public:
        RestorationShamanBuffStrategy(PlayerbotAI* ai) : ShamanBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanBuffPveStrategy : public RestorationShamanBuffStrategy
    {
    public:
        RestorationShamanBuffPveStrategy(PlayerbotAI* ai) : RestorationShamanBuffStrategy(ai) {}
        std::string getName() override { return "buff restoration pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanBuffPvpStrategy : public RestorationShamanBuffStrategy
    {
    public:
        RestorationShamanBuffPvpStrategy(PlayerbotAI* ai) : RestorationShamanBuffStrategy(ai) {}
        std::string getName() override { return "buff restoration pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanBuffRaidStrategy : public RestorationShamanBuffStrategy
    {
    public:
        RestorationShamanBuffRaidStrategy(PlayerbotAI* ai) : RestorationShamanBuffStrategy(ai) {}
        std::string getName() override { return "buff restoration raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司爆发增益策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanBoostStrategy : public ShamanBoostStrategy
    {
    public:
        RestorationShamanBoostStrategy(PlayerbotAI* ai) : ShamanBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanBoostPveStrategy : public RestorationShamanBoostStrategy
    {
    public:
        RestorationShamanBoostPveStrategy(PlayerbotAI* ai) : RestorationShamanBoostStrategy(ai) {}
        std::string getName() override { return "boost restoration pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanBoostPvpStrategy : public RestorationShamanBoostStrategy
    {
    public:
        RestorationShamanBoostPvpStrategy(PlayerbotAI* ai) : RestorationShamanBoostStrategy(ai) {}
        std::string getName() override { return "boost restoration pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 恢复萨满祭司爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class RestorationShamanBoostRaidStrategy : public RestorationShamanBoostStrategy
    {
    public:
        RestorationShamanBoostRaidStrategy(PlayerbotAI* ai) : RestorationShamanBoostStrategy(ai) {}
        std::string getName() override { return "boost restoration raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
