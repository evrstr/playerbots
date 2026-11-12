/// 近战战斗、绕背与追击跳跃策略头文件
#include "CombatStrategy.h"
#include "playerbot/strategy/generic/CombatStrategy.h"
#pragma once

namespace ai
{
    /// 策略：近战战斗走位策略（自动贴近至近战攻击范围并避免与目标重叠）
    class MeleeCombatStrategy : public CombatStrategy
    {
    public:
        MeleeCombatStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}
        
        virtual int GetType() override { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_MELEE; }
        virtual std::string getName() override { return "close"; }

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：近战自动绕至敌人背后攻击
    class SetBehindCombatStrategy : public CombatStrategy
    {
    public:
        SetBehindCombatStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}
        std::string getName() override { return "behind"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };

    /// 策略：追击无法立即触及的敌人时进行跳跃移动
    class ChaseJumpStrategy : public Strategy
    {
    public:
        ChaseJumpStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "chase jump"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "chase jump"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy makes bot jump when chasing enemies they can't reach.\n";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "melee" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
