#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 摧毁物品指令动作：根据名称或物品链接销毁背包中的指定物品
    class DestroyItemAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化摧毁物品指令动作
        DestroyItemAction(PlayerbotAI* ai, std::string name = "destroy") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（摧毁物品指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（摧毁物品指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "destroy"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This command will make the bot destroy a certain item.\n"
                "Usage: destroy [itemlink]\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return { "force item usage" }; }
#endif

    protected:
        /// 销毁背包中指定的物品
        void DestroyItem(FindItemVisitor* visitor, Player* requester);
    };

    /// 智能清理背包动作：背包已满时自动销毁低价值灰色或冗余物品腾出空间
    class SmartDestroyItemAction : public DestroyItemAction 
    {
    public:
        /// 构造函数：初始化智能清理背包动作
        SmartDestroyItemAction(PlayerbotAI* ai) : DestroyItemAction(ai, "smart destroy item") {}
        /// 执行动作主逻辑（智能清理背包动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（智能清理背包动作）
        virtual bool isUseful() override { return !ai->HasActivePlayerMaster(); }
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（智能清理背包动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "smart destroy item"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This command will make the bot destroy a certain item.\n"
                "Usage: destroy [itemlink]\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {"destroy"}; }
        virtual std::vector<std::string> GetUsedValues() { return { "bag space", "force item usage" }; }
#endif
    };

    /// 一键销毁灰色物品动作：销毁背包内所有灰色品质垃圾物品
    class DestroyAllGrayItemsAction : public DestroyItemAction
    {
    public:
        /// 构造函数：初始化一键销毁灰色物品动作
        DestroyAllGrayItemsAction(PlayerbotAI* ai) : DestroyItemAction(ai, "destroy all gray") {}
        /// 执行动作主逻辑（一键销毁灰色物品动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（一键销毁灰色物品动作）
        virtual bool isUseful() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "destroy all gray"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This command will make the bot destroy all gray items.\n"
                "Usage: destroy all gray\n";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif
    };
}
