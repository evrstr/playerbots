#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 重置 AI 动作：将机器人所有策略与 AI 状态重置为默认配置
    class ResetAiAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化重置 AI 动作
        ResetAiAction(PlayerbotAI* ai, bool fullReset = true, std::string name = "reset ai") : ChatCommandAction(ai, name), fullReset(fullReset) {}
        /// 执行动作主逻辑（重置 AI 动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（重置 AI 动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "reset ai"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "Reset the bot to it's initial state.\n"
                "Saved settings and values will be cleared.";
        }
        virtual std::vector<std::string> GetUsedActions() { return { "reset strats" , "reset values" }; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    protected:
        /// 重置机器人当前 AI 策略至默认状态
        virtual void ResetStrategies();
        /// 清空并重置机器人黑板状态值
        virtual void ResetValues();
        bool fullReset;
    };

    /// 保存 AI 配置动作：将当前机器人策略与状态配置保存到数据库或预设
    class SaveAiAction : public ChatCommandAction, public Qualified
    {
    public:
       /// 构造函数：初始化保存 AI 配置动作
       SaveAiAction(PlayerbotAI* ai, std::string name = "save ai") : ChatCommandAction(ai, name), Qualified() {}
       /// 执行动作主逻辑（保存 AI 配置动作）
       virtual bool Execute(Event& event) override;
       /// 判断当前状态下该动作是否可用/有效（保存 AI 配置动作）
       bool isUseful() override { return true; };
       /// 判断在被昏迷或控制状态下是否仍可执行该动作（保存 AI 配置动作）
       virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 加载 AI 配置动作：从已保存的配置中加载机器人的策略与状态
    class LoadAiAction : public ChatCommandAction, public Qualified
    {
    public:
       /// 构造函数：初始化加载 AI 配置动作
       LoadAiAction(PlayerbotAI* ai, std::string name = "load ai") : ChatCommandAction(ai, name), Qualified() {}
       /// 执行动作主逻辑（加载 AI 配置动作）
       virtual bool Execute(Event& event) override;
       /// 判断当前状态下该动作是否可用/有效（加载 AI 配置动作）
       bool isUseful() override { return true; };
       /// 判断在被昏迷或控制状态下是否仍可执行该动作（加载 AI 配置动作）
       virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 列出 AI 配置动作：查询并展示可用的已保存 AI 策略配置名称
    class ListAiAction : public ChatCommandAction, public Qualified
    {
    public:
       /// 构造函数：初始化列出 AI 配置动作
       ListAiAction(PlayerbotAI* ai, std::string name = "list ai") : ChatCommandAction(ai, name), Qualified() {}
       /// 执行动作主逻辑（列出 AI 配置动作）
       virtual bool Execute(Event& event) override;
       /// 判断当前状态下该动作是否可用/有效（列出 AI 配置动作）
       bool isUseful() override { return true; };
       /// 判断在被昏迷或控制状态下是否仍可执行该动作（列出 AI 配置动作）
       virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 重置策略动作：仅重置机器人的战斗/非战斗策略组合
    class ResetStratsAction : public ResetAiAction
    {
    public:
        /// 构造函数：初始化重置策略动作
        ResetStratsAction(PlayerbotAI* ai, std::string name = "reset strats", bool fullReset = true) : ResetAiAction(ai, fullReset, name) {}
        /// 执行动作主逻辑（重置策略动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（重置策略动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "reset strats"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "Reset the strategies of the bot to the standard values.\n"
                "Saved strategies will be cleared.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {"reset ai"}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };

    /// 重置状态值动作：清空并重置机器人黑板中存储的运行时状态值
    class ResetValuesAction : public ResetAiAction
    {
    public:
        /// 构造函数：初始化重置状态值动作
        ResetValuesAction(PlayerbotAI* ai, std::string name = "reset values", bool fullReset = true) : ResetAiAction(ai, fullReset, name) {}
        /// 执行动作主逻辑（重置状态值动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（重置状态值动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "reset values"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "Reset the settings of the bot to the default values.\n"
                "Saved values will be cleared.";
        }
        virtual std::vector<std::string> GetUsedActions() { return { "reset ai" }; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };

    /// 通用重置动作：重置机器人当前目标、移动与交互状态
    class ResetAction : public Action
    {
    public:
        /// 构造函数：初始化通用重置动作
        ResetAction(PlayerbotAI* ai, std::string name = "reset") : Action(ai, name) {}
        /// 执行动作主逻辑（通用重置动作）
        virtual bool Execute(Event& event) override { ai->Reset(true); return true; };
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（通用重置动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "reset"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "Reset internal buffers to clear current behavior.";
        }
        virtual std::vector<std::string> GetUsedActions() { return { "reset ai" }; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };
}
