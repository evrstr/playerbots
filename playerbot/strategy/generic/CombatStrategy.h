/// 通用战斗与避险策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    // TO DO: Remove this class when no more dependencies | 待办：解除全部依赖后可移除此类
    /// 策略：基础通用战斗触发逻辑（目标切换、脱困、饰品等）
    class CombatStrategy : public Strategy
    {
    public:
        CombatStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_COMBAT; }

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：躲避地面 AoE 危险区域并打断自身读条
    class AvoidAoeStrategy : public Strategy
    {
    public:
        AvoidAoeStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "avoid aoe"; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "avoid aoe"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() 
        {
            return "This strategy will make bots move away when they are in aoe.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { }; }
#endif

    private:
        void InitCombatMultipliers(std::list<Multiplier*>& multipliers) override;
        void InitReactionMultipliers(std::list<Multiplier*>& multipliers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：远离指定避让列表中的危险生物
    class AvoidSpecificCreaturesStrategy : public Strategy
    {
    public:
        AvoidSpecificCreaturesStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "avoid specific creatures"; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "avoid specific creatures"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() 
        {
            return "This strategy will make bots move away from specific creatures.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { }; }
#endif

    private:
        void InitCombatMultipliers(std::list<Multiplier*>& multipliers) override;
        void InitReactionMultipliers(std::list<Multiplier*>& multipliers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 乘数：处于区域性持续伤害中时禁止施放有施法时间的法术
    class AvoidAoeStrategyMultiplier : public Multiplier
    {
    public:
        AvoidAoeStrategyMultiplier(PlayerbotAI* ai) : Multiplier(ai, "run away on area debuff") {}
        float GetValue(Action* action) override;
        
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "run away on area debuff"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This stops bots from casting certain (cast-time) spells when affected by an area debuf.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {}; }
#endif
    };

    /// 乘数：躲避特定生物策略动作权重调节
    class AvoidSpecificCreaturesStrategyMultiplier : public Multiplier
    {
    public:
        AvoidSpecificCreaturesStrategyMultiplier(PlayerbotAI* ai) : Multiplier(ai, "avoid specific creatures") {}
        float GetValue(Action* action) { return 1.0f; }
        
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "avoid specific creatures" } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This makes bots run away from specific creatures.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {}; }
#endif
    };

    /// 策略：与真人玩家组队时等待开怪/坦克建立仇恨后再全力输出
    class WaitForAttackStrategy : public Strategy
    {
    public:
        WaitForAttackStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        static WaitForAttackStrategy* Get(PlayerbotAI* ai);
        std::string getName() override { return "wait for attack"; }

        static bool ShouldWait(PlayerbotAI* ai);
        static uint8 GetWaitTime(PlayerbotAI* ai);
        static float GetSafeDistance() { return sPlayerbotAIConfig.fleeDistance; }
        static float GetSafeDistanceThreshold() { return 2.5f; }
        ReactStates GetPetReactState() const { return petReactState; }
        void SetPetReactState(ReactStates reactState) { petReactState = reactState; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "wait for attack"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make bots wait a specified time before attacking.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { }; }
#endif

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatMultipliers(std::list<Multiplier*>& multipliers) override;

    private:
        ReactStates petReactState;
    };

    /// 乘数：等待开怪期间抑制产生威胁值的攻击动作
    class WaitForAttackMultiplier : public Multiplier
    {
    public:
        WaitForAttackMultiplier(PlayerbotAI* ai) : Multiplier(ai, "wait for for attack") {}
        float GetValue(Action* action) override;
    };

    /// 策略：当治疗目标已满血时自动中断正在读条的治疗法术
    class HealInterruptStrategy : public Strategy
    {
    public:
        HealInterruptStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "heal interrupt"; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "heal interrupt"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription()
        {
            return "This strategy will make the bot interrupt the heal it currently casts if target is at full health";
        }
#endif

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：预治疗（Pre-heal），结合预期受到的近战伤害决定治疗时机
    class PreHealStrategy : public Strategy
    {
    public:
        PreHealStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "preheal"; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "preheal"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription()
        {
            return "This strategy will make the bot calculate melee damage of attacker when deciding how to heal target";
        }
#endif
    };
}
