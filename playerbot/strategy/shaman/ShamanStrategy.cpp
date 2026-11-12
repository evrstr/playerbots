// 萨满祭司 - 萨满祭司策略实现文件 (ShamanStrategy.cpp)

#include "playerbot/playerbot.h"
#include "ShamanMultipliers.h"
#include "RestorationShamanStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class ShamanStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    ShamanStrategyActionNodeFactory()
    {
        creators["flametongue weapon"] = &flametongue_weapon;
        creators["frostbrand weapon"] = &frostbrand_weapon;
        creators["lesser healing wave"] = &lesser_healing_wave;
        creators["lesser healing wave on party"] = &lesser_healing_wave_on_party;
        creators["earth shock"] = &earth_shock;
        creators["wind shear"] = &wind_shear;
    }

private:
    // 动作节点 wind_shear：风剪 -> 备选(A)动作：大地震击
    ACTION_NODE_A(wind_shear, "wind shear", "earth shock");

    // 动作节点 earth_shock：大地震击 -> 备选(A)动作：烈焰震击
    ACTION_NODE_A(earth_shock, "earth shock", "flame shock");

    // 动作节点 flametongue_weapon：火舌武器 -> 备选(A)动作：冰封武器
    ACTION_NODE_A(flametongue_weapon, "flametongue weapon", "frostbrand weapon");

    // 动作节点 frostbrand_weapon：冰封武器 -> 备选(A)动作：石化武器
    ACTION_NODE_A(frostbrand_weapon, "frostbrand weapon", "rockbiter weapon");

    // 动作节点 lesser_healing_wave：次级治疗波 -> 备选(A)动作：治疗波
    ACTION_NODE_A(lesser_healing_wave, "lesser healing wave", "healing wave");

    // 动作节点 lesser_healing_wave_on_party：对队友施放次级治疗波 -> 备选(A)动作：治疗波 (对队友)
    ACTION_NODE_A(lesser_healing_wave_on_party, "lesser healing wave on party", "healing wave on party");
};

// 构造函数：初始化萨满祭司策略并挂载动作节点工厂
ShamanStrategy::ShamanStrategy(PlayerbotAI* ai) : ClassStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<ShamanStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 初始化战斗阶段触发器列表 (萨满祭司策略)
void ShamanStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("healing wave", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "purge",
        NextAction::array(0, new NextAction("purge", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司策略)
void ShamanStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member dead",
        NextAction::array(0, new NextAction("ancestral spirit", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("healing wave", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (萨满祭司策略)
void ShamanStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (萨满祭司策略)
void ShamanStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司PVP策略)
void ShamanPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("ghost wolf", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司PVP策略)
void ShamanPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("ghost wolf", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (萨满祭司PVP策略)
void ShamanPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (萨满祭司PVP策略)
void ShamanPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司PVE策略)
void ShamanPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司PVE策略)
void ShamanPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (萨满祭司PVE策略)
void ShamanPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (萨满祭司PVE策略)
void ShamanPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司团队副本策略)
void ShamanRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司团队副本策略)
void ShamanRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (萨满祭司团队副本策略)
void ShamanRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (萨满祭司团队副本策略)
void ShamanRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司AOE群体策略)
void ShamanAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司AOE群体策略)
void ShamanAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司AOE群体PVP策略)
void ShamanAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司AOE群体PVP策略)
void ShamanAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司AOE群体PVE策略)
void ShamanAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司AOE群体PVE策略)
void ShamanAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司AOE群体团队副本策略)
void ShamanAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司AOE群体团队副本策略)
void ShamanAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司控制(CC)策略)
void ShamanCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "wind shear",
        NextAction::array(0, new NextAction("wind shear", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "wind shear on enemy healer",
        NextAction::array(0, new NextAction("wind shear on enemy healer", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司控制(CC)策略)
void ShamanCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司控制(CC)PVP策略)
void ShamanCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司控制(CC)PVP策略)
void ShamanCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司控制(CC)PVE策略)
void ShamanCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司控制(CC)PVE策略)
void ShamanCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司控制(CC)团队副本策略)
void ShamanCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司控制(CC)团队副本策略)
void ShamanCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司驱散净化策略)
void ShamanCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("cure disease", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("cure disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("cure poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("cure poison on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司驱散净化策略)
void ShamanCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("cure disease", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("cure disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("cure poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("cure poison on party", ACTION_DISPEL), NULL)));
}

// 初始化战斗阶段触发器列表 (萨满祭司驱散净化PVP策略)
void ShamanCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司驱散净化PVP策略)
void ShamanCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司驱散净化PVE策略)
void ShamanCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司驱散净化PVE策略)
void ShamanCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司驱散净化团队副本策略)
void ShamanCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司驱散净化团队副本策略)
void ShamanCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司辅助治疗策略)
void ShamanOffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司辅助治疗策略)
void ShamanOffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化战斗阶段触发器列表 (萨满祭司辅助治疗PVP策略)
void ShamanOffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司辅助治疗PVP策略)
void ShamanOffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司辅助治疗PVE策略)
void ShamanOffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司辅助治疗PVE策略)
void ShamanOffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司辅助治疗团队副本策略)
void ShamanOffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitCombatTriggers(triggers);
    OffhealRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司辅助治疗团队副本策略)
void ShamanOffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司图腾策略)
void ShamanTotemsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (萨满祭司图腾策略)
void ShamanTotemsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司图腾PVP策略)
void ShamanTotemsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (萨满祭司图腾PVP策略)
void ShamanTotemsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司图腾PVE策略)
void ShamanTotemsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (萨满祭司图腾PVE策略)
void ShamanTotemsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司图腾团队副本策略)
void ShamanTotemsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (萨满祭司图腾团队副本策略)
void ShamanTotemsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司增益Buff策略)
void ShamanBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司增益Buff策略)
void ShamanBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "water breathing",
        NextAction::array(0, new NextAction("water breathing", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "water walking",
        NextAction::array(0, new NextAction("water walking", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "water breathing on party",
        NextAction::array(0, new NextAction("water breathing on party", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "water walking on party",
        NextAction::array(0, new NextAction("water walking on party", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (萨满祭司增益BuffPVP策略)
void ShamanBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司增益BuffPVP策略)
void ShamanBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司增益BuffPVE策略)
void ShamanBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司增益BuffPVE策略)
void ShamanBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司增益Buff团队副本策略)
void ShamanBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司增益Buff团队副本策略)
void ShamanBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司爆发增益策略)
void ShamanBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司爆发增益策略)
void ShamanBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司爆发增益PVP策略)
void ShamanBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司爆发增益PVP策略)
void ShamanBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司爆发增益PVE策略)
void ShamanBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司爆发增益PVE策略)
void ShamanBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司爆发增益团队副本策略)
void ShamanBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司爆发增益团队副本策略)
void ShamanBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司图腾动作条元素策略)
void ShamanTotemBarElementsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司图腾动作条先祖策略)
void ShamanTotemBarAncestorsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司图腾动作条灵魂策略)
void ShamanTotemBarSpiritsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 初始化战斗阶段触发器列表 (萨满祭司策略)
void ShamanStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("healing wave", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "purge",
        NextAction::array(0, new NextAction("purge", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司策略)
void ShamanStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member dead",
        NextAction::array(0, new NextAction("ancestral spirit", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("healing wave", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_LIGHT_HEAL), NULL)));
}

