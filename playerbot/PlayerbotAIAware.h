#pragma once
#include <string>

#ifndef GenerateBotHelp
//#define GenerateBotHelp //Enable only for help generation (仅在生成帮助文档时启用)
#endif

#ifndef GenerateBotTests
//#define GenerateBotTests //Enable only for test generation (仅在生成测试时启用，保持注释)
#endif

class PlayerbotAI;

namespace ai
{
    /// 持有 PlayerbotAI 指针的基类接口，供策略/动作/触发器等组件继承
    class PlayerbotAIAware 
    {
    public:
        PlayerbotAIAware(PlayerbotAI* const ai) : ai(ai) { }
        virtual ~PlayerbotAIAware() = default;
        virtual std::string getName() { return std::string(); }
    protected:
        PlayerbotAI* ai;
    };
}
