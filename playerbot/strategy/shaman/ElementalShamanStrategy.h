// 萨满祭司 - 元素萨满祭司策略头文件 (ElementalShamanStrategy.h)
#pragma once
#include "ShamanStrategy.h"

namespace ai
{
    // 元素萨满祭司专精占位策略：用于专精识别与占位的策略类
    class ElementalShamanPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        ElementalShamanPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_DPS | STRATEGY_TYPE_RANGED; }
        std::string getName() override { return "elemental"; }
    };

    // 元素萨满祭司策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanStrategy : public ShamanStrategy
    {
    public:
        ElementalShamanStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    // 元素萨满祭司PVE策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanPveStrategy : public ElementalShamanStrategy
    {
    public:
        ElementalShamanPveStrategy(PlayerbotAI* ai) : ElementalShamanStrategy(ai) {}
        std::string getName() override { return "elemental pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司PVP策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanPvpStrategy : public ElementalShamanStrategy
    {
    public:
        ElementalShamanPvpStrategy(PlayerbotAI* ai) : ElementalShamanStrategy(ai) {}
        std::string getName() override { return "elemental pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司团队副本策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanRaidStrategy : public ElementalShamanStrategy
    {
    public:
        ElementalShamanRaidStrategy(PlayerbotAI* ai) : ElementalShamanStrategy(ai) {}
        std::string getName() override { return "elemental raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司AOE群体策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanAoeStrategy : public ShamanAoeStrategy
    {
    public:
        ElementalShamanAoeStrategy(PlayerbotAI* ai) : ShamanAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司AOE群体PVE策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanAoePveStrategy : public ElementalShamanAoeStrategy
    {
    public:
        ElementalShamanAoePveStrategy(PlayerbotAI* ai) : ElementalShamanAoeStrategy(ai) {}
        std::string getName() override { return "aoe elemental pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司AOE群体PVP策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanAoePvpStrategy : public ElementalShamanAoeStrategy
    {
    public:
        ElementalShamanAoePvpStrategy(PlayerbotAI* ai) : ElementalShamanAoeStrategy(ai) {}
        std::string getName() override { return "aoe elemental pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司AOE群体团队副本策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanAoeRaidStrategy : public ElementalShamanAoeStrategy
    {
    public:
        ElementalShamanAoeRaidStrategy(PlayerbotAI* ai) : ElementalShamanAoeStrategy(ai) {}
        std::string getName() override { return "aoe elemental raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司控制(CC)策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanCcStrategy : public ShamanCcStrategy
    {
    public:
        ElementalShamanCcStrategy(PlayerbotAI* ai) : ShamanCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司控制(CC)PVE策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanCcPveStrategy : public ElementalShamanCcStrategy
    {
    public:
        ElementalShamanCcPveStrategy(PlayerbotAI* ai) : ElementalShamanCcStrategy(ai) {}
        std::string getName() override { return "cc elemental pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司控制(CC)PVP策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanCcPvpStrategy : public ElementalShamanCcStrategy
    {
    public:
        ElementalShamanCcPvpStrategy(PlayerbotAI* ai) : ElementalShamanCcStrategy(ai) {}
        std::string getName() override { return "cc elemental pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司控制(CC)团队副本策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanCcRaidStrategy : public ElementalShamanCcStrategy
    {
    public:
        ElementalShamanCcRaidStrategy(PlayerbotAI* ai) : ElementalShamanCcStrategy(ai) {}
        std::string getName() override { return "cc elemental raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司驱散净化策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanCureStrategy : public ShamanCureStrategy
    {
    public:
        ElementalShamanCureStrategy(PlayerbotAI* ai) : ShamanCureStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司驱散净化PVE策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanCurePveStrategy : public ElementalShamanCureStrategy
    {
    public:
        ElementalShamanCurePveStrategy(PlayerbotAI* ai) : ElementalShamanCureStrategy(ai) {}
        std::string getName() override { return "cure elemental pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司驱散净化PVP策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanCurePvpStrategy : public ElementalShamanCureStrategy
    {
    public:
        ElementalShamanCurePvpStrategy(PlayerbotAI* ai) : ElementalShamanCureStrategy(ai) {}
        std::string getName() override { return "cure elemental pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司驱散净化团队副本策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanCureRaidStrategy : public ElementalShamanCureStrategy
    {
    public:
        ElementalShamanCureRaidStrategy(PlayerbotAI* ai) : ElementalShamanCureStrategy(ai) {}
        std::string getName() override { return "cure elemental raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司图腾策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanTotemsStrategy : public ShamanTotemsStrategy
    {
    public:
        ElementalShamanTotemsStrategy(PlayerbotAI* ai) : ShamanTotemsStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司图腾PVE策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanTotemsPveStrategy : public ElementalShamanTotemsStrategy
    {
    public:
        ElementalShamanTotemsPveStrategy(PlayerbotAI* ai) : ElementalShamanTotemsStrategy(ai) {}
        std::string getName() override { return "totems elemental pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司图腾PVP策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanTotemsPvpStrategy : public ElementalShamanTotemsStrategy
    {
    public:
        ElementalShamanTotemsPvpStrategy(PlayerbotAI* ai) : ElementalShamanTotemsStrategy(ai) {}
        std::string getName() override { return "totems elemental pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司图腾团队副本策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanTotemsRaidStrategy : public ElementalShamanTotemsStrategy
    {
    public:
        ElementalShamanTotemsRaidStrategy(PlayerbotAI* ai) : ElementalShamanTotemsStrategy(ai) {}
        std::string getName() override { return "totems elemental raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司增益Buff策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanBuffStrategy : public ShamanBuffStrategy
    {
    public:
        ElementalShamanBuffStrategy(PlayerbotAI* ai) : ShamanBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司增益BuffPVE策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanBuffPveStrategy : public ElementalShamanBuffStrategy
    {
    public:
        ElementalShamanBuffPveStrategy(PlayerbotAI* ai) : ElementalShamanBuffStrategy(ai) {}
        std::string getName() override { return "buff elemental pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司增益BuffPVP策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanBuffPvpStrategy : public ElementalShamanBuffStrategy
    {
    public:
        ElementalShamanBuffPvpStrategy(PlayerbotAI* ai) : ElementalShamanBuffStrategy(ai) {}
        std::string getName() override { return "buff elemental pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司增益Buff团队副本策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanBuffRaidStrategy : public ElementalShamanBuffStrategy
    {
    public:
        ElementalShamanBuffRaidStrategy(PlayerbotAI* ai) : ElementalShamanBuffStrategy(ai) {}
        std::string getName() override { return "buff elemental raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司爆发增益策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanBoostStrategy : public ShamanBoostStrategy
    {
    public:
        ElementalShamanBoostStrategy(PlayerbotAI* ai) : ShamanBoostStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司爆发增益PVE策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanBoostPveStrategy : public ElementalShamanBoostStrategy
    {
    public:
        ElementalShamanBoostPveStrategy(PlayerbotAI* ai) : ElementalShamanBoostStrategy(ai) {}
        std::string getName() override { return "boost elemental pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司爆发增益PVP策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanBoostPvpStrategy : public ElementalShamanBoostStrategy
    {
    public:
        ElementalShamanBoostPvpStrategy(PlayerbotAI* ai) : ElementalShamanBoostStrategy(ai) {}
        std::string getName() override { return "boost elemental pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // 元素萨满祭司爆发增益团队副本策略：定义该专精/场景下的触发器与默认行为
    class ElementalShamanBoostRaidStrategy : public ElementalShamanBoostStrategy
    {
    public:
        ElementalShamanBoostRaidStrategy(PlayerbotAI* ai) : ElementalShamanBoostStrategy(ai) {}
        std::string getName() override { return "boost elemental raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
