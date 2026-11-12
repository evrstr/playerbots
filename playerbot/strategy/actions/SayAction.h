#pragma once

#include "playerbot/strategy/Action.h"
#include "QuestAction.h"

namespace ai
{
    /// 机器人发言动作：根据事件、占位符或 LLM 生成并在频道中发送对话文本
    class SayAction : public Action, public Qualified
    {
    public:
        /// 构造函数：初始化机器人发言动作
        SayAction(PlayerbotAI* ai);
        /// 执行动作主逻辑（机器人发言动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（机器人发言动作）
        virtual bool isUseful() override;
        /// 获取动作名称
        virtual std::string getName() override { return "say::" + qualifier; }
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（机器人发言动作）
        virtual bool isUsefulWhenStunned() override { return true; }

    private:
    };

    typedef std::pair<WorldPacket, uint32> delayedPacket;
    typedef std::vector<delayedPacket> delayedPackets;
    typedef std::future<delayedPackets> futurePackets;

    /// 聊天回复动作：监听并回复来自玩家或频道的聊天消息
    class ChatReplyAction : public Action
    {
    public:
        /// 构造函数：初始化聊天回复动作
        ChatReplyAction(PlayerbotAI* ai) : Action(ai, "chat message") {}
        /// 执行动作主逻辑（聊天回复动作）
        virtual bool Execute(Event& event) override { return true; }
        /// 判断当前状态下该动作是否可用/有效（聊天回复动作）
        bool isUseful() override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（聊天回复动作）
        virtual bool isUsefulWhenStunned() override { return true; }

        /// 收集当前场景下的聊天占位符变量（如目标、位置、NPC 职责等）
        static void GetAIChatPlaceholders(std::map<std::string, std::string>& placeholders, Unit* sender = nullptr, Unit* receiver = nullptr);
        /// 收集当前场景下的聊天占位符变量（如目标、位置、NPC 职责等）
        static void GetAIChatPlaceholders(std::map<std::string, std::string>& placeholders, Unit* unit, const std::string preFix = "bot", Player* observer = nullptr);
        /// 构造用于测试或发送的网络封包模板
        static WorldPacket GetPacketTemplate(Opcodes op, uint32 type, Unit* sender, Unit* target = nullptr, std::string channelName = "");
        /// 将多行文本消息拆分为聊天封包序列
        static delayedPackets LinesToPackets(const std::vector<std::string>& lines, WorldPacket packetTemplate, bool debug = false, uint32 MsPerChar = 0, WorldPacket emoteTemplate = WorldPacket(), uint32 timeDiff = 0);

        /// 根据调试或交互命令生成模拟响应网络封包
        static delayedPackets GenerateResponsePackets(const std::string json
            , const WorldPacket chatTemplate, const WorldPacket emoteTemplate, const WorldPacket systemTemplate, const std::string startPattern, const std::string endPattern, const std::string deletePattern, const std::string splitPattern, bool debug = false);

        /// 根据玩家聊天消息内容匹配并生成自动回复
        static void ChatReplyDo(Player* bot, uint32 type, uint32 guid1, uint32 guid2, std::string msg, std::string chanName, std::string name);
        /// 处理带有雷霆之怒等趣味梗的聊天触发回复
        static bool HandleThunderfuryReply(Player* bot, ChatChannelSource chatChannelSource, std::string msg, std::string name);
        /// 过滤或趣味回应聊天中的恶搞链接消息
        static bool HandleToxicLinksReply(Player* bot, ChatChannelSource chatChannelSource, std::string msg, std::string name);
        /// 响应并回复世界频道中的求购物品消息
        static bool HandleWTBItemsReply(Player* bot, ChatChannelSource chatChannelSource, std::string msg, std::string name);
        /// 生成并回复关于当前地下城或任务寻队的聊天响应
        static bool HandleLFGQuestsReply(Player* bot, ChatChannelSource chatChannelSource, std::string msg, std::string name);
        /// 发送通用的交易或邮件操作反馈消息
        static bool SendGeneralResponse(Player* bot, ChatChannelSource chatChannelSource, std::string responseMessage, std::string name);
        /// 结合模板或占位符生成机器人回复文本
        static std::string GenerateReplyMessage(Player* bot, std::string incomingMessage, uint32 guid1, std::string name);
    };

    /// 语音/台词发言动作：按指定频道与文本直接发送机器人台词
    class SpeakAction : public Action, public Qualified
    {
    public:
        /// 构造函数：初始化语音/台词发言动作
        SpeakAction(PlayerbotAI* ai) : Action(ai, "speak"), Qualified() {};
        /// 执行动作主逻辑（语音/台词发言动作）
        virtual bool Execute(Event& event) override;
        /// 判断在被昏迷或控制状态下是否仍可执行该动作（语音/台词发言动作）
        virtual bool isUsefulWhenStunned() override { return true; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "speak"; } // Must equal iternal name (必须与内部动作名称一致)
        virtual std::string GetHelpDescription()
        {
            return "This action wil make bots speak a certain line\n"
                   "Use \\p, \\1 \\y ect to make bots use different channels.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {""}; }
#endif    
    };
}
