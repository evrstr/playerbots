#pragma once
#include "CastCustomSpellAction.h"
#include "UseItemAction.h"


namespace ai
{
    /// 前往钓鱼点动作：寻找附近合适的水域钓鱼点并移动至岸边
    class MoveToFishAction : public MovementAction, public Qualified
    {
    public:
        /// 构造函数：初始化前往钓鱼点动作
        MoveToFishAction(PlayerbotAI* ai) : MovementAction(ai, "move to fish"), Qualified() {}
        /// 判断当前状态下该动作是否可用/有效（前往钓鱼点动作）
        virtual bool isUseful() override;
        /// 执行动作主逻辑（前往钓鱼点动作）
        virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "move to fish"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot move to a fishing location.\n"
                   "It identifies suitable spots for fishing and navigates there.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };

    /// 钓鱼动作：在水域旁施放钓鱼技能进行垂钓
    class FishAction : public CastCustomSpellAction
    {
    public:
        /// 构造函数：初始化钓鱼动作
        FishAction(PlayerbotAI* ai) : CastCustomSpellAction(ai, "fish") {}
        /// 判断当前状态下该动作是否可用/有效（钓鱼动作）
        virtual bool isUseful() override;
        /// 执行动作主逻辑（钓鱼动作）
        virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "fish"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot perform fishing.\n"
                   "It casts the fishing spell to catch fish at the current location.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };

    /// 收杆拾取鱼漂动作：检测鱼漂上钩动画并点击收杆获取渔获
    class UseFishingBobberAction : public UseAction
    {
    public:
        /// 构造函数：初始化收杆拾取鱼漂动作
        UseFishingBobberAction(PlayerbotAI* ai) : UseAction(ai, "use fishing bobber") {}

        /// 执行动作主逻辑（收杆拾取鱼漂动作）
        bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "use fishing bobber"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot use a fishing bobber.\n"
                   "It interacts with the bobber to complete the fishing process.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };
}
