/// RPG 城镇与NPC交互触发器定义
#pragma once
#include "playerbot/strategy/Trigger.h"

namespace ai
{
    /// 触发器：当前没有有效的 RPG 交互目标或目标超出两倍反应距离
    class NoRpgTargetTrigger : public Trigger
    {
    public:
        NoRpgTargetTrigger(PlayerbotAI* ai, std::string name = "no rpg target", int checkInterval = 10) : Trigger(ai, name, checkInterval) {}

        virtual bool IsActive() override { return !AI_VALUE(GuidPosition, "rpg target") || AI_VALUE2(float, "distance", "rpg target") > sPlayerbotAIConfig.reactDistance * 2; };
    };

    /// 触发器：存在有效的 RPG 交互目标且有具体待执行动作
    class HasRpgTargetTrigger : public NoRpgTargetTrigger
    {
    public:
        HasRpgTargetTrigger(PlayerbotAI* ai, std::string name = "has rpg target", int checkInterval = 2) : NoRpgTargetTrigger(ai, name, checkInterval) {}

        virtual bool IsActive() override { return !NoRpgTargetTrigger::IsActive() && AI_VALUE(std::string, "next rpg action") != "choose rpg target"; }; //Ingore rpg targets that only have the cancel action available. | 忽略仅包含取消动作的 RPG 目标
    };

    /// 触发器：距离当前 RPG 交互目标过远，需要移动接近
    class FarFromRpgTargetTrigger : public NoRpgTargetTrigger
    {
    public:
        FarFromRpgTargetTrigger(PlayerbotAI* ai, std::string name = "far from rpg target", int checkInterval = 1) : NoRpgTargetTrigger(ai, name, checkInterval) {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "far from rpg target"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpDescription() { return "This trigger activates [h:strategy|no rpg target] is not active and is 5y away from it's current [h:value|rpg target].";}
        virtual std::vector<std::string> GetUsedTriggers() { return { "no rpg target" }; }
        virtual std::vector<std::string> GetUsedValues() { return {"distance", "rpg target"}; }
#endif

        virtual bool IsActive() override { return !NoRpgTargetTrigger::IsActive() && AI_VALUE2(float, "distance", "rpg target") > maxDistance; };
    protected:
        float maxDistance = INTERACTION_DISTANCE;
    };

    /// 触发器：已靠近当前 RPG 交互目标（位于交互距离内）
    class NearRpgTargetTrigger : public FarFromRpgTargetTrigger
    {
    public:
        NearRpgTargetTrigger(PlayerbotAI* ai, std::string name = "near rpg target", int checkInterval = 1) : FarFromRpgTargetTrigger(ai, name, checkInterval) {}

        virtual bool IsActive() override { return !NoRpgTargetTrigger::IsActive() && !FarFromRpgTargetTrigger::IsActive(); };
    };

    //Sub actions: | 子交互动作触发器：
    /// 触发器基类：各类 RPG 子交互触发器的公共基类
    class RpgTrigger : public FarFromRpgTargetTrigger
    {
    public:
        RpgTrigger(PlayerbotAI* ai, std::string name = "rpg", int checkInterval = 2) : FarFromRpgTargetTrigger(ai, name, checkInterval) {}

        GuidPosition getGuidP() { return AI_VALUE(GuidPosition, "rpg target"); }

        virtual bool IsActive() override;
        virtual Event Check() override { if (!NoRpgTargetTrigger::IsActive() && (AI_VALUE(std::string, "next rpg action") == "choose rpg target" || !FarFromRpgTargetTrigger::IsActive())) return Trigger::Check(); return Event(); };
    };


    /// 触发器：随机游荡 RPG 交互（针对有真人主人的非队友玩家）
    class RpgWanderTrigger : public RpgTrigger
    {
    public:
        RpgWanderTrigger(PlayerbotAI* ai, std::string name = "rpg wander") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override { return ai->HasRealPlayerMaster() && (!bot->GetGroup() || !getGuidP().GetPlayer() || !bot->GetGroup()->IsMember(getGuidP())); };
    };

