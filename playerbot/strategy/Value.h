#pragma once
#include "Action.h"
#include "Event.h"
#include "playerbot/PlayerbotAIAware.h"
#include "playerbot/PerformanceMonitor.h"
#include "Globals/ObjectMgr.h"
#include "AiObject.h"
#include "playerbot/GuidPosition.h"
#include "NamedObjectContext.h"

namespace ai
{
    /// 无类型 AI 状态值基类，提供重置、格式化、序列化与过期检测接口
    class UntypedValue : public AiNamedObject
    {
    public:
        UntypedValue(PlayerbotAI* ai, std::string name) : AiNamedObject(ai, name) {}
        virtual void Update() {}  //Nonfunctional see AiObjectContext::Update() to enable.
        virtual void Reset() {}
        virtual std::string Format() { return "?"; }
        virtual std::string Save() { return "?"; }
        virtual bool Load(std::string value) { return false; }
        virtual bool Expired() { return false; }
        virtual bool Expired(uint32 interval) { return false; }
        virtual bool Protected() { return false; }

        virtual uint32 LastChangeDelay() { return 0; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "dummy"; } //Must equal iternal name
        virtual std::string GetHelpTypeName() { return ""; }
        virtual std::string GetHelpDescription() { return "This is a value."; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 
    };

    /// 强类型 AI 状态值读取/写入泛型接口
    template<class T>
    class Value
    {
    public:
        virtual T Get() = 0;
        virtual T LazyGet() = 0;
        virtual void Reset() {}
        virtual void Set(T value) = 0;
        operator T() { return Get(); }
    };

    template<class T>
    /// 按检查间隔(checkInterval)缓存并惰性重算的状态值基类
    class CalculatedValue : public UntypedValue, public Value<T>
    {
    public:
        CalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) : UntypedValue(ai, name),
            checkInterval(checkInterval)
        {
            lastCheckTime = 0;
        }
        virtual ~CalculatedValue() {}

    public:
        virtual T Get() override
        {
            time_t now = time(0);
            if (!lastCheckTime || (checkInterval < 2 && (now - lastCheckTime > 0.1)) || now - lastCheckTime >= checkInterval / 2)
            {
                lastCheckTime = now;

                auto pmo = sPerformanceMonitor.start(PERF_MON_VALUE, AiNamedObject::getName(), this->ai);
                value = Calculate();
            }
            return value;
        }
        virtual T LazyGet() override
        {
            if (!lastCheckTime)
                return Get();
            return value;
        }
        virtual void Set(T value) override { this->value = value; }
        virtual void Update() { }
        virtual void Reset() override { lastCheckTime = 0; }
        virtual bool Expired() override { return Expired(checkInterval / 2); }
        virtual bool Expired(uint32 interval) override { return time(0) - lastCheckTime >= interval; }
    protected:
        virtual T Calculate() = 0;

    protected:
        int checkInterval;
        time_t lastCheckTime;
        T value;
    };

    /// 仅在首次访问或重置后计算一次的单次计算值
    template <class T> class SingleCalculatedValue : public CalculatedValue<T>
    {
    public:
        SingleCalculatedValue(PlayerbotAI* ai, std::string name = "value") : CalculatedValue<T>(ai, name) { this->Reset(); }

        virtual T Get() override
        {
            time_t now = time(0);
            if (!this->lastCheckTime)
            {
                this->lastCheckTime = now;

                auto pmo = sPerformanceMonitor.start(PERF_MON_VALUE, AiNamedObject::getName(), this->ai);
                this->value = this->Calculate();
            }
            return this->value;
        }
    };

    /// 带历史值变化追踪与变化速率(GetDelta)的计算值模板
    template<class T> class MemoryCalculatedValue : public CalculatedValue<T>
    {
    public:
        MemoryCalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) : CalculatedValue<T>(ai, name, checkInterval) { lastChangeTime = 0; }
        virtual bool EqualToLast(T value) = 0;
        virtual bool CanCheckChange() { return !lastChangeTime || (time(0) - lastChangeTime > minChangeInterval && !EqualToLast(this->value)); }
        virtual bool UpdateChange() { if (!CanCheckChange()) return false; lastChangeTime = time(0); lastValue = this->value; return true; }

