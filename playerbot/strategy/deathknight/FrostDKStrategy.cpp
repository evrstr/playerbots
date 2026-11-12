// 死亡骑士 - 冰霜死亡骑士策略实现文件 (FrostDKStrategy.cpp)

#include "playerbot/playerbot.h"
#include "DKMultipliers.h"
#include "FrostDKStrategy.h"

using namespace ai;

// 动作节点工厂：配置技能前置(P)、备选(A)与后续(C)动作优先级链
class FrostDKStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    FrostDKStrategyActionNodeFactory()
    {
        //creators["icy touch"] = &icy_touch;
        creators["obliterate"] = &obliterate;
        creators["howling blast"] = &howling_blast;
        creators["frost strike"] = &frost_strike;
        //creators["chains of ice"] = &chains_of_ice;
        creators["rune strike"] = &rune_strike;
        //creators["icy clutch"] = &icy_clutch;
        //creators["horn of winter"] = &horn_of_winter;
        //creators["killing machine"] = &killing_machine;
        //creators["frost presence"] = &frost_presence;
        //creators["deathchill"] = &deathchill;
        //creators["icebound fortitude"] = &icebound_fortitude;
        //creators["mind freeze"] = &mind_freeze;
        //creators["empower weapon"] = &empower_weapon;
        //creators["hungering cold"] = &hungering_cold;
        //creators["unbreakable armor"] = &unbreakable_armor;
        //creators["improved icy talons"] = &improved_icy_talons;
    }

    private:
        // 构建 湮灭 (obliterate) 动作节点
        static ActionNode* obliterate(PlayerbotAI* ai)
        {
        return new ActionNode("obliterate",
            /*P*/ NextAction::array(0, new NextAction("blood presence"), NULL),
            /*A*/ NextAction::array(0, new NextAction("frost strike"), NULL),
            /*C*/ NULL);
        }
        // 构建 符文打击 (rune_strike) 动作节点
        static ActionNode* rune_strike(PlayerbotAI* ai)
        {
        return new ActionNode("rune strike",
            /*P*/ NextAction::array(0, new NextAction("blood presence"), NULL),
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NULL);
        }
        // 构建 冰霜打击 (frost_strike) 动作节点
        static ActionNode* frost_strike(PlayerbotAI* ai)
        {
        return new ActionNode("frost strike",
            /*P*/ NextAction::array(0, new NextAction("blood presence"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
        }
        // 构建 凛风冲击 (howling_blast) 动作节点
        static ActionNode* howling_blast(PlayerbotAI* ai)
        {
        return new ActionNode("howling blast",
            /*P*/ NextAction::array(0, new NextAction("blood presence"), NULL),
            /*A*/ NextAction::array(0, new NextAction("icy touch"), NULL),
            /*C*/ NULL);    
        }
};

// 构造函数：初始化冰霜死亡骑士策略并挂载动作节点工厂
FrostDKStrategy::FrostDKStrategy(PlayerbotAI* ai) : GenericDKStrategy(ai)
{
    actionNodeFactories.Add(std::make_unique<FrostDKStrategyActionNodeFactory>());
}

// 获取默认战斗动作序列 (冰霜死亡骑士策略)
NextAction** FrostDKStrategy::GetDefaultCombatActions()
{
    return NextAction::array(0, 
            new NextAction("melee", ACTION_NORMAL), 
            new NextAction("frost strike", ACTION_NORMAL + 5),
            new NextAction("obliterate", ACTION_NORMAL + 4), NULL);
}

// 初始化战斗阶段触发器列表 (冰霜死亡骑士策略)
void FrostDKStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDKStrategy::InitCombatTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "empower weapon",
        NextAction::array(0, new NextAction("empower weapon", ACTION_NORMAL + 4), NULL)));
}

// 初始化战斗阶段触发器列表 (冰霜死亡骑士AOE群体策略)
void FrostDKAoeStrategy::InitCombatTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("howling blast", ACTION_NORMAL + 4), NULL)));
}
