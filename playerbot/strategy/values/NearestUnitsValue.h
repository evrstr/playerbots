// 策略值头文件：NearestUnitsValue（附近单位基类与附近潜行单位检测）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"

#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"

namespace ai
{
    // 单位列表计算器抽象基类：统一实现单位扫描、视线校验及模板方法 AcceptUnit 过滤
    class NearestUnitsValue : public ObjectGuidListCalculatedValue
    {
    public:
        NearestUnitsValue(PlayerbotAI* ai, std::string name = "nearest units", float range = sPlayerbotAIConfig.sightDistance, bool ignoreLos = false) :
            ObjectGuidListCalculatedValue(ai, name, 2), range(range), ignoreLos(ignoreLos) {}

    public:
        virtual std::list<ObjectGuid> Calculate() override
        {
            std::list<Unit*> targets;
            FindUnits(targets);

            std::list<ObjectGuid> results;
            for(std::list<Unit *>::iterator i = targets.begin(); i!= targets.end(); ++i)
            {
                Unit* unit = *i;
                if(ai->IsSafe(unit))
                {
                    if ((ignoreLos || sServerFacade.IsWithinLOSInMap(bot, unit)) && AcceptUnit(unit))
                        results.push_back(unit->GetObjectGuid());
                }
            }
            return results;
        }

    protected:
        virtual void FindUnits(std::list<Unit*> &targets) = 0;
        virtual bool AcceptUnit(Unit* unit) = 0;

    protected:
        float range;
        bool ignoreLos;
    };

    // 单位列表计算器：查找附近处于潜行状态但尚未被侦测到的非友方单位
    class NearestStealthedUnitsValue : public NearestUnitsValue
    {
    public:
        NearestStealthedUnitsValue(PlayerbotAI* ai, float range = 30.0f) :
            NearestUnitsValue(ai, "nearest stealthed units", range) {}

    protected:
        void FindUnits(std::list<Unit*>& targets) override
        {
            MaNGOS::AnyUnfriendlyUnitInObjectRangeCheck u_check(bot, range);
            MaNGOS::UnitListSearcher<MaNGOS::AnyUnfriendlyUnitInObjectRangeCheck> searcher(targets, u_check);
            Cell::VisitAllObjects(bot, searcher, range);
        }
        bool AcceptUnit(Unit* unit) override
        {
            if (!unit || !unit->IsAlive() || !sServerFacade.IsHostileTo(unit, bot))
                return false;

            return unit->HasAuraType(SPELL_AURA_MOD_STEALTH) || unit->HasAuraType(SPELL_AURA_MOD_INVISIBILITY);

            // 注释：预留的驱散/破潜检测逻辑
            /*uint32 dispelMask = 0;
            dispelMask |= GetDispellMask(DispelType(DISPEL_STEALTH));
            dispelMask |= GetDispellMask(DispelType(DISPEL_INVISIBILITY));

            return unit->HasMechanicMaskOrDispelMaskAura(dispelMask, 0, bot);*/
        }
    };

    // 目标值计算器：从附近潜行单位列表中随机选取一个潜行目标
    class NearestStealthedSingleUnitValue : public UnitCalculatedValue
    {
    public:
        NearestStealthedSingleUnitValue(PlayerbotAI* ai) :
            UnitCalculatedValue(ai, "nearest stealthed unit") {}

        virtual ObjectGuid Calculate() override
        {
            std::list<ObjectGuid> targets = AI_VALUE(std::list<ObjectGuid>, "nearest stealthed units");
            if (targets.empty())
                return ObjectGuid();

            std::vector<Unit*> units;
            for (std::list<ObjectGuid>::iterator i = targets.begin(); i != targets.end(); ++i)
            {
                Unit* unit = ai->GetUnit(*i);
                if (!unit)
                    continue;

                units.push_back(unit);
            }

            if (units.empty())
                return ObjectGuid();

            Unit* unit = units[urand(0, units.size() - 1)];
            return unit ? unit->GetObjectGuid() : ObjectGuid();
        }
    };
}
