#pragma once

#include "PlayerbotAI.h"

class Player;

namespace ai
{
    class AiObjectContext;
    class ReactionEngine;
    class Engine;
}

using namespace ai;

/// AI 工厂类，负责创建 AI 上下文、战斗/非战斗/死亡/反应引擎，并解析玩家天赋专精与团队角色
class AiFactory
{
public:
    static AiObjectContext* createAiObjectContext(Player* player, PlayerbotAI* ai);
    static Engine* createCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext);
    static Engine* createNonCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext);
    static Engine* createDeadEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext);
    static ReactionEngine* createReactionEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext);
    static void AddDefaultNonCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* nonCombatEngine);
    static void AddDefaultDeadStrategies(Player* player, PlayerbotAI* const facade, Engine* deadEngine);
    static void AddDefaultCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* engine);
    static void AddDefaultReactionStrategies(Player* player, PlayerbotAI* const facade, ReactionEngine* reactionEngine);

public:
    static int GetPlayerSpecTab(const Player* player);
    static std::map<uint32, int32> GetPlayerSpecTabs(const Player* player);
    static BotRoles GetPlayerRoles(uint8 cls, uint8 specTab);
    static BotRoles GetPlayerRoles(const Player* player);
};
