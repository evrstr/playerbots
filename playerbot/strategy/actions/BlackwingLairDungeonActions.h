#pragma once
#include "DungeonActions.h"
#include "ChangeStrategyAction.h"
#include "MovementActions.h"
#include "UseItemAction.h"
#include "playerbot/strategy/values/GuidPositionValues.h"

namespace ai
{
    const uint32 SPELL_DISARM_TRAP = 1842;

    /// 启用黑翼之巢副本策略动作：开启黑翼之巢团队副本专用战术策略
    class BlackwingLairEnableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用黑翼之巢副本策略动作
        BlackwingLairEnableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable blackwing lair strategy", "+blackwing lair") {}
    };

    /// 禁用黑翼之巢副本策略动作：离开或完成时关闭黑翼之巢副本策略
    class BlackwingLairDisableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用黑翼之巢副本策略动作
        BlackwingLairDisableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable blackwing lair strategy", "-blackwing lair") {}
    };

    /// 前往压制装置动作（黑翼之巢）：引导盗贼前往陷阱房中的龙族压制装置附近
    class MoveToSuppressionDeviceAction : public MovementAction
    {
    public:
        /// 构造函数：初始化前往压制装置动作（黑翼之巢）
        MoveToSuppressionDeviceAction(PlayerbotAI* ai) : MovementAction(ai, "move to suppression device") {}

        /// 执行动作主逻辑（前往压制装置动作（黑翼之巢））
        bool Execute(Event& event) override
        {
            std::list<GuidPosition> gos = AI_VALUE(std::list<GuidPosition>, "go usable filter::go trapped filter::entry filter::{gos in sight,suppression devices}");
            
            if (gos.empty())
                return false;

            WorldPosition botPos(bot);
            GuidPosition closest;
            float closestDist = FLT_MAX;

            for (const GuidPosition& gp : gos)
            {
                float dist = botPos.distance(gp);
                if (dist < closestDist)
                {
                    closestDist = dist;
                    closest = gp;
                }
            }

            if (!closest)
                return false;
            
            if (ai->HasStrategy("debug move", BotState::BOT_STATE_NON_COMBAT))
            {
                ai->TellPlayerNoFacing(GetMaster(), "Moving to Suppression Device at " + std::to_string((int)closestDist) + " yards");
            }

            return MoveTo(closest.getMapId(), closest.getX(), closest.getY(), closest.getZ());
        }

        /// 判断执行该动作的前置条件是否满足（前往压制装置动作（黑翼之巢））
        bool isPossible() override
        {
            return ai->CanMove();
        }

        /// 判断当前状态下该动作是否可用/有效（前往压制装置动作（黑翼之巢））
        bool isUseful() override
        {
            std::list<GuidPosition> gos = AI_VALUE(std::list<GuidPosition>, "go usable filter::go trapped filter::entry filter::{gos in sight,suppression devices}");
            return !gos.empty();
        }
    };

    /// 潜行接近压制装置动作（黑翼之巢）：盗贼在解除陷阱前进入潜行状态
    class StealthForSuppressionDeviceAction : public Action
    {
    public:
        /// 构造函数：初始化潜行接近压制装置动作（黑翼之巢）
        StealthForSuppressionDeviceAction(PlayerbotAI* ai) : Action(ai, "stealth for suppression device") {}

        /// 执行动作主逻辑（潜行接近压制装置动作（黑翼之巢））
        bool Execute(Event& event) override
        {
            if (bot->getClass() != CLASS_ROGUE)
                return false;

            if (ai->HasAura("stealth", bot))
                return false;

            if (ai->CastSpell("stealth", bot))
            {
                ai->ChangeStrategy("+stealthed", BotState::BOT_STATE_COMBAT);
                ai->ChangeStrategy("+stealthed", BotState::BOT_STATE_NON_COMBAT);
                bot->InterruptSpell(CURRENT_MELEE_SPELL);
                return true;
            }

            return false;
        }

        /// 判断执行该动作的前置条件是否满足（潜行接近压制装置动作（黑翼之巢））
        bool isPossible() override
        {
            return bot->getClass() == CLASS_ROGUE && !ai->HasAura("stealth", bot);
        }

        /// 判断当前状态下该动作是否可用/有效（潜行接近压制装置动作（黑翼之巢））
        bool isUseful() override
        {
            if (ai->HasAura("stealth", bot))
                return false;

            // Core rogue stealth logic had some WSG/EYE flag checks, added in here too just in case (核心盗贼潜行逻辑包含战歌/风暴旗帜检查，此处一并加入以防万一)
            return !ai->HasAura(23333, bot) && !ai->HasAura(23335, bot) && !ai->HasAura(34976, bot);
        }
    };

    /// 停用压制装置动作（黑翼之巢）：与开启的压制装置交互使其暂时失效
    class DeactivateSuppressionDeviceAction : public Action
    {
    public:
        /// 构造函数：初始化停用压制装置动作（黑翼之巢）
        DeactivateSuppressionDeviceAction(PlayerbotAI* ai) : Action(ai, "deactivate suppression device") {}

        /// 执行动作主逻辑（停用压制装置动作（黑翼之巢））
        bool Execute(Event& event) override
        {
            std::list<GuidPosition> gos = AI_VALUE(std::list<GuidPosition>, "entry filter::{gos close,suppression devices}");
            
            if (gos.empty())
                return false;

            for (const GuidPosition& guidPos : gos)
            {
                GameObject* go = ai->GetGameObject(guidPos);
                if (!go)
                    continue;

                if (go->GetLootState() != GO_READY)
                    continue;

                if (!bot->GetGameObjectIfCanInteractWith(go->GetObjectGuid(), GAMEOBJECT_TYPE_TRAP))
                    continue;

                std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_GAMEOBJ_USE));
                *packet << go->GetObjectGuid();
                bot->GetSession()->QueuePacket(std::move(packet));

                if (ai->HasStrategy("debug move", BotState::BOT_STATE_NON_COMBAT))
                {
                    ai->TellPlayerNoFacing(GetMaster(), "Deactivating Suppression Device");
                }

                return true;
            }

            return false;
        }

        /// 判断执行该动作的前置条件是否满足（停用压制装置动作（黑翼之巢））
        bool isPossible() override
        {
            return ai->CanMove();
        }
    };

    /// 解除压制装置陷阱动作（黑翼之巢）：盗贼施放解除陷阱技能关闭压制装置
    class DisarmSuppressionDeviceAction : public Action
    {
    public:
        /// 构造函数：初始化解除压制装置陷阱动作（黑翼之巢）
        DisarmSuppressionDeviceAction(PlayerbotAI* ai) : Action(ai, "disarm suppression device") {}

        /// 执行动作主逻辑（解除压制装置陷阱动作（黑翼之巢））
        bool Execute(Event& event) override
        {
            if (bot->getClass() != CLASS_ROGUE)
                return false;

            if (!bot->HasSpell(SPELL_DISARM_TRAP))
                return false;

            std::list<GuidPosition> gos = AI_VALUE(std::list<GuidPosition>, "go usable filter::go trapped filter::entry filter::{gos close,suppression devices}");
            
            if (gos.empty())
                return false;

            WorldPosition botPos(bot);
            GameObject* closestGo = nullptr;
            float closestDist = FLT_MAX;

            for (const GuidPosition& guidPos : gos)
            {
                GameObject* go = ai->GetGameObject(guidPos);
                if (!go)
                    continue;

                if (go->GetLootState() != GO_READY)
                    continue;

                float dist = botPos.distance(WorldPosition(go));
                if (dist < closestDist)
                {
                    closestDist = dist;
                    closestGo = go;
                }
            }

            if (!closestGo)
                return false;

            if (ai->HasStrategy("debug move", BotState::BOT_STATE_NON_COMBAT))
            {
                ai->TellPlayerNoFacing(GetMaster(), "Casting Disarm Trap on Suppression Device");
            }

            return ai->CastSpell(SPELL_DISARM_TRAP, closestGo);
        }

        /// 判断执行该动作的前置条件是否满足（解除压制装置陷阱动作（黑翼之巢））
        bool isPossible() override
        {
            return bot->getClass() == CLASS_ROGUE && 
                   bot->HasSpell(SPELL_DISARM_TRAP) && 
                   ai->CanMove();
        }

        /// 判断当前状态下该动作是否可用/有效（解除压制装置陷阱动作（黑翼之巢））
        bool isUseful() override
        {
            std::list<GuidPosition> gos = AI_VALUE(std::list<GuidPosition>, "go usable filter::go trapped filter::entry filter::{gos close,suppression devices}");
            return !gos.empty();
        }
    };
}
