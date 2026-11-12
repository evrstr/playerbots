#pragma once
#include "DungeonActions.h"
#include "playerbot/strategy/generic/KarazhanDungeonStrategies.h"
#include "ChangeStrategyAction.h"
#include "UseItemAction.h"

namespace ai
{
    /// 启用卡拉赞副本策略动作：开启卡拉赞团队副本专用战术策略
    class KarazhanEnableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用卡拉赞副本策略动作
        KarazhanEnableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable karazhan strategy", "+karazhan") {}
    };

    /// 禁用卡拉赞副本策略动作：关闭卡拉赞团队副本专用战术策略
    class KarazhanDisableDungeonStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用卡拉赞副本策略动作
        KarazhanDisableDungeonStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable karazhan strategy", "-karazhan") {}
    };

    /// 启用虚空幽龙战斗策略动作：开启卡拉赞虚空幽龙首领战专项策略
    class NetherspiteEnableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用虚空幽龙战斗策略动作
        NetherspiteEnableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable netherspite fight strategy", "+netherspite") {}
    };

    /// 禁用虚空幽龙战斗策略动作：关闭卡拉赞虚空幽龙首领战专项策略
    class NetherspiteDisableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用虚空幽龙战斗策略动作
        NetherspiteDisableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable netherspite fight strategy", "-netherspite") {}
    };

    /// 远离虚空地带动作：在虚空幽龙等战斗中迅速跑离地面生成的虚空伤害圈
    class VoidZoneMoveAwayAction : public MoveAwayFromCreature
    {
    public:
        /// 构造函数：初始化远离虚空地带动作
        VoidZoneMoveAwayAction(PlayerbotAI* ai) : MoveAwayFromCreature(ai, "move away from void zone", 16697, 6.0f) {}
    };

    /// 清除虚空幽龙门射线状态动作：处理虚空门射线切换时的状态清理
    class RemoveNetherPortalBuffsFromNetherspiteAction : public Action
    {
    public:
        /// 构造函数：初始化清除虚空幽龙门射线状态动作
        RemoveNetherPortalBuffsFromNetherspiteAction(PlayerbotAI* ai) : Action(ai, "remove nether portal buffs from netherspite") {}
        /// 执行动作主逻辑（清除虚空幽龙门射线状态动作）
        virtual bool Execute(Event& event) override;
    };

    /// 坦克挡蓝线（坚毅之门）动作：引导坦克站在蓝色虚空门射线上吸收增益并拉怪
    class AddNetherPortalPerseverenceForTankAction : public Action
    {
    public:
        /// 构造函数：初始化坦克挡蓝线（坚毅之门）动作
        AddNetherPortalPerseverenceForTankAction(PlayerbotAI* ai) : Action(ai, "add nether portal - perseverence for tank") {}
        /// 执行动作主逻辑（坦克挡蓝线（坚毅之门）动作）
        bool Execute(Event& event) override
        {
            if (ai->IsTank(bot))
            {
                ai->AddAura(bot, 30421);
                NetherspiteFightStrategy* strategy = NetherspiteFightStrategy::Get(ai);
                if (strategy)
                {
                    // Need to fixate aggro to mimic red beam spell hit script (需固定仇恨以模拟红线法术命中的首领脚本机制)
                    Unit* target = ai->GetUnit(strategy->GetBossGuid());
                    if (target)
                        target->FixateTarget(bot);
                }
                    
                return true;
            }
            
            return false;

        }
    };

    /// 离开坚毅之门射线动作：当对应减益层数过高时离开蓝色虚空门射线
    class RemoveNetherPortalPerseverenceAction : public Action
    {
    public:
        /// 构造函数：初始化离开坚毅之门射线动作
        RemoveNetherPortalPerseverenceAction(PlayerbotAI* ai) : Action(ai, "remove nether portal - perseverence") {}
        /// 执行动作主逻辑（离开坚毅之门射线动作）
        bool Execute(Event& event) override
        {
            bot->RemoveAurasDueToSpell(30421);
            return true;
        }
    };

    /// 离开宁静之门射线动作：治疗者层数过高时离开绿色虚空门射线
    class RemoveNetherPortalSerenityAction : public Action
    {
    public:
        /// 构造函数：初始化离开宁静之门射线动作
        RemoveNetherPortalSerenityAction(PlayerbotAI* ai) : Action(ai, "remove nether portal - serenity") {}
        /// 执行动作主逻辑（离开宁静之门射线动作）
        bool Execute(Event& event) override
        {
            bot->RemoveAurasDueToSpell(30422);
            return true;
        }
    };

    /// 离开支配之门射线动作：输出职业层数过高时离开红色虚空门射线
    class RemoveNetherPortalDominanceAction : public Action
    {
    public:
        /// 构造函数：初始化离开支配之门射线动作
        RemoveNetherPortalDominanceAction(PlayerbotAI* ai) : Action(ai, "remove nether portal - dominance") {}
        /// 执行动作主逻辑（离开支配之门射线动作）
        bool Execute(Event& event) override
        {
            bot->RemoveAurasDueToSpell(30423);
            return true;
        }
    };

    /// 启用埃兰之影战斗策略动作：开启卡拉赞埃兰之影首领战专项策略
    class ShadeOfAranEnableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用埃兰之影战斗策略动作
        ShadeOfAranEnableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable shade of aran fight strategy", "+shade of aran") {}
    };

    /// 禁用埃兰之影战斗策略动作：关闭埃兰之影首领战专项策略
    class ShadeOfAranDisableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用埃兰之影战斗策略动作
        ShadeOfAranDisableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable shade of aran fight strategy", "-shade of aran") {}
    };

    /// 远离埃兰之影动作：在埃兰之影施放魔爆术等范围技能时跑开躲避
    class ShadeOfAranMoveAwayAction : public MoveAwayFromCreature
    {
    public:
        /// 构造函数：初始化远离埃兰之影动作
        ShadeOfAranMoveAwayAction(PlayerbotAI* ai) : MoveAwayFromCreature(ai, "move away from shade of aran", 16524, 22.0f, false, false) {}
    };

    /// 埃兰之影烈焰花环阶段开始动作：进入烈焰花环阶段时强制原地站立避免炸团
    class ShadeOfAranFirePhaseStartedAction : public Action
    {
    public:
        /// 构造函数：初始化埃兰之影烈焰花环阶段开始动作
        ShadeOfAranFirePhaseStartedAction(PlayerbotAI* ai) : Action(ai, "start aran fire phase") {}
        /// 执行动作主逻辑（埃兰之影烈焰花环阶段开始动作）
        bool Execute(Event& event) override;
    };

    /// 埃兰之影暴风雪阶段开始动作：处理埃兰之影寒冰阶段的站位与策略切换
    class ShadeOfAranFrostPhaseStartedAction : public Action
    {
    public:
        /// 构造函数：初始化埃兰之影暴风雪阶段开始动作
        ShadeOfAranFrostPhaseStartedAction(PlayerbotAI* ai) : Action(ai, "start aran frost phase") {}
        /// 执行动作主逻辑（埃兰之影暴风雪阶段开始动作）
        bool Execute(Event& event) override;
    };

    /// 埃兰之影奥术阶段开始动作：进入奥爆阶段时切换到安全走位策略
    class ShadeOfAranArcanePhaseStartedAction : public Action
    {
    public:
        /// 构造函数：初始化埃兰之影奥术阶段开始动作
        ShadeOfAranArcanePhaseStartedAction(PlayerbotAI* ai) : Action(ai, "start aran arcane phase") {}
        /// 执行动作主逻辑（埃兰之影奥术阶段开始动作）
        bool Execute(Event& event) override;
    };

    /// 埃兰之影奥术阶段结束动作：奥术阶段结束后恢复常规战斗走位策略
    class ShadeOfAranArcanePhaseEndedAction : public Action
    {
    public:
        /// 构造函数：初始化埃兰之影奥术阶段结束动作
        ShadeOfAranArcanePhaseEndedAction(PlayerbotAI* ai) : Action(ai, "end aran arcane phase") {}
        /// 执行动作主逻辑（埃兰之影奥术阶段结束动作）
        bool Execute(Event& event) override;
    };

    /// 埃兰之影水元素应对动作：水元素召唤阶段调整目标选择优先清理元素
    class ShadeOfAranElementalsAction : public Action
    {
    public:
        /// 构造函数：初始化埃兰之影水元素应对动作
        ShadeOfAranElementalsAction(PlayerbotAI* ai) : Action(ai, "start aran elementals") {}
        /// 执行动作主逻辑（埃兰之影水元素应对动作）
        bool Execute(Event& event) override;
    };

    /// 启用大灰狼战斗策略动作：开启卡拉赞歌剧院大灰狼首领战策略
    class BigBadWolfEnableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用大灰狼战斗策略动作
        BigBadWolfEnableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable big bad wolf fight strategy", "+big bad wolf") {}
    };

    /// 禁用大灰狼战斗策略动作：关闭大灰狼首领战策略
    class BigBadWolfDisableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用大灰狼战斗策略动作
        BigBadWolfDisableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable big bad wolf fight strategy", "-big bad wolf") {}
    };

    /// 远离大灰狼动作：被变身为小红帽点名时迅速远离大灰狼风筝逃跑
    class BigBadWolfMoveAwayAction : public MoveAwayFromCreature
    {
    public:
        /// 构造函数：初始化远离大灰狼动作
        BigBadWolfMoveAwayAction(PlayerbotAI* ai) : MoveAwayFromCreature(ai, "move away from big bad wolf", 17521, 28.0f, true) {}
    };

    /// 启用玛克扎尔王子战斗策略动作：开启卡拉赞玛克扎尔王子首领战策略
    class PrinceMalchezaarEnableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化启用玛克扎尔王子战斗策略动作
        PrinceMalchezaarEnableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "enable prince malchezaar fight strategy", "+prince malchezaar") {}
    };

    /// 禁用玛克扎尔王子战斗策略动作：关闭玛克扎尔王子首领战策略
    class PrinceMalchezaarDisableFightStrategyAction : public ChangeAllStrategyAction
    {
    public:
        /// 构造函数：初始化禁用玛克扎尔王子战斗策略动作
        PrinceMalchezaarDisableFightStrategyAction(PlayerbotAI* ai) : ChangeAllStrategyAction(ai, "disable prince malchezaar fight strategy", "-prince malchezaar") {}
    };

    /// 远离玛克扎尔地狱火动作：在首领战中躲避从天而降的地狱火燃烧范围
    class NetherspiteInfernalMoveAwayAction : public MoveAwayFromCreature
    {
    public:
        /// 构造函数：初始化远离玛克扎尔地狱火动作
        NetherspiteInfernalMoveAwayAction(PlayerbotAI* ai) : MoveAwayFromCreature(ai, "move away from netherspite infernal", 17646, 22.0f, false, true) {}

        /// 执行动作主逻辑（远离玛克扎尔地狱火动作）
        bool Execute(Event& event) override;
    };

    /// 远离玛克扎尔王子动作：在首领施放暗影新星等致命近身技能时迅速撤离
    class PrinceMalchezaarMoveAwayAction : public MoveAwayFromCreature
    {
    public:
        /// 构造函数：初始化远离玛克扎尔王子动作
        PrinceMalchezaarMoveAwayAction(PlayerbotAI* ai) : MoveAwayFromCreature(ai, "move away from prince malchezaar", 15690, 32.0f, false, true) {}
    };
    
}
