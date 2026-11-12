// 策略值头文件：OperatorValues（策略组合逻辑运算符：与/非/或/大于比较）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 逻辑与计算器：判断逗号分隔的多个布尔 AI 值是否全部为真
    class BoolAndValue : public BoolCalculatedValue, public Qualified
    {
    public:
        BoolAndValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "bool and"), Qualified() {}
        virtual bool Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "bool and"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "operator"; }
        virtual std::string GetHelpDescription()
        {
            return "This value will return true if all of the values included in the qualifier return true.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };

    // 逻辑非计算器：判断逗号分隔的多个布尔 AI 值是否全部为假
    class NotValue : public BoolCalculatedValue, public Qualified
    {
    public:
        NotValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "not"), Qualified() {}
        virtual bool Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "not"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "operator"; }
        virtual std::string GetHelpDescription()
        {
            return "This value will return false if any of the values included in the qualifier return true.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };

    // 逻辑或计算器：判断逗号分隔的多个布尔 AI 值中是否至少有一个为真
    class BoolOrValue : public BoolCalculatedValue, public Qualified
    {
    public:
        BoolOrValue(PlayerbotAI* ai) : BoolCalculatedValue(ai, "bool or"), Qualified() {}
        virtual bool Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "bool or"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "operator"; }
        virtual std::string GetHelpDescription()
        {
            return "This value will return true if any of the values included in the qualifier return true.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };

    // 数值比较计算器：比较两个数值或 AI 值的大小（左值大于右值时返回真）
    class GT32Value : public BoolCalculatedValue, public Qualified
    {
    public:
        GT32Value(PlayerbotAI* ai) : BoolCalculatedValue(ai, "gt32"), Qualified() {}
        virtual bool Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "gt"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "operator"; }
        virtual std::string GetHelpDescription()
        {
            return "This value will return true if the first value is greater than the second value";
        }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };
}
