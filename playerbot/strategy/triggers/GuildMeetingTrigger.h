/// 公会集结活动触发器定义
#include "playerbot/playerbot.h"
#include "playerbot/strategy/Trigger.h"
#include <string>
#include <ctime>

namespace ai
{
    /// 触发器：根据公会今日信息（MOTD）检测是否到达公会聚会时间
    class GuildMeetingTrigger : public Trigger
    {
    public:
        GuildMeetingTrigger(PlayerbotAI* ai) : Trigger(ai, "guild meeting", 60) {}

        bool IsActive() override;

    private:
        // Parse Guild MOTD | 解析公会今日信息（MOTD）
        // Format 24h: Meeting: <location> <start HH:MM> <end HH:MM> | 24小时制格式：Meeting: <地点> <开始 HH:MM> <结束 HH:MM>
        // Format 12h: Meeting: <location> <start HH:MM AM/PM> <end HH:MM AM/PM> | 12小时制格式：Meeting: <地点> <开始 HH:MM AM/PM> <结束 HH:MM AM/PM>
        bool ParseMotd(const std::string& motd, std::string& outLocation, time_t& outStartTime, time_t& outEndTime) const;
    };
}