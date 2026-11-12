/// 非战斗拾取、采集与掷骰策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 策略：非战斗状态下搜寻并拾取附近可拾取尸体或宝箱
    class LootNonCombatStrategy : public Strategy
    {
    public:
        LootNonCombatStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "loot"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "loot"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make bots look for, open and get items from nearby lootable objects.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "gather" }; }
#endif        
    public:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };

    /// 策略：自动扫描并记录附近的矿石/草药等商业技能采集点
    class GatherStrategy : public Strategy
    {
    public:
        GatherStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "gather"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "gather"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make bots look for and save nearby gathering nodes to loot later.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "reveal" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };

    /// 策略：响应 'get' 指令前往指定对象拾取/采集后返回跟随
    class FetchStrategy : public Strategy
    {
    public:
        FetchStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "fetch"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "fetch"; }
        virtual std::string GetHelpDescription() {
            return "This strategy is added by the 'get' command: the bot walks to the requested object, gathers or opens it and then follows its master again.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "loot", "follow" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };

    /// 策略：主动指出周围自身可开启的采集节点位置
    class RevealStrategy : public Strategy
    {
    public:
        RevealStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "reveal"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "reveal"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make bots point out nearby gathering nodes that they can open.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "gather" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
    };

    /// 策略：自动参与队伍战利品需求/贪婪/放弃掷骰
    class RollStrategy : public Strategy
    {
    public:
        RollStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "roll"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "roll"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make bots automatically roll on items.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "delayed roll"}; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：延迟掷骰（等待主人先选择 Roll 点后再跟进）
    class DelayedRollStrategy : public Strategy
    {
    public:
        DelayedRollStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        std::string getName() override { return "delayed roll"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "delayed roll"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will make bots roll on item after the master rolls..";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "roll" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}
