#pragma once

#include "playerbot/strategy/Action.h"
#include "QuestAction.h"
#include "UseItemAction.h"

namespace ai
{
   /// 磨刀石/平衡石武器附魔动作：为近战武器涂抹磨刀石或平衡石临时强化效果
   class ImbueWithStoneAction : public UseAction
   {
   public:
      /// 构造函数：初始化磨刀石/平衡石武器附魔动作
      ImbueWithStoneAction(PlayerbotAI* ai) : UseAction(ai, "apply stone") {}
      /// 执行动作主逻辑（磨刀石/平衡石武器附魔动作）
      bool Execute(Event& event) override;
      /// 判断当前状态下该动作是否可用/有效（磨刀石/平衡石武器附魔动作）
      bool isUseful() override;
   };

   /// 巫师之油/法力之油武器附魔动作：为武器涂抹法系临时强化油类道具
   class ImbueWithOilAction : public UseAction
   {
   public:
      /// 构造函数：初始化巫师之油/法力之油武器附魔动作
      ImbueWithOilAction(PlayerbotAI* ai) : UseAction(ai, "apply oil") {}
      /// 执行动作主逻辑（巫师之油/法力之油武器附魔动作）
      bool Execute(Event& event) override;
      /// 判断当前状态下该动作是否可用/有效（巫师之油/法力之油武器附魔动作）
      bool isUseful() override;
   };

   /// 紧急自保动作：在危急血量或突发状况下尝试使用保命技能或消耗品
   class TryEmergencyAction : public Action
   {
   public:
      /// 构造函数：初始化紧急自保动作
      TryEmergencyAction(PlayerbotAI* ai) : Action(ai, "try emergency") {}
      /// 执行动作主逻辑（紧急自保动作）
      bool Execute(Event& event) override;
   };
}

static const uint32 uPriorizedHealingItemIds[19] =
{
    HEALTHSTONE_DISPLAYID, FEL_REGENERATION_POTION, SUPER_HEALING_POTION, CRYSTAL_HEALING_POTION, MAJOR_DREAMLESS_SLEEP_POTION, VOLATILE_HEALING_POTION,
    MAJOR_HEALING_POTION, WHIPPER_ROOT_TUBER, NIGHT_DRAGON_BREATH, LIMITED_INVULNERABILITY_POTION, GREATER_DREAMLESS_SLEEP_POTION,
    SUPERIOR_HEALING_POTION, CRYSTAL_RESTORE, DREAMLESS_SLEEP_POTION, GREATER_HEALING_POTION, HEALING_POTION, LESSER_HEALING_POTION, DISCOLORED_HEALING_POTION, MINOR_HEALING_POTION,
};
