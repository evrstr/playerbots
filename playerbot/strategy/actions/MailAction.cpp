
#include "Mails/Mail.h"
#include "playerbot/playerbot.h"
#include "MailAction.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/Helpers.h"

using namespace ai;

std::map<std::string, MailProcessor*> MailAction::processors;

/// 邮件播报处理器：遍历邮箱内容并向主人汇报邮件列表
class TellMailProcessor : public MailProcessor
{
public:
    bool Before(Player* requester, PlayerbotAI* ai) override
    {
        ai->TellPlayer(requester, "=== Mailbox ===", PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        tells.clear();
        return true;
    }

    bool Process(Player* requester, int index, Mail* mail, PlayerbotAI* ai, Event& event) override
    {
        Player* bot = ai->GetBot();
        time_t cur_time = time(0);
        int days = (cur_time - mail->deliver_time) / 3600 / 24;
        std::ostringstream out;
        out << "#" << (index+1) << " ";
        if (!mail->money && !mail->has_items)
            out << "|cffffffff" << mail->subject;

        if (mail->money)
        {
            out << "|cffffff00" << ChatHelper::formatMoney(mail->money);
            if (!mail->subject.empty()) out << " |cffa0a0a0(" << mail->subject << ")";
        }

        if (mail->has_items)
        {
            for (MailItemInfoVec::iterator i = mail->items.begin(); i != mail->items.end(); ++i)
            {
                Item* item = bot->GetMItem(i->item_guid);
                int count = item ? item->GetCount() : 1;
                ItemPrototype const *proto = sObjectMgr.GetItemPrototype(i->item_template);
                if (proto)
                {
                    sPlayerbotAIConfig.logEvent(ai, "MailAction", proto->Name1, std::to_string(proto->ItemId));
                    out << ChatHelper::formatItem(item, count);
                    if (!mail->subject.empty()) out << " |cffa0a0a0(" << mail->subject << ")";
                }
            }
        }

        out  << ", |cff00ff00" << days << " day(s)";
        tells.push_front(out.str());
        return true;
    }

    bool After(Player* requester, PlayerbotAI* ai) override
    {
        for (std::list<std::string>::iterator i = tells.begin(); i != tells.end(); ++i)
        {
            ai->TellPlayer(requester, *i, PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        }

        return true;
    }

    static TellMailProcessor instance;

private:
    std::list<std::string> tells;
};

/// 邮件提取处理器：自动收取邮件中包含的金币与附件物品
class TakeMailProcessor : public MailProcessor
{
public:

    bool Before(Player* requester, PlayerbotAI* ai) override
    {
        copper = 0;
        items.clear();
        return true;
    }

    bool Process(Player* requester, int index, Mail* mail, PlayerbotAI* ai, Event& event) override
    {
        Player* bot = ai->GetBot();
        if (!CheckBagSpace(bot))
        {
            ai->TellError(requester, "Not enough bag space");
            return false;
        }

        ObjectGuid mailbox = FindMailbox(ai);
        if (mail->money)
        {
            std::ostringstream out;
            if (event.getSource() == "rpg action")
            {
                copper += mail->money;
            }
            else
            {
                out << mail->subject << ", |cffffff00" << ChatHelper::formatMoney(mail->money) << "|cff00ff00 processed";
                ai->TellPlayer(requester, out.str(), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
            }

            WorldPacket packet;
            packet << mailbox;
            packet << mail->messageID;
            bot->GetSession()->HandleMailTakeMoney(packet);
            RemoveMail(bot, mail->messageID, mailbox);
        }
        else if (mail->has_items)
        {
            std::list<uint32> guids;
            for (MailItemInfoVec::iterator i = mail->items.begin(); i != mail->items.end(); ++i)
            {
                ItemPrototype const* proto = sObjectMgr.GetItemPrototype(i->item_template);
                if (proto)
                    guids.push_back(i->item_guid);
            }

            for (std::list<uint32>::iterator i = guids.begin(); i != guids.end(); ++i)
            {
                WorldPacket packet;
                packet << mailbox;
                packet << mail->messageID;
#ifndef MANGOSBOT_ZERO
                packet << *i;
#endif
                Item* item = bot->GetMItem(*i);

                if (item)
                {
                    if (event.getSource() == "rpg action")
                    {
                        items.push_back(ChatHelper::formatItem(item, item->GetCount()));
                    }
                    else
                    {
                        std::ostringstream out;
                        out << mail->subject << ", " << ChatHelper::formatItem(item) << "|cff00ff00 processed";
                        ai->TellPlayer(requester, out.str(), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
                    }
                }

                bot->GetSession()->HandleMailTakeItem(packet);
            }

            RemoveMail(bot, mail->messageID, mailbox);
        }
        else if (mail->sender < 10 && !ai->HasActivePlayerMaster()) // Remove empty mails from auctionhouse. (清理来自拍卖行的空附件邮件。)
        {
            RemoveMail(bot, mail->messageID, mailbox);
        }
        return true;
    }

    bool After(Player* requester, PlayerbotAI* ai) override
    {
        if (!items.empty())
        {
            std::map<std::string, std::string> args;
            args["%itemcount"] = std::to_string(items.size());

            std::vector<std::string> lines = { BOT_TEXT2("|cff00ff00%itemcount items recieved from mail: ", args) };
            for (auto& item : items)
            {
                if (lines.back().size() + item.size() > 256)
                    lines.push_back("");

                lines.back() = lines.back() + item;
            }
 
            for (auto& line : lines)
                ai->TellPlayer(requester, line, PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        }

        if (copper > 0)
        {
            std::map<std::string, std::string> args;
            args["%money"] = ChatHelper::formatMoney(copper);
            ai->TellPlayer(requester, BOT_TEXT2("|cffffff00%money |cff00ff00recieved from mail.", args), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        }

        return true;
    }

    static TakeMailProcessor instance;

private:
    bool CheckBagSpace(Player* bot)
    {
        uint32 totalused = 0, total = 16;
        for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
        {
            if (bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
                totalused++;
        }
        uint32 totalfree = 16 - totalused;
        for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
        {
            if (const Bag* const pBag = (Bag*)bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag))
            {
                ItemPrototype const* pBagProto = pBag->GetProto();
                if (pBagProto->Class == ITEM_CLASS_CONTAINER && pBagProto->SubClass == ITEM_SUBCLASS_CONTAINER)
                    totalfree += pBag->GetFreeSlots();
            }

        }

        return totalfree >= 2;
    }

private:
    uint32 copper = 0;
    std::vector<std::string> items;
};

/// 邮件删除处理器：清理空邮件或已收取附件的过期邮件
class DeleteMailProcessor : public MailProcessor
{
public:
    bool Process(Player* requester, int index, Mail* mail, PlayerbotAI* ai, Event& event) override
    {
        std::ostringstream out;
        out << "|cffffffff" << mail->subject << "|cffff0000 deleted";
        RemoveMail(ai->GetBot(), mail->messageID, FindMailbox(ai));
        ai->TellPlayer(requester, out.str(), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        return true;
    }

    static DeleteMailProcessor instance;
};

/// 邮件已读标记处理器：检查邮件并处理相关交互状态
class ReadMailProcessor : public MailProcessor
{
public:
    bool Process(Player* requester, int index, Mail* mail, PlayerbotAI* ai, Event& event) override
    {
        std::ostringstream out, body;
        out << "|cffffffff" << mail->subject;
        ai->TellPlayer(requester, out.str(), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
#ifdef MANGOSBOT_TWO

#else
        if (mail->itemTextId)
        {
            body << "\n" << sObjectMgr.GetItemText(mail->itemTextId);
            ai->TellPlayer(requester, body.str(), PlayerbotSecurityLevel::PLAYERBOT_SECURITY_ALLOW_ALL, false);
        }
#endif
        return true;
    }

    static ReadMailProcessor instance;
};

TellMailProcessor TellMailProcessor::instance;
TakeMailProcessor TakeMailProcessor::instance;
DeleteMailProcessor DeleteMailProcessor::instance;
ReadMailProcessor ReadMailProcessor::instance;

/// 执行动作主逻辑（邮件管理指令动作）
bool MailAction::Execute(Event& event)
{
    Player* requester = event.getOwner() ? event.getOwner() : GetMaster();
    if (!requester && event.getSource() != "rpg action")
        return false;

    if (!MailProcessor::FindMailbox(ai) && event.getSource() != "debug")
    {
        ai->TellError(requester, "There is no mailbox nearby");
        return false;
    }

    if (processors.empty())
    {
        processors["?"] = &TellMailProcessor::instance;
        processors["take"] = &TakeMailProcessor::instance;
        processors["delete"] = &DeleteMailProcessor::instance;
        processors["read"] = &ReadMailProcessor::instance;
    }

    std::string text = event.getParam();
    if (text.empty())
    {
        ai->TellPlayer(requester, "whisper 'mail ?' to query mailbox, 'mail take/delete/read filter' to take/delete/read mails by filter");
        return false;
    }

    // 按空格拆分命令行参数
    std::vector<std::string> ss = split(text, ' ');
    std::string action = ss[0];
    std::string filter = ss.size() > 1 ? ss[1] : "";
    MailProcessor* processor = processors[action];
    if (!processor)
    {
        std::ostringstream out; out << action << ": I don't know how to do that";
        ai->TellPlayer(requester, out.str());
        return false;
    }

    if (!processor->Before(requester, ai))
        return false;

    std::vector<Mail*> mailList;
    time_t cur_time = time(0);
    for (PlayerMails::iterator itr = bot->GetMailBegin(); itr != bot->GetMailEnd(); ++itr)
    {
        if ((*itr)->state == MAIL_STATE_DELETED || cur_time < (*itr)->deliver_time)
            continue;

        Mail *mail = *itr;
        mailList.push_back(mail);
    }

    if (mailList.empty())
        return false;

    std::map<int, Mail*> filtered = filterList(mailList, filter);
    for (std::map<int, Mail*>::iterator i = filtered.begin(); i != filtered.end(); ++i)
    {
        if (!processor->Process(requester, i->first, i->second, ai, event))
            break;
    }

    return processor->After(requester, ai);
}

/// 删除已读或空附件的邮件记录
void MailProcessor::RemoveMail(Player* bot, uint32 id, ObjectGuid mailbox)
{
    WorldPacket packet;
    packet << mailbox;
    packet << id;
#ifndef MANGOSBOT_ZERO
    packet << (uint32)0; //mailTemplateId
#endif
    bot->GetSession()->HandleMailDelete(packet);
}

/// 在附近搜索可用的邮箱游戏对象
ObjectGuid MailProcessor::FindMailbox(PlayerbotAI* ai)
{
    std::list<ObjectGuid> gos = *ai->GetAiObjectContext()->GetValue<std::list<ObjectGuid> >("nearest game objects no los");
    ObjectGuid mailbox;
    for (std::list<ObjectGuid>::iterator i = gos.begin(); i != gos.end(); ++i)
    {
        GameObject* go = ai->GetGameObject(*i);
        if (go && go->GetGoType() == GAMEOBJECT_TYPE_MAILBOX)
        {
            mailbox = go->GetObjectGuid();
            break;
        }
    }

    return mailbox;
}