// 初始化反应阶段触发器列表 (萨满祭司策略)
void ShamanStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (萨满祭司策略)
void ShamanStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司PVP策略)
void ShamanPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("ghost wolf", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司PVP策略)
void ShamanPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("ghost wolf", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (萨满祭司PVP策略)
void ShamanPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (萨满祭司PVP策略)
void ShamanPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司PVE策略)
void ShamanPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司PVE策略)
void ShamanPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (萨满祭司PVE策略)
void ShamanPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (萨满祭司PVE策略)
void ShamanPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司团队副本策略)
void ShamanRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司团队副本策略)
void ShamanRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (萨满祭司团队副本策略)
void ShamanRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (萨满祭司团队副本策略)
void ShamanRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司AOE群体策略)
void ShamanAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司AOE群体策略)
void ShamanAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司AOE群体PVP策略)
void ShamanAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司AOE群体PVP策略)
void ShamanAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司AOE群体PVE策略)
void ShamanAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司AOE群体PVE策略)
void ShamanAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司AOE群体团队副本策略)
void ShamanAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司AOE群体团队副本策略)
void ShamanAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司控制(CC)策略)
void ShamanCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "wind shear",
        NextAction::array(0, new NextAction("wind shear", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "wind shear on enemy healer",
        NextAction::array(0, new NextAction("wind shear on enemy healer", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司控制(CC)策略)
void ShamanCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司控制(CC)PVP策略)
void ShamanCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司控制(CC)PVP策略)
void ShamanCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司控制(CC)PVE策略)
void ShamanCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司控制(CC)PVE策略)
void ShamanCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司控制(CC)团队副本策略)
void ShamanCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司控制(CC)团队副本策略)
void ShamanCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司驱散净化策略)
void ShamanCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("cure disease", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("cure disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("cure poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("cure poison on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司驱散净化策略)
void ShamanCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("cure disease", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("cure disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("cure poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("cure poison on party", ACTION_DISPEL), NULL)));
}

// 初始化战斗阶段触发器列表 (萨满祭司驱散净化PVP策略)
void ShamanCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司驱散净化PVP策略)
void ShamanCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司驱散净化PVE策略)
void ShamanCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司驱散净化PVE策略)
void ShamanCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司驱散净化团队副本策略)
void ShamanCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司驱散净化团队副本策略)
void ShamanCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司辅助治疗策略)
void ShamanOffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司辅助治疗策略)
void ShamanOffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化战斗阶段触发器列表 (萨满祭司辅助治疗PVP策略)
void ShamanOffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司辅助治疗PVP策略)
void ShamanOffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司辅助治疗PVE策略)
void ShamanOffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司辅助治疗PVE策略)
void ShamanOffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司辅助治疗团队副本策略)
void ShamanOffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitCombatTriggers(triggers);
    OffhealRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司辅助治疗团队副本策略)
void ShamanOffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司图腾策略)
void ShamanTotemsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (萨满祭司图腾策略)
void ShamanTotemsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司图腾PVP策略)
void ShamanTotemsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (萨满祭司图腾PVP策略)
void ShamanTotemsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司图腾PVE策略)
void ShamanTotemsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (萨满祭司图腾PVE策略)
void ShamanTotemsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司图腾团队副本策略)
void ShamanTotemsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (萨满祭司图腾团队副本策略)
void ShamanTotemsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司增益Buff策略)
void ShamanBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司增益Buff策略)
void ShamanBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "water breathing",
        NextAction::array(0, new NextAction("water breathing", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "water walking",
        NextAction::array(0, new NextAction("water walking", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "water breathing on party",
        NextAction::array(0, new NextAction("water breathing on party", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "water walking on party",
        NextAction::array(0, new NextAction("water walking on party", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "totemic recall",
        NextAction::array(0, new NextAction("totemic recall", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (萨满祭司增益BuffPVP策略)
void ShamanBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司增益BuffPVP策略)
void ShamanBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司增益BuffPVE策略)
void ShamanBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司增益BuffPVE策略)
void ShamanBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司增益Buff团队副本策略)
void ShamanBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司增益Buff团队副本策略)
void ShamanBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司爆发增益策略)
void ShamanBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "heroism",
        NextAction::array(0, new NextAction("heroism", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "bloodlust",
        NextAction::array(0, new NextAction("bloodlust", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司爆发增益策略)
void ShamanBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司爆发增益PVP策略)
void ShamanBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司爆发增益PVP策略)
void ShamanBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司爆发增益PVE策略)
void ShamanBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司爆发增益PVE策略)
void ShamanBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司爆发增益团队副本策略)
void ShamanBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司爆发增益团队副本策略)
void ShamanBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司图腾动作条元素策略)
void ShamanTotemBarElementsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司图腾动作条先祖策略)
void ShamanTotemBarAncestorsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司图腾动作条灵魂策略)
void ShamanTotemBarSpiritsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 初始化战斗阶段触发器列表 (萨满祭司策略)
void ShamanStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("healing wave", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "purge",
        NextAction::array(0, new NextAction("purge", ACTION_DISPEL), NULL)));

    if (sRandomPlayerbotMgr.IsRandomBot(ai->GetBot()))
    {
        triggers.push_back(new TriggerNode(
            "levelup",
            NextAction::array(0, new NextAction("set totembars on levelup", ACTION_HIGH), NULL)));
    }
}

