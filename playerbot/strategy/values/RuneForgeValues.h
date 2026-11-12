// 策略值头文件：RuneForgeValues（死亡骑士可用符文熔铸法术、最佳符文选择与附魔需求）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai 
{
    // 值计算器：列出死亡骑士已学会的所有符文熔铸（Runeforging）法术 ID
    class RuneForgeSpellsValue : public CalculatedValue<std::vector<uint32>> {
    public:
        RuneForgeSpellsValue(PlayerbotAI* ai, std::string name = "runeforge spells", int checkInterval = 10)
            : CalculatedValue<std::vector<uint32>>(ai, name, checkInterval) {}
        virtual std::vector<uint32> Calculate() override;
    };

    // 值计算器：根据当前天赋专精与坦克/输出/PvP风格推荐最佳符文附魔法术
    class BestRuneForgeSpellValue : public Uint32CalculatedValue {
    public:
        BestRuneForgeSpellValue(PlayerbotAI* ai, std::string name = "best runeforge spell", int checkInterval = 10)
            : Uint32CalculatedValue(ai, name, checkInterval) {}
        virtual uint32 Calculate() override;
    };

    // 布尔值计算器：判断主手或副手武器当前是否缺少推荐的符文熔铸效果
    class ShouldRuneForgeValue : public BoolCalculatedValue {
    public:
        ShouldRuneForgeValue(PlayerbotAI* ai, std::string name = "should runeforge")
            : BoolCalculatedValue(ai, name) {}
        virtual bool Calculate() override;

        static uint32 RuneForgeEnchantFromSpell(uint32 spellId);
        static int32 CurrentRuneForgeEnchant(Player* bot);
    };
} 