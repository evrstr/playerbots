#pragma once
#include "GenericSpellActions.h"
#include "GenericActions.h"

namespace ai
{
    /// 拉怪状态检查指令动作：检查或切换当前拉怪策略状态
    class PullCheckAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化拉怪状态检查指令动作
        PullCheckAction(PlayerbotAI* ai, std::string name) : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（拉怪状态检查指令动作）
        bool Execute(Event& event) override;
    };

    /// 拉怪请求基类动作：接收指挥指令并选定目标准备发起开怪拉怪
    class PullRequestAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化拉怪请求基类动作
        PullRequestAction(PlayerbotAI* ai, std::string name) : ChatCommandAction(ai, name) {}

    protected:
        /// 执行动作主逻辑（拉怪请求基类动作）
        virtual bool Execute(Event& event) override;
        /// 获取当前动作的目标单位（拉怪请求基类动作）
        virtual Unit* GetTarget(Event& event) = 0;
    };

    /// 拉取主人目标动作：按主人当前选中目标发起开怪拉怪
    class PullMyTargetAction : public PullRequestAction
    {
    public:
        /// 构造函数：初始化拉取主人目标动作
        PullMyTargetAction(PlayerbotAI* ai) : PullRequestAction(ai, "pull my target") {}
    
    private:
        /// 获取当前动作的目标单位（拉取主人目标动作）
        Unit* GetTarget(Event& event) override;
    };

    /// 拉取团队标记目标动作：按团队目标标记发起开怪拉怪
    class PullRTITargetAction : public PullRequestAction
    {
    public:
        /// 构造函数：初始化拉取团队标记目标动作
        PullRTITargetAction(PlayerbotAI* ai) : PullRequestAction(ai, "pull rti target") {}

    private:
        /// 获取当前动作的目标单位（拉取团队标记目标动作）
        Unit* GetTarget(Event& event) override;
    };

    /// 开始拉怪动作：初始化拉怪状态（如记录返回点、调整宠物为被动）
    class PullStartAction : public Action
    {
    public:
        /// 构造函数：初始化开始拉怪动作
        PullStartAction(PlayerbotAI* ai, std::string name = "pull start") : Action(ai, name) {}
        /// 执行动作主逻辑（开始拉怪动作）
        bool Execute(Event& event) override;
    };

    /// 执行拉怪动作：施放拉怪法术或远程射击将目标引回队伍位置
    class PullAction : public CastSpellAction
    {
    public:
        /// 构造函数：初始化执行拉怪动作
        PullAction(PlayerbotAI* ai, std::string name = "pull action");
        /// 执行动作主逻辑（执行拉怪动作）
        bool Execute(Event& event) override;
        /// 判断执行该动作的前置条件是否满足（执行拉怪动作）
        bool isPossible() override;
    private:
        /// 初始化拉怪动作的法术与状态参数
        void InitPullAction();
        /// 获取当前动作的目标名称标识（执行拉怪动作）
        std::string GetTargetName() override { return "pull target"; }
        /// 获取接近目标阶段所使用的移动动作名称
        std::string GetReachActionName() override { return "reach pull"; }
    };

    /// 结束拉怪动作：目标到达或仇恨建立后恢复正常战斗状态
    class PullEndAction : public Action
    {
    public:
        /// 构造函数：初始化结束拉怪动作
        PullEndAction(PlayerbotAI* ai, std::string name = "pull end") : Action(ai, name) {}
        /// 执行动作主逻辑（结束拉怪动作）
        bool Execute(Event& event) override;
    };
}
