// 策略值头文件：PartyMemberValue（队友筛选基类及查找接口）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 玩家单位筛选谓词抽象基类
    class FindPlayerPredicate
    {
    public:
        virtual ~FindPlayerPredicate() {}
        virtual bool Check(Unit*) = 0;
    };

    // 法术原型匹配谓词抽象基类
    class SpellEntryPredicate
    {
    public:
        virtual bool Check(SpellEntry const*) = 0;
    };

    // 队友目标计算器基类：按主控/治疗/坦克/普通队友顺序遍历队伍与附近友军并检查施法冲突
    class PartyMemberValue : public UnitCalculatedValue
    {
    public:
        PartyMemberValue(PlayerbotAI* ai, std::string name = "party member") : UnitCalculatedValue(ai, name) {}

    public:
        bool IsTargetOfSpellCast(Player* target, SpellEntryPredicate &predicate);

    protected:
        Unit* FindPartyMember(FindPlayerPredicate &predicate, bool ignoreOutOfGroup = false, bool ignoreTanks = false);
        Unit* FindPartyMember(std::list<Player*>* party, FindPlayerPredicate &predicate, bool ignoreTanks);
        bool Check(Unit* player);
    };
}
