/// 通用非战斗、碰撞避让、坐骑、世界增益、雕文与钓鱼策略头文件
#pragma once
#include "PassTroughStrategy.h"

namespace ai
{
    // TO DO: Remove this when no dependencies are left | 待办：解除全部依赖后移除
    /// 策略：通用非战斗基础策略（坐骑状态、数值维护与黑暗之门移动）
    class NonCombatStrategy : public Strategy
    {
    public:
        NonCombatStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        std::string getName() override { return "nc"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "nc"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "Generic noncombat behavior strategy. Currently handles bots mounting and moves them for the dark portal event.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {}; }
#endif
    protected:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };

    /// 策略：碰撞分散策略，与其他机器人重叠时微微挪步散开
    class CollisionStrategy : public Strategy
    {
    public:
        CollisionStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        std::string getName() override { return "collision"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "collision"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy makes bots move away from other bots a little if they are touching.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {}; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };

    /// 策略：坐骑开关标志策略（控制机器人是否允许上马）
    class MountStrategy : public Strategy
    {
    public:
        MountStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        std::string getName() override { return "mount"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "mount"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This is a toggle strategy which tells bots if they are allowed to mount up or not.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {}; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：允许攻击已被非同队玩家先手开怪（灰名归属）的目标
    class AttackTaggedStrategy : public Strategy
    {
    public:
        AttackTaggedStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        std::string getName() override { return "attack tagged"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "attack tagged"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This is a toggle strategy which tells bots if they are allowed to attack mobs tagged by players (not in their group).";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {}; }
#endif
    };

    /// 策略：作弊自动补全预设世界增益（wbuff）
    class WorldBuffStrategy : public Strategy
    {
    public:
        WorldBuffStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        std::string getName() override { return "wbuff"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "wbuff"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This cheat strategy which automatically applies predefined worldbuffs to the bots if they don't have them.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {}; }
#endif
    protected:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void OnStrategyRemoved(BotState state) override;
    };

    /// 策略：静默模式（禁止机器人主动在频道说话刷屏）
    class SilentStrategy : public Strategy
    {
    public:
        SilentStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "silent"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "wbuff"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This cheat strategy which automatically applies predefined worldbuffs to the bots if they don't have them.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {}; }
#endif
    };

    /// 策略：自动解除阵营“处于交战状态”标志以防止误杀中立阵营
    class NoWarStrategy : public Strategy
    {
    public:
        NoWarStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "nowar"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "nowar"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This a toggle strategy that removes the 'at war' check for all factions from time to time.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {}; }
#endif
    protected:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：按预设配置自动学习与镶嵌职业雕文
    class GlyphStrategy : public Strategy
    {
    public:
        GlyphStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "glyph"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "glyph"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "Automatically applies the best glyphs based on the config.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {}; }
#endif
    protected:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：自动寻找附近水域执行钓鱼
    class FishStrategy : public Strategy
    {
    public:
        FishStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        virtual std::string getName() override { return "fish"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "fish"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "Automatically tries to fish in some water nearby.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {}; }
#endif
    protected:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        std::string modifier = "";
    };

    /// 策略：长途旅行途中的顺路钓鱼策略
    class TFishStrategy : public FishStrategy
    {
    public:
        TFishStrategy(PlayerbotAI* ai) : FishStrategy(ai) { modifier = "::travel"; }

        virtual std::string getName() override { return "tfish"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "tfish"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "Fishing during travel.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {}; }
#endif
    };
}
