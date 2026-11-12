#pragma once
#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 赠送物品动作：向队伍成员或主人交易/邮寄指定物品
    class GiveItemAction : public Action
    {
    public:
        /// 构造函数：初始化赠送物品动作
        GiveItemAction(PlayerbotAI* ai, std::string name, std::string item) : Action(ai, name), item(item) {}
        /// 执行动作主逻辑（赠送物品动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（赠送物品动作）
        virtual bool isUseful() override { return GetTarget() && AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.lowMana; }
        /// 获取当前动作的目标单位（赠送物品动作）
        virtual Unit* GetTarget() override;

    protected:
        std::string item;
    };

    /// 赠送食物动作：当队友缺少食物时主动交易提供食物
    class GiveFoodAction : public GiveItemAction
    {
    public:
        /// 构造函数：初始化赠送食物动作
        GiveFoodAction(PlayerbotAI* ai) : GiveItemAction(ai, "give food", "conjured food") {}
        /// 获取当前动作的目标单位（赠送食物动作）
        virtual Unit* GetTarget() override;
        /// 判断当前状态下该动作是否可用/有效（赠送食物动作）
        virtual bool isUseful() override
        {
            Unit* target = GetTarget();
            if (!target)
                return false;

            bool isBot = target->IsPlayer() && ((Player*)target)->GetPlayerbotAI();

            return !isBot || (isBot && !((Player*)target)->GetPlayerbotAI()->HasCheat(BotCheatMask::item));
        }
    };

    /// 赠送饮水动作：当法系队友缺水时主动交易提供魔法水或饮料
    class GiveWaterAction : public GiveItemAction
    {
    public:
        /// 构造函数：初始化赠送饮水动作
        GiveWaterAction(PlayerbotAI* ai) : GiveItemAction(ai, "give water", "conjured water") {}
        /// 获取当前动作的目标单位（赠送饮水动作）
        virtual Unit* GetTarget() override;
        /// 判断当前状态下该动作是否可用/有效（赠送饮水动作）
        virtual bool isUseful() override
        {
            Unit* target = GetTarget();
            if (!target)
                return false;

            bool isBot = target->IsPlayer() && ((Player*)target)->GetPlayerbotAI();

            return !isBot || (isBot && !((Player*)target)->GetPlayerbotAI()->HasCheat(BotCheatMask::item));
        }
    };
}
