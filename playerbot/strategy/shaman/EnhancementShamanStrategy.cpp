// 萨满祭司 - 增强萨满祭司策略实现文件 (EnhancementShamanStrategy.cpp)

#include "playerbot/playerbot.h"
#include "ShamanMultipliers.h"
#include "EnhancementShamanStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class EnhancementShamanStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    EnhancementShamanStrategyActionNodeFactory()
    {
        creators["stormstrike"] = &stormstrike;
        creators["lava lash"] = &lava_lash;
        creators["searing totem"] = &searing_totem;
        creators["mana spring totem"] = &mana_spring_totem;
        creators["water shield"] = &water_shield;
        creators["magma totem"] = &magma_totem;
        creators["strength of earth totem"] = &strength_of_earth_totem;
        creators["windfury totem"] = &windfury_totem;
        creators["windfury weapon"] = &windfury_weapon;
    }

private:
    // 动作节点 stormstrike：风暴打击 -> 备选(A)动作：熔岩猛击
    ACTION_NODE_A(stormstrike, "stormstrike", "lava lash");

    // 动作节点 lava_lash：熔岩猛击 -> 备选(A)动作：melee
    ACTION_NODE_A(lava_lash, "lava lash", "melee");

    // 动作节点 searing_totem：灼热图腾 -> 备选(A)动作：火舌图腾
    ACTION_NODE_A(searing_totem, "searing totem", "flametongue totem");

    // 动作节点 mana_spring_totem：法力之泉图腾 -> 备选(A)动作：治疗之泉图腾
    ACTION_NODE_A(mana_spring_totem, "mana spring totem", "healing stream totem");

    // 动作节点 magma_totem：熔岩图腾 -> 后续(C)动作：火焰新星
    ACTION_NODE_C(magma_totem, "magma totem", "fire nova");

    // 动作节点 strength_of_earth_totem：大地之力图腾 -> 备选(A)动作：石肤图腾
    ACTION_NODE_A(strength_of_earth_totem, "strength of earth totem", "stoneskin totem");

    // 动作节点 windfury_totem：风怒图腾 -> 备选(A)动作：风之优雅图腾
    ACTION_NODE_A(windfury_totem, "windfury totem", "grace of air totem");

    // 动作节点 windfury_weapon：风怒武器 -> 备选(A)动作：石化武器
    ACTION_NODE_A(windfury_weapon, "windfury weapon", "rockbiter weapon");

    // 动作节点 water_shield：水之盾 -> 备选(A)动作：闪电之盾
    ACTION_NODE_A(water_shield, "water shield", "lightning shield");
};

// 构造函数：初始化增强萨满祭司策略并挂载动作节点工厂
EnhancementShamanStrategy::EnhancementShamanStrategy(PlayerbotAI* ai) : ShamanStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<EnhancementShamanStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (增强萨满祭司策略)
NextAction** EnhancementShamanStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司策略)
void EnhancementShamanStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "stormstrike",
        NextAction::array(0, new NextAction("stormstrike", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "shock",
        NextAction::array(0, new NextAction("earth shock", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司策略)
void EnhancementShamanStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (增强萨满祭司策略)
void EnhancementShamanStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (增强萨满祭司策略)
void EnhancementShamanStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司PVE策略)
void EnhancementShamanPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitCombatTriggers(triggers);
    ShamanPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司PVE策略)
void EnhancementShamanPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (增强萨满祭司PVE策略)
void EnhancementShamanPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitReactionTriggers(triggers);
    ShamanPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (增强萨满祭司PVE策略)
void EnhancementShamanPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitDeadTriggers(triggers);
    ShamanPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司PVP策略)
void EnhancementShamanPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitCombatTriggers(triggers);
    ShamanPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司PVP策略)
void EnhancementShamanPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (增强萨满祭司PVP策略)
void EnhancementShamanPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitReactionTriggers(triggers);
    ShamanPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (增强萨满祭司PVP策略)
void EnhancementShamanPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitDeadTriggers(triggers);
    ShamanPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司团队副本策略)
void EnhancementShamanRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitCombatTriggers(triggers);
    ShamanRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司团队副本策略)
void EnhancementShamanRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (增强萨满祭司团队副本策略)
void EnhancementShamanRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitReactionTriggers(triggers);
    ShamanRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (增强萨满祭司团队副本策略)
void EnhancementShamanRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitDeadTriggers(triggers);
    ShamanRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司AOE群体策略)
void EnhancementShamanAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("fire nova", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司AOE群体策略)
void EnhancementShamanAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司AOE群体PVE策略)
void EnhancementShamanAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司AOE群体PVE策略)
void EnhancementShamanAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司AOE群体PVP策略)
void EnhancementShamanAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司AOE群体PVP策略)
void EnhancementShamanAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司AOE群体团队副本策略)
void EnhancementShamanAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司AOE群体团队副本策略)
void EnhancementShamanAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司控制(CC)策略)
void EnhancementShamanCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "frost shock snare",
        NextAction::array(0, new NextAction("frost shock", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司控制(CC)策略)
void EnhancementShamanCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司控制(CC)PVE策略)
void EnhancementShamanCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司控制(CC)PVE策略)
void EnhancementShamanCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司控制(CC)PVP策略)
void EnhancementShamanCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司控制(CC)PVP策略)
void EnhancementShamanCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司控制(CC)团队副本策略)
void EnhancementShamanCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司控制(CC)团队副本策略)
void EnhancementShamanCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司驱散净化策略)
void EnhancementShamanCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司驱散净化策略)
void EnhancementShamanCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司驱散净化PVE策略)
void EnhancementShamanCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司驱散净化PVE策略)
void EnhancementShamanCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司驱散净化PVP策略)
void EnhancementShamanCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司驱散净化PVP策略)
void EnhancementShamanCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司驱散净化团队副本策略)
void EnhancementShamanCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司驱散净化团队副本策略)
void EnhancementShamanCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司图腾策略)
void EnhancementShamanTotemsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "air totem",
        NextAction::array(0, new NextAction("windfury totem", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "air totem",
        NextAction::array(0, new NextAction("grace of air totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "water totem",
        NextAction::array(0, new NextAction("mana spring totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem aoe",
        NextAction::array(0, new NextAction("magma totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem",
        NextAction::array(0, new NextAction("searing totem", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司图腾策略)
void EnhancementShamanTotemsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司图腾PVE策略)
void EnhancementShamanTotemsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司图腾PVE策略)
void EnhancementShamanTotemsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司图腾PVP策略)
void EnhancementShamanTotemsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司图腾PVP策略)
void EnhancementShamanTotemsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司图腾团队副本策略)
void EnhancementShamanTotemsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司图腾团队副本策略)
void EnhancementShamanTotemsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司增益Buff策略)
void EnhancementShamanBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("windfury weapon", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司增益Buff策略)
void EnhancementShamanBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("windfury weapon", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "lightning shield",
        NextAction::array(0, new NextAction("lightning shield", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (增强萨满祭司增益BuffPVE策略)
void EnhancementShamanBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司增益BuffPVE策略)
void EnhancementShamanBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司增益BuffPVP策略)
void EnhancementShamanBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司增益BuffPVP策略)
void EnhancementShamanBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司增益Buff团队副本策略)
void EnhancementShamanBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司增益Buff团队副本策略)
void EnhancementShamanBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司爆发增益策略)
void EnhancementShamanBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司爆发增益策略)
void EnhancementShamanBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司爆发增益PVE策略)
void EnhancementShamanBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司爆发增益PVE策略)
void EnhancementShamanBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司爆发增益PVP策略)
void EnhancementShamanBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司爆发增益PVP策略)
void EnhancementShamanBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司爆发增益团队副本策略)
void EnhancementShamanBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司爆发增益团队副本策略)
void EnhancementShamanBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (增强萨满祭司策略)
NextAction** EnhancementShamanStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司策略)
void EnhancementShamanStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "stormstrike",
        NextAction::array(0, new NextAction("stormstrike", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "flame shock",
        NextAction::array(0, new NextAction("flame shock", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "shock",
        NextAction::array(0, new NextAction("earth shock", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司策略)
void EnhancementShamanStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (增强萨满祭司策略)
void EnhancementShamanStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (增强萨满祭司策略)
void EnhancementShamanStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司PVE策略)
void EnhancementShamanPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitCombatTriggers(triggers);
    ShamanPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司PVE策略)
void EnhancementShamanPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (增强萨满祭司PVE策略)
void EnhancementShamanPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitReactionTriggers(triggers);
    ShamanPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (增强萨满祭司PVE策略)
void EnhancementShamanPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitDeadTriggers(triggers);
    ShamanPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司PVP策略)
void EnhancementShamanPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitCombatTriggers(triggers);
    ShamanPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司PVP策略)
void EnhancementShamanPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (增强萨满祭司PVP策略)
void EnhancementShamanPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitReactionTriggers(triggers);
    ShamanPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (增强萨满祭司PVP策略)
void EnhancementShamanPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitDeadTriggers(triggers);
    ShamanPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司团队副本策略)
void EnhancementShamanRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitCombatTriggers(triggers);
    ShamanRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司团队副本策略)
void EnhancementShamanRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (增强萨满祭司团队副本策略)
void EnhancementShamanRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitReactionTriggers(triggers);
    ShamanRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (增强萨满祭司团队副本策略)
void EnhancementShamanRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitDeadTriggers(triggers);
    ShamanRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司AOE群体策略)
void EnhancementShamanAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("fire nova", ACTION_HIGH), NULL)));

    //triggers.push_back(new TriggerNode(
        //"melee light aoe",
        //NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司AOE群体策略)
void EnhancementShamanAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司AOE群体PVE策略)
void EnhancementShamanAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司AOE群体PVE策略)
void EnhancementShamanAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司AOE群体PVP策略)
void EnhancementShamanAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司AOE群体PVP策略)
void EnhancementShamanAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司AOE群体团队副本策略)
void EnhancementShamanAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司AOE群体团队副本策略)
void EnhancementShamanAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司控制(CC)策略)
void EnhancementShamanCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "frost shock snare",
        NextAction::array(0, new NextAction("frost shock", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司控制(CC)策略)
void EnhancementShamanCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司控制(CC)PVE策略)
void EnhancementShamanCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司控制(CC)PVE策略)
void EnhancementShamanCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司控制(CC)PVP策略)
void EnhancementShamanCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司控制(CC)PVP策略)
void EnhancementShamanCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司控制(CC)团队副本策略)
void EnhancementShamanCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司控制(CC)团队副本策略)
void EnhancementShamanCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司驱散净化策略)
void EnhancementShamanCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司驱散净化策略)
void EnhancementShamanCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司驱散净化PVE策略)
void EnhancementShamanCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司驱散净化PVE策略)
void EnhancementShamanCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司驱散净化PVP策略)
void EnhancementShamanCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司驱散净化PVP策略)
void EnhancementShamanCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司驱散净化团队副本策略)
void EnhancementShamanCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司驱散净化团队副本策略)
void EnhancementShamanCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司图腾策略)
void EnhancementShamanTotemsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "air totem",
        NextAction::array(0, new NextAction("windfury totem", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "air totem",
        NextAction::array(0, new NextAction("grace of air totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "water totem",
        NextAction::array(0, new NextAction("mana spring totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem aoe",
        NextAction::array(0, new NextAction("magma totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem",
        NextAction::array(0, new NextAction("flametongue totem", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司图腾策略)
void EnhancementShamanTotemsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司图腾PVE策略)
void EnhancementShamanTotemsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司图腾PVE策略)
void EnhancementShamanTotemsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司图腾PVP策略)
void EnhancementShamanTotemsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司图腾PVP策略)
void EnhancementShamanTotemsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司图腾团队副本策略)
void EnhancementShamanTotemsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司图腾团队副本策略)
void EnhancementShamanTotemsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司增益Buff策略)
void EnhancementShamanBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("windfury weapon", ACTION_HIGH), NULL)));

}

// 初始化非战斗阶段触发器列表 (增强萨满祭司增益Buff策略)
void EnhancementShamanBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("windfury weapon", ACTION_NORMAL), NULL)));

}

// 初始化战斗阶段触发器列表 (增强萨满祭司增益BuffPVE策略)
void EnhancementShamanBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "lightning shield",
        NextAction::array(0, new NextAction("lightning shield", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司增益BuffPVE策略)
void EnhancementShamanBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "lightning shield",
        NextAction::array(0, new NextAction("lightning shield", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (增强萨满祭司增益BuffPVP策略)
void EnhancementShamanBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "lightning shield",
        NextAction::array(0, new NextAction("lightning shield", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司增益BuffPVP策略)
void EnhancementShamanBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "lightning shield",
        NextAction::array(0, new NextAction("lightning shield", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (增强萨满祭司增益Buff团队副本策略)
void EnhancementShamanBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "lightning shield",
        NextAction::array(0, new NextAction("water shield", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司增益Buff团队副本策略)
void EnhancementShamanBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "lightning shield",
        NextAction::array(0, new NextAction("water shield", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (增强萨满祭司爆发增益策略)
void EnhancementShamanBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司爆发增益策略)
void EnhancementShamanBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司爆发增益PVE策略)
void EnhancementShamanBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司爆发增益PVE策略)
void EnhancementShamanBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司爆发增益PVP策略)
void EnhancementShamanBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司爆发增益PVP策略)
void EnhancementShamanBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司爆发增益团队副本策略)
void EnhancementShamanBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司爆发增益团队副本策略)
void EnhancementShamanBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (增强萨满祭司策略)
NextAction** EnhancementShamanStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司策略)
void EnhancementShamanStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "stormstrike",
        NextAction::array(0, new NextAction("stormstrike", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "shock",
        NextAction::array(0, new NextAction("earth shock", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司策略)
void EnhancementShamanStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (增强萨满祭司策略)
void EnhancementShamanStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (增强萨满祭司策略)
void EnhancementShamanStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司PVE策略)
void EnhancementShamanPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitCombatTriggers(triggers);
    ShamanPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司PVE策略)
void EnhancementShamanPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (增强萨满祭司PVE策略)
void EnhancementShamanPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitReactionTriggers(triggers);
    ShamanPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (增强萨满祭司PVE策略)
void EnhancementShamanPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitDeadTriggers(triggers);
    ShamanPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司PVP策略)
void EnhancementShamanPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitCombatTriggers(triggers);
    ShamanPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司PVP策略)
void EnhancementShamanPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (增强萨满祭司PVP策略)
void EnhancementShamanPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitReactionTriggers(triggers);
    ShamanPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (增强萨满祭司PVP策略)
void EnhancementShamanPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitDeadTriggers(triggers);
    ShamanPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司团队副本策略)
void EnhancementShamanRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitCombatTriggers(triggers);
    ShamanRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司团队副本策略)
void EnhancementShamanRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (增强萨满祭司团队副本策略)
void EnhancementShamanRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitReactionTriggers(triggers);
    ShamanRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (增强萨满祭司团队副本策略)
void EnhancementShamanRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanStrategy::InitDeadTriggers(triggers);
    ShamanRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司AOE群体策略)
void EnhancementShamanAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("fire nova", ACTION_HIGH), NULL)));

    //triggers.push_back(new TriggerNode(
        //"melee light aoe",
        //NextAction::array(0, new NextAction("oil of immolation", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司AOE群体策略)
void EnhancementShamanAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司AOE群体PVE策略)
void EnhancementShamanAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司AOE群体PVE策略)
void EnhancementShamanAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司AOE群体PVP策略)
void EnhancementShamanAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司AOE群体PVP策略)
void EnhancementShamanAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司AOE群体团队副本策略)
void EnhancementShamanAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司AOE群体团队副本策略)
void EnhancementShamanAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司控制(CC)策略)
void EnhancementShamanCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "frost shock snare",
        NextAction::array(0, new NextAction("frost shock", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司控制(CC)策略)
void EnhancementShamanCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司控制(CC)PVE策略)
void EnhancementShamanCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司控制(CC)PVE策略)
void EnhancementShamanCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司控制(CC)PVP策略)
void EnhancementShamanCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("throw grenade", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司控制(CC)PVP策略)
void EnhancementShamanCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司控制(CC)团队副本策略)
void EnhancementShamanCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司控制(CC)团队副本策略)
void EnhancementShamanCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司驱散净化策略)
void EnhancementShamanCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司驱散净化策略)
void EnhancementShamanCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司驱散净化PVE策略)
void EnhancementShamanCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司驱散净化PVE策略)
void EnhancementShamanCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司驱散净化PVP策略)
void EnhancementShamanCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司驱散净化PVP策略)
void EnhancementShamanCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司驱散净化团队副本策略)
void EnhancementShamanCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司驱散净化团队副本策略)
void EnhancementShamanCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司图腾策略)
void EnhancementShamanTotemsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "air totem",
        NextAction::array(0, new NextAction("windfury totem", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "air totem",
        NextAction::array(0, new NextAction("grace of air totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "water totem",
        NextAction::array(0, new NextAction("mana spring totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem aoe",
        NextAction::array(0, new NextAction("magma totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem",
        NextAction::array(0, new NextAction("flametongue totem", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司图腾策略)
void EnhancementShamanTotemsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司图腾PVE策略)
void EnhancementShamanTotemsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司图腾PVE策略)
void EnhancementShamanTotemsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司图腾PVP策略)
void EnhancementShamanTotemsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司图腾PVP策略)
void EnhancementShamanTotemsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司图腾团队副本策略)
void EnhancementShamanTotemsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司图腾团队副本策略)
void EnhancementShamanTotemsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司增益Buff策略)
void EnhancementShamanBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("windfury weapon", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司增益Buff策略)
void EnhancementShamanBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("windfury weapon", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "lightning shield",
        NextAction::array(0, new NextAction("lightning shield", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (增强萨满祭司增益BuffPVE策略)
void EnhancementShamanBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司增益BuffPVE策略)
void EnhancementShamanBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司增益BuffPVP策略)
void EnhancementShamanBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司增益BuffPVP策略)
void EnhancementShamanBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司增益Buff团队副本策略)
void EnhancementShamanBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司增益Buff团队副本策略)
void EnhancementShamanBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司爆发增益策略)
void EnhancementShamanBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司爆发增益策略)
void EnhancementShamanBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司爆发增益PVE策略)
void EnhancementShamanBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司爆发增益PVE策略)
void EnhancementShamanBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司爆发增益PVP策略)
void EnhancementShamanBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司爆发增益PVP策略)
void EnhancementShamanBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (增强萨满祭司爆发增益团队副本策略)
void EnhancementShamanBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (增强萨满祭司爆发增益团队副本策略)
void EnhancementShamanBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    EnhancementShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
