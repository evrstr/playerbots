// 策略值实现：CreatureIdValue（生物 Entry ID 提取与校验）

#include "playerbot/playerbot.h"
#include "CreatureIdValue.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"
#ifdef MANGOSBOT_TWO
#include "Entities/Vehicle.h"
#endif

using namespace ai;

// 构造函数：设置 10 秒检查周期并启用限定符
CreatureIdValue::CreatureIdValue(PlayerbotAI* ai) : CalculatedValue<uint32>(ai, "creature id", 10), Qualified()
{
}

// 使用聊天解析器从限定符提取生物 ID，并校验数据库是否存在对应生物信息
uint32 CreatureIdValue::Calculate()
{
    std::string namepart = qualifier;
    PlayerbotChatHandler handler(bot);
    uint32 extractedCreatureId = handler.extractCreatureId(namepart);
    if (extractedCreatureId)
    {
        const CreatureInfo* pCreatureInfo = sServerFacade.LookupCreatureInfo(extractedCreatureId);
        if (pCreatureInfo)
            return extractedCreatureId;
    }

    return 0;
}
