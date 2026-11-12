/// 旅行系统诊断探针（TravelProbe）头文件
#pragma once

#ifdef GenerateBotTests

#include <string>
#include <list>

class Player;

namespace ai
{
    class TravelTarget;
}

    /// 测试辅助探针：记录机器人旅行目标切换（Flip）、采样可用旅行点及追踪目标决策
class TravelProbe
{
public:
    static void ReportFlip(Player* bot, ai::TravelTarget* newTarget, ai::TravelTarget* oldTarget);
    static std::list<std::string> HandleTravelSample(Player* bot, const std::string& param);
    static std::list<std::string> HandleTravelTrace(const std::string& param);
};

#endif
