// 战士 - 防护战士策略实现文件 (ProtectionWarriorStrategy.cpp)

#include "playerbot/playerbot.h"
#include "ProtectionWarriorStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class ProtectionWarriorStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    ProtectionWarriorStrategyActionNodeFactory()
    {
        creators["charge"] = &charge;
        creators["sunder armor"] = &sunder_armor;
        creators["commanding shout"] = &commanding_shout;
        creators["devastate"] = &devastate;
        creators["last stand"] = &last_stand;
        creators["heroic throw on snare target"] = &heroic_throw_on_snare_target;
        creators["heroic throw taunt"] = &heroic_throw_taunt;
        creators["taunt"] = &taunt;
        creators["berserker rage fear"] = &berserker_rage_fear;
    }

private:
    // 动作节点 charge：冲锋 -> 备选(A)动作：reach melee
    ACTION_NODE_A(charge, "charge", "reach melee");

    // 动作节点 sunder_armor：破甲攻击 -> 备选(A)动作：melee
    ACTION_NODE_A(sunder_armor, "sunder armor", "melee");

    // 动作节点 commanding_shout：命令怒吼 -> 备选(A)动作：战斗怒吼
    ACTION_NODE_A(commanding_shout, "commanding shout", "battle shout");

    // 动作节点 devastate：毁灭打击 -> 备选(A)动作：破甲攻击
    ACTION_NODE_A(devastate, "devastate", "sunder armor");

    // 动作节点 last_stand：破釜沉舟 -> 备选(A)动作：破胆怒吼
    ACTION_NODE_A(last_stand, "last stand", "intimidating shout");

    // 动作节点 heroic_throw_on_snare_target：对减速目标施放英勇投掷 -> 备选(A)动作：嘲讽 (对被减速目标)
    ACTION_NODE_A(heroic_throw_on_snare_target, "heroic throw on snare target", "taunt on snare target");

    // 动作节点 heroic_throw_taunt：英勇投掷 -> 备选(A)动作：嘲讽
    ACTION_NODE_A(heroic_throw_taunt, "heroic throw", "taunt");

    // 动作节点 taunt：嘲讽 -> 备选(A)动作：惩戒痛击
    ACTION_NODE_A(taunt, "taunt", "mocking blow");

    // 动作节点 berserker_rage_fear：狂暴之怒 -> 备选(A)动作：死亡之愿
    ACTION_NODE_A(berserker_rage_fear, "berserker rage", "death wish");
};

// 构造函数：初始化防护战士策略并挂载动作节点工厂
ProtectionWarriorStrategy::ProtectionWarriorStrategy(PlayerbotAI* ai) : WarriorStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<ProtectionWarriorStrategyActionNodeFactory>());
}

// 经典旧世 (Vanilla 60级) 版本逻辑
#ifdef MANGOSBOT_ZERO // Vanilla

