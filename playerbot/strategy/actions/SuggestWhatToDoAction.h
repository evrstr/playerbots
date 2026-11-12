#pragma once
#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 行动建议播报动作：向周边或公会发送组队刷怪、做任务、打副本等互动建议
    class SuggestWhatToDoAction : public Action
    {
    public:
        /// 构造函数：初始化行动建议播报动作
        SuggestWhatToDoAction(PlayerbotAI* ai, std::string name = "suggest what to do");
        /// 执行动作主逻辑（行动建议播报动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（行动建议播报动作）
        virtual bool isUseful() override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（行动建议播报动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    protected:
        typedef void (SuggestWhatToDoAction::*Suggestion) ();
        std::vector<Suggestion> suggestions;
        /// 生成建议前往某个地下城副本的行动建议文本
        void instance();
        /// 生成针对特定活跃任务的建议喊话文本
        void specificQuest();
        /// 生成刷取专业材料相关的行动建议文本
        void grindMaterials();
        /// 生成刷取阵营声望相关的行动建议文本
        void grindReputation();
        /// 生成一条通用日常闲聊或组队建议文本
        void something();
        /// 生成一条带幽默吐槽风格的随机频道互动文本
        void somethingToxic();
        /// 生成趣味物品链接回复台词
        void toxicLinks();
        /// 生成关于雷霆之怒的趣味世界频道台词
        void thunderfury();

        /// 获取机器人当前尚未完成的任务列表
        std::vector<uint32> GetIncompletedQuests();

    private:
        static std::map<std::string, int> instances;
        static std::map<std::string, int> factions;
        int32 _locale;
    };

    /// 交易建议播报动作：扫描背包多余物品并在频道中发送交易或售卖广告
    class SuggestTradeAction : public SuggestWhatToDoAction
    {
    public:
        /// 构造函数：初始化交易建议播报动作
        SuggestTradeAction(PlayerbotAI* ai) : SuggestWhatToDoAction(ai) {}
        /// 执行动作主逻辑（交易建议播报动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（交易建议播报动作）
        virtual bool isUseful() override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（交易建议播报动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };
}