        virtual void Set(T value) override { CalculatedValue<T>::Set(value); UpdateChange(); }
        virtual T Get() override { this->value = CalculatedValue<T>::Get(); UpdateChange(); return this->value; }

        time_t LastChangeOn() { Get(); return lastChangeTime; }
        uint32 LastChangeDelay() override { return time(0) - LastChangeOn(); }
        T GetLastValue() { return lastValue; }
        time_t GetLastTime() { return lastChangeTime; }

        virtual T GetDelta() { T lVal = lastValue; time_t lTime = lastChangeTime; if (lastChangeTime == time(0)) return Get() - Get(); return (Get() - lVal) / float(time(0) - lTime); }

        virtual void Reset() override { CalculatedValue<T>::Reset(); lastChangeTime = time(0); }
        virtual bool Protected() override { return true; }
    protected:
        T lastValue;
        uint32 minChangeInterval = 0; //Change will not be checked untill this interval has passed.
        time_t lastChangeTime;
    };

    /// 记录近期数值时间序列日志并支持窗口期变化率计算的模板
    template<class T> class LogCalculatedValue : public MemoryCalculatedValue<T>
    {
    public:
        LogCalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) : MemoryCalculatedValue<T>(ai, name, checkInterval) {};
        virtual bool UpdateChange() override { if (MemoryCalculatedValue<T>::UpdateChange()) return false; valueLog.push_back(std::make_pair(this->value, time(0))); if (valueLog.size() > logLength) valueLog.pop_front(); return true; }

        virtual T Get() override { return MemoryCalculatedValue<T>::Get(); }

        std::list<std::pair<T, time_t>> ValueLog() { return valueLog; }

        std::pair<T, time_t> GetLogOn(time_t t) { auto log = std::find_if(valueLog.rbegin(), valueLog.rend(), [t](std::pair<T, time_t> p) {return p.second < t; }); if (log == valueLog.rend()) return valueLog.front(); return *log; }
        T GetValueOn(time_t t) { return GetLogOn(t)->first; }
        T GetTimeOn(time_t t) { return GetTimeOn(t)->second; }

        virtual T GetDelta(uint32 window) { std::pair<T, time_t> log = GetLogOn(time(0) - window); if (log.second == time(0)) return Get() - Get(); return (Get() - log.first) / float(time(0) - log.second); }

        virtual void Reset() override { MemoryCalculatedValue<T>::Reset(); valueLog.clear(); }
    protected:
        std::list<std::pair<T, time_t>> valueLog;
        uint8 logLength = 10; //Maxium number of values recorded.
    };

    /// uint8 类型计算值
    class Uint8CalculatedValue : public CalculatedValue<uint8>
    {
    public:
        Uint8CalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) :
            CalculatedValue<uint8>(ai, name, checkInterval) {}

        virtual std::string Format() override
        {
            std::ostringstream out; out << (int)this->Calculate();
            return out.str();
        }
    };

    /// uint32 类型计算值
    class Uint32CalculatedValue : public CalculatedValue<uint32>
    {
    public:
        Uint32CalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) :
            CalculatedValue<uint32>(ai, name, checkInterval) {}

        virtual std::string Format() override
        {
            std::ostringstream out; out << (int)this->Calculate();
            return out.str();
        }
    };

    /// float 类型计算值
    class FloatCalculatedValue : public CalculatedValue<float>
    {
    public:
        FloatCalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) :
            CalculatedValue<float>(ai, name, checkInterval) {}

        virtual std::string Format() override
        {
            std::ostringstream out; out << this->Calculate();
            return out.str();
        }
    };

    /// bool 类型计算值
    class BoolCalculatedValue : public CalculatedValue<bool>
    {
    public:
        BoolCalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) :
            CalculatedValue<bool>(ai, name, checkInterval) {}

        virtual std::string Format() override
        {
            return this->Calculate() ? "true" : "false";
        }
    };

    /// std::string 类型计算值
    class StringCalculatedValue : public CalculatedValue<std::string>
    {
    public:
        StringCalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) :
            CalculatedValue<std::string>(ai, name, checkInterval) {}

        virtual std::string Format() override
        {
            return this->Calculate();
        }
    };

    /// 单位 ObjectGuid 计算值
    class UnitCalculatedValue : public CalculatedValue<ObjectGuid>
    {
    public:
        UnitCalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) : CalculatedValue<ObjectGuid>(ai, name, checkInterval) { this->lastCheckTime = time(0) - checkInterval / 2; }

        virtual std::string Format() override;
    };

    /// CreatureDataPair 指针计算值
    class CDPairCalculatedValue : public CalculatedValue<CreatureDataPair const*>
    {
    public:
        CDPairCalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) :
            CalculatedValue<CreatureDataPair const*>(ai, name, checkInterval) { this->lastCheckTime = time(0) - checkInterval / 2; }

        virtual std::string Format() override
        {
            CreatureDataPair const* creatureDataPair = this->Calculate();
            if (!creatureDataPair)
                return "<none>";

            CreatureInfo const* bmTemplate = ObjectMgr::GetCreatureTemplate(creatureDataPair->second.id);
            return bmTemplate ? bmTemplate->Name : "<none>";
        }
    };

    /// CreatureDataPair 指针列表计算值
    class CDPairListCalculatedValue : public CalculatedValue<std::list<CreatureDataPair const*>>
    {
    public:
        CDPairListCalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) :
            CalculatedValue<std::list<CreatureDataPair const*>>(ai, name, checkInterval) { this->lastCheckTime = time(0) - checkInterval / 2; }

        virtual std::string Format() override
        {
            std::ostringstream out; out << "{";
            std::list<CreatureDataPair const*> cdPairs = this->Calculate();
            for (std::list<CreatureDataPair const*>::iterator i = cdPairs.begin(); i != cdPairs.end(); ++i)
            {
                CreatureDataPair const* cdPair = *i;
                out << cdPair->first << ",";
            }
            out << "}";
            return out.str();
        }
    };

    /// ObjectGuid 计算值
    class ObjectGuidCalculatedValue : public CalculatedValue<ObjectGuid>
    {
    public:
        ObjectGuidCalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) :
            CalculatedValue<ObjectGuid>(ai, name, checkInterval) { this->lastCheckTime = time(0) - checkInterval / 2; }

        virtual std::string Format() override;
    };

    /// ObjectGuid 列表计算值
    class ObjectGuidListCalculatedValue : public CalculatedValue<std::list<ObjectGuid> >
    {
    public:
        ObjectGuidListCalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) :
            CalculatedValue<std::list<ObjectGuid> >(ai, name, checkInterval) { this->lastCheckTime = time(0) - checkInterval / 2; }

        virtual std::string Format() override;
    };

    /// GuidPosition 计算值
    class GuidPositionCalculatedValue : public CalculatedValue<GuidPosition>
    {
    public:
        GuidPositionCalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) :
            CalculatedValue<GuidPosition>(ai, name, checkInterval) { this->lastCheckTime = time(0) - checkInterval / 2; }

        virtual std::string Format() override;
    };

    /// GuidPosition 列表计算值
    class GuidPositionListCalculatedValue : public CalculatedValue<std::list<GuidPosition> >
    {
    public:
        GuidPositionListCalculatedValue(PlayerbotAI* ai, std::string name = "value", int checkInterval = 1) :
            CalculatedValue<std::list<GuidPosition> >(ai, name, checkInterval) { this->lastCheckTime = time(0) - checkInterval / 2; }

        virtual std::string Format() override;
    };

    template<class T>
    /// 手动设置并支持重置为默认值的状态值模板
    class ManualSetValue : public UntypedValue, public Value<T>
    {
    public:
        ManualSetValue(PlayerbotAI* ai, T defaultValue, std::string name = "value") :
            UntypedValue(ai, name), value(defaultValue), defaultValue(defaultValue) {}
        virtual ~ManualSetValue() {}

    public:
        virtual T Get() override { return value; }
        virtual T LazyGet() override { return value; }
        virtual void Set(T value) override { this->value = value; }
        virtual void Update() { }
        virtual void Reset() override { value = defaultValue; }

    protected:
        T value;
        T defaultValue;
    };

    /// 手动设置的单位 ObjectGuid 状态值
    class UnitManualSetValue : public ManualSetValue<ObjectGuid>
    {
    public:
        UnitManualSetValue(PlayerbotAI* ai, ObjectGuid defaultValue, std::string name = "value") :
            ManualSetValue<ObjectGuid>(ai, defaultValue, name) {}

        virtual std::string Format() override;
    };

    /// 手动设置的 GuidPosition 状态值
    class GuidPositionManualSetValue : public ManualSetValue<GuidPosition>
    {
    public:
        GuidPositionManualSetValue(PlayerbotAI* ai, GuidPosition defaultValue, std::string name = "value") :
            ManualSetValue<GuidPosition>(ai, defaultValue, name) {}

        virtual std::string Format() override;
    };

    /// 带参数限定符的手动设置布尔状态值
    class BoolManualSetValue : public ManualSetValue<bool>, public Qualified
    {
    public:
        BoolManualSetValue(PlayerbotAI* ai, bool defaultValue = false, std::string name = "manual bool") : ManualSetValue<bool>(ai, defaultValue, name), Qualified() {};

        virtual std::string Format() override
        {
            return this->value ? "true" : "false";
        }
    };

    /// 带参数限定符的手动设置整型状态值
    class IntManualSetValue : public ManualSetValue<int32>, public Qualified
    {
    public:
        IntManualSetValue(PlayerbotAI* ai, int32 defaultValue = 0, std::string name = "manual int") : ManualSetValue<int32>(ai, defaultValue, name), Qualified() {};

        virtual std::string Format() override
        {
            return std::to_string(this->value);
        }
    };

    /// 支持数据库持久化保存/读取的整型状态值
    class IntManualSetSavedValue : public IntManualSetValue
    {
    public:
        IntManualSetSavedValue(PlayerbotAI* ai, int32 defaultValue = -1, std::string name = "manual saved int") : IntManualSetValue(ai, defaultValue, name){};

        virtual std::string Format() override
        {
            return std::to_string(this->value);
        }

        virtual std::string Save() override { return std::to_string(this->value); }
        virtual bool Load(std::string text) override { value = stoi(text); return true; }
    };

    /// 带参数限定符的手动设置字符串状态值
    class StringManualSetValue : public ManualSetValue<std::string>, public Qualified
    {
    public:
        StringManualSetValue(PlayerbotAI* ai, std::string defaultValue = "", std::string name = "manual string") : ManualSetValue<std::string>(ai, defaultValue, name), Qualified() {};

        virtual std::string Format() override
        {
            return this->value;
        }
    };

    /// 支持数据库持久化保存/读取的字符串状态值
    class StringManualSetSavedValue : public ManualSetValue<std::string>, public Qualified
    {
    public:
        StringManualSetSavedValue(PlayerbotAI* ai, std::string defaultValue = "", std::string name = "manual saved string") : ManualSetValue<std::string>(ai, defaultValue, name), Qualified() {};
        virtual std::string Format() override
        {
            return this->value;
        }
        virtual std::string Save() override { return value; }
        virtual bool Load(std::string text) override { value = text; return true; }
    };

    /// 带参数限定符的手动设置时间戳状态值
    class TimeManualSetValue : public ManualSetValue<time_t>, public Qualified
    {
    public:
        TimeManualSetValue(PlayerbotAI* ai, int32 defaultValue = 0, std::string name = "manual time") : ManualSetValue<time_t>(ai, defaultValue, name), Qualified() {};

        virtual std::string Format() override
        {
            return std::to_string(this->value);
        }
    };
}
