// 策略值头文件：GlyphValues（可用雕文、预设目标雕文、已装备雕文与升级判定）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 雕文插槽类型枚举（大雕文、小雕文、无槽位、未解锁槽位）
    enum class GlyphSlotType : uint8
    {
          MAJOR_SLOT = 0
        , MINOR_SLOT = 1
        , NO_SLOT = 98
        , LOCKED_SLOT = 99
    };

    // 值计算器：列出机器人当前职业可用且拥有（或作弊开启）的雕文物品 ID
    class AvailableGlyphsValue : public CalculatedValue<std::vector<uint32>>
    {
    public:
        AvailableGlyphsValue(PlayerbotAI* ai, std::string name = "available glyphs") : CalculatedValue<std::vector<uint32>>(ai, name, 30) {}

        std::vector<uint32> Calculate() override;

        static uint32 GetGlyphIdFromProto(const ItemPrototype* glyphProto);
        static const ItemPrototype* GetGlyphProtoFromGlyphId(uint32 glyphId, uint32 classMask);

        static GlyphSlotType GetGlyphSlotTypeFromItemId(uint32 itemId);
        static GlyphSlotType GetGlyphSlotTypeFromSlot(uint8 slotId, uint32 level = 80);
    };

    // 值计算器：根据当前天赋树与等级从预设配置中选取期望雕文列表
    class WantedGlyphsValue : public AvailableGlyphsValue
    {
    public:
        WantedGlyphsValue(PlayerbotAI* ai) : AvailableGlyphsValue(ai, "wanted glyphs") {}

        std::vector<uint32> Calculate() override;
    };

    // 值计算器：读取机器人当前所有雕文插槽已安装的雕文物品 ID
    class EquipedGlyphsValue : public AvailableGlyphsValue
    {
    public:
        EquipedGlyphsValue(PlayerbotAI* ai) : AvailableGlyphsValue(ai, "equiped glyphs") {}

        std::vector<uint32> Calculate() override;
    };

    // 布尔值计算器：判断指定雕文物品相较于同类型已装备雕文是否为更优升级
    class GlyphIsUpgradeValue : public BoolCalculatedValue, public Qualified
    {
    public:
        GlyphIsUpgradeValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "glyph is upgrade"), Qualified() {}

        static size_t GetWantedRank(uint32 itemId, const std::vector<uint32>& wantedGlyhps);

        bool Calculate() override;
    };
}
