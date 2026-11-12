/// 通用职业基础策略、子模块（AoE/驱散/控场/增益/爆发/潜行/副奶/副输出）及占位策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    // Generic strategy to be used for all class rotations | 用于所有职业战斗循环的通用基类策略
    /// 策略：通用职业基类策略（所有职业输出/治疗循环公共框架）
    class ClassStrategy : public Strategy
    {
    public:
        ClassStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*> &triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode *>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode *>& triggers) override;
    };

    /// 通用职业 PvP 模式公共触发器接口
    class ClassPvpStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 通用职业 PvE 模式公共触发器接口
    class ClassPveStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 通用职业团队副本（Raid）模式公共触发器接口
    class ClassRaidStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitReactionTriggers(std::list<TriggerNode*>& triggers);
        static void InitDeadTriggers(std::list<TriggerNode*>& triggers);
    };

    // Generic strategy to be used for all class aoe rotations | 用于所有职业群体伤害循环的通用基类策略
    /// 策略：通用群体伤害（AoE）策略基类
    class AoeStrategy : public Strategy
    {
    public:
        AoeStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// AoE 策略 PvP 模式接口
    class AoePvpStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// AoE 策略 PvE 模式接口
    class AoePveStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// AoE 策略团队副本模式接口
    class AoeRaidStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // Generic strategy to be used for all class cure rotations | 用于所有职业驱散循环的通用基类策略
    /// 策略：通用驱散（Cure）策略基类
    class CureStrategy : public Strategy
    {
    public:
        CureStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 驱散策略 PvP 模式接口
    class CurePvpStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 驱散策略 PvE 模式接口
    class CurePveStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 驱散策略团队副本模式接口
    class CureRaidStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // Generic strategy to be used for all class cc rotations | 用于所有职业控制技能循环的通用基类策略
    /// 策略：通用控制（CC）策略基类
    class CcStrategy : public Strategy
    {
    public:
        CcStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 控制策略 PvP 模式接口
    class CcPvpStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 控制策略 PvE 模式接口
    class CcPveStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 控制策略团队副本模式接口
    class CcRaidStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // Generic strategy to be used for all class buff rotations | 用于所有职业增益循环的通用基类策略
    /// 策略：通用增益（Buff）策略基类
    class BuffStrategy : public Strategy
    {
    public:
        BuffStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 增益策略 PvP 模式接口
    class BuffPvpStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 增益策略 PvE 模式接口
    class BuffPveStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 增益策略团队副本模式接口
    class BuffRaidStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // Generic strategy to be used for all class boost CDs rotations | 用于所有职业冷却爆发循环的通用基类策略
    /// 策略：通用长冷却爆发（Boost）策略基类
    class BoostStrategy : public Strategy
    {
    public:
        BoostStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 爆发策略 PvP 模式接口
    class BoostPvpStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 爆发策略 PvE 模式接口
    class BoostPveStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 爆发策略团队副本模式接口
    class BoostRaidStrategy
    {
    protected:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // Generic strategy to be used for stealth classes (druid and rogue) rotations | 用于德鲁伊与盗贼潜行循环的通用基类策略
    /// 策略：通用潜行（Stealth，德鲁伊/盗贼）策略基类
    class StealthStrategy : public Strategy
    {
    public:
        StealthStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 潜行策略 PvP 模式接口
    class StealthPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 潜行策略 PvE 模式接口
    class StealthPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 潜行策略团队副本模式接口
    class StealthRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // Generic strategy to be used for offheal spell rotations | 用于辅助治疗法术循环的通用基类策略
    /// 策略：通用辅助治疗（Offheal）策略基类
    class OffhealStrategy : public Strategy
    {
    public:
        OffhealStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 辅助治疗策略 PvP 模式接口
    class OffhealPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 辅助治疗策略 PvE 模式接口
    class OffhealPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 辅助治疗策略团队副本模式接口
    class OffhealRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // Generic strategy to be used for offdps spell rotations | 用于辅助输出法术循环的通用基类策略
    /// 策略：通用辅助输出（Offdps）策略基类
    class OffdpsStrategy : public Strategy
    {
    public:
        OffdpsStrategy(PlayerbotAI* ai) : Strategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 辅助输出策略 PvP 模式接口
    class OffdpsPvpStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 辅助输出策略 PvE 模式接口
    class OffdpsPveStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    /// 辅助输出策略团队副本模式接口
    class OffdpsRaidStrategy
    {
    public:
        static void InitCombatTriggers(std::list<TriggerNode*>& triggers);
        static void InitNonCombatTriggers(std::list<TriggerNode*>& triggers);
    };

    // Generic strategy to be used for white-listing what can be done during stealth (druid and rogue) | 用于控制潜行期间允许动作的白名单策略
    /// 策略：潜行状态白名单策略，标记处于潜行状态中允许执行的动作
    class StealthedStrategy : public Strategy
    {
    public:
        StealthedStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "stealthed"; }
    };

    // This is a strategy to be used only as a placeholder | 仅作为策略名占位的基类策略
    /// 策略：占位策略基类（仅用于策略名称占位与动态上下文切换）
    class PlaceholderStrategy : public Strategy
    {
    public:
        PlaceholderStrategy(PlayerbotAI* ai) : Strategy(ai) {}
    };

    // This strategy is used to hold the bot spec strategy | 用于托管机器人天赋专精切换的占位策略
    /// 策略：天赋专精占位策略，根据战斗场景自动切换 PvE / PvP / Raid 专精策略
    class SpecPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        SpecPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        int GetType() override = 0;

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    // This strategy is used to hold the aoe strategy | 用于占位托管 aoe 策略
    /// 策略：通用 AoE 占位策略
    class AoePlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        AoePlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "aoe"; }
    };

    // This strategy is used to hold the cure strategy | 用于占位托管 cure 策略
    /// 策略：通用驱散（cure）占位策略
    class CurePlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        CurePlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "cure"; }
    };

    // This strategy is used to hold the cc strategy | 用于占位托管 cc 策略
    /// 策略：通用控制（cc）占位策略
    class CcPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        CcPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "cc"; }
    };

    // This strategy is used to hold the buff strategy | 用于占位托管 buff 策略
    /// 策略：通用增益（buff）占位策略
    class BuffPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        BuffPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "buff"; }
    };

    // This strategy is used to hold the buff strategy | 用于占位托管 boost 策略
    /// 策略：通用爆发（boost）占位策略
    class BoostPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        BoostPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "boost"; }
    };

    // This strategy is used to hold the stealth strategy | 用于占位托管 stealth 策略
    /// 策略：通用潜行（stealth）占位策略
    class StealthPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        StealthPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "stealth"; }
    };

    // This strategy is used to hold the offheal strategy | 用于占位托管 offheal 策略
    /// 策略：通用辅助治疗（offheal）占位策略
    class OffhealPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        OffhealPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "offheal"; }
    };

    // This strategy is used to hold the offdps strategy | 用于占位托管 offdps 策略
    /// 策略：通用辅助输出（offdps）占位策略
    class OffdpsPlaceholderStrategy : public PlaceholderStrategy
    {
    public:
        OffdpsPlaceholderStrategy(PlayerbotAI* ai) : PlaceholderStrategy(ai) {}
        std::string getName() override { return "offdps"; }
    };
}