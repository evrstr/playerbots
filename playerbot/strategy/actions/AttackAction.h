#pragma once

#include "playerbot/strategy/Action.h"
#include "MovementActions.h"

namespace ai
{
    /// 攻击动作基类：向目标移动并进入近战或远程攻击状态
    class AttackAction : public MovementAction
    {
    public:
        /// 构造函数：初始化攻击动作基类
        AttackAction(PlayerbotAI* ai, std::string name) : MovementAction(ai, name) {}

    public:
        /// 执行动作主逻辑（攻击动作基类）
        virtual bool Execute(Event& event) override;
        /// 判断执行该动作的前置条件是否满足（攻击动作基类）
        virtual bool isPossible() override { return !bot->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CLIENT_CONTROL_LOST); }; // Override movement stay. (覆盖原地停留（stay）移动限制。)

    protected:
        /// 启动或切换至指定目标的近战/远程攻击流程
        bool Attack(Player* requester, Unit* target);
        /// 命令机器人召唤的宠物主动攻击指定目标
        bool PetAttack(Player* requester, Unit* target);
        /// 检查目标单位是否存活、在视野内且满足攻击/施法合法性
        bool IsTargetValid(Player* requester, Unit* target);

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "attack"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot attack a specified target.\n"
                   "The bot will engage the enemy if it's within range and not friendly or already dead.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {"current target", "old target", "available loot"}; }
#endif 
    };

    /// 攻击主人目标动作：切换并攻击当前主人/队长选中的目标
    class AttackMyTargetAction : public AttackAction
    {
    public:
        /// 构造函数：初始化攻击主人目标动作
        AttackMyTargetAction(PlayerbotAI* ai, std::string name = "attack my target") : AttackAction(ai, name) { MakeVerbose(true); }

    public:
        /// 执行动作主逻辑（攻击主人目标动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（攻击主人目标动作）
        virtual bool isUseful() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "attack my target"; }
        virtual std::string GetHelpDescription()
        {
            return "This action directs the bot to attack the target you currently have selected.\n"
                   "Useful for coordinating attacks with the bot on a specific enemy.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {"attack target"}; }
#endif 
    };

    /// 攻击团队标记目标动作：攻击带有指定团队目标标记（RTI）的敌人
    class AttackRTITargetAction : public AttackAction
    {
    public:
        /// 构造函数：初始化攻击团队标记目标动作
        AttackRTITargetAction(PlayerbotAI* ai, std::string name = "attack rti target") : AttackAction(ai, name) { MakeVerbose(true); }

    public:
        /// 执行动作主逻辑（攻击团队标记目标动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（攻击团队标记目标动作）
        virtual bool isUseful() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "attack rti target"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot attack a target marked with a Raid Target Icon (RTI).\n"
                   "This is useful in group scenarios where specific enemies are marked for focus.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {"rti target", "attack target"}; }
#endif 
    };

    /// 攻击决斗对手动作：在决斗开始后主动攻击决斗对手
    class AttackDuelOpponentAction : public AttackAction
    {
    public:
        /// 构造函数：初始化攻击决斗对手动作
        AttackDuelOpponentAction(PlayerbotAI* ai, std::string name = "attack duel opponent") : AttackAction(ai, name) {}

    public:
        /// 执行动作主逻辑（攻击决斗对手动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（攻击决斗对手动作）
        virtual bool isUseful() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "attack duel opponent"; }
        virtual std::string GetHelpDescription()
        {
            return "This action makes the bot attack its opponent during a duel.\n"
                   "Use this to have the bot engage in combat when dueling another player.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {"duel target"}; }
#endif 
    };
}
