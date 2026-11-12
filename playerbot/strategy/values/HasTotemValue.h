// 策略值头文件：HasTotemValue（检测范围内是否已存在己方或同队指定图腾）
#pragma once
#include "playerbot/strategy/Value.h"
#include "TargetValue.h"
#include "playerbot/LootObjectStack.h"

namespace ai
{
    // 布尔值计算器：遍历附近 NPC 检查是否存在名称匹配指定限定符且归属己方/同小队的图腾
    class HasTotemValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HasTotemValue(PlayerbotAI* ai, std::string name = "has totem") : BoolCalculatedValue(ai, name), Qualified() {}

        bool Calculate() override
        {
            std::list<ObjectGuid> units = *context->GetValue<std::list<ObjectGuid> >("nearest npcs");
            for (std::list<ObjectGuid>::iterator i = units.begin(); i != units.end(); i++)
            {
                Unit* unit = ai->GetUnit(*i);
                if (!unit)
                    continue;

                Creature* totem = dynamic_cast<Creature*>(unit);
                if (!totem || !totem->IsTotem())
                    continue;
                
                const bool totemIsInRange = strstri(totem->GetName(), qualifier.c_str()) &&
                    sServerFacade.GetDistance2d(bot, totem) <= ai->GetRange("spell");
                
                if (!totemIsInRange) continue;

                Unit* totemOwner = totem->GetCreator(totem);
                if (!totemOwner)
                    continue;

                if (totemOwner == bot) return true; // Found our own totem in range | 在有效范围内找到机器人自己放置的图腾

                const Group* botGroup = bot->GetGroup();
                if (!botGroup) continue;

                if (const Player* totemPlayerOwner = totemOwner->IsPlayer() ? dynamic_cast<Player*>(totemOwner) : nullptr)
                {
#ifdef MANGOSBOT_TWO
                    // Most totems are raid-wide in Wrath - Special handling should be added for the handful that aren't | WLK 中多数图腾对全团生效，仅少数需区分小队（此处保留原说明）
                    if (totemPlayerOwner->GetGroup() == botGroup) return true;
#else
                    // Totem from a player in our group found, and we are either not in a raid or in the same raid subgroup | 找到来自队友或同小队成员的图腾
                    if (totemPlayerOwner->GetGroup() == botGroup)
                    {
                        if (!botGroup->IsRaidGroup() || botGroup->SameSubGroup(totemPlayerOwner, bot)) return true;
                    }
#endif
                }
            }

            return false;
        }
    };
}
