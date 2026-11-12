#pragma once
#include "playerbot/strategy/values/CraftValues.h"
#include "GenericActions.h"

namespace ai
{
    /// 设置制造配方动作：配置机器人当前需要自动制作或代工的专业配方与费用
    class SetCraftAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化设置制造配方动作
        SetCraftAction(PlayerbotAI* ai) : ChatCommandAction(ai, "craft") {}
        /// 执行动作主逻辑（设置制造配方动作）
        virtual bool Execute(Event& event) override;
        /// 获取设定的专业代工收费金额
        static uint32 GetCraftFee(CraftData&);

    private:
        /// 汇报当前已设置的制造配方或代工状态
        void TellCraft(Player* requester);
        /// 列出指定专业能够制作的所有物品清单
        void TellCraftableByProfession(Player* requester, uint32 skill);
        /// 解析聊天指令中的专业技能名称或关键字
        static uint32 ParseProfession(const std::string& text);
        /// 加载指定专业或武器技能相关的法术列表
        static void LoadSkillSpells();

    private:
        static std::map<uint32, SkillLineAbilityEntry const*> skillSpells;
    };
}
