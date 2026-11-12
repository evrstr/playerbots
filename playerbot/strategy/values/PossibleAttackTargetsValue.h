// 策略值头文件：PossibleAttackTargetsValue（可攻击战斗目标列表与潜伏增援检测）
#pragma once
#include "playerbot/strategy/Value.h"
#include "TargetValue.h"
#include "NearestUnitsValue.h"

namespace ai
{
    // List of hostile targets that are in combat with the bot (or bot group) and can be attacked (is reachable, not cc'ed, etc...) | 与机器人（或其队伍）交战且可合法攻击（可达、未被控场等）的敌对目标列表
    // 目标列表计算器：从 attackers 中过滤掉不可攻击/被控场/无拾取权目标，输出可直接交战的目标列表
    class PossibleAttackTargetsValue : public ObjectGuidListCalculatedValue, public Qualified
    {
    public:
        PossibleAttackTargetsValue(PlayerbotAI* ai) : ObjectGuidListCalculatedValue(ai, "possible attack targets", 2), Qualified() {}
        std::list<ObjectGuid> Calculate() override;
        static bool IsValid(Unit* target, Player* player, float range = sPlayerbotAIConfig.sightDistance, bool ignoreCC = false, bool checkAttackerValid = true);
        static bool IsPossibleTarget(Unit* target, Player* player, float range, bool ignoreCC);
        static bool HasBreakableCC(Unit* target, Player* player);
        static bool HasUnBreakableCC(Unit* target, Player* player);
        virtual std::string Format() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "possible attack targets"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "combat"; }
        virtual std::string GetHelpDescription()
        {
            return "This value contains all the units the bot should attack.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { "attackers", "attack target"}; }
#endif 

    private:
        void RemoveNonThreating(std::list<ObjectGuid>& targets, bool getOne);

        static bool IsImmuneToDamage(Unit* target, Player* player);
        static bool HasIgnoreCCRti(Unit* target, Player* player);
        static bool IsTapped(Unit* target, Player* player);
        static bool IsCcTarget(Unit* attacker, Player* player);
    };

    // 布尔值计算器：检测当前战斗目标周围是否存在尚未进入战斗的潜在引怪增援
    class PossibleAddsValue : public BoolCalculatedValue
    {
    public:
        PossibleAddsValue(PlayerbotAI* const ai, std::string name = "possible adds") : BoolCalculatedValue(ai, name) {}
        virtual bool Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "possible adds"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "combat"; }
        virtual std::string GetHelpDescription()
        {
            return "This value returns true if any of the targets the bot wants to attack could agro adds.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { "possible targets no los", "possible attack targets" }; }
#endif 
    };
}