// 初始化非战斗阶段触发器列表 (萨满祭司策略)
void ShamanStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member dead",
        NextAction::array(0, new NextAction("ancestral spirit", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("healing wave", ACTION_MEDIUM_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_LIGHT_HEAL), NULL)));

    if (sRandomPlayerbotMgr.IsRandomBot(ai->GetBot()))
    {
        triggers.push_back(new TriggerNode(
            "levelup",
            NextAction::array(0, new NextAction("set totembars on levelup", ACTION_HIGH), NULL)));
    }

    triggers.push_back(new TriggerNode(
        "totemic recall",
        NextAction::array(0, new NextAction("totemic recall", ACTION_NORMAL), NULL)));
}

// 初始化反应阶段触发器列表 (萨满祭司策略)
void ShamanStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (萨满祭司策略)
void ShamanStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司PVP策略)
void ShamanPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("ghost wolf", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司PVP策略)
void ShamanPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "player has flag",
        NextAction::array(0, new NextAction("ghost wolf", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (萨满祭司PVP策略)
void ShamanPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (萨满祭司PVP策略)
void ShamanPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司PVE策略)
void ShamanPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司PVE策略)
void ShamanPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (萨满祭司PVE策略)
void ShamanPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (萨满祭司PVE策略)
void ShamanPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司团队副本策略)
void ShamanRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司团队副本策略)
void ShamanRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (萨满祭司团队副本策略)
void ShamanRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (萨满祭司团队副本策略)
void ShamanRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ClassRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司AOE群体策略)
void ShamanAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司AOE群体策略)
void ShamanAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司AOE群体PVP策略)
void ShamanAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司AOE群体PVP策略)
void ShamanAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司AOE群体PVE策略)
void ShamanAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司AOE群体PVE策略)
void ShamanAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司AOE群体团队副本策略)
void ShamanAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司AOE群体团队副本策略)
void ShamanAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    AoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司控制(CC)策略)
void ShamanCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "wind shear",
        NextAction::array(0, new NextAction("wind shear", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "wind shear on enemy healer",
        NextAction::array(0, new NextAction("wind shear on enemy healer", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司控制(CC)策略)
void ShamanCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司控制(CC)PVP策略)
void ShamanCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司控制(CC)PVP策略)
void ShamanCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司控制(CC)PVE策略)
void ShamanCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司控制(CC)PVE策略)
void ShamanCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司控制(CC)团队副本策略)
void ShamanCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司控制(CC)团队副本策略)
void ShamanCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CcRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司驱散净化策略)
void ShamanCureStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("cure disease", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("cure disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse spirit poison",
        NextAction::array(0, new NextAction("cleanse spirit", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse spirit disease",
        NextAction::array(0, new NextAction("cleanse spirit", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse spirit curse",
        NextAction::array(0, new NextAction("cleanse spirit", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cleanse spirit poison",
        NextAction::array(0, new NextAction("cleanse spirit poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cleanse spirit disease",
        NextAction::array(0, new NextAction("cleanse spirit disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cleanse spirit curse",
        NextAction::array(0, new NextAction("cleanse spirit curse on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("cure poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("cure poison on party", ACTION_DISPEL), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司驱散净化策略)
void ShamanCureStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "cure disease",
        NextAction::array(0, new NextAction("cure disease", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure disease",
        NextAction::array(0, new NextAction("cure disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse spirit poison",
        NextAction::array(0, new NextAction("cleanse spirit", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse spirit disease",
        NextAction::array(0, new NextAction("cleanse spirit", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse spirit curse",
        NextAction::array(0, new NextAction("cleanse spirit", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cleanse spirit poison",
        NextAction::array(0, new NextAction("cleanse spirit poison on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cleanse spirit disease",
        NextAction::array(0, new NextAction("cleanse spirit disease on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cleanse spirit curse",
        NextAction::array(0, new NextAction("cleanse spirit curse on party", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("cure poison", ACTION_DISPEL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("cure poison on party", ACTION_DISPEL), NULL)));
}

// 初始化战斗阶段触发器列表 (萨满祭司驱散净化PVP策略)
void ShamanCurePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司驱散净化PVP策略)
void ShamanCurePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司驱散净化PVE策略)
void ShamanCurePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司驱散净化PVE策略)
void ShamanCurePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CurePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司驱散净化团队副本策略)
void ShamanCureRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司驱散净化团队副本策略)
void ShamanCureRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    CureRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司辅助治疗策略)
void ShamanOffhealStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司辅助治疗策略)
void ShamanOffhealStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    OffhealStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("healing wave on party", ACTION_MEDIUM_HEAL), NULL)));
}

// 初始化战斗阶段触发器列表 (萨满祭司辅助治疗PVP策略)
void ShamanOffhealPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司辅助治疗PVP策略)
void ShamanOffhealPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司辅助治疗PVE策略)
void ShamanOffhealPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitCombatTriggers(triggers);
    OffhealPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司辅助治疗PVE策略)
void ShamanOffhealPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司辅助治疗团队副本策略)
void ShamanOffhealRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitCombatTriggers(triggers);
    OffhealRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司辅助治疗团队副本策略)
void ShamanOffhealRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ShamanOffhealStrategy::InitNonCombatTriggers(triggers);
    OffhealRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司图腾策略)
void ShamanTotemsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (萨满祭司图腾策略)
void ShamanTotemsStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司图腾PVP策略)
void ShamanTotemsPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (萨满祭司图腾PVP策略)
void ShamanTotemsPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司图腾PVE策略)
void ShamanTotemsPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (萨满祭司图腾PVE策略)
void ShamanTotemsPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司图腾团队副本策略)
void ShamanTotemsRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化非战斗阶段触发器列表 (萨满祭司图腾团队副本策略)
void ShamanTotemsRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{

}

// 初始化战斗阶段触发器列表 (萨满祭司增益Buff策略)
void ShamanBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司增益Buff策略)
void ShamanBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "water breathing",
        NextAction::array(0, new NextAction("water breathing", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "water walking",
        NextAction::array(0, new NextAction("water walking", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "water breathing on party",
        NextAction::array(0, new NextAction("water breathing on party", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "water walking on party",
        NextAction::array(0, new NextAction("water walking on party", ACTION_NORMAL), NULL)));
}

// 初始化战斗阶段触发器列表 (萨满祭司增益BuffPVP策略)
void ShamanBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司增益BuffPVP策略)
void ShamanBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司增益BuffPVE策略)
void ShamanBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司增益BuffPVE策略)
void ShamanBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司增益Buff团队副本策略)
void ShamanBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司增益Buff团队副本策略)
void ShamanBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司爆发增益策略)
void ShamanBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "heroism",
        NextAction::array(0, new NextAction("heroism", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "bloodlust",
        NextAction::array(0, new NextAction("bloodlust", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司爆发增益策略)
void ShamanBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司爆发增益PVP策略)
void ShamanBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司爆发增益PVP策略)
void ShamanBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司爆发增益PVE策略)
void ShamanBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司爆发增益PVE策略)
void ShamanBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司爆发增益团队副本策略)
void ShamanBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (萨满祭司爆发增益团队副本策略)
void ShamanBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    BoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (萨满祭司图腾动作条元素策略)
void ShamanTotemBarElementsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "call of the elements",
        NextAction::array(0, new NextAction("call of the elements", ACTION_HIGH), NULL)));
}

// 初始化战斗阶段触发器列表 (萨满祭司图腾动作条先祖策略)
void ShamanTotemBarAncestorsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "call of the ancestors",
        NextAction::array(0, new NextAction("call of the ancestors", ACTION_HIGH), NULL)));
}

// 初始化战斗阶段触发器列表 (萨满祭司图腾动作条灵魂策略)
void ShamanTotemBarSpiritsStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "call of the ancestors",
        NextAction::array(0, new NextAction("call of the spirits", ACTION_HIGH), NULL)));
}

#endif

// 初始化战斗阶段触发器列表 (萨满祭司手动图腾策略)
void ShamanManualTotemStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        triggerName,
        NextAction::array(0, new NextAction(actionName, ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "place totems",
        NextAction::array(0, new NextAction(actionName, ACTION_MEDIUM_HEAL + 5), NULL)));
}

// 初始化非战斗阶段触发器列表 (萨满祭司手动图腾策略)
void ShamanManualTotemStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode(
        "place totems",
        NextAction::array(0, new NextAction(actionName, ACTION_MEDIUM_HEAL + 5), NULL)));
}
