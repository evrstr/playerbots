// 策略值头文件：RTSCValues（即时战略式指针指挥：法术落点、选中状态、下步指令与保存坐标）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 日志位置计算器：记录当前通过点击预览法术指示器看到的世界坐标
    class SeeSpellLocationValue : public LogCalculatedValue<WorldPosition>
    {
    public:
        SeeSpellLocationValue(PlayerbotAI* ai, std::string name = "see spell location") : LogCalculatedValue(ai, name) {};

        virtual bool EqualToLast(WorldPosition value) override { return value == lastValue; };

        WorldPosition Calculate() override { return this->value; }
    };

    // 手动设置值：标记当前机器人是否被 RTSC（即时战略模式）选中指挥
    class RTSCSelectedValue : public ManualSetValue<bool>
    {
    public:
        RTSCSelectedValue(PlayerbotAI* ai, bool defaultvalue = false, std::string name = "RTSC selected") : ManualSetValue(ai, defaultvalue,name) {};
    };

    // 手动设置值：保存 RTSC 指挥下待释放的下一个法术或动作指令名
    class RTSCNextSpellActionValue : public ManualSetValue<std::string>
    {
    public:
        RTSCNextSpellActionValue(PlayerbotAI* ai, std::string defaultvalue = "", std::string name = "RTSC next spell action") : ManualSetValue(ai, defaultvalue, name) {};
    };

    // 手动设置值：按限定符名称保存和读取 RTSC 指挥标记的世界坐标位置
    class RTSCSavedLocationValue : public ManualSetValue<WorldPosition>, public Qualified
    {
    public:
        RTSCSavedLocationValue(PlayerbotAI* ai, WorldPosition defaultvalue = WorldPosition(), std::string name = "RTSC saved location") : ManualSetValue(ai, defaultvalue, name), Qualified() {};
        virtual std::string Save() override { return value.to_string(); }
        virtual bool Load(std::string text) override { value = WorldPosition(text); return true; }
    };
}
