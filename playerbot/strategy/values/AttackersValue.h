// 策略值头文件：AttackersValue（交战攻击者列表及正攻击自身的目标列表）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/PlayerbotAIConfig.h"

namespace ai
{
    // List of hostile targets that are in combat with the bot (or bot group) | 与机器人（或其队伍）处于交战状态的敌对目标列表
    // 目标列表计算器：收集与机器人及其队伍处于战斗状态的敌对单位列表
    class AttackersValue : public ObjectGuidListCalculatedValue, public Qualified
    {
        // 辅助仿函数：将目标的守护者或宠物一并加入单位集合
        struct AddGuardiansHelper
        {
            explicit AddGuardiansHelper(std::set<Unit*>& units) : units(units) {}
            void operator()(Unit* target) const
            {
                units.insert(target);
            }

            std::set<Unit*>& units;
        };

    public:
        AttackersValue(PlayerbotAI* ai, std::string name = "attackers", int interval = 2) : ObjectGuidListCalculatedValue(ai, name, interval), Qualified() {}
        virtual std::list<ObjectGuid> Calculate() override;

        static bool IsValid(Unit* target, Player* player, Player* owner = nullptr, bool checkInCombat = true, bool validatePossibleTarget = true);
        static bool IgnoreTarget(Unit* target, Player* playerToCheckAgainst);
        virtual std::string Format() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "attackers"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "combat"; }
        virtual std::string GetHelpDescription()
        {
            return "This value contains all the units attacking the player, it's group or those the player or group is attacking.";
        }
        virtual std::vector<std::string> GetUsedValues() { return {"possible targets", "current target" , "attack target" ,  "pull target" }; }
#endif

    private:
        void AddTargetsOf(Group* group, std::set<Unit*>& targets, std::set<ObjectGuid>& invalidTargets, bool getOne = false);
        void AddTargetsOf(Player* player, std::set<Unit*>& targets, std::set<ObjectGuid>& invalidTargets, bool getOne = false);
        static float GetRange() { return sPlayerbotAIConfig.sightDistance; }

        static bool InCombat(Unit* target, Player* player, bool checkPullTargets = true);

        WorldPosition calculatePos;
    };

    // List of attackers that are currently targeting the bot | 当前正在攻击机器人本体的敌人列表
    // 目标列表计算器：从攻击者列表中筛选当前正以机器人为目标的敌人
    class AttackersTargetingMeValue : public ObjectGuidListCalculatedValue
    {
    public:
        AttackersTargetingMeValue(PlayerbotAI* ai, std::string name = "attackers targeting me") : ObjectGuidListCalculatedValue(ai, name) {}
        std::list<ObjectGuid> Calculate() override;
    };
}
