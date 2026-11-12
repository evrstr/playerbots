/// 通用非战斗基础行为、碰撞避让、世界增益、雕文与钓鱼策略实现

#include "playerbot/playerbot.h"
#include "NonCombatStrategy.h"
#include "playerbot/strategy/Value.h"

using namespace ai;

/// 初始化非战斗触发器：坐骑检查、AI Value 检查及黑暗之门穿越流程
void NonCombatStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("check mount state", 1.0f), new NextAction("check values", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "near dark portal",
        NextAction::array(0, new NextAction("move to dark portal", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "at dark portal azeroth",
        NextAction::array(0, new NextAction("use dark portal azeroth", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "at dark portal outland",
        NextAction::array(0, new NextAction("move from dark portal", 1.0f), NULL)));

    /*
    triggers.push_back(new TriggerNode(
        "vehicle near",
        NextAction::array(0, new NextAction("enter vehicle", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("use lightwell", 80.0f), NULL)));
    */
}

/// 初始化碰撞避让触发器：与其他机器人模型重叠时轻微错开站位
void CollisionStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "collision",
        NextAction::array(0, new NextAction("move out of collision", 2.0f), NULL)));
}

/// 初始化坐骑策略触发器
void MountStrategy::InitNonCombatTriggers(std::list<TriggerNode*> &triggers)
{
    /*triggers.push_back(new TriggerNode(
        "no possible targets",
        NextAction::array(0, new NextAction("mount", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "no rpg target",
        NextAction::array(0, new NextAction("mount", 1.0f), NULL)));*/

    /*triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("mount", 4.0f), NULL)));*/
}

/// 初始化作弊世界增益触发器：缺少预设世界 Buff 时自动补全
void WorldBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "need world buff",
        NextAction::array(0, new NextAction("world buff", 1.0f), NULL)));
}

/// 移除世界增益策略时清除所有由其施加的预设世界 Buff 光环
void WorldBuffStrategy::OnStrategyRemoved(BotState state)
{
    // Remove world buffs | 移除已施加的世界增益光环
    Player* bot = ai->GetBot();
    if (bot)
    {
        for (auto& wb : sPlayerbotAIConfig.worldBuffs)
        {
            if (bot->HasAura(wb.spellId))
            {
                bot->RemoveAurasDueToSpell(wb.spellId);
            }
        }
    }
}

/// 初始化停战触发器：定期取消声望界面的“交战中”标记
void NoWarStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "at war",
        NextAction::array(0, new NextAction("faction", 1.0f), NULL)));
}

/// 初始化雕文策略触发器：定期自动装配配置的最佳雕文
void GlyphStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "apply glyphs",
        NextAction::array(0, new NextAction("auto set glyph", 1.0f), NULL)));
}

/// 初始化钓鱼策略触发器：寻水甩杆、点击鱼漂及钓鱼结束后换回装备
void FishStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "val::can fish",
        NextAction::array(0, new NextAction("move to fish" + modifier, 5.0f), new NextAction("fish" + modifier, 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "val::can open fishing dobber",
        NextAction::array(0, new NextAction("use fishing bobber", 99.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "val::done fishing",
        NextAction::array(0, new NextAction("equip upgrades", 6.0f), NULL)));
}
