// 死亡骑士 - 邪恶死亡骑士策略实现文件 (UnholyDKStrategy.cpp)

#include "playerbot/playerbot.h"
#include "DKMultipliers.h"
#include "UnholyDKStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class UnholyDKStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    UnholyDKStrategyActionNodeFactory()
    {
        // Unholy
        //creators["bone shield"] = &bone_shield;
        //creators["plague strike"] = &plague_strike;
        //creators["death grip"] = &death_grip;
        //creators["death coil"] = &death_coil;
        creators["death strike"] = &death_strike;
        //creators["unholy blight"] = &unholy_blight;
        creators["scourge strike"] = &scourge_strike;
        //creators["death and decay"] = &death_and_decay;
        //creators["unholy pressence"] = &unholy_pressence;
        //creators["raise dead"] = &raise_dead;
        //creators["army of the dead"] = &army of the dead;
        //creators["summon gargoyle"] = &army of the dead;
        //creators["anti magic shell"] = &anti_magic_shell;
        //creators["anti magic zone"] = &anti_magic_zone;
        //creators["ghoul frenzy"] = &ghoul_frenzy;
        creators["corpse explosion"] = &corpse_explosion;
    }

private:
    // 构建 灵界打击 (death_strike) 动作节点
    static ActionNode* death_strike(PlayerbotAI* ai)
    {
        return new ActionNode("death strike",
            /*P*/ NextAction::array(0, new NextAction("unholy pressence"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    // 构建 尸体爆炸 (corpse_explosion) 动作节点
    static ActionNode* corpse_explosion(PlayerbotAI* ai)
    {
        return new ActionNode("corpse explosion",
            /*P*/ NextAction::array(0, new NextAction("unholy pressence"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    // 构建 天灾打击 (scourge_strike) 动作节点
    static ActionNode* scourge_strike(PlayerbotAI* ai)
    {
        return new ActionNode("scourge strike",
            /*P*/ NextAction::array(0, new NextAction("unholy pressence"), NULL),
            /*A*/ NextAction::array(0, new NextAction("death strike"), NULL),
            /*C*/ NULL);
    }
};

// 获取默认战斗动作序列 (邪恶死亡骑士策略)
NextAction** UnholyDKStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_NORMAL), new NextAction("scourge strike" , ACTION_NORMAL + 3), NULL);
}

// 初始化战斗阶段触发器列表 (邪恶死亡骑士策略)
void UnholyDKStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDKStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "often",
        NextAction::array(0, new NextAction("ghoul frenzy", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("death pact", ACTION_EMERGENCY + 1), NULL)));
}

// 初始化战斗阶段触发器列表 (邪恶死亡骑士AOE群体策略)
void UnholyDKAoeStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "loot available",
        NextAction::array(0, new NextAction("corpse explosion", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("death and decay", ACTION_NORMAL + 3),
            new NextAction("corpse explosion", ACTION_NORMAL + 3), NULL)));
}
