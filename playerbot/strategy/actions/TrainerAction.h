#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 训练师交互动作：访问职业或专业训练师以学习新法术与技能
    class TrainerAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化训练师交互动作
        TrainerAction(PlayerbotAI* ai) : ChatCommandAction(ai, "trainer") {}
        /// 执行动作主逻辑（训练师交互动作）
        virtual bool Execute(Event& event) override;

    private:
        typedef void (TrainerAction::*TrainerSpellAction)(uint32, ObjectGuid trainerGuid, uint32 spellId, TrainerSpell const*, std::ostringstream& msg);
        /// 遍历目标集合并逐项执行检查或处理逻辑
        bool Iterate(Player* requester, Creature* creature, TrainerSpellAction action, SpellIds& spells);
        /// 执行学习指定法术或配方的核心逻辑
        void Learn(uint32 cost, ObjectGuid trainerGuid, uint32 spellId, TrainerSpell const* tSpell, std::ostringstream& msg);
        /// 输出列表汇报的头部标题信息
        void TellHeader(Player* requester, Creature* creature);
        /// 输出列表汇报的尾部统计信息
        void TellFooter(Player* requester, uint32 totalCost);
    };
}
