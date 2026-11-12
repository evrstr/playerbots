// 萨满祭司 - 元素萨满祭司策略实现文件 (ElementalShamanStrategy.cpp)

#include "playerbot/playerbot.h"
#include "ShamanMultipliers.h"
#include "ElementalShamanStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class ElementalShamanStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    ElementalShamanStrategyActionNodeFactory()
    {
        creators["flametongue weapon"] = &flametongue_weapon;
        creators["totem of wrath"] = &totem_of_wrath;
        creators["searing totem"] = &searing_totem;
        creators["strength of earth totem"] = &strength_of_earth_totem;
        creators["windfury totem"] = &windfury_totem;
        creators["mana spring totem"] = &mana_spring_totem;
    }

private:
    // 动作节点 flametongue_weapon：火舌武器 -> 备选(A)动作：风怒武器
    ACTION_NODE_A(flametongue_weapon, "flametongue weapon", "windfury weapon");

    // 动作节点 totem_of_wrath：天罚图腾 -> 备选(A)动作：灼热图腾
    ACTION_NODE_A(totem_of_wrath, "totem of wrath", "searing totem");

    // 动作节点 searing_totem：灼热图腾 -> 备选(A)动作：火舌图腾
    ACTION_NODE_A(searing_totem, "searing totem", "flametongue totem");

    // 动作节点 strength_of_earth_totem：大地之力图腾 -> 备选(A)动作：石肤图腾
    ACTION_NODE_A(strength_of_earth_totem, "strength of earth totem", "stoneskin totem");

    // 动作节点 windfury_totem：风怒图腾 -> 备选(A)动作：空气之怒图腾
    ACTION_NODE_A(windfury_totem, "windfury totem", "wrath of air totem");
   
    // 动作节点 mana_spring_totem：法力之泉图腾 -> 备选(A)动作：治疗之泉图腾
    ACTION_NODE_A(mana_spring_totem, "mana spring totem", "healing stream totem");
};

// 构造函数：初始化元素萨满祭司策略并挂载动作节点工厂
ElementalShamanStrategy::ElementalShamanStrategy(PlayerbotAI* ai) 
: ShamanStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<ElementalShamanStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (元素萨满祭司策略)
NextAction** ElementalShamanStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("lightning bolt", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司策略)
void ElementalShamanStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shock",
        NextAction::array(0, new NextAction("earth shock", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司策略)
void ElementalShamanStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (元素萨满祭司策略)
void ElementalShamanStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (元素萨满祭司策略)
void ElementalShamanStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司PVE策略)
void ElementalShamanPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitCombatTriggers(triggers);
    ShamanPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司PVE策略)
void ElementalShamanPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (元素萨满祭司PVE策略)
void ElementalShamanPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitReactionTriggers(triggers);
    ShamanPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (元素萨满祭司PVE策略)
void ElementalShamanPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitDeadTriggers(triggers);
    ShamanPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司PVP策略)
void ElementalShamanPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitCombatTriggers(triggers);
    ShamanPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "chain lightning",
        NextAction::array(0, new NextAction("chain lightning", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("fire nova", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司PVP策略)
void ElementalShamanPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (元素萨满祭司PVP策略)
void ElementalShamanPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitReactionTriggers(triggers);
    ShamanPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (元素萨满祭司PVP策略)
void ElementalShamanPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitDeadTriggers(triggers);
    ShamanPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司团队副本策略)
void ElementalShamanRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitCombatTriggers(triggers);
    ShamanRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司团队副本策略)
void ElementalShamanRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (元素萨满祭司团队副本策略)
void ElementalShamanRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitReactionTriggers(triggers);
    ShamanRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (元素萨满祭司团队副本策略)
void ElementalShamanRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitDeadTriggers(triggers);
    ShamanRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司AOE群体策略)
void ElementalShamanAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ranged light aoe",
        NextAction::array(0, new NextAction("chain lightning", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司AOE群体策略)
void ElementalShamanAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司AOE群体PVE策略)
void ElementalShamanAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司AOE群体PVE策略)
void ElementalShamanAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司AOE群体PVP策略)
void ElementalShamanAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司AOE群体PVP策略)
void ElementalShamanAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司AOE群体团队副本策略)
void ElementalShamanAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司AOE群体团队副本策略)
void ElementalShamanAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司控制(CC)策略)
void ElementalShamanCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "frost shock snare",
        NextAction::array(0, new NextAction("frost shock", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司控制(CC)策略)
void ElementalShamanCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司控制(CC)PVE策略)
void ElementalShamanCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司控制(CC)PVE策略)
void ElementalShamanCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司控制(CC)PVP策略)
void ElementalShamanCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司控制(CC)PVP策略)
void ElementalShamanCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司控制(CC)团队副本策略)
void ElementalShamanCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司控制(CC)团队副本策略)
void ElementalShamanCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司驱散净化策略)
void ElementalShamanCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司驱散净化策略)
void ElementalShamanCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司驱散净化PVE策略)
void ElementalShamanCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司驱散净化PVE策略)
void ElementalShamanCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司驱散净化PVP策略)
void ElementalShamanCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司驱散净化PVP策略)
void ElementalShamanCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司驱散净化团队副本策略)
void ElementalShamanCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司驱散净化团队副本策略)
void ElementalShamanCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司图腾策略)
void ElementalShamanTotemsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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
        NextAction::array(0, new NextAction("mana spring totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem aoe",
        NextAction::array(0, new NextAction("magma totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem",
        NextAction::array(0, new NextAction("totem of wrath", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司图腾策略)
void ElementalShamanTotemsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司图腾PVE策略)
void ElementalShamanTotemsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司图腾PVE策略)
void ElementalShamanTotemsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司图腾PVP策略)
void ElementalShamanTotemsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司图腾PVP策略)
void ElementalShamanTotemsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司图腾团队副本策略)
void ElementalShamanTotemsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司图腾团队副本策略)
void ElementalShamanTotemsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司增益Buff策略)
void ElementalShamanBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司增益Buff策略)
void ElementalShamanBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "lightning shield",
        NextAction::array(0, new NextAction("lightning shield", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (元素萨满祭司增益BuffPVE策略)
void ElementalShamanBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司增益BuffPVE策略)
void ElementalShamanBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (元素萨满祭司增益BuffPVP策略)
void ElementalShamanBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司增益BuffPVP策略)
void ElementalShamanBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (元素萨满祭司增益Buff团队副本策略)
void ElementalShamanBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司增益Buff团队副本策略)
void ElementalShamanBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (元素萨满祭司爆发增益策略)
void ElementalShamanBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司爆发增益策略)
void ElementalShamanBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司爆发增益PVE策略)
void ElementalShamanBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司爆发增益PVE策略)
void ElementalShamanBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司爆发增益PVP策略)
void ElementalShamanBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司爆发增益PVP策略)
void ElementalShamanBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司爆发增益团队副本策略)
void ElementalShamanBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司爆发增益团队副本策略)
void ElementalShamanBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (元素萨满祭司策略)
NextAction** ElementalShamanStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("lightning bolt", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司策略)
void ElementalShamanStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shock",
        NextAction::array(0, new NextAction("earth shock", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司策略)
void ElementalShamanStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (元素萨满祭司策略)
void ElementalShamanStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (元素萨满祭司策略)
void ElementalShamanStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司PVE策略)
void ElementalShamanPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitCombatTriggers(triggers);
    ShamanPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司PVE策略)
void ElementalShamanPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (元素萨满祭司PVE策略)
void ElementalShamanPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitReactionTriggers(triggers);
    ShamanPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (元素萨满祭司PVE策略)
void ElementalShamanPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitDeadTriggers(triggers);
    ShamanPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司PVP策略)
void ElementalShamanPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitCombatTriggers(triggers);
    ShamanPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "chain lightning",
        NextAction::array(0, new NextAction("chain lightning", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("fire nova", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司PVP策略)
void ElementalShamanPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (元素萨满祭司PVP策略)
void ElementalShamanPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitReactionTriggers(triggers);
    ShamanPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (元素萨满祭司PVP策略)
void ElementalShamanPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitDeadTriggers(triggers);
    ShamanPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司团队副本策略)
void ElementalShamanRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitCombatTriggers(triggers);
    ShamanRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司团队副本策略)
void ElementalShamanRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (元素萨满祭司团队副本策略)
void ElementalShamanRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitReactionTriggers(triggers);
    ShamanRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (元素萨满祭司团队副本策略)
void ElementalShamanRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitDeadTriggers(triggers);
    ShamanRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司AOE群体策略)
void ElementalShamanAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ranged light aoe",
        NextAction::array(0, new NextAction("chain lightning", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司AOE群体策略)
void ElementalShamanAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司AOE群体PVE策略)
void ElementalShamanAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司AOE群体PVE策略)
void ElementalShamanAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司AOE群体PVP策略)
void ElementalShamanAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司AOE群体PVP策略)
void ElementalShamanAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司AOE群体团队副本策略)
void ElementalShamanAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司AOE群体团队副本策略)
void ElementalShamanAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司控制(CC)策略)
void ElementalShamanCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "frost shock snare",
        NextAction::array(0, new NextAction("frost shock", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司控制(CC)策略)
void ElementalShamanCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司控制(CC)PVE策略)
void ElementalShamanCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司控制(CC)PVE策略)
void ElementalShamanCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司控制(CC)PVP策略)
void ElementalShamanCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司控制(CC)PVP策略)
void ElementalShamanCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司控制(CC)团队副本策略)
void ElementalShamanCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司控制(CC)团队副本策略)
void ElementalShamanCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司驱散净化策略)
void ElementalShamanCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司驱散净化策略)
void ElementalShamanCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司驱散净化PVE策略)
void ElementalShamanCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司驱散净化PVE策略)
void ElementalShamanCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司驱散净化PVP策略)
void ElementalShamanCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司驱散净化PVP策略)
void ElementalShamanCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司驱散净化团队副本策略)
void ElementalShamanCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司驱散净化团队副本策略)
void ElementalShamanCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司图腾策略)
void ElementalShamanTotemsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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
        NextAction::array(0, new NextAction("mana spring totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem aoe",
        NextAction::array(0, new NextAction("searing totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem",
        NextAction::array(0, new NextAction("totem of wrath", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司图腾策略)
void ElementalShamanTotemsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司图腾PVE策略)
void ElementalShamanTotemsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司图腾PVE策略)
void ElementalShamanTotemsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司图腾PVP策略)
void ElementalShamanTotemsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司图腾PVP策略)
void ElementalShamanTotemsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司图腾团队副本策略)
void ElementalShamanTotemsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司图腾团队副本策略)
void ElementalShamanTotemsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司增益Buff策略)
void ElementalShamanBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "water shield",
        NextAction::array(0, new NextAction("water shield", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司增益Buff策略)
void ElementalShamanBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "water shield",
        NextAction::array(0, new NextAction("water shield", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (元素萨满祭司增益BuffPVE策略)
void ElementalShamanBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司增益BuffPVE策略)
void ElementalShamanBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (元素萨满祭司增益BuffPVP策略)
void ElementalShamanBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司增益BuffPVP策略)
void ElementalShamanBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (元素萨满祭司增益Buff团队副本策略)
void ElementalShamanBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司增益Buff团队副本策略)
void ElementalShamanBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("apply oil", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (元素萨满祭司爆发增益策略)
void ElementalShamanBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司爆发增益策略)
void ElementalShamanBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司爆发增益PVE策略)
void ElementalShamanBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司爆发增益PVE策略)
void ElementalShamanBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司爆发增益PVP策略)
void ElementalShamanBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司爆发增益PVP策略)
void ElementalShamanBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司爆发增益团队副本策略)
void ElementalShamanBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司爆发增益团队副本策略)
void ElementalShamanBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (元素萨满祭司策略)
NextAction** ElementalShamanStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("lightning bolt", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司策略)
void ElementalShamanStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shock",
        NextAction::array(0, new NextAction("earth shock", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司策略)
void ElementalShamanStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (元素萨满祭司策略)
void ElementalShamanStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (元素萨满祭司策略)
void ElementalShamanStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司PVE策略)
void ElementalShamanPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitCombatTriggers(triggers);
    ShamanPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司PVE策略)
void ElementalShamanPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (元素萨满祭司PVE策略)
void ElementalShamanPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitReactionTriggers(triggers);
    ShamanPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (元素萨满祭司PVE策略)
void ElementalShamanPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitDeadTriggers(triggers);
    ShamanPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司PVP策略)
void ElementalShamanPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitCombatTriggers(triggers);
    ShamanPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "chain lightning",
        NextAction::array(0, new NextAction("chain lightning", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "target of attacker close",
        NextAction::array(0, new NextAction("fire nova", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司PVP策略)
void ElementalShamanPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (元素萨满祭司PVP策略)
void ElementalShamanPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitReactionTriggers(triggers);
    ShamanPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (元素萨满祭司PVP策略)
void ElementalShamanPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitDeadTriggers(triggers);
    ShamanPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司团队副本策略)
void ElementalShamanRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitCombatTriggers(triggers);
    ShamanRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司团队副本策略)
void ElementalShamanRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitNonCombatTriggers(triggers);
    ShamanRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (元素萨满祭司团队副本策略)
void ElementalShamanRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitReactionTriggers(triggers);
    ShamanRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (元素萨满祭司团队副本策略)
void ElementalShamanRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanStrategy::InitDeadTriggers(triggers);
    ShamanRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司AOE群体策略)
void ElementalShamanAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "ranged light aoe",
        NextAction::array(0, new NextAction("chain lightning", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司AOE群体策略)
void ElementalShamanAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司AOE群体PVE策略)
void ElementalShamanAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司AOE群体PVE策略)
void ElementalShamanAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司AOE群体PVP策略)
void ElementalShamanAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司AOE群体PVP策略)
void ElementalShamanAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司AOE群体团队副本策略)
void ElementalShamanAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司AOE群体团队副本策略)
void ElementalShamanAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanAoeStrategy::InitNonCombatTriggers(triggers);
    ShamanAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司控制(CC)策略)
void ElementalShamanCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "frost shock snare",
        NextAction::array(0, new NextAction("frost shock", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司控制(CC)策略)
void ElementalShamanCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司控制(CC)PVE策略)
void ElementalShamanCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司控制(CC)PVE策略)
void ElementalShamanCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司控制(CC)PVP策略)
void ElementalShamanCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司控制(CC)PVP策略)
void ElementalShamanCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司控制(CC)团队副本策略)
void ElementalShamanCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司控制(CC)团队副本策略)
void ElementalShamanCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCcStrategy::InitNonCombatTriggers(triggers);
    ShamanCcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司驱散净化策略)
void ElementalShamanCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司驱散净化策略)
void ElementalShamanCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanCureStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司驱散净化PVE策略)
void ElementalShamanCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司驱散净化PVE策略)
void ElementalShamanCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司驱散净化PVP策略)
void ElementalShamanCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司驱散净化PVP策略)
void ElementalShamanCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司驱散净化团队副本策略)
void ElementalShamanCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司驱散净化团队副本策略)
void ElementalShamanCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanCureStrategy::InitNonCombatTriggers(triggers);
    ShamanCureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司图腾策略)
void ElementalShamanTotemsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
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
        NextAction::array(0, new NextAction("mana spring totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "earth totem",
        NextAction::array(0, new NextAction("strength of earth totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem aoe",
        NextAction::array(0, new NextAction("magma totem", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "fire totem",
        NextAction::array(0, new NextAction("totem of wrath", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司图腾策略)
void ElementalShamanTotemsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanTotemsStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司图腾PVE策略)
void ElementalShamanTotemsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司图腾PVE策略)
void ElementalShamanTotemsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司图腾PVP策略)
void ElementalShamanTotemsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司图腾PVP策略)
void ElementalShamanTotemsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司图腾团队副本策略)
void ElementalShamanTotemsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司图腾团队副本策略)
void ElementalShamanTotemsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanTotemsStrategy::InitNonCombatTriggers(triggers);
    ShamanTotemsRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司增益Buff策略)
void ElementalShamanBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "water shield",
        NextAction::array(0, new NextAction("water shield", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司增益Buff策略)
void ElementalShamanBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "water shield",
        NextAction::array(0, new NextAction("water shield", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (元素萨满祭司增益BuffPVE策略)
void ElementalShamanBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司增益BuffPVE策略)
void ElementalShamanBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPveStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (元素萨满祭司增益BuffPVP策略)
void ElementalShamanBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司增益BuffPVP策略)
void ElementalShamanBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (元素萨满祭司增益Buff团队副本策略)
void ElementalShamanBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司增益Buff团队副本策略)
void ElementalShamanBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBuffStrategy::InitNonCombatTriggers(triggers);
    ShamanBuffRaidStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (元素萨满祭司爆发增益策略)
void ElementalShamanBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司爆发增益策略)
void ElementalShamanBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司爆发增益PVE策略)
void ElementalShamanBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司爆发增益PVE策略)
void ElementalShamanBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司爆发增益PVP策略)
void ElementalShamanBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司爆发增益PVP策略)
void ElementalShamanBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (元素萨满祭司爆发增益团队副本策略)
void ElementalShamanBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (元素萨满祭司爆发增益团队副本策略)
void ElementalShamanBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ElementalShamanBoostStrategy::InitNonCombatTriggers(triggers);
    ShamanBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
