#pragma once
#include "ChooseTravelTargetAction.h"
#include "playerbot/strategy/values/BudgetValues.h"
#include "playerbot/ServerFacade.h"

namespace ai
{
    class TravelTarget;

    /// 购买公会创建登记表动作：前往公会注册员处购买公会登记表
    class BuyPetitionAction : public Action 
    {
    public:
        /// 构造函数：初始化购买公会创建登记表动作
        BuyPetitionAction(PlayerbotAI* ai) : Action(ai, "buy petition") {}
        /// 执行动作主逻辑（购买公会创建登记表动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（购买公会创建登记表动作）
        virtual bool isUseful() override;
        /// 检查是否满足购买公会创建登记表的金币与身份条件
        static bool canBuyPetition(Player* bot);
    };

    /// 征集公会签名动作：向目标玩家发送公会登记表请求签名
    class PetitionOfferAction : public Action 
    {
    public:
        /// 构造函数：初始化征集公会签名动作
        PetitionOfferAction(PlayerbotAI* ai, std::string name = "petition offer") : Action(ai, name) {}
        /// 执行动作主逻辑（征集公会签名动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（征集公会签名动作）
        virtual bool isUseful() override { return sPlayerbotAIConfig.randomBotFormGuild && !bot->GetGuildId(); };
    };

    /// 向附近玩家征集签名动作：自动向周围未加入公会的玩家请求公会签名
    class PetitionOfferNearbyAction : public PetitionOfferAction 
    {
    public:
        /// 构造函数：初始化向附近玩家征集签名动作
        PetitionOfferNearbyAction(PlayerbotAI* ai) : PetitionOfferAction(ai, "petition offer nearby") {}
        /// 执行动作主逻辑（向附近玩家征集签名动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（向附近玩家征集签名动作）
        virtual bool isUseful() override { return sPlayerbotAIConfig.randomBotFormGuild && !bot->GetGuildId() && AI_VALUE2(uint32, "item count", chat->formatQItem(5863)) && AI_VALUE(uint8, "petition signs") < sWorld.getConfig(CONFIG_UINT32_MIN_PETITION_SIGNS); };
    };

    /// 提交公会登记表动作：收集齐足够签名后返回公会注册员处正式创建公会
    class PetitionTurnInAction : public ChooseTravelTargetAction 
    {
    public:
        /// 构造函数：初始化提交公会登记表动作
        PetitionTurnInAction(PlayerbotAI* ai) : ChooseTravelTargetAction(ai, "turn in petition") {}
        /// 执行动作主逻辑（提交公会登记表动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（提交公会登记表动作）
        virtual bool isUseful() override;
    };

    /// 购买公会战袍动作：前往战袍商人处购买公会战袍并穿戴
    class BuyTabardAction : public ChooseTravelTargetAction 
    {
    public:
        /// 构造函数：初始化购买公会战袍动作
        BuyTabardAction(PlayerbotAI* ai) : ChooseTravelTargetAction(ai, "buy tabard") {}
        /// 执行动作主逻辑（购买公会战袍动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（购买公会战袍动作）
        virtual bool isUseful() override;
    };
}
