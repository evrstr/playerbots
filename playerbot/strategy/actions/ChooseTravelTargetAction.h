#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"
#include "GenericActions.h"
#include "playerbot/TravelMgr.h"

namespace ai
{
    const std::vector<uint32> travelPartitions = { 100, 250, 500, 1000, 2000, 3000, 4000, 5000, 6000, 10000, 50000, 100000, 500000 };

    /// 选择旅行目标动作：综合任务、训练师、商人、刷怪点等因素规划下一个长途旅行目标
    class ChooseTravelTargetAction : public Action {
    public:
        /// 构造函数：初始化选择旅行目标动作
        ChooseTravelTargetAction(PlayerbotAI* ai, std::string name = "choose travel target") : Action(ai, name) {}

        /// 执行动作主逻辑（选择旅行目标动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（选择旅行目标动作）
        virtual bool isUseful() override;
        /// 向主人或调试频道汇报当前旅行目标与预计距离
        static void ReportTravelTarget(Player* bot, Player* requester, TravelTarget* newTarget, TravelTarget* oldTarget);
        /// 从附近潜在敌对目标列表中选出最佳攻击目标
        static TravelPoint PickBestTarget(Player* bot, Player* requester, PlayerbotAI* ai, bool forced, const PlayerTravelInfo& info, PartitionedTravelList& partitionedList);
    protected:
        /// 更新并设定新的目标 GUID
        void setNewTarget(Player* requester, TravelTarget* newTarget, TravelTarget* oldTarget);        

        /// 挑选并锁定当前优先级最高的战斗目标
        bool SetBestTarget(Player* requester, TravelTarget* target, PartitionedTravelList& travelPartitions, bool onlyActive = true);
    public:
        /// 根据名称、任务或策略查找匹配的旅行目的地
        static DestinationList FindDestination(PlayerTravelInfo info, std::string name, bool zones = true, bool npcs = true, bool quests = true, bool mobs = true, bool bosses = true, bool gather = true);
    private:
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "choose travel target"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This action is used to select a target for the bots to travel to.\n"
                "Bots will travel to specific places for specific reasons.\n"
                "For example bots will travel to a vendor if they need to sell stuff\n"
                "The current destination or those of group members are also options.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return { "travel target", "group or", "should sell","can sell","can ah sell","should repair","can repair","following party","near leader","should get money","can fight equal","can fight elite","can fight boss","can free move","rpg target","attack target",}; }
#endif 
    };

    /// 选择队伍旅行目标动作：同步并跟随队长或团队选定的旅行目标
    class ChooseGroupTravelTargetAction : public ChooseTravelTargetAction {
    public:
        /// 构造函数：初始化选择队伍旅行目标动作
        ChooseGroupTravelTargetAction(PlayerbotAI* ai, std::string name = "choose group travel target") : ChooseTravelTargetAction(ai, name) {}

        /// 执行动作主逻辑（选择队伍旅行目标动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（选择队伍旅行目标动作）
        virtual bool isUseful() override;
    };

    /// 刷新旅行目标动作：重新评估并更新当前旅行目标的进度或状态
    class RefreshTravelTargetAction : public ChooseTravelTargetAction {
    public:
        /// 构造函数：初始化刷新旅行目标动作
        RefreshTravelTargetAction(PlayerbotAI* ai, std::string name = "refresh travel target") : ChooseTravelTargetAction(ai, name) {}

        /// 执行动作主逻辑（刷新旅行目标动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（刷新旅行目标动作）
        virtual bool isUseful() override;
    };

    /// 重置旅行目标动作：清除当前旅行目标并触发重新规划
    class ResetTargetAction : public ChooseTravelTargetAction {
    public:
        /// 构造函数：初始化重置旅行目标动作
        ResetTargetAction(PlayerbotAI* ai, std::string name = "reset travel target") : ChooseTravelTargetAction(ai, name) {}

        /// 执行动作主逻辑（重置旅行目标动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（重置旅行目标动作）
        virtual bool isUseful() override;
    };    

    /// 请求旅行目标基类动作：接收玩家指令请求机器人前往指定类型目的地
    class RequestTravelTargetAction : public Action, public Qualified {
    public:
        /// 构造函数：初始化请求旅行目标基类动作
        RequestTravelTargetAction(PlayerbotAI* ai, std::string name = "request travel target") : Action(ai, name), Qualified() {}
    protected:
        /// 执行动作主逻辑（请求旅行目标基类动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（请求旅行目标基类动作）
        virtual bool isUseful() override;
        /// 检查当前物品、技能或动作是否被策略或配置允许使用
        virtual bool isAllowed() const;
    };

    /// 按名称请求旅行目标动作：根据输入的区域、NPC 或怪物名称查找并设定旅行目标
    class RequestNamedTravelTargetAction : public RequestTravelTargetAction {
    public:
        /// 构造函数：初始化按名称请求旅行目标动作
        RequestNamedTravelTargetAction(PlayerbotAI* ai, std::string name = "request named travel target") : RequestTravelTargetAction(ai, name) {}
    private:
        /// 执行动作主逻辑（按名称请求旅行目标动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（按名称请求旅行目标动作）
        virtual bool isUseful() override;
        /// 检查当前物品、技能或动作是否被策略或配置允许使用
        virtual bool isAllowed() const override;
    };

    /// 请求任务旅行目标动作：查找并设定与当前活动任务相关的旅行目的地
    class RequestQuestTravelTargetAction : public RequestTravelTargetAction {
    public:
        /// 构造函数：初始化请求任务旅行目标动作
        RequestQuestTravelTargetAction(PlayerbotAI* ai, std::string name = "request quest travel target") : RequestTravelTargetAction(ai, name) {}
    private:
        /// 执行动作主逻辑（请求任务旅行目标动作）
        virtual bool Execute(Event& event) override;
        /// 检查当前物品、技能或动作是否被策略或配置允许使用
        virtual bool isAllowed() const override;
    };

    /// 聚焦旅行目标指令动作：锁定或查看机器人当前专注的旅行目标
    class FocusTravelTargetAction : public ChatCommandAction {
    public:
        /// 构造函数：初始化聚焦旅行目标指令动作
        FocusTravelTargetAction(PlayerbotAI* ai, std::string name = "focus travel target") : ChatCommandAction(ai, name) {}

        /// 执行动作主逻辑（聚焦旅行目标指令动作）
        virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "focus travel target"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This command specifies quests the bot should focus on.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };
}
