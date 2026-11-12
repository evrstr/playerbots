#pragma once

namespace ai
{
    /// 聊天消息过滤器基类
    class ChatFilter : public PlayerbotAIAware
    {
    public:
        ChatFilter(PlayerbotAI* ai) : PlayerbotAIAware(ai) {}
        virtual std::string Filter(std::string message) { return Filter(message, ""); }
        virtual std::string Filter(std::string message, std::string filter);
        virtual ~ChatFilter() {}

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "dummy"; }
        virtual std::unordered_map<std::string, std::string> GetFilterExamples() {return {};}
        virtual std::string GetHelpDescription() { return ""; }
#endif
    };

    /// 组合聊天过滤器，串联多个子过滤器依次处理聊天文本
    class CompositeChatFilter : public ChatFilter
    {
    public:
        CompositeChatFilter(PlayerbotAI* ai);
        virtual ~CompositeChatFilter() override;
        std::string Filter(std::string message) override;
#ifdef GenerateBotHelp
        virtual std::list<ChatFilter*> GetFilters() { return filters;}
#endif
    private:
    std::list<ChatFilter*> filters;
    };
};
