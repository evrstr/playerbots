#pragma once

namespace ai 
{
    /// 惰性求值缓存模板，首次调用 GetValue 时求值并缓存结果，直至调用 Reset
    template <class TValue, class TOwner>
    class LazyCalculatedValue
    {
    public:
        typedef TValue (TOwner::*Calculator)();

    public:
        LazyCalculatedValue(TOwner* owner, Calculator calculator) 
        {
            this->calculator = calculator;
            this->owner = owner;
            Reset();
        }

    public:
        TValue GetValue()
        {
            if (!calculated)
            {
                value = (owner->*calculator)();
                calculated = true;
            }
            return value;
        }
        void Reset() 
        {
            calculated = false;
        }

    protected:
        Calculator calculator;
        TOwner* owner;
        bool calculated;
        TValue value;
    };
};
