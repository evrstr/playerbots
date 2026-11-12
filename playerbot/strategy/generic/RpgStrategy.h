/// RPG 城镇拟真交互策略族头文件
#pragma once
#include "playerbot/strategy/Multiplier.h"
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 乘数：协调当前选定的 RPG 子动作与取消动作之间的执行权重
    class RpgActionMultiplier : public Multiplier
    {
    public:
        RpgActionMultiplier(PlayerbotAI* ai) : Multiplier(ai, "rpg action") {}

    public:
        virtual float GetValue(Action* action) override;
    };

    /// 策略：RPG 总控策略，驱动机器人在城镇中选择 NPC 移动并协调各类拟真交互
    class RpgStrategy : public Strategy
    {
    public:
        RpgStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual std::string getName() override { return "rpg"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "rpg"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy makes bot move between npcs to automatically do various interaction.\n"
            "This is the main rpg strategy which make bots pickand move to various rpg targets.\n"
            "The interactions included in this strategy are limited to emotesand wait.";            
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return {"rpg quest", "rpg vendor", "rpg explore", "rpg maintenance", "rpg guild", "rpg bg", "rpg player", "rpg craft", "debug rpg"}; }
#endif
    protected:
        virtual void OnStrategyAdded(BotState state) override;
        virtual void OnStrategyRemoved(BotState state) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*> &triggers) override;
        virtual void InitNonCombatMultipliers(std::list<Multiplier*>& multipliers) override;
    };

    /// 策略：RPG 任务交互子策略（接取、交付与可重复任务）
    class RpgQuestStrategy : public Strategy
    {
    public:
        RpgQuestStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "rpg quest"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "rpg quest"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy makes bot move to npcs that have quests the bot can pick up or hand in.\n"
                "Bots will only pick up quests that give xp unless low on durability.\n"
                "Bots will also try to do repeatable quests.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "rpg" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：RPG 商人/拍卖/邮箱子策略
    class RpgVendorStrategy : public Strategy
    {
    public:
        RpgVendorStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "rpg vendor"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "rpg vendor"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy makes bot move to vendors, auctionhouses and mail-boxes.\n"
                "Bots will buy and sell items depending on usage see [h:action|query item usage].\n"
                "Bots will pick up their mail if there is any items or gold attached.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "rpg" }; }
#endif
    private:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：RPG 探索与交通子策略（旅店绑定与飞行点探索搭乘）
    class RpgExploreStrategy : public Strategy
    {
    public:
        RpgExploreStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "rpg explore"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "rpg explore"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy makes bot move to innkeepers and flight masters.\n"
                "Bots will make this inn their new home when their current home is far away.\n"
                "Bots pick a random flight (when not with a player) or discover new flightpaths.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "rpg" }; }
#endif
    private:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：RPG 角色维护子策略（修理装备与学习技能）
    class RpgMaintenanceStrategy : public Strategy
    {
    public:
        RpgMaintenanceStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "rpg maintenance"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "rpg maintenance"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy makes bot move to trainers and armorers.\n"
                "Bots will automatically train new spells or skills that are available.\n"
                "Bots will automatically repair their armor when below 80% durability.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "rpg" }; }
#endif
    private:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：RPG 公会交互子策略（买签名表与公会银行存取）
    class RpgGuildStrategy : public Strategy
    {
    public:
        RpgGuildStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "rpg guild"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "rpg guild"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy makes bot move to guild master npcs and guild banks.\n"
                "Bots will automatically buy a petition if they are not already in a guild.\n"
                "Bots will deposit surplus items to guild bank and withdraw useful items.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "rpg" }; }
#endif
    private:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：RPG 银行存取子策略
    class RpgBankStrategy : public Strategy
    {
    public:
        RpgBankStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "rpg bank"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "rpg bank"; }
        virtual std::string GetHelpDescription() {
            return "This strategy makes bot move to bankers.\n"
                "Bots will deposit items they can use later (higher level equip, crafting materials).\n"
                "Bots will withdraw items when they become useful (level requirement met, crafting ready).";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "rpg" }; }
#endif
    private:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：RPG 战场排队子策略
    class RpgBgStrategy : public Strategy
    {
    public:
        RpgBgStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "rpg bg"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "rpg bg"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy makes bot move to battlemasters.\n"
                "Bots will automatically queue for battlegrounds.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "rpg" }; }
#endif
    private:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：RPG 玩家社交互动子策略（赠送装备、附魔与决斗）
    class RpgPlayerStrategy : public Strategy
    {
    public:
        RpgPlayerStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "rpg player"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "rpg player"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy makes bot move to nearby players.\n"
                "Bots will automatically trade other bots items they don't need but the other bot can use.\n"
                "Bots will automatically start duels with other players 3 levels above and 10 levels below them.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "rpg" }; }
#endif
    private:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：RPG 专业制造与娱乐施法子策略
    class RpgCraftStrategy : public Strategy
    {
    public:
        RpgCraftStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "rpg craft"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "rpg craft"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy makes bot move to nearby objects, players, npcs.\n"
                "Bots will automatically craft items they think are usefull or will give them skill points.\n"
                "Bots will automatically cast random spells on or near players or npcs.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "rpg" }; }
#endif
    private:
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    /// 策略：RPG 闲暇随机跳跃策略
    class RpgJumpStrategy : public Strategy
    {
    public:
        RpgJumpStrategy(PlayerbotAI* ai) : Strategy(ai) {};
        std::string getName() override { return "rpg jump"; }
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "rpg jump"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy makes bot jump randomly.\n"
                "Chances of jumps forward, in place, backward depend on config.\n";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "rpg" }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
    };
}