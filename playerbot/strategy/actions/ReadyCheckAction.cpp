
#include "playerbot/playerbot.h"
#include "ReadyCheckAction.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/ServerFacade.h"

using namespace ai;

/// 格式化输出名称、数值及其百分比文本
std::string formatPercent(std::string name, uint8 value, float percent)
{
    std::ostringstream out;

    std::string color;
    if (percent > 75)
        color = "|cff00ff00";
    else if (percent > 50)
        color = "|cffffff00";
    else
        color = "|cffff0000";

    out << "|cffffffff[" << name << "]" << color << "x" << (int)value;
    return out.str();
}

/// 就位检查条件基类：定义检查机器人是否已准备好开战的抽象接口
class ReadyChecker
{
public:
    virtual bool Check(Player* requester, PlayerbotAI *ai, AiObjectContext* context) = 0;
    virtual std::string GetName() = 0;
    virtual bool PrintAlways() { return true; }

    static std::list<ReadyChecker*> checkers;
};

std::list<ReadyChecker*> ReadyChecker::checkers;

/// 生命值就位检查器：检查机器人生命值是否达到就位确认要求
class HealthChecker : public ReadyChecker
{
public:
    bool Check(Player* requester, PlayerbotAI *ai, AiObjectContext* context) override
    {
        return AI_VALUE2(uint8, "health", "self target") > sPlayerbotAIConfig.almostFullHealth;
    }

    virtual std::string GetName() override { return "HP"; }
};

/// 法力值就位检查器：检查法系机器人法力值是否达到就位确认要求
class ManaChecker : public ReadyChecker
{
public:
    bool Check(Player* requester, PlayerbotAI *ai, AiObjectContext* context) override
    {
        return !AI_VALUE2(bool, "has mana", "self target") || AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.mediumHealth;
    }
    virtual std::string GetName() override { return "MP"; }
};

/// 距离就位检查器：检查机器人与队长之间的距离是否处于合理范围
class DistanceChecker : public ReadyChecker
{
public:
    bool Check(Player* requester, PlayerbotAI *ai, AiObjectContext* context) override
    {
        Player* bot = ai->GetBot();
        if (requester)
        {
            bool distance = sServerFacade.GetDistance2d(bot, requester) <= sPlayerbotAIConfig.sightDistance;
            if (!distance)
            {
                return false;
            }
        }

        return true;
    }

    virtual bool PrintAlways() override { return false; }
    virtual std::string GetName() override { return "Far away"; }
};

/// 猎人弹药与宠物就位检查器：检查猎人是否携带足够弹药且宠物存活
class HunterChecker : public ReadyChecker
{
public:
    bool Check(Player* requester, PlayerbotAI *ai, AiObjectContext* context) override
    {
        Player* bot = ai->GetBot();
        if (bot->getClass() == CLASS_HUNTER)
        {
            if (!bot->GetUInt32Value(PLAYER_AMMO_ID))
            {
                ai->TellError(requester, "Out of ammo!");
                return false;
            }

            if (!bot->GetPet())
            {
                ai->TellError(requester, "No pet!");
                return false;
            }

            if (bot->GetPet()->GetHappinessState() == UNHAPPY)
            {
                ai->TellError(requester, "Pet is unhappy!");
                return false;
            }
        }

        return true;
    }

    virtual bool PrintAlways() override { return false; }
    virtual std::string GetName() override { return "Far away"; }
};


/// 物品数量就位检查器：检查特定消耗品数量是否满足团队准备要求
class ItemCountChecker : public ReadyChecker
{
public:
    ItemCountChecker(std::string item, std::string name) { this->item = item; this->name = name; }

    bool Check(Player* requester, PlayerbotAI *ai, AiObjectContext* context) override
    {
        return AI_VALUE2(uint32, "item count", item) > 0;
    }

    virtual std::string GetName() override { return name; }

private:
    std::string item, name;
};

/// 法力药水就位检查器：检查背包内法力药水储备是否充足
class ManaPotionChecker : public ItemCountChecker
{
public:
    ManaPotionChecker(std::string item, std::string name) : ItemCountChecker(item, name) {}

    bool Check(Player* requester, PlayerbotAI *ai, AiObjectContext* context) override
    {
        return !AI_VALUE2(bool, "has mana", "self target") || ItemCountChecker::Check(requester, ai, context);
    }
};

/// 执行动作主逻辑（响应就位确认动作）
bool ReadyCheckAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    WorldPacket p = event.getPacket();
    ObjectGuid player;
    p.rpos(0);
    if (!p.empty())
    {
        p >> player;
        if (player == bot->GetObjectGuid())
            return false;
    }

    return ReadyCheck(requester);
}

/// 遍历并执行当前就位确认检查项的检测逻辑
bool ReadyCheckAction::ReadyCheck(Player* requester)
{
    if (ReadyChecker::checkers.empty())
    {
        ReadyChecker::checkers.push_back(new HealthChecker());
        ReadyChecker::checkers.push_back(new ManaChecker());
        ReadyChecker::checkers.push_back(new DistanceChecker());
        ReadyChecker::checkers.push_back(new HunterChecker());

        ReadyChecker::checkers.push_back(new ItemCountChecker("food", "Food"));
        ReadyChecker::checkers.push_back(new ManaPotionChecker("drink", "Water"));
        ReadyChecker::checkers.push_back(new ItemCountChecker("healing potion", "Hpot"));
        ReadyChecker::checkers.push_back(new ManaPotionChecker("mana potion", "Mpot"));
    }

    bool result = true;
    for (std::list<ReadyChecker*>::iterator i = ReadyChecker::checkers.begin(); i != ReadyChecker::checkers.end(); ++i)
    {
        ReadyChecker* checker = *i;
        bool ok = checker->Check(requester, ai, context);
        result = result && ok;
    }

    std::ostringstream out;

    uint32 hp = AI_VALUE2(uint32, "item count", "healing potion");
    out << formatPercent("Hp", hp, 100.0 * hp / 5);

    out << ", ";
    uint32 food = AI_VALUE2(uint32, "item count", "food");
    out << formatPercent("Food", food, 100.0 * food / 20);

    if (AI_VALUE2(bool, "has mana", "self target"))
    {
        out << ", ";
        uint32 mp = AI_VALUE2(uint32, "item count", "mana potion");
        out << formatPercent("Mp", mp, 100.0 * mp / 5);

        out << ", ";
        uint32 water = AI_VALUE2(uint32, "item count", "water");
        out << formatPercent("Water", water, 100.0 * water / 20);
    }

    ai->TellPlayer(requester, out, PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);

    WorldPacket packet(MSG_RAID_READY_CHECK);
    packet << uint8(1);
    bot->GetSession()->HandleRaidReadyCheckOpcode(packet);

    ai->ChangeStrategy("-ready check", BotState::BOT_STATE_NON_COMBAT);

    return true;
}

/// 执行动作主逻辑（完成就位确认动作）
bool FinishReadyCheckAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    return ReadyCheck(requester);
}
