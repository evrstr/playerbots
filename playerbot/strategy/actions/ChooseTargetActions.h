#pragma once

#include "playerbot/strategy/Action.h"
#include "AttackAction.h"
#include "playerbot/ServerFacade.h"
#include "playerbot/playerbot.h"
#include "playerbot/LootObjectStack.h"
#include "ChooseRpgTargetAction.h"

namespace ai
{
    /// 群体输出目标选择动作：在存在多目标时选择最适合群体攻击的目标
    class DpsAoeAction : public AttackAction
    {
    public:
        /// 构造函数：初始化群体输出目标选择动作
        DpsAoeAction(PlayerbotAI* ai) : AttackAction(ai, "dps aoe") {}
        /// 获取当前动作的目标名称标识（群体输出目标选择动作）
        std::string GetTargetName() override { return "dps aoe target"; }
    };

    /// 输出集火协助动作：协助队伍坦克或主目标进行集火输出
    class DpsAssistAction : public AttackAction
    {
    public:
        /// 构造函数：初始化输出集火协助动作
        DpsAssistAction(PlayerbotAI* ai) : AttackAction(ai, "dps assist") {}
        /// 获取当前动作的目标名称标识（输出集火协助动作）
        std::string GetTargetName() override { return "dps target"; } 
        /// 判断当前状态下该动作是否可用/有效（输出集火协助动作）
        bool isUseful() override;
    };

    /// 坦克协助动作：协助当前主坦克接怪或建立仇恨目标
    class TankAssistAction : public AttackAction
    {
    public:
        /// 构造函数：初始化坦克协助动作
        TankAssistAction(PlayerbotAI* ai) : AttackAction(ai, "tank assist") {}
        /// 获取当前动作的目标名称标识（坦克协助动作）
        std::string GetTargetName() override { return "tank target"; }
    };

    /// 攻击任意敌对目标动作：自动寻找并攻击附近可交战的敌对单位
    class AttackAnythingAction : public AttackAction
    {
    private:   
    public:
        /// 构造函数：初始化攻击任意敌对目标动作
        AttackAnythingAction(PlayerbotAI* ai) : AttackAction(ai, "attack anything") {}
        /// 获取当前动作的目标名称标识（攻击任意敌对目标动作）
        std::string GetTargetName() override { return "grind target"; }

        /// 判断当前状态下该动作是否可用/有效（攻击任意敌对目标动作）
        bool isUseful() override;
        /// 判断执行该动作的前置条件是否满足（攻击任意敌对目标动作）
        bool isPossible() override;
        /// 执行动作主逻辑（攻击任意敌对目标动作）
        bool Execute(Event& event) override;
    };

    /// 攻击最低血量目标动作：优先选择生命值最低的敌人进行斩杀输出
    class AttackLeastHpTargetAction : public AttackAction
    {
    public:
        /// 构造函数：初始化攻击最低血量目标动作
        AttackLeastHpTargetAction(PlayerbotAI* ai) : AttackAction(ai, "attack least hp target") {}
        /// 获取当前动作的目标名称标识（攻击最低血量目标动作）
        std::string GetTargetName() override { return "least hp target"; }
    };

    /// 攻击敌对玩家动作：在 PvP 环境下搜寻并攻击敌对阵营玩家
    class AttackEnemyPlayerAction : public AttackAction
    {
    public:
        /// 构造函数：初始化攻击敌对玩家动作
        AttackEnemyPlayerAction(PlayerbotAI* ai) : AttackAction(ai, "attack enemy player") {}
        /// 获取当前动作的目标名称标识（攻击敌对玩家动作）
        std::string GetTargetName() override { return "enemy player target"; }
        /// 判断当前状态下该动作是否可用/有效（攻击敌对玩家动作）
        bool isUseful() override;
    };

    /// 攻击敌方扛旗手动作：在战场中优先追击并攻击携带旗帜的敌方玩家
    class AttackEnemyFlagCarrierAction : public AttackAction
    {
    public:
        /// 构造函数：初始化攻击敌方扛旗手动作
        AttackEnemyFlagCarrierAction(PlayerbotAI* ai) : AttackAction(ai, "attack enemy flag carrier") {}
        /// 获取当前动作的目标名称标识（攻击敌方扛旗手动作）
        std::string GetTargetName() override { return "enemy flag carrier"; }
        /// 判断当前状态下该动作是否可用/有效（攻击敌方扛旗手动作）
        bool isUseful() override;
    };

    /// 选择新目标动作：当前目标失效或不可攻击时重新挑选战斗目标
    class SelectNewTargetAction : public Action
    {
    public:
        /// 构造函数：初始化选择新目标动作
        SelectNewTargetAction(PlayerbotAI* ai) : Action(ai, "select new target") {}
        /// 执行动作主逻辑（选择新目标动作）
        bool Execute(Event& event) override;
    };
}
