// 死亡骑士 - 鲜血死亡骑士策略实现文件 (BloodDKStrategy.cpp)

#include "playerbot/playerbot.h"
#include "DKMultipliers.h"
#include "BloodDKStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class BloodDKStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    BloodDKStrategyActionNodeFactory()
    {
        //creators["melee"] = &melee;
        //creators["blood strike"] = &blood_strike;
        creators["rune strike"] = &rune_strike;
        creators["heart strike"] = &heart_strike;
        creators["death strike"] = &death_strike;
        //creators["death grip"] = &death_grip;
        //creators["plague strike"] = &plague_strike;
        //creators["pestilence"] = &pestilence;
        //creators["icy touch"] = &icy_touch;
        //creators["obliterate"] = &obliterate;
        //creators["blood boil"] = &blood_boil;
        //creators["mark of_blood"] = &mark_of_blood;
        //creators["blood presence"] = &blood_presence;
        //creators["rune tap"] = &rune_tap;
        //creators["vampiric blood"] = &vampiric_blood;
        //creators["death pact"] = &death_pact;
        //creators["death rune_mastery"] = &death_rune_mastery;
        //creators["hysteria"] = &hysteria;
        //creators["dancing weapon"] = &dancing_weapon;
        //creators["dark command"] = &dark_command;
    }
private:
    // 构建 符文打击 (rune_strike) 动作节点
    static ActionNode* rune_strike(PlayerbotAI* ai)
    {
        return new ActionNode("rune strike",
            /*P*/ NextAction::array(0, new NextAction("frost presence"), NULL),
            /*A*/ NextAction::array(0, new NextAction("death coil"), NULL),
            /*C*/ NULL);
    }
    // 构建 心脏打击 (heart_strike) 动作节点
    static ActionNode* heart_strike(PlayerbotAI* ai)
    {
        return new ActionNode ("heart strike",
            /*P*/ NextAction::array(0, new NextAction("frost presence"), NULL),
            /*A*/ NextAction::array(0, new NextAction("death strike"), NULL),
            /*C*/ NULL);
    }
    // 构建 灵界打击 (death_strike) 动作节点
    static ActionNode* death_strike(PlayerbotAI* ai)
    {
        return new ActionNode("death strike",
            /*P*/ NextAction::array(0, new NextAction("frost presence"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    
};

// 构造函数：初始化鲜血死亡骑士策略并挂载动作节点工厂
BloodDKStrategy::BloodDKStrategy(PlayerbotAI* ai) : GenericDKStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<BloodDKStrategyActionNodeFactory>());
}

// 获取默认战斗动作序列 (鲜血死亡骑士策略)
NextAction** BloodDKStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0,
        new NextAction("melee", ACTION_NORMAL + 2),
        new NextAction("heart strike", ACTION_NORMAL + 5),
        new NextAction("death strike", ACTION_NORMAL + 4),
        new NextAction("rune strike", ACTION_NORMAL + 3), NULL);
}

// 初始化战斗阶段触发器列表 (鲜血死亡骑士策略)
void BloodDKStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDKStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "has blessing of salvation",
        NextAction::array(0, new NextAction("remove blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "has greater blessing of salvation",
        NextAction::array(0, new NextAction("remove greater blessing of salvation", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "rune strike",
        NextAction::array(0, new NextAction("rune strike", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "blood tap",
        NextAction::array(0, new NextAction("blood tap", ACTION_HIGH + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("dark command", ACTION_PASSTROUGH), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0,
            new NextAction("blood tap", ACTION_HIGH + 5),
            new NextAction("vampiric blood", ACTION_HIGH + 3),
            new NextAction("death strike", ACTION_HIGH + 4), NULL)));
}
