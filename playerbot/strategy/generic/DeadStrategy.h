/// 死亡状态恢复策略头文件
#pragma once
#include "PassTroughStrategy.h"

namespace ai
{
    /// 策略：管理机器人死亡后的释放灵魂、跑尸与复活恢复流程
    class DeadStrategy : public PassTroughStrategy
    {
    public:
        DeadStrategy(PlayerbotAI* ai) : PassTroughStrategy(ai) {}
        std::string getName() override { return "dead"; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "dead"; } //Must equal iternal name | 必须与内部策略名一致
        virtual std::string GetHelpDescription() {
            return "This strategy will includes various behavior when the bot is dead.\n The main goal is to revive in a safe location.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { }; }
#endif
    private:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override {}
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override {}
        void InitDeadTriggers(std::list<TriggerNode*> &triggers) override;
    };
}