// 获取默认战斗动作序列 (防护战士策略)
NextAction** ProtectionWarriorStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (防护战士策略)
void ProtectionWarriorStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("last stand", ACTION_EMERGENCY + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("shield wall", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));

    //triggers.push_back(new TriggerNode(
        //"enemy out of melee",
        //NextAction::array(0, new NextAction("heroic throw", ACTION_MOVE + 8), new NextAction("charge", ACTION_MOVE + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "intercept and rage",
        NextAction::array(0, new NextAction("berserker stance", ACTION_MOVE + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "intercept and rage",
        NextAction::array(0, new NextAction("intercept", ACTION_MOVE + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("taunt", ACTION_PASSTROUGH), NULL)));

    //triggers.push_back(new TriggerNode(
        //"taunt on snare target",
        //NextAction::array(0, new NextAction("heroic throw on snare target", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "demoralizing shout",
        NextAction::array(0, new NextAction("demoralizing shout", ACTION_HIGH + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "shield block",
        NextAction::array(0, new NextAction("shield block", ACTION_HIGH + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "sunder armor",
        NextAction::array(0, new NextAction("devastate", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "revenge",
        NextAction::array(0, new NextAction("revenge", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "light rage available",
        NextAction::array(0, new NextAction("shield slam", ACTION_HIGH + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "bloodthirst",
        NextAction::array(0, new NextAction("bloodthirst", ACTION_HIGH + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "mortal strike",
        NextAction::array(0, new NextAction("mortal strike", ACTION_HIGH + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "heroic strike",
        NextAction::array(0, new NextAction("heroic strike", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "disarm",
        NextAction::array(0, new NextAction("disarm", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护战士策略)
void ProtectionWarriorStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (防护战士策略)
void ProtectionWarriorStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护战士策略)
void ProtectionWarriorStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士PVE策略)
void ProtectionWarriorPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士PVE策略)
void ProtectionWarriorPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护战士PVE策略)
void ProtectionWarriorPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护战士PVE策略)
void ProtectionWarriorPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士PVP策略)
void ProtectionWarriorPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士PVP策略)
void ProtectionWarriorPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护战士PVP策略)
void ProtectionWarriorPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护战士PVP策略)
void ProtectionWarriorPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士团队副本策略)
void ProtectionWarriorRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitCombatTriggers(triggers);
    WarriorRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士团队副本策略)
void ProtectionWarriorRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护战士团队副本策略)
void ProtectionWarriorRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitReactionTriggers(triggers);
    WarriorRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护战士团队副本策略)
void ProtectionWarriorRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitDeadTriggers(triggers);
    WarriorRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士AOE群体策略)
void ProtectionWarriorAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("challenging shout", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("battle shout taunt", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护战士AOE群体策略)
void ProtectionWarriorAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士AOE群体PVE策略)
void ProtectionWarriorAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士AOE群体PVE策略)
void ProtectionWarriorAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士AOE群体PVP策略)
void ProtectionWarriorAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士AOE群体PVP策略)
void ProtectionWarriorAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士AOE群体团队副本策略)
void ProtectionWarriorAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士AOE群体团队副本策略)
void ProtectionWarriorAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士增益Buff策略)
void ProtectionWarriorBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "defensive stance",
        NextAction::array(0, new NextAction("defensive stance", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "feared",
        NextAction::array(0, new NextAction("berserker rage fear", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护战士增益Buff策略)
void ProtectionWarriorBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士增益BuffPVE策略)
void ProtectionWarriorBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士增益BuffPVE策略)
void ProtectionWarriorBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士增益BuffPVP策略)
void ProtectionWarriorBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士增益BuffPVP策略)
void ProtectionWarriorBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士增益Buff团队副本策略)
void ProtectionWarriorBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("stoneshield potion", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护战士增益Buff团队副本策略)
void ProtectionWarriorBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士爆发增益策略)
void ProtectionWarriorBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士爆发增益策略)
void ProtectionWarriorBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士爆发增益PVE策略)
void ProtectionWarriorBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士爆发增益PVE策略)
void ProtectionWarriorBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士爆发增益PVP策略)
void ProtectionWarriorBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士爆发增益PVP策略)
void ProtectionWarriorBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士爆发增益团队副本策略)
void ProtectionWarriorBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士爆发增益团队副本策略)
void ProtectionWarriorBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士控制(CC)策略)
void ProtectionWarriorCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "concussion blow",
        NextAction::array(0, new NextAction("concussion blow", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "shield bash",
        NextAction::array(0, new NextAction("shield bash", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "shield bash on enemy healer",
        NextAction::array(0, new NextAction("shield bash on enemy healer", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护战士控制(CC)策略)
void ProtectionWarriorCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士控制(CC)PVE策略)
void ProtectionWarriorCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士控制(CC)PVE策略)
void ProtectionWarriorCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士控制(CC)PVP策略)
void ProtectionWarriorCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士控制(CC)PVP策略)
void ProtectionWarriorCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士控制(CC)团队副本策略)
void ProtectionWarriorCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士控制(CC)团队副本策略)
void ProtectionWarriorCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 燃烧的远征 (TBC 70级) 版本逻辑
#ifdef MANGOSBOT_ONE // TBC

