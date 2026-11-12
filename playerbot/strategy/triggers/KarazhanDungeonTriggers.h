/// 卡拉赞（Karazhan）团队副本触发器定义
#pragma once
#include "DungeonTriggers.h"
#include "GenericTriggers.h"
#include "playerbot/strategy/generic/KarazhanDungeonStrategies.h"

namespace ai
{
    /// 触发器：进入卡拉赞副本
    class KarazhanEnterDungeonTrigger : public EnterDungeonTrigger
    {
    public:
        KarazhanEnterDungeonTrigger(PlayerbotAI* ai) : EnterDungeonTrigger(ai, "enter karazhan", "karazhan", 532) {}
    };

    /// 触发器：离开卡拉赞副本
    class KarazhanLeaveDungeonTrigger : public LeaveDungeonTrigger
    {
    public:
        KarazhanLeaveDungeonTrigger(PlayerbotAI* ai) : LeaveDungeonTrigger(ai, "leave karazhan", "karazhan", 532) {}
    };

    /// 触发器：开始虚空幽龙（Netherspite）战斗
    class NetherspiteStartFightTrigger : public StartBossFightTrigger
    {
    public:
        NetherspiteStartFightTrigger(PlayerbotAI* ai) : StartBossFightTrigger(ai, "start netherspite fight", "netherspite", 15689) {}
    };

    /// 触发器：结束虚空幽龙战斗
    class NetherspiteEndFightTrigger : public EndBossFightTrigger
    {
    public:
        NetherspiteEndFightTrigger(PlayerbotAI* ai) : EndBossFightTrigger(ai, "end netherspite fight", "netherspite", 15689) {}
    };

    /// 触发器：虚空地带（16697）距离过近需躲避
    class VoidZoneTooCloseTrigger : public CloseToCreatureHazardTrigger
    {
    public:
        VoidZoneTooCloseTrigger(PlayerbotAI* ai) : CloseToCreatureHazardTrigger(ai, "void zone too close", 16697, 5.0f, 99999999.0f) {}
    };

    /// 触发器：虚空幽龙传送门阶段非坦克成员需要刷新射线作弊/位置站位
    class NetherspiteBeamsCheatNeedRefreshTrigger : public Trigger
    {
    public:
        NetherspiteBeamsCheatNeedRefreshTrigger(PlayerbotAI* ai, int checkInteval = 1) : Trigger(ai, "netherspite beams cheat need refresh", checkInteval) {}
        bool IsActive() override;
    };

    /// 触发器：虚空幽龙传送门阶段坦克玩家需要刷新射线站位
    class NetherspiteBeamsPlayerCheatNeedRefreshTrigger : public Trigger
    {
    public:
        NetherspiteBeamsPlayerCheatNeedRefreshTrigger(PlayerbotAI* ai, int checkInteval = 2) : Trigger(ai, "netherspite beams player cheat need refresh", checkInteval) {}
        bool IsActive() override;
    };

