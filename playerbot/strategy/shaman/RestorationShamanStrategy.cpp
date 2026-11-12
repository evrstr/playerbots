// 萨满祭司 - 恢复萨满祭司策略实现文件 (RestorationShamanStrategy.cpp)

#include "playerbot/playerbot.h"
#include "ShamanMultipliers.h"
#include "RestorationShamanStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class RestorationShamanStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    RestorationShamanStrategyActionNodeFactory()
    {
        creators["earthliving weapon"] = &earthliving_weapon;
        creators["mana tide totem"] = &mana_tide_totem;
        creators["searing totem"] = &searing_totem;
        creators["magma totem"] = &magma_totem;
        creators["strength of earth totem"] = &strength_of_earth_totem;
        creators["windfury"] = &windfury_totem;
        creators["healing stream totem"] = &healing_stream_totem;
        creators["riptide"] = &riptide;
        creators["riptide on party"] = &riptide_on_party;
        creators["chain heal"] = &chain_heal;
        creators["chain heal on party"] = &chain_heal_on_party;
    }

private:
    // 动作节点 earthliving_weapon：大地生命武器 -> 备选(A)动作：火舌武器
    ACTION_NODE_A(earthliving_weapon, "earthliving weapon", "flametongue weapon");

    // 动作节点 mana_tide_totem：法力之潮图腾 -> 备选(A)动作：mana potion
    ACTION_NODE_A(mana_tide_totem, "mana tide totem", "mana potion");

    // 动作节点 searing_totem：灼热图腾 -> 备选(A)动作：火舌图腾
    ACTION_NODE_A(searing_totem, "searing totem", "flametongue totem");

    // 动作节点 magma_totem：熔岩图腾 -> 后续(C)动作：火焰新星
    ACTION_NODE_C(magma_totem, "magma totem", "fire nova");

    // 动作节点 strength_of_earth_totem：大地之力图腾 -> 备选(A)动作：石肤图腾
    ACTION_NODE_A(strength_of_earth_totem, "strength of earth totem", "stoneskin totem");

    // 动作节点 windfury_totem：风怒图腾 -> 备选(A)动作：空气之怒图腾
    ACTION_NODE_A(windfury_totem, "windfury totem", "wrath of air totem");

    // 动作节点 healing_stream_totem：治疗之泉图腾 -> 备选(A)动作：法力之泉图腾
    ACTION_NODE_A(healing_stream_totem, "healing stream totem", "mana spring totem");

    // 动作节点 riptide：激流 -> 备选(A)动作：治疗波
    ACTION_NODE_A(riptide, "riptide", "healing wave");

    // 动作节点 riptide_on_party：对队友施放激流 -> 备选(A)动作：治疗波 (对队友)
    ACTION_NODE_A(riptide_on_party, "riptide on party", "healing wave on party");

    // 动作节点 chain_heal：治疗链 -> 备选(A)动作：次级治疗波
    ACTION_NODE_A(chain_heal, "chain heal", "lesser healing wave");

    // 动作节点 chain_heal_on_party：对队友施放治疗链 -> 备选(A)动作：对队友施放次级治疗波
    ACTION_NODE_A(chain_heal_on_party, "chain heal on party", "lesser healing wave on party");
};

// 构造函数：初始化恢复萨满祭司策略并挂载动作节点工厂
RestorationShamanStrategy::RestorationShamanStrategy(PlayerbotAI* ai) : ShamanStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<RestorationShamanStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (恢复萨满祭司策略)
void RestorationShamanStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    ShamanStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("mana tide totem", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("healing wave", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("riptide", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("riptide on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("chain heal", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("healing wave", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("lesser healing wave", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("lesser healing wave on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司策略)
void RestorationShamanStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("healing wave", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("riptide", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("riptide on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("healing wave", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("lesser healing wave", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("lesser healing wave on party", ACTION_NORMAL), NULL)));
}

// 初始化反应阶段触发器列表 (恢复萨满祭司策略)
void RestorationShamanStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复萨满祭司策略)
void RestorationShamanStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司PVE策略)
void RestorationShamanPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitCombatTriggers(triggers);
    ShamanPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司PVE策略)
void RestorationShamanPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复萨满祭司PVE策略)
void RestorationShamanPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitReactionTriggers(triggers);
    ShamanPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复萨满祭司PVE策略)
void RestorationShamanPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitDeadTriggers(triggers);
    ShamanPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司PVP策略)
void RestorationShamanPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitCombatTriggers(triggers);
    ShamanPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司PVP策略)
void RestorationShamanPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复萨满祭司PVP策略)
void RestorationShamanPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitReactionTriggers(triggers);
    ShamanPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复萨满祭司PVP策略)
void RestorationShamanPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitDeadTriggers(triggers);
    ShamanPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司团队副本策略)
void RestorationShamanRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitCombatTriggers(triggers);
    ShamanRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司团队副本策略)
void RestorationShamanRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复萨满祭司团队副本策略)
void RestorationShamanRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitReactionTriggers(triggers);
    ShamanRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复萨满祭司团队副本策略)
void RestorationShamanRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitDeadTriggers(triggers);
    ShamanRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司AOE群体策略)
void RestorationShamanAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司AOE群体策略)
void RestorationShamanAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司AOE群体PVE策略)
void RestorationShamanAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司AOE群体PVE策略)
void RestorationShamanAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司AOE群体PVP策略)
void RestorationShamanAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司AOE群体PVP策略)
void RestorationShamanAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司AOE群体团队副本策略)
void RestorationShamanAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司AOE群体团队副本策略)
void RestorationShamanAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司控制(CC)策略)
void RestorationShamanCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司控制(CC)策略)
void RestorationShamanCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司控制(CC)PVE策略)
void RestorationShamanCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司控制(CC)PVE策略)
void RestorationShamanCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司控制(CC)PVP策略)
void RestorationShamanCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司控制(CC)PVP策略)
void RestorationShamanCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司控制(CC)团队副本策略)
void RestorationShamanCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司控制(CC)团队副本策略)
void RestorationShamanCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司驱散净化策略)
void RestorationShamanCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司驱散净化策略)
void RestorationShamanCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司驱散净化PVE策略)
void RestorationShamanCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司驱散净化PVE策略)
void RestorationShamanCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司驱散净化PVP策略)
void RestorationShamanCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司驱散净化PVP策略)
void RestorationShamanCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司驱散净化团队副本策略)
void RestorationShamanCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司驱散净化团队副本策略)
void RestorationShamanCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司图腾策略)
void RestorationShamanTotemsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "air totem",
        NextAction::array(0, new NextAction("windfury totem", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "air totem",
        NextAction::array(0, new NextAction("wrath of air totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "water totem",
        NextAction::array(0, new NextAction("healing stream totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem",
        NextAction::array(0, new NextAction("searing totem", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司图腾策略)
void RestorationShamanTotemsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司图腾PVE策略)
void RestorationShamanTotemsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司图腾PVE策略)
void RestorationShamanTotemsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司图腾PVP策略)
void RestorationShamanTotemsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司图腾PVP策略)
void RestorationShamanTotemsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司图腾团队副本策略)
void RestorationShamanTotemsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司图腾团队副本策略)
void RestorationShamanTotemsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司增益Buff策略)
void RestorationShamanBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司增益Buff策略)
void RestorationShamanBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司增益BuffPVE策略)
void RestorationShamanBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("earthliving weapon", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司增益BuffPVE策略)
void RestorationShamanBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("earthliving weapon", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司增益BuffPVP策略)
void RestorationShamanBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("earthliving weapon", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司增益BuffPVP策略)
void RestorationShamanBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("earthliving weapon", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司增益Buff团队副本策略)
void RestorationShamanBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司增益Buff团队副本策略)
void RestorationShamanBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司爆发增益策略)
void RestorationShamanBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司爆发增益策略)
void RestorationShamanBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司爆发增益PVE策略)
void RestorationShamanBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司爆发增益PVE策略)
void RestorationShamanBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司爆发增益PVP策略)
void RestorationShamanBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司爆发增益PVP策略)
void RestorationShamanBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司爆发增益团队副本策略)
void RestorationShamanBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司爆发增益团队副本策略)
void RestorationShamanBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (恢复萨满祭司策略)
void RestorationShamanStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("mana tide totem", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("healing wave", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("riptide", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("riptide on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("chain heal", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("healing wave", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("lesser healing wave", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("lesser healing wave on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司策略)
void RestorationShamanStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("healing wave", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("riptide", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("riptide on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("healing wave", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("lesser healing wave", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("lesser healing wave on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (恢复萨满祭司策略)
void RestorationShamanStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复萨满祭司策略)
void RestorationShamanStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司PVE策略)
void RestorationShamanPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitCombatTriggers(triggers);
    ShamanPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司PVE策略)
void RestorationShamanPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复萨满祭司PVE策略)
void RestorationShamanPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitReactionTriggers(triggers);
    ShamanPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复萨满祭司PVE策略)
void RestorationShamanPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitDeadTriggers(triggers);
    ShamanPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司PVP策略)
void RestorationShamanPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitCombatTriggers(triggers);
    ShamanPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司PVP策略)
void RestorationShamanPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复萨满祭司PVP策略)
void RestorationShamanPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitReactionTriggers(triggers);
    ShamanPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复萨满祭司PVP策略)
void RestorationShamanPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitDeadTriggers(triggers);
    ShamanPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司团队副本策略)
void RestorationShamanRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitCombatTriggers(triggers);
    ShamanRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司团队副本策略)
void RestorationShamanRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复萨满祭司团队副本策略)
void RestorationShamanRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitReactionTriggers(triggers);
    ShamanRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复萨满祭司团队副本策略)
void RestorationShamanRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitDeadTriggers(triggers);
    ShamanRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司AOE群体策略)
void RestorationShamanAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司AOE群体策略)
void RestorationShamanAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司AOE群体PVE策略)
void RestorationShamanAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司AOE群体PVE策略)
void RestorationShamanAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司AOE群体PVP策略)
void RestorationShamanAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司AOE群体PVP策略)
void RestorationShamanAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司AOE群体团队副本策略)
void RestorationShamanAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司AOE群体团队副本策略)
void RestorationShamanAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司控制(CC)策略)
void RestorationShamanCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司控制(CC)策略)
void RestorationShamanCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司控制(CC)PVE策略)
void RestorationShamanCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司控制(CC)PVE策略)
void RestorationShamanCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司控制(CC)PVP策略)
void RestorationShamanCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司控制(CC)PVP策略)
void RestorationShamanCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司控制(CC)团队副本策略)
void RestorationShamanCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司控制(CC)团队副本策略)
void RestorationShamanCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司驱散净化策略)
void RestorationShamanCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司驱散净化策略)
void RestorationShamanCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司驱散净化PVE策略)
void RestorationShamanCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司驱散净化PVE策略)
void RestorationShamanCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司驱散净化PVP策略)
void RestorationShamanCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司驱散净化PVP策略)
void RestorationShamanCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司驱散净化团队副本策略)
void RestorationShamanCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司驱散净化团队副本策略)
void RestorationShamanCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司图腾策略)
void RestorationShamanTotemsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "air totem",
        NextAction::array(0, new NextAction("windfury totem", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "air totem",
        NextAction::array(0, new NextAction("wrath of air totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "water totem",
        NextAction::array(0, new NextAction("healing stream totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem",
        NextAction::array(0, new NextAction("flametongue totem", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司图腾策略)
void RestorationShamanTotemsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司图腾PVE策略)
void RestorationShamanTotemsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司图腾PVE策略)
void RestorationShamanTotemsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司图腾PVP策略)
void RestorationShamanTotemsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司图腾PVP策略)
void RestorationShamanTotemsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司图腾团队副本策略)
void RestorationShamanTotemsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司图腾团队副本策略)
void RestorationShamanTotemsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司增益Buff策略)
void RestorationShamanBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "water shield",
        NextAction::array(0, new NextAction("water shield", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司增益Buff策略)
void RestorationShamanBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "water shield",
        NextAction::array(0, new NextAction("water shield", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司增益BuffPVE策略)
void RestorationShamanBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("earthliving weapon", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司增益BuffPVE策略)
void RestorationShamanBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("earthliving weapon", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司增益BuffPVP策略)
void RestorationShamanBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("earthliving weapon", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司增益BuffPVP策略)
void RestorationShamanBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitNonCombatTriggers(triggers);

        triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("earthliving weapon", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司增益Buff团队副本策略)
void RestorationShamanBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "earth shield on party tank",
        NextAction::array(0, new NextAction("earth shield on party tank", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司增益Buff团队副本策略)
void RestorationShamanBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "earth shield on party tank",
        NextAction::array(0, new NextAction("earth shield on party tank", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司爆发增益策略)
void RestorationShamanBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司爆发增益策略)
void RestorationShamanBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司爆发增益PVE策略)
void RestorationShamanBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司爆发增益PVE策略)
void RestorationShamanBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司爆发增益PVP策略)
void RestorationShamanBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司爆发增益PVP策略)
void RestorationShamanBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司爆发增益团队副本策略)
void RestorationShamanBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司爆发增益团队副本策略)
void RestorationShamanBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (恢复萨满祭司策略)
void RestorationShamanStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("mana tide totem", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("healing wave", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("riptide", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("riptide on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("chain heal", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("healing wave", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("lesser healing wave", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("lesser healing wave on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司策略)
void RestorationShamanStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("healing wave", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("riptide", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("riptide on party", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("healing wave", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("lesser healing wave", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("lesser healing wave on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (恢复萨满祭司策略)
void RestorationShamanStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复萨满祭司策略)
void RestorationShamanStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司PVE策略)
void RestorationShamanPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitCombatTriggers(triggers);
    ShamanPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司PVE策略)
void RestorationShamanPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复萨满祭司PVE策略)
void RestorationShamanPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitReactionTriggers(triggers);
    ShamanPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复萨满祭司PVE策略)
void RestorationShamanPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitDeadTriggers(triggers);
    ShamanPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司PVP策略)
void RestorationShamanPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitCombatTriggers(triggers);
    ShamanPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司PVP策略)
void RestorationShamanPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复萨满祭司PVP策略)
void RestorationShamanPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitReactionTriggers(triggers);
    ShamanPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复萨满祭司PVP策略)
void RestorationShamanPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitDeadTriggers(triggers);
    ShamanPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司团队副本策略)
void RestorationShamanRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitCombatTriggers(triggers);
    ShamanRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司团队副本策略)
void RestorationShamanRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (恢复萨满祭司团队副本策略)
void RestorationShamanRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitReactionTriggers(triggers);
    ShamanRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (恢复萨满祭司团队副本策略)
void RestorationShamanRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanStrategy::InitDeadTriggers(triggers);
    ShamanRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司AOE群体策略)
void RestorationShamanAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司AOE群体策略)
void RestorationShamanAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司AOE群体PVE策略)
void RestorationShamanAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司AOE群体PVE策略)
void RestorationShamanAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司AOE群体PVP策略)
void RestorationShamanAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司AOE群体PVP策略)
void RestorationShamanAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司AOE群体团队副本策略)
void RestorationShamanAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司AOE群体团队副本策略)
void RestorationShamanAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司控制(CC)策略)
void RestorationShamanCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司控制(CC)策略)
void RestorationShamanCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司控制(CC)PVE策略)
void RestorationShamanCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司控制(CC)PVE策略)
void RestorationShamanCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司控制(CC)PVP策略)
void RestorationShamanCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司控制(CC)PVP策略)
void RestorationShamanCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司控制(CC)团队副本策略)
void RestorationShamanCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司控制(CC)团队副本策略)
void RestorationShamanCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司驱散净化策略)
void RestorationShamanCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司驱散净化策略)
void RestorationShamanCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司驱散净化PVE策略)
void RestorationShamanCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司驱散净化PVE策略)
void RestorationShamanCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司驱散净化PVP策略)
void RestorationShamanCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司驱散净化PVP策略)
void RestorationShamanCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司驱散净化团队副本策略)
void RestorationShamanCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司驱散净化团队副本策略)
void RestorationShamanCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司图腾策略)
void RestorationShamanTotemsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "air totem",
        NextAction::array(0, new NextAction("windfury totem", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "air totem",
        NextAction::array(0, new NextAction("wrath of air totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "water totem",
        NextAction::array(0, new NextAction("healing stream totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem",
        NextAction::array(0, new NextAction("flametongue totem", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司图腾策略)
void RestorationShamanTotemsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司图腾PVE策略)
void RestorationShamanTotemsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司图腾PVE策略)
void RestorationShamanTotemsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司图腾PVP策略)
void RestorationShamanTotemsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司图腾PVP策略)
void RestorationShamanTotemsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司图腾团队副本策略)
void RestorationShamanTotemsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司图腾团队副本策略)
void RestorationShamanTotemsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司增益Buff策略)
void RestorationShamanBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("earthliving weapon", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "water shield",
        NextAction::array(0, new NextAction("water shield", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司增益Buff策略)
void RestorationShamanBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("earthliving weapon", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "water shield",
        NextAction::array(0, new NextAction("water shield", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司增益BuffPVE策略)
void RestorationShamanBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司增益BuffPVE策略)
void RestorationShamanBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司增益BuffPVP策略)
void RestorationShamanBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司增益BuffPVP策略)
void RestorationShamanBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司增益Buff团队副本策略)
void RestorationShamanBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "earth shield on party tank",
        NextAction::array(0, new NextAction("earth shield on party tank", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司增益Buff团队副本策略)
void RestorationShamanBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "earth shield on party tank",
        NextAction::array(0, new NextAction("earth shield on party tank", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司爆发增益策略)
void RestorationShamanBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司爆发增益策略)
void RestorationShamanBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司爆发增益PVE策略)
void RestorationShamanBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司爆发增益PVE策略)
void RestorationShamanBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司爆发增益PVP策略)
void RestorationShamanBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司爆发增益PVP策略)
void RestorationShamanBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (恢复萨满祭司爆发增益团队副本策略)
void RestorationShamanBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (恢复萨满祭司爆发增益团队副本策略)
void RestorationShamanBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    RestorationShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
