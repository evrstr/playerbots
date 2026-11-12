// 策略值头文件：MaintenanceValues（移动许可、修理/买卖/拍卖/收信条件、战斗准备度与吃喝判断）
#pragma once
#include "playerbot/strategy/Value.h"
#include "ItemUsageValue.h"
#include "BudgetValues.h"

namespace ai
{
    // 布尔值计算器：检查机器人是否未在交易、引导施法或等待队友，可自由移动执行非战斗任务
    class CanMoveAroundValue : public BoolCalculatedValue
    {
    public:
        CanMoveAroundValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can move around", 2) {}
        virtual bool Calculate() override
        {
            if (bot->GetTradeData())
                return false;

            if (!AI_VALUE(bool, "group ready"))
                return false;

            if (AI_VALUE2(bool, "trigger active", "castnc"))
                return false;

            if (ai->HasStrategy("wander", BotState::BOT_STATE_NON_COMBAT))
            {
                float dist = AI_VALUE2(float, "distance", "master target");
                bool wanderTooFar = dist > ai->GetRange("wandermax");

                if (wanderTooFar)
                    return false;
            }

            return true;
        }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "can move around"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "movement"; }
        virtual std::string GetHelpDescription() { return "This value indicates whether the bot should wait for a trade to complete, a crafting cast or for the group to have enough health/mana before moving to rpg, grind or travel targets."; }
        virtual std::vector<std::string> GetUsedValues() { return {"group ready", "trigger active"}; }
#endif 
    };

    // 布尔值计算器：判断距离炉石绑定点是否过远（超过 1000 码），需要重新绑定
    class ShouldHomeBindValue : public BoolCalculatedValue
    {
    public:
        ShouldHomeBindValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "should home bind", 2) {}
        virtual bool Calculate() override { return AI_VALUE2(float, "distance", "home bind") > 1000.0f; };
    };


    // 布尔值计算器：判断装备耐久度是否过低（平均低于 30% 或最低件低于 10%）需要修理
    class ShouldRepairValue : public BoolCalculatedValue
    {
    public:
        ShouldRepairValue(PlayerbotAI* ai) : BoolCalculatedValue(ai,"should repair",2) {}
        virtual bool Calculate() override { return AI_VALUE(uint8, "durability") < 30 || AI_VALUE(uint8, "lowest durability") < 10; };
    };

    // 布尔值计算器：判断是否具备修理条件（开启维护策略、存在受损且资金足够最低修理费）
    class CanRepairValue : public BoolCalculatedValue
    {
    public:
        CanRepairValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can repair",2) {}
        virtual bool Calculate() override { return  ai->HasStrategy("rpg maintenance", BotState::BOT_STATE_NON_COMBAT) && AI_VALUE(uint8, "durability inventory") < 100 && AI_VALUE(uint32, "min repair cost") < AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::repair); };
    };

    // 布尔值计算器：判断背包占用率是否超过 80% 需要清理出售
    class ShouldSellValue : public BoolCalculatedValue
    {
    public:
        ShouldSellValue(PlayerbotAI* ai, std::string name = "should sell", int checkInterval = 2) : BoolCalculatedValue(ai, name , checkInterval) {}
        virtual bool Calculate() override { return AI_VALUE(uint8, "bag space") > 80; };
    };

    // 布尔值计算器：判断是否开启商人策略且背包内存在可卖店的物品
    class CanSellValue : public BoolCalculatedValue
    {
    public:
        CanSellValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can sell",2) {}
        virtual bool Calculate() override { return ai->HasStrategy("rpg vendor", BotState::BOT_STATE_NON_COMBAT) && AI_VALUE2(uint32, "item count", "usage " + std::to_string((uint8)ItemUsage::ITEM_USAGE_VENDOR)) > 0; };
    };

    // 布尔值计算器：判断是否满足前往商人购买补给/弹药/装备/材料的前置条件
    class CanBuyValue : public BoolCalculatedValue
    {
    public:
        CanBuyValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can buy", 2) {}
        virtual bool Calculate() override { return ai->HasStrategy("rpg vendor", BotState::BOT_STATE_NON_COMBAT) && !AI_VALUE(bool, "should repair") && AI_VALUE(uint8, "bag space") < 90 && !AI_VALUE(bool, "can get mail") && (AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::ammo) || AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::consumables) || AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::gear) || AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::tradeskill)); };
    };

    // 布尔值计算器：判断背包是否拥挤或存在高修理费破损拍卖品，应尽快挂入拍卖行
    class ShouldAHSellValue : public ShouldSellValue
    {
    public:
        ShouldAHSellValue(PlayerbotAI* ai) : ShouldSellValue(ai, "should ah sell", 2) {}
        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断是否开启商人策略、有足够多拍卖品且携带足够保证金
    class CanAHSellValue : public BoolCalculatedValue
    {
    public:
        CanAHSellValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can ah sell", 2) {}
        virtual bool Calculate() override { return ai->HasStrategy("rpg vendor", BotState::BOT_STATE_NON_COMBAT) && AI_VALUE2(uint32, "item count", "usage " + std::to_string((uint8)ItemUsage::ITEM_USAGE_AH)) > 1 && AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::ah) > GetAuctionDeposit(); };

        uint32 GetAuctionDeposit()
        {
            float minDeposit = 0;
            for (auto item : AI_VALUE2(std::list<Item*>, "inventory items", "usage " + std::to_string((uint8)ItemUsage::ITEM_USAGE_AH)))
            {
                uint32 deposit = ItemUsageValue::GetAhDepositCost(item->GetProto(), item->GetCount());

                if (minDeposit == 0 || deposit < minDeposit)
                    minDeposit = deposit;
            }

            return minDeposit;
        }
    };

    // 布尔值计算器：判断是否具备前往拍卖行竞拍/采购物品的条件
    class CanAHBuyValue : public BoolCalculatedValue
    {
    public:
        CanAHBuyValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can ah buy", 2) {}
        virtual bool Calculate() override { return ai->HasStrategy("rpg vendor", BotState::BOT_STATE_NON_COMBAT) && !AI_VALUE(bool, "should repair") && !AI_VALUE(bool, "should sell") && !AI_VALUE(bool, "can get mail") && AI_VALUE2(uint32, "free money for", (uint32)NeedMoneyFor::ah) > 0; };
    };


    // 布尔值计算器：判断邮箱中是否存在满足领取条件的邮件
    class CanGetMailValue : public BoolCalculatedValue
    {
    public:
        CanGetMailValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can get mail", 2) {}
        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断邮件是否达到可收取时间阈值或含所需金币/公会拍卖物资
    class ShouldGetMailValue : public BoolCalculatedValue
    {
    public:
        ShouldGetMailValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "should get mail", 60) {}
        virtual bool Calculate() override;
    };

    // 布尔值计算器：判断装备耐久高于 20% 且无复活虚弱减益，可正常作战
    class CanFightEqualValue: public BoolCalculatedValue
    {
    public:
        CanFightEqualValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can fight equal",2) {}
        virtual bool Calculate() override { return AI_VALUE(uint8, "durability") > 20 && !ai->HasAura(SPELL_ID_PASSIVE_RESURRECTION_SICKNESS,bot); };
    };

    // 布尔值计算器：判断小队全体成员是否均就绪且跟随，适合挑战精英怪
    class CanFightEliteValue : public BoolCalculatedValue
    {
    public:
        CanFightEliteValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can fight elite", 2) {}
        virtual bool Calculate() override { return bot->GetGroup() && AI_VALUE2(bool, "group and", "can fight equal") && AI_VALUE2(bool, "group and", "following party") && !AI_VALUE2(bool, "group or", "should sell,can sell"); };
    };

    // 布尔值计算器：判断超过 3 人的队伍是否全员就绪，适合挑战首领
    class CanFightBossValue : public BoolCalculatedValue
    {
    public:
        CanFightBossValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "can fight boss", 2) {}
        virtual bool Calculate() override { return bot->GetGroup() && bot->GetGroup()->GetMembersCount() > 3 && AI_VALUE2(bool, "group and", "can fight equal") && AI_VALUE2(bool, "group and", "following party") && !AI_VALUE2(bool, "group or", "should sell,can sell"); };
    };        

    // 布尔值计算器：综合法力百分比与队友平均水平判断脱战后是否应当坐下喝水
    class ShouldDrinkValue : public BoolCalculatedValue
    {
    public:
        ShouldDrinkValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "should drink", 2) {}
        virtual bool Calculate() override
        {
            if (!bot->HasMana())
                return false;

            if (AI_VALUE2(uint8, "mana", "self target") >= 85)
                return false;

            Player* master = ai->GetMaster();
            if (!master)
                return true;

            if (!bot->GetGroup())
                return true;

            if (!(ai->HasStrategy("follow", BotState::BOT_STATE_NON_COMBAT) ||
                ai->HasStrategy("wander", BotState::BOT_STATE_NON_COMBAT)))
                return true;

            if (!bot->IsWithinDist(master, sPlayerbotAIConfig.EatDrinkMaxDistance))
                return true;

            if (!master->IsMoving())
                return true;

            float minDistance = sPlayerbotAIConfig.EatDrinkMinDistance;
            if (!bot->GetGroup()->IsRaidGroup())
                minDistance += sPlayerbotAIConfig.followDistance;
            else
                minDistance += sPlayerbotAIConfig.raidFollowDistance;
            
            if (bot->IsWithinDist(master, minDistance))
                return true;

            return false;
        }
    };

    // 布尔值计算器：综合生命百分比与队友平均水平判断脱战后是否应当坐下进食
    class ShouldEatValue : public BoolCalculatedValue
    {
    public:
        ShouldEatValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "should eat", 2) {}
        virtual bool Calculate() override
        {
            if (AI_VALUE2(uint8, "health", "self target") >= sPlayerbotAIConfig.lowHealth)
                return false;

            Player* master = ai->GetMaster();
            if (!master)
                return true;

            if (!bot->GetGroup())
                return true;

            if (!(ai->HasStrategy("follow", BotState::BOT_STATE_NON_COMBAT) ||
                ai->HasStrategy("wander", BotState::BOT_STATE_NON_COMBAT)))
                return true;

            if (!bot->IsWithinDist(master, sPlayerbotAIConfig.EatDrinkMaxDistance))
                return true;

            if (!master->IsMoving())
                return true;

            float minDistance = sPlayerbotAIConfig.EatDrinkMinDistance;
            if (!bot->GetGroup()->IsRaidGroup())
                minDistance += sPlayerbotAIConfig.followDistance;
            else
                minDistance += sPlayerbotAIConfig.raidFollowDistance;

            if (bot->IsWithinDist(master, minDistance))
                return true;

            return false;
        }
    };

    // 浮点值计算器：计算机器人本次喝水回蓝需要持续的时间
    class DrinkDurationValue : public FloatCalculatedValue
    {
    public:
        DrinkDurationValue(PlayerbotAI* ai) : FloatCalculatedValue(ai, "drink duration") {}
        virtual float Calculate() override
        {
            Player* master = ai->GetMaster();

            float mpMissingPct = 100.0f - bot->GetPowerPercent();
            float multiplier = bot->InBattleGround() ? 20000.0f : 27000.0f;
            float drinkDuration = multiplier * (mpMissingPct / 100.0f);

            if (!master)
                return drinkDuration;

            if (!bot->GetGroup())
                return drinkDuration;

            if (!(ai->HasStrategy("follow", BotState::BOT_STATE_NON_COMBAT) ||
                ai->HasStrategy("wander", BotState::BOT_STATE_NON_COMBAT)))
                return drinkDuration;

            float minDistance = sPlayerbotAIConfig.followDistance;

            if (bot->GetGroup()->IsRaidGroup())
                minDistance = sPlayerbotAIConfig.raidFollowDistance;

            if (!master->IsMoving())
                minDistance += sPlayerbotAIConfig.EatDrinkMinDistance;

            if (bot->IsWithinDist(master, minDistance))
                return drinkDuration;

            float masterOrientation = master->GetOrientation();
            float angleToBot = master->GetAngle(bot);
            float angleDiff = fabs(masterOrientation - angleToBot);

            if (angleDiff > M_PI / 2 && angleDiff < 3 * M_PI / 2)
            {
                drinkDuration *= 0.25f;
            }
            return drinkDuration;
        }
    };

    // 浮点值计算器：计算机器人本次进食回血需要持续的时间
    class EatDurationValue : public FloatCalculatedValue
    {
    public:
        EatDurationValue(PlayerbotAI* ai) : FloatCalculatedValue(ai, "eat duration") {}
        virtual float Calculate() override
        {
            Player* master = ai->GetMaster();

            float hpMissingPct = 100.0f - bot->GetHealthPercent();
            float multiplier = bot->InBattleGround() ? 20000.0f : 27000.0f;
            float eatDuration = multiplier * (hpMissingPct / 100.0f);
          
            if (!master)
                return eatDuration;

            if (!bot->GetGroup())
                return eatDuration;

            if (!(ai->HasStrategy("follow", BotState::BOT_STATE_NON_COMBAT) ||
                ai->HasStrategy("wander", BotState::BOT_STATE_NON_COMBAT)))
                return eatDuration;

            float minDistance = sPlayerbotAIConfig.followDistance;

            if (bot->GetGroup()->IsRaidGroup())
                minDistance = sPlayerbotAIConfig.raidFollowDistance;

            if (!master->IsMoving())
                minDistance += sPlayerbotAIConfig.EatDrinkMinDistance;

            if (bot->IsWithinDist(master, minDistance))
                return eatDuration;

            float masterOrientation = master->GetOrientation();
            float angleToBot = master->GetAngle(bot);
            float angleDiff = fabs(masterOrientation - angleToBot);

            if (angleDiff > M_PI / 2 && angleDiff < 3 * M_PI / 2)
            {
                eatDuration *= 0.25f;
            }
            return eatDuration;
        }
    };
}