    /// 触发器：与飞行管理员对话搭乘鸟点航线
    class RpgTaxiTrigger : public RpgTrigger
    {
    public:
        RpgTaxiTrigger(PlayerbotAI* ai, std::string name = "rpg taxi") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：与飞行管理员对话解锁未知飞行点
    class RpgDiscoverTrigger : public RpgTrigger
    {
    public:
        RpgDiscoverTrigger(PlayerbotAI* ai, std::string name = "rpg discover") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：向任务发布者接取新任务
    class RpgStartQuestTrigger : public RpgTrigger
    {
    public:
        RpgStartQuestTrigger(PlayerbotAI* ai, std::string name = "rpg start quest") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：向任务交付NPC提交已完成任务
    class RpgEndQuestTrigger : public RpgTrigger
    {
    public:
        RpgEndQuestTrigger(PlayerbotAI* ai, std::string name = "rpg end quest") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：向NPC接取/提交可重复任务
    class RpgRepeatQuestTrigger : public RpgTrigger
    {
    public:
        RpgRepeatQuestTrigger(PlayerbotAI* ai, std::string name = "rpg repeat quest") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：从商人NPC购买有用物品
    class RpgBuyTrigger : public RpgTrigger
    {
    public:
        RpgBuyTrigger(PlayerbotAI* ai, std::string name = "rpg buy") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：向商人NPC出售背包物品
    class RpgSellTrigger : public RpgTrigger
    {
    public:
        RpgSellTrigger(PlayerbotAI* ai, std::string name = "rpg sell") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：在拍卖师处上架出售物品
    class RpgAHSellTrigger : public RpgTrigger
    {
    public:
        RpgAHSellTrigger(PlayerbotAI* ai, std::string name = "rpg ah sell") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：在拍卖师处竞拍或一口价购买物品
    class RpgAHBuyTrigger : public RpgTrigger
    {
    public:
        RpgAHBuyTrigger(PlayerbotAI* ai, std::string name = "rpg ah buy") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：从邮箱收取邮件与附件
    class RpgGetMailTrigger : public RpgTrigger
    {
    public:
        RpgGetMailTrigger(PlayerbotAI* ai, std::string name = "rpg get mail") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：在修理商处修理装备耐久度
    class RpgRepairTrigger : public RpgTrigger
    {
    public:
        RpgRepairTrigger(PlayerbotAI* ai, std::string name = "rpg repair") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：向训练师学习新技能/法术/商业技能/骑术
    class RpgTrainTrigger : public RpgTrigger
    {
    public:
        RpgTrainTrigger(PlayerbotAI* ai, std::string name = "rpg train") : RpgTrigger(ai, name) {}

        static bool IsTrainerOf(CreatureInfo const* cInfo, Player* pPlayer);

        virtual bool IsActive() override;
    };

    /// 触发器：治疗受损的友方 NPC 或生物
    class RpgHealTrigger : public RpgTrigger
    {
    public:
        RpgHealTrigger(PlayerbotAI* ai, std::string name = "rpg heal") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：与旅店老板绑定炉石位置
    class RpgHomeBindTrigger : public RpgTrigger
    {
    public:
        RpgHomeBindTrigger(PlayerbotAI* ai, std::string name = "rpg home bind") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：与军官对话排队进入战场
    class RpgQueueBGTrigger : public RpgTrigger
    {
    public:
        RpgQueueBGTrigger(PlayerbotAI* ai, std::string name = "rpg queue bg") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：购买公会创建签名表
    class RpgBuyPetitionTrigger : public RpgTrigger
    {
    public:
        RpgBuyPetitionTrigger(PlayerbotAI* ai, std::string name = "rpg buy petition") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：交互使用场景中的可操作游戏对象（门、箱子、椅子等）
    class RpgUseTrigger : public RpgTrigger
    {
    public:
        RpgUseTrigger(PlayerbotAI* ai, std::string name = "rpg use") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：使用任务相关的游戏对象或对任务目标使用任务物品
    class RpgQuestUseTrigger : public RpgUseTrigger
    {
    public:
        RpgQuestUseTrigger(PlayerbotAI* ai, std::string name = "rpg quest use") : RpgUseTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：与附近玩家或AI机器人进行大语言模型（LLM）闲聊互动
    class RpgAIChatTrigger : public RpgTrigger
    {
    public:
        RpgAIChatTrigger(PlayerbotAI* ai, std::string name = "rpg ai chat") : RpgTrigger(ai, name, checkInterval = 1) {}
        virtual bool IsActive() override;
    };

