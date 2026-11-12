// 策略值头文件：SubStrategyValue（逗号分隔子策略开关基类）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{    
    // 手动设置值基类：管理由逗号分隔的启/停子策略开关集合（支持 +/-/~/all 语法操作）
    class SubStrategyValue : public ManualSetValue<std::string>
    {
    public:
        SubStrategyValue(PlayerbotAI* ai, std::string defaultValue = "", std::string name = "substrategy", std::string allowedValues = "") : ManualSetValue(ai, defaultValue, name), allowedValues(allowedValues) {};
        virtual void Set(std::string newValue) override;

        void SetValues(std::string& currentValue, const std::string newValue, const std::string allowedValue);
        virtual std::vector<std::string> GetAllowedValues() { return StrSplit(allowedValues, ","); }

        virtual std::string Save() override { return value; };
        virtual bool Load(std::string value) override;
    private:
        std::string allowedValues;
    };
};

