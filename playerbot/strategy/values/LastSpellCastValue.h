// 策略值头文件：LastSpellCastValue（上一次施放的法术 ID、目标与时间记录）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 法术施放记录结构：保存法术 ID、施法目标 GUID 及施放时间戳
    class LastSpellCast 
    {
    public:
        LastSpellCast() : id(0),time(0) {}

    public:
        void Set(uint32 id, ObjectGuid target, time_t time)
        {
            this->id = id;
            this->target = target;
            this->time = time;
        }
        
        void Reset()
        {
            id = 0;
            target.Set(0);
            time = 0;
        }
    public:
        uint32 id;
        ObjectGuid target;
        time_t time;
    };
   
    // 手动设置值：存储机器人最近一次成功施放的法术信息
    class LastSpellCastValue : public ManualSetValue<LastSpellCast&>
    {
    public:
        LastSpellCastValue(PlayerbotAI* ai, std::string name = "last spell cast") : ManualSetValue<LastSpellCast&>(ai, data, name) {}

    private:
        LastSpellCast data;
    };
}
