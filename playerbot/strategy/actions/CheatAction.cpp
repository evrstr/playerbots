
#include "playerbot/playerbot.h"
#include "CheatAction.h"

using namespace ai;

/// 执行动作主逻辑（作弊调试指令动作）
bool CheatAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (requester && requester->GetSession()->GetSecurity() >= SEC_GAMEMASTER)
    {
        std::string param = event.getParam();
        uint32 cheatMask = (uint32)ai->GetCheat();
        std::vector<std::string> splitted = split(param, ',');
        for (std::vector<std::string>::iterator i = splitted.begin(); i != splitted.end(); i++)
        {
            const char* name = i->c_str();
            BotCheatMask newCheat = GetCheatMask(name + 1);

            switch (name[0])
            {
            case '+':
                AddCheat(newCheat);
                cheatMask |= (uint32)newCheat;
                break;
            case '-':
                RemCheat(newCheat);
                cheatMask &= ~(uint32)newCheat;
                break;
            case '~':
                if (ai->HasCheat(newCheat))
                    RemCheat(newCheat);
                else
                    AddCheat(newCheat);

                cheatMask ^= (uint32)newCheat;
                break;
            case '?':
                ListCheats(requester);
                return true;
            }
        }

        ai->SetCheat(BotCheatMask(cheatMask));
        return true;
    }

    return false;
}

/// 根据作弊名称获取对应的位掩码标志
BotCheatMask CheatAction::GetCheatMask(std::string cheat)
{
    BotCheatMask cheatMask = BotCheatMask::none;
    std::vector<std::string> cheats = Qualified::getMultiQualifiers(cheat, ",");

    for (auto cheat : cheats)
    {
        for (int i = 0; i < log2((uint32)BotCheatMask::maxMask); i++)
        {
            if (sPlayerbotAIConfig.BotCheatMaskName[i] == cheat)
                cheatMask = BotCheatMask(uint32(cheatMask) | uint32(BotCheatMask(1 << i)));
        }
    }

    return cheatMask;
}

/// 根据作弊位掩码获取可读名称
std::string CheatAction::GetCheatName(BotCheatMask cheatMask)
{
    return sPlayerbotAIConfig.BotCheatMaskName[log2(((uint32)cheatMask))];
}

/// 列出机器人当前已开启的所有作弊功能
void CheatAction::ListCheats(Player* requester)
{
    std::ostringstream out;
    for (int i = 0; i < log2((uint32)BotCheatMask::maxMask); i++)
    {
        BotCheatMask cheatMask = BotCheatMask(1 << i);
        if (sRandomPlayerbotMgr.IsRandomBot(bot) && (uint32)cheatMask & (uint32)sPlayerbotAIConfig.rndBotCheatMask)
            out << "[conf:" << GetCheatName(BotCheatMask(cheatMask)) << "]";
        else if (!sRandomPlayerbotMgr.IsRandomBot(bot) && (uint32)cheatMask & (uint32)sPlayerbotAIConfig.botCheatMask)
            out << "[conf:" << GetCheatName(BotCheatMask(cheatMask)) << "]";
        else if (ai->HasCheat(cheatMask))
            out << "[" << GetCheatName(BotCheatMask(cheatMask)) << "]";
    }

    std::streampos pos = out.tellp();  // store current location (保存当前位置坐标)
    out.seekp(0, std::ios_base::end);  // go to end (前往终点)
    if (out.tellp() == std::streampos(0))
        out << "No cheats enabled.";
    out.seekp(pos);                    // restore location (恢复原有坐标位置)

    ai->TellPlayerNoFacing(requester, out);
}

/// 为机器人启用指定的作弊调试标志
void CheatAction::AddCheat(BotCheatMask cheatMask)
{
    switch(cheatMask)
    {
    case BotCheatMask::attackspeed:
        int32 amount = 9999;

        uint32 SPELL_MOD_MELEE_HASTE = 15181;
        uint32 SPELL_MOD_RANGE_HASTE = 15182;
        uint32 SPELL_MOD_SPELL_HASTE = 15183;

        bot->RemoveAurasDueToSpell(SPELL_MOD_MELEE_HASTE);
        bot->CastCustomSpell(bot, SPELL_MOD_MELEE_HASTE, &amount, &amount, nullptr, TRIGGERED_OLD_TRIGGERED);
        bot->RemoveAurasDueToSpell(SPELL_MOD_RANGE_HASTE);
        bot->CastCustomSpell(bot, SPELL_MOD_RANGE_HASTE, &amount, &amount, nullptr, TRIGGERED_OLD_TRIGGERED);
        bot->RemoveAurasDueToSpell(SPELL_MOD_SPELL_HASTE);
        bot->CastCustomSpell(bot, SPELL_MOD_SPELL_HASTE, &amount, &amount, nullptr, TRIGGERED_OLD_TRIGGERED);

        break;
    }
}

/// 移除机器人指定的作弊调试标志
void CheatAction::RemCheat(BotCheatMask cheatMask)
{
    switch (cheatMask)
    {
    case BotCheatMask::movespeed:
        bot->UpdateSpeed(MOVE_WALK, true, 1);
        bot->UpdateSpeed(MOVE_RUN, true, 1);
        bot->UpdateSpeed(MOVE_SWIM, true, 1);
        break;
    case BotCheatMask::attackspeed:
        uint32 SPELL_MOD_MELEE_HASTE = 15181;
        uint32 SPELL_MOD_RANGE_HASTE = 15182;
        uint32 SPELL_MOD_SPELL_HASTE = 15183;

        bot->RemoveAurasDueToSpell(SPELL_MOD_MELEE_HASTE);
        bot->RemoveAurasDueToSpell(SPELL_MOD_RANGE_HASTE);
        bot->RemoveAurasDueToSpell(SPELL_MOD_SPELL_HASTE);
        break;
    }
}
