#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 列出法术指令动作：查询并输出机器人当前已掌握的法术列表
    class ListSpellsAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化列出法术指令动作
        ListSpellsAction(PlayerbotAI* ai, std::string name = "spells") : ChatCommandAction(ai, name) {}
        /// 执行动作主逻辑（列出法术指令动作）
        virtual bool Execute(Event& event) override;
        virtual std::list<std::pair<uint32, std::string> > GetSpellList(std::string filter = "");
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（列出法术指令动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
        static std::map<uint32, SkillLineAbilityEntry const*> skillSpells;
        static std::set<uint32> vendorItems;
    };
}
