#pragma once
#include "playerbot/strategy/Action.h"

namespace ai
{
    /// 雕文管理动作：查看或为机器人装备指定的铭文雕文（WLK 支持）
    class GlyphAction : public Action, public Qualified
    {
    public:
       /// 构造函数：初始化雕文管理动作
       GlyphAction(PlayerbotAI* ai, std::string name = "set glyph") : Action(ai, name), Qualified() {}
        /// 执行动作主逻辑（雕文管理动作）
        virtual bool Execute(Event& event) override;
        typedef void (GlyphAction::* ProcessGlyphAction)(uint32, uint8, std::ostringstream& msg);
        /// 遍历目标集合并逐项执行检查或处理逻辑
        void Iterate(Player* requester, ProcessGlyphAction action, const std::vector<uint32> glyphs, const std::vector<uint8> glyphSlots);  
        /// 按指定条件列出物品、节点或配置列表
        void List(uint32 itemId, uint8 slotId, std::ostringstream& msg);
        /// 设置指定的策略参数或状态配置值
        void Set(uint32 itemId, uint8 wantedSlotId, std::ostringstream& msg);
        /// 移除指定的自定义配置、避让区域或忽略项
        void Remove(uint32 itemId, uint8 removeSlotId, std::ostringstream& msg);

        /// 判断在被昏迷或控制状态下是否仍可执行该动作（雕文管理动作）
        virtual bool isUsefulWhenStunned() override { return true; }
    private:
        /// 查找当前已镶嵌的对应雕文槽位索引
        uint8 GetEquipedGlyphSlot(uint32 itemId);
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "set glyph"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This action will list or apply new glyphs to the bot..\n"
                "glyph [itemlink] : equip glyph in a open slot.\n"
                "glyph [itemlink] <slotnumber> : replace current glyph in slot with new glyph\n"
                "glyph remove: remove all current glyphs\n"
                "glyph remove <slotnumber>: remove glyph from slot\n"
                "glyph all/wanted/equiped: list glyphs";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };    

    /// 自动装配雕文动作：根据职业与专精自动挑选并镶嵌雕文
    class AutoSetGlyphAction : public GlyphAction
    {
    public:
        /// 构造函数：初始化自动装配雕文动作
        AutoSetGlyphAction(PlayerbotAI* ai, std::string name = "auto set glyph") : GlyphAction(ai, name) {}
        /// 执行动作主逻辑（自动装配雕文动作）
        virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "auto set glyph"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This action will automatically apply new glyphs to the bot based on the config.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };
}