// 获取默认战斗动作序列 (防护战士策略)
NextAction** ProtectionWarriorStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (防护战士策略)
void ProtectionWarriorStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("last stand", ACTION_EMERGENCY + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("shield wall", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "protect party member",
        NextAction::array(0, new NextAction("intervene", ACTION_EMERGENCY), NULL)));

    //triggers.push_back(new TriggerNode(
        //"enemy out of melee",
        //NextAction::array(0, new NextAction("heroic throw", ACTION_MOVE + 8), new NextAction("charge", ACTION_MOVE + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "intercept and rage",
        NextAction::array(0, new NextAction("berserker stance", ACTION_MOVE + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "intercept and rage",
        NextAction::array(0, new NextAction("intercept", ACTION_MOVE + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("taunt", ACTION_PASSTROUGH), NULL)));

    triggers.push_back(new TriggerNode(
        "spell reflection",
        NextAction::array(0, new NextAction("spell reflection", ACTION_MOVE + 1), NULL)));

    //triggers.push_back(new TriggerNode(
        //"taunt on snare target",
        //NextAction::array(0, new NextAction("heroic throw on snare target", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "demoralizing shout",
        NextAction::array(0, new NextAction("demoralizing shout", ACTION_HIGH + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "shield block",
        NextAction::array(0, new NextAction("shield block", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "sunder armor",
        NextAction::array(0, new NextAction("devastate", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "light rage available",
        NextAction::array(0, new NextAction("shield slam", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "revenge",
        NextAction::array(0, new NextAction("revenge", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "heroic strike",
        NextAction::array(0, new NextAction("heroic strike", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "disarm",
        NextAction::array(0, new NextAction("disarm", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "devastate",
        NextAction::array(0, new NextAction("devastate", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护战士策略)
void ProtectionWarriorStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitNonCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));
}

// 初始化反应阶段触发器列表 (防护战士策略)
void ProtectionWarriorStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护战士策略)
void ProtectionWarriorStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士PVE策略)
void ProtectionWarriorPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士PVE策略)
void ProtectionWarriorPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护战士PVE策略)
void ProtectionWarriorPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护战士PVE策略)
void ProtectionWarriorPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士PVP策略)
void ProtectionWarriorPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士PVP策略)
void ProtectionWarriorPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护战士PVP策略)
void ProtectionWarriorPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护战士PVP策略)
void ProtectionWarriorPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士团队副本策略)
void ProtectionWarriorRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitCombatTriggers(triggers);
    WarriorRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士团队副本策略)
void ProtectionWarriorRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护战士团队副本策略)
void ProtectionWarriorRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitReactionTriggers(triggers);
    WarriorRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护战士团队副本策略)
void ProtectionWarriorRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitDeadTriggers(triggers);
    WarriorRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士AOE群体策略)
void ProtectionWarriorAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("thunder clap threat", ACTION_HIGH + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("challenging shout", ACTION_HIGH + 1), NULL)));

    /*
    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("battle shout taunt", ACTION_HIGH), NULL)));
    */
}

// 初始化非战斗阶段触发器列表 (防护战士AOE群体策略)
void ProtectionWarriorAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士AOE群体PVE策略)
void ProtectionWarriorAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士AOE群体PVE策略)
void ProtectionWarriorAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士AOE群体PVP策略)
void ProtectionWarriorAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士AOE群体PVP策略)
void ProtectionWarriorAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士AOE群体团队副本策略)
void ProtectionWarriorAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士AOE群体团队副本策略)
void ProtectionWarriorAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士增益Buff策略)
void ProtectionWarriorBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "defensive stance",
        NextAction::array(0, new NextAction("defensive stance", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "commanding shout",
        NextAction::array(0, new NextAction("commanding shout", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护战士增益Buff策略)
void ProtectionWarriorBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士增益BuffPVE策略)
void ProtectionWarriorBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士增益BuffPVE策略)
void ProtectionWarriorBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士增益BuffPVP策略)
void ProtectionWarriorBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士增益BuffPVP策略)
void ProtectionWarriorBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士增益Buff团队副本策略)
void ProtectionWarriorBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士增益Buff团队副本策略)
void ProtectionWarriorBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士爆发增益策略)
void ProtectionWarriorBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士爆发增益策略)
void ProtectionWarriorBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士爆发增益PVE策略)
void ProtectionWarriorBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士爆发增益PVE策略)
void ProtectionWarriorBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士爆发增益PVP策略)
void ProtectionWarriorBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士爆发增益PVP策略)
void ProtectionWarriorBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士爆发增益团队副本策略)
void ProtectionWarriorBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士爆发增益团队副本策略)
void ProtectionWarriorBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士控制(CC)策略)
void ProtectionWarriorCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "concussion blow",
        NextAction::array(0, new NextAction("concussion blow", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "shield bash",
        NextAction::array(0, new NextAction("shield bash", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "shield bash on enemy healer",
        NextAction::array(0, new NextAction("shield bash on enemy healer", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护战士控制(CC)策略)
void ProtectionWarriorCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士控制(CC)PVE策略)
void ProtectionWarriorCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士控制(CC)PVE策略)
void ProtectionWarriorCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士控制(CC)PVP策略)
void ProtectionWarriorCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士控制(CC)PVP策略)
void ProtectionWarriorCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士控制(CC)团队副本策略)
void ProtectionWarriorCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士控制(CC)团队副本策略)
void ProtectionWarriorCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
// 巫妖王之怒 (WotLK 80级) 版本逻辑
#ifdef MANGOSBOT_TWO // WOTLK