    /// 触发器：需要移除虚空传送门“支配”减益层数
    class RemoveNetherPortalDominanceTrigger : public HasAuraTrigger
    {
    public:
        RemoveNetherPortalDominanceTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "remove nether portal - dominance", 20) {}
    };

    /// 触发器：非主抗坦克需要移除虚空传送门“坚毅”光环（30421）
    class RemoveNetherPortalPerseverenceTrigger : public Trigger
    {
    public:
        RemoveNetherPortalPerseverenceTrigger(PlayerbotAI* ai) : Trigger(ai, "remove nether portal - perseverence", 1) {}
        bool IsActive() override
        {
            //Bot is not tank with aggro | 机器人当前并非持有仇恨的坦克
            if (ai->IsTank(bot) && AI_VALUE2(bool, "has aggro", "current target"))
                return false;

            return ai->HasAura(30421, bot);
        }
    };

    /// 触发器：需要移除虚空传送门“宁静”光环
    class RemoveNetherPortalSerenityTrigger : public HasAuraTrigger
    {
    public:
        RemoveNetherPortalSerenityTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "remove nether portal - serenity", 5) {}
    };

    /// 触发器：开始埃兰之影（Shade of Aran）战斗
    class ShadeOfAranStartFightTrigger : public StartBossFightTrigger
    {
    public:
        ShadeOfAranStartFightTrigger(PlayerbotAI* ai) : StartBossFightTrigger(ai, "start shade of aran fight", "shade of aran", 16524) {}
    };

    /// 触发器：结束埃兰之影战斗
    class ShadeOfAranEndFightTrigger : public EndBossFightTrigger
    {
    public:
        ShadeOfAranEndFightTrigger(PlayerbotAI* ai) : EndBossFightTrigger(ai, "end shade of aran fight", "shade of aran", 16524) {}
    };

    /// 触发器：埃兰之影正在施放魔爆术
    class ShadeOfAranCastingArcaneExplosionTrigger : public Trigger
    {
    public:
        ShadeOfAranCastingArcaneExplosionTrigger(PlayerbotAI* ai, int checkInteval = 1) : Trigger(ai, "shade of aran casting arcane explosion", checkInteval) {}
        virtual bool IsActive() override;
    };

    /// 触发器：埃兰之影魔爆术施法结束
    class ShadeOfAranDoneCastingArcaneExplosionTrigger : public Trigger
    {
    public:
        ShadeOfAranDoneCastingArcaneExplosionTrigger(PlayerbotAI* ai, int checkInteval = 1) : Trigger(ai, "shade of aran done casting arcane explosion", checkInteval) {}
        virtual bool IsActive() override;
    };

    /// 触发器：埃兰之影正在施放烈焰花环
    class ShadeOfAranCastingFlameWreathTrigger : public Trigger
    {
    public:
        ShadeOfAranCastingFlameWreathTrigger(PlayerbotAI* ai, int checkInteval = 3) : Trigger(ai, "shade of aran casting flame wreath", checkInteval) {}
        virtual bool IsActive() override;
    };

    /// 触发器：埃兰之影正在施放暴风雪
    class ShadeOfAranCastingBlizzardTrigger : public Trigger
    {
    public:
        ShadeOfAranCastingBlizzardTrigger(PlayerbotAI* ai, int checkInteval = 1) : Trigger(ai, "shade of aran casting blizzard", checkInteval) {}
        virtual bool IsActive() override;
    };

    /// 触发器：埃兰之影召唤出四个水元素
    class ShadeOfAranElementalsTrigger : public Trigger
  {
    public:
        ShadeOfAranElementalsTrigger(PlayerbotAI* ai, int checkInteval = 1) : Trigger(ai, "shade of aran elementals out", checkInteval) {}
        virtual bool IsActive() override;
  };

    /// 触发器：开始大灰狼战斗
    class BigBadWolfStartFightTrigger : public StartBossFightTrigger
    {
    public:
        BigBadWolfStartFightTrigger(PlayerbotAI* ai) : StartBossFightTrigger(ai, "start big bad wolf fight", "big bad wolf", 17521) {}
    };

    /// 触发器：结束大灰狼战斗
    class BigBadWolfEndFightTrigger : public EndBossFightTrigger
    {
    public:
        BigBadWolfEndFightTrigger(PlayerbotAI* ai) : EndBossFightTrigger(ai, "end big bad wolf fight", "big bad wolf", 17521) {}
    };

    /// 触发器：被变为小红帽（30756）且大灰狼距离过近
    class BigBadWolfTooCloseTrigger : public CloseToCreatureTrigger
    {
    public:
        BigBadWolfTooCloseTrigger(PlayerbotAI* ai) : CloseToCreatureTrigger(ai, "big bad wolf too close", 17521, 20.0f, true) {}

        bool IsActive() override
        {
            return ai->HasAura(30756, bot) && CloseToCreatureTrigger::IsActive();
        }
    };

    /// 触发器：开始玛克扎尔王子战斗
    class PrinceMalchezaarStartFightTrigger : public StartBossFightTrigger
    {
    public:
        PrinceMalchezaarStartFightTrigger(PlayerbotAI* ai) : StartBossFightTrigger(ai, "start prince malchezaar fight", "prince malchezaar", 15690) {}
    };

    /// 触发器：结束玛克扎尔王子战斗
    class PrinceMalchezaarEndFightTrigger : public EndBossFightTrigger
    {
    public:
        PrinceMalchezaarEndFightTrigger(PlayerbotAI* ai) : EndBossFightTrigger(ai, "end prince malchezaar fight", "prince malchezaar", 15690) {}
    };

    /// 触发器：虚空幽龙/地狱火（17646）距离过近需远离
    class NetherspiteInfernalTooCloseTrigger : public CloseToCreatureTrigger
    {
    public:
        NetherspiteInfernalTooCloseTrigger(PlayerbotAI* ai) : CloseToCreatureTrigger(ai, "netherspite infernal too close", 17646, 21.0f) {}
    };

    /// 触发器：玛克扎尔王子距离过近或处于暗影新星/虚弱阶段需撤离
    class PrinceMalchezaarTooCloseTrigger : public CloseToCreatureTrigger
    {
    public:
        PrinceMalchezaarTooCloseTrigger(PlayerbotAI* ai) : CloseToCreatureTrigger(ai, "prince malchezaar too close", 15690, ai->HasStrategy("ranged", BotState::BOT_STATE_COMBAT) ? 30.0f : 32.0f, false, ai->HasStrategy("ranged", BotState::BOT_STATE_COMBAT) ? 2 : 1)  {}

        bool IsActive() override;

        bool MeleeWaitCheck(Unit* target);

        bool EnfeeblePart();
    };
}