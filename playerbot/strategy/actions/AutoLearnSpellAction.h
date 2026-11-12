#pragma once


#include "playerbot/playerbot.h"
#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 自动学习技能动作：根据等级与职业自动从训练师处学习可用法术
    class AutoLearnSpellAction : public Action {
    public:
        /// 构造函数：初始化自动学习技能动作
        AutoLearnSpellAction(PlayerbotAI* ai, std::string name = "auto learn spell") : Action(ai, name) {}
        
    public:
        /// 执行动作主逻辑（自动学习技能动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（自动学习技能动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private: 
        /// 遍历并批量学习所有符合当前等级的可用法术
        void LearnSpells(std::ostringstream* out);
        /// 向职业训练师学习当前等级及前置条件满足的法术
        void LearnTrainerSpells(std::ostringstream* out);
        /// 补学机器人当前等级已完成任务应获得的职业法术
        void LearnQuestSpells(std::ostringstream* out);
        /// 学习由物品或掉落物触发解锁的法术
        void LearnDroppedSpells(std::ostringstream* out);
        /// 获取当前职业或任务阶段所需的职业专属任务物品
        void GetClassQuestItem(Quest const* quest, std::ostringstream* out);
        /// 直接使机器人学会指定 ID 的法术
        bool LearnSpell(uint32 spellId, std::ostringstream* out);
        /// 通过教学法术学习其关联的目标法术
        bool LearnSpellFromSpell(uint32 spellId, std::ostringstream* out);
        /// 校验法术 ID 在法术模板中是否有效存在
        bool IsValidSpell(uint32 spellId);
        /// 检查法术是否为本身仅作教学触发的占位法术
        bool IsTeachingSpellListedAsSpell(uint32 spellId);
    };
}