    /// 触发器：闲暇时随机施放 RPG 娱乐法术
    class RpgSpellTrigger : public RpgTrigger
    {
    public:
        RpgSpellTrigger(PlayerbotAI* ai, std::string name = "rpg spell") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：在制造台/熔炉附近制作商业技能物品
    class RpgCraftTrigger : public RpgTrigger
    {
    public:
        RpgCraftTrigger(PlayerbotAI* ai, std::string name = "rpg craft") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：向友方玩家交易赠送有用物品
    class RpgTradeUsefulTrigger : public RpgTrigger
    {
    public:
        RpgTradeUsefulTrigger(PlayerbotAI* ai, std::string name = "rpg trade useful") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    protected:
        virtual bool isFriend(Player* player); //Move to value later. | 后续可迁移至 Value 系统
    };

    /// 触发器：为友方玩家装备提供附魔
    class RpgEnchantTrigger : public RpgTradeUsefulTrigger
    {
    public:
        RpgEnchantTrigger(PlayerbotAI* ai, std::string name = "rpg enchant") : RpgTradeUsefulTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：向附近玩家发起决斗邀请
    class RpgDuelTrigger : public RpgTrigger
    {
    public:
        RpgDuelTrigger(PlayerbotAI* ai, std::string name = "rpg duel") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：对 RPG 目标使用背包中的任务物品
    class RpgItemTrigger : public RpgTrigger
    {
    public:
        RpgItemTrigger(PlayerbotAI* ai, std::string name = "rpg item") : RpgTrigger(ai, name) { maxDistance = INTERACTION_DISTANCE * 2; }
        virtual bool IsActive() override;
    };

    /// 触发器：对支持 SpellClick 的生物/载具执行点击法术交互
    class RpgSpellClickTrigger : public RpgTrigger
    {
    public:
        RpgSpellClickTrigger(PlayerbotAI* ai, std::string name = "rpg spell click") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：与 NPC 进行闲聊菜单（Gossip）对话
    class RpgGossipTalkTrigger : public RpgTrigger
    {
    public:
        RpgGossipTalkTrigger(PlayerbotAI* ai, std::string name = "rpg gossip talk") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：附近有玩家时随机跳跃
    class RandomJumpTrigger : public Trigger
    {
    public:
        RandomJumpTrigger(PlayerbotAI* ai, std::string name = "random jump") : Trigger(ai, name, 2) {}
        bool IsActive() override;
    };

    /// 触发器：向银行职员存入物品
    class RpgBankDepositTrigger : public RpgTrigger
    {
    public:
        RpgBankDepositTrigger(PlayerbotAI* ai, std::string name = "rpg bank deposit") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：从银行职员取出物品
    class RpgBankWithdrawTrigger : public RpgTrigger
    {
    public:
        RpgBankWithdrawTrigger(PlayerbotAI* ai, std::string name = "rpg bank withdraw") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

#ifndef MANGOSBOT_ZERO
    /// 触发器：向公会银行存入物品
    class RpgGuildBankDepositTrigger : public RpgTrigger
    {
    public:
        RpgGuildBankDepositTrigger(PlayerbotAI* ai, std::string name = "rpg guild bank deposit") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };

    /// 触发器：从公会银行取出物品
    class RpgGuildBankWithdrawTrigger : public RpgTrigger
    {
    public:
        RpgGuildBankWithdrawTrigger(PlayerbotAI* ai, std::string name = "rpg guild bank withdraw") : RpgTrigger(ai, name) {}
        virtual bool IsActive() override;
    };
#endif
}
