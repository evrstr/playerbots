#pragma once
#include "playerbot/LootObjectStack.h"
#include "GenericActions.h"
#include "ChatShortcutActions.h"

namespace ai
{
    /// 拾取策略指令动作：配置机器人的战利品拾取偏好与过滤规则
    class LootStrategyAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化拾取策略指令动作
        LootStrategyAction(PlayerbotAI* ai) : ChatCommandAction(ai, "ll") {}
        /// 执行动作主逻辑（拾取策略指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（拾取策略指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        /// 向主人汇报当前待拾取队列中的战利品清单
        void TellLootList(Player* requester, const std::string& name);
        /// 输出 go 命令支持前往的目标或预设点清单
        void TellGoList(Player* requester, const std::string& name);
    };

    /// 收集物品指令动作：设置机器人优先收集指定名称或类型的物品
    class CollectAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化收集物品指令动作
        CollectAction(PlayerbotAI* ai) : ChatCommandAction(ai, "collect") {}
        /// 执行动作主逻辑（收集物品指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（收集物品指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        /// 汇报当前自动收集物品的配置状态
        void TellCollectState(Player* requester);
    };

    /// 勘测采集物指令动作：查询附近可采集的草药、矿脉与宝箱信息
    class SurveyAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化勘测采集物指令动作
        SurveyAction(PlayerbotAI* ai) : ChatCommandAction(ai, "survey") {}
        /// 执行动作主逻辑（勘测采集物指令动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（勘测采集物指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    };

    /// 查找对象动作：在附近搜索指定游戏对象或生物并报告其位置
    class FindObjectAction : public ReturnPositionResetAction
    {
    public:
        /// 构造函数：初始化查找对象动作
        FindObjectAction(PlayerbotAI* ai) : ReturnPositionResetAction(ai, "find") {}
        /// 执行动作主逻辑（查找对象动作）
        virtual bool Execute(Event& event) override;
    };

    /// 获取对象动作：前往指定目标对象位置并执行拾取或收集
    class GetObjectAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化获取对象动作
        GetObjectAction(PlayerbotAI* ai) : ChatCommandAction(ai, "get") {}
        /// 执行动作主逻辑（获取对象动作）
        virtual bool Execute(Event& event) override;
    };
}
