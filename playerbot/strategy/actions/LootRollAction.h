#pragma once
#include "QueryItemUsageAction.h"
#include "LootAction.h"
#include "GenericActions.h"

namespace ai
{
    /// 发起掷骰动作：向队伍发起战利品分配掷骰或查询
    class LootStartRollAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化发起掷骰动作
        LootStartRollAction(PlayerbotAI* ai, std::string name = "loot start roll") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（发起掷骰动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（发起掷骰动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "loot start roll"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This is a WorldPacket action which will stores rollable item to be rolled on later.\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return { "active rolls" }; }
#endif 
    };

    /// 掷骰基类动作：评估战利品需求并执行需求/贪婪/放弃掷骰
    class RollAction : public QueryItemUsageAction 
    {
    public:
        /// 构造函数：初始化掷骰基类动作
        RollAction(PlayerbotAI* ai, std::string name = "roll") : QueryItemUsageAction(ai, name) {}
        /// 执行动作主逻辑（掷骰基类动作）
        virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "roll"; } // Must equal internal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This will make the bot roll a certain way on a specific item.\n"
                "Usage: roll <roll type> [itemlink].\n"
                "Types are need, greed, pass, emote and auto.\n"
                "When no itemlink is provided bots will roll on all current rollable loot.\n"
                "Examples:\n"
                "roll greed [item]\n"
                "roll auto\n"
                "See also strategies [h:strategy|roll] and [h:strategy|delayed roll].\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return { "item usage", "force item usage"}; }
#endif 

    protected:
        /// 根据掷骰物品 GUID 获取对应的物品实例或原型
        virtual ItemQualifier GetRollItem(ObjectGuid lootGuid, uint32 slot);
        /// 根据物品对自身的提升与用途计算掷骰方式（需求/贪婪/放弃）
        virtual RollVote CalculateRollVote(ItemQualifier& itemQualifier);
        /// 向服务端发送指定战利品槽位的掷骰选择封包
        virtual bool RollOnItemInSlot(RollVote type, ObjectGuid lootGuid, uint32 slot);
    };

    /// 战利品掷骰动作：响应服务端战利品掷骰请求并自动选择投点方式
    class LootRollAction : public RollAction 
    {
    public:
        /// 构造函数：初始化战利品掷骰动作
        LootRollAction(PlayerbotAI* ai, std::string name = "loot roll") : RollAction(ai, name) {}
        /// 执行动作主逻辑（战利品掷骰动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（战利品掷骰动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "loot roll"; } // Must equal internal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This action will make the bot roll on an item the master just rolled on.\n"
                "The type of roll will be automatically determined based on if the bot finds the item useful.";
        }
        virtual std::vector<std::string> GetUsedActions() { return { "roll" }; }
        virtual std::vector<std::string> GetUsedValues() { return { "item usage", "force item usage" }; }
#endif 
    };

    /// 自动战利品掷骰动作：对无需人工干预的掉落物品自动完成掷骰
    class AutoLootRollAction : public RollAction 
    {
    public:
        /// 构造函数：初始化自动战利品掷骰动作
        AutoLootRollAction(PlayerbotAI* ai, std::string name = "auto loot roll") : RollAction(ai, name) {}
        /// 执行动作主逻辑（自动战利品掷骰动作）
        virtual bool Execute(Event& event) override;
        /// 判断执行该动作的前置条件是否满足（自动战利品掷骰动作）
        virtual bool isPossible() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "auto loot roll"; } // Must equal internal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This action will make the bot roll on one item that it hasn't rolled for yet.\n"
                "The type of roll will be automatically determined based on if the bot finds the item useful.";
        }
        virtual std::vector<std::string> GetUsedActions() { return { "roll" }; }
        virtual std::vector<std::string> GetUsedValues() { return { "item usage", "force item usage" }; }
#endif 
    };
}