// 获取默认战斗动作序列 (防护战士策略)
NextAction** ProtectionWarriorStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_IDLE), NULL);
}

// 初始化战斗阶段触发器列表 (防护战士策略)
void ProtectionWarriorStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("last stand", ACTION_EMERGENCY + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("shield wall", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "protect party member",
        NextAction::array(0, new NextAction("intervene", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("heroic throw", ACTION_MOVE + 8), new NextAction("charge", ACTION_MOVE + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "intercept and rage",
        NextAction::array(0, new NextAction("berserker stance", ACTION_MOVE + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "intercept and rage",
        NextAction::array(0, new NextAction("intercept", ACTION_MOVE + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("heroic throw taunt", ACTION_PASSTROUGH), NULL)));

    triggers.push_back(new TriggerNode(
        "spell reflection",
        NextAction::array(0, new NextAction("spell reflection", ACTION_MOVE + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "taunt on snare target",
        NextAction::array(0, new NextAction("heroic throw on snare target", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "demoralizing shout",
        NextAction::array(0, new NextAction("demoralizing shout", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "sword and board",
        NextAction::array(0, new NextAction("shield slam", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "shield block",
        NextAction::array(0, new NextAction("shield block", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "light rage available",
        NextAction::array(0, new NextAction("shield slam", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "sunder armor",
        NextAction::array(0, new NextAction("devastate", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "heroic strike",
        NextAction::array(0, new NextAction("heroic strike", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "revenge",
        NextAction::array(0, new NextAction("revenge", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "disarm",
        NextAction::array(0, new NextAction("disarm", ACTION_NORMAL), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护战士策略)
void ProtectionWarriorStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护战士策略)
void ProtectionWarriorStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护战士策略)
void ProtectionWarriorStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士PVE策略)
void ProtectionWarriorPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士PVE策略)
void ProtectionWarriorPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护战士PVE策略)
void ProtectionWarriorPveStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPveStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护战士PVE策略)
void ProtectionWarriorPveStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPveStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士PVP策略)
void ProtectionWarriorPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitCombatTriggers(triggers);
    WarriorPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士PVP策略)
void ProtectionWarriorPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护战士PVP策略)
void ProtectionWarriorPvpStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitReactionTriggers(triggers);
    WarriorPvpStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护战士PVP策略)
void ProtectionWarriorPvpStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitDeadTriggers(triggers);
    WarriorPvpStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士团队副本策略)
void ProtectionWarriorRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitCombatTriggers(triggers);
    WarriorRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士团队副本策略)
void ProtectionWarriorRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitNonCombatTriggers(triggers);
    WarriorRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化反应阶段触发器列表 (防护战士团队副本策略)
void ProtectionWarriorRaidStrategy::InitReactionTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitReactionTriggers(triggers);
    WarriorRaidStrategy::InitReactionTriggers(triggers);
}

// 初始化死亡状态触发器列表 (防护战士团队副本策略)
void ProtectionWarriorRaidStrategy::InitDeadTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorStrategy::InitDeadTriggers(triggers);
    WarriorRaidStrategy::InitDeadTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士AOE群体策略)
void ProtectionWarriorAoeStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("challenging shout", ACTION_HIGH + 1), NULL)));
    
    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("thunder clap threat", ACTION_HIGH + 7), NULL)));

    /*triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("battle shout taunt", ACTION_HIGH), NULL)));*/
}

// 初始化非战斗阶段触发器列表 (防护战士AOE群体策略)
void ProtectionWarriorAoeStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorAoeStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士AOE群体PVE策略)
void ProtectionWarriorAoePveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士AOE群体PVE策略)
void ProtectionWarriorAoePveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士AOE群体PVP策略)
void ProtectionWarriorAoePvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士AOE群体PVP策略)
void ProtectionWarriorAoePvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoePvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士AOE群体团队副本策略)
void ProtectionWarriorAoeRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士AOE群体团队副本策略)
void ProtectionWarriorAoeRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorAoeStrategy::InitNonCombatTriggers(triggers);
    WarriorAoeRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士增益Buff策略)
void ProtectionWarriorBuffStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "defensive stance",
        NextAction::array(0, new NextAction("defensive stance", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "commanding shout",
        NextAction::array(0, new NextAction("commanding shout", ACTION_HIGH), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护战士增益Buff策略)
void ProtectionWarriorBuffStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBuffStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士增益BuffPVE策略)
void ProtectionWarriorBuffPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士增益BuffPVE策略)
void ProtectionWarriorBuffPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士增益BuffPVP策略)
void ProtectionWarriorBuffPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士增益BuffPVP策略)
void ProtectionWarriorBuffPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士增益Buff团队副本策略)
void ProtectionWarriorBuffRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士增益Buff团队副本策略)
void ProtectionWarriorBuffRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBuffStrategy::InitNonCombatTriggers(triggers);
    WarriorBuffRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士爆发增益策略)
void ProtectionWarriorBoostStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士爆发增益策略)
void ProtectionWarriorBoostStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorBoostStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士爆发增益PVE策略)
void ProtectionWarriorBoostPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士爆发增益PVE策略)
void ProtectionWarriorBoostPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士爆发增益PVP策略)
void ProtectionWarriorBoostPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士爆发增益PVP策略)
void ProtectionWarriorBoostPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士爆发增益团队副本策略)
void ProtectionWarriorBoostRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士爆发增益团队副本策略)
void ProtectionWarriorBoostRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorBoostStrategy::InitNonCombatTriggers(triggers);
    WarriorBoostRaidStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士控制(CC)策略)
void ProtectionWarriorCcStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "concussion blow",
        NextAction::array(0, new NextAction("concussion blow", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "shield bash",
        NextAction::array(0, new NextAction("shield bash", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "shield bash on enemy healer",
        NextAction::array(0, new NextAction("shield bash on enemy healer", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "shockwave on snare target",
        NextAction::array(0, new NextAction("shockwave on snare target", ACTION_INTERRUPT), NULL)));

    triggers.push_back(new TriggerNode(
        "shockwave",
        NextAction::array(0, new NextAction("shockwave", ACTION_INTERRUPT), NULL)));
}

// 初始化非战斗阶段触发器列表 (防护战士控制(CC)策略)
void ProtectionWarriorCcStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    WarriorCcStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士控制(CC)PVE策略)
void ProtectionWarriorCcPveStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPveStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士控制(CC)PVE策略)
void ProtectionWarriorCcPveStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPveStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士控制(CC)PVP策略)
void ProtectionWarriorCcPvpStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士控制(CC)PVP策略)
void ProtectionWarriorCcPvpStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcPvpStrategy::InitNonCombatTriggers(triggers);
}

// 初始化战斗阶段触发器列表 (防护战士控制(CC)团队副本策略)
void ProtectionWarriorCcRaidStrategy::InitCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitCombatTriggers(triggers);
}

// 初始化非战斗阶段触发器列表 (防护战士控制(CC)团队副本策略)
void ProtectionWarriorCcRaidStrategy::InitNonCombatTriggers(std::list<TriggerNode*>& triggers)
{
    ProtectionWarriorCcStrategy::InitNonCombatTriggers(triggers);
    WarriorCcRaidStrategy::InitNonCombatTriggers(triggers);
}

#endif
