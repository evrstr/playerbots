// 策略值头文件：ThreatValues（自身仇恨、坦克仇恨与相对仇恨等级百分比）
#pragma once
#include "playerbot/strategy/Value.h"

namespace ai
{
    // 日志浮点值计算器：记录并监控机器人自身对当前或指定目标的仇恨数值变化
    class MyThreatValue : public LogCalculatedValue<float>, public Qualified
    {
    public:
        MyThreatValue(PlayerbotAI* ai, std::string name = "my threat") : LogCalculatedValue(ai, name), Qualified() { minChangeInterval = 1; lastTarget = ObjectGuid(); }
        virtual bool EqualToLast(float value) override { return value == lastValue; }
        virtual float Calculate() override;

    public:
        ObjectGuid lastTarget;
    };

    // 浮点值计算器：获取队伍中除自己外的最高坦克/其他玩家对目标的仇恨值
    class TankThreatValue : public FloatCalculatedValue, public Qualified
    {
    public:
        TankThreatValue(PlayerbotAI* ai, std::string name = "tank threat") : FloatCalculatedValue(ai, name), Qualified() {}
        virtual float Calculate() override;
    };

    // 值计算器：计算机器人相对于坦克/最高仇恨者的威胁度分级（0=无仇恨，50=安全，90=濒临OT，100=已OT/无坦克）
    class ThreatValue : public Uint8CalculatedValue, public Qualified
    {
    public:
        ThreatValue(PlayerbotAI* ai, std::string name = "threat") : Uint8CalculatedValue(ai, name), Qualified() {}
        virtual uint8 Calculate() override;
        static float GetThreat(Player* player, Unit* target);
        static float GetTankThreat(PlayerbotAI* ai, Unit* target);

    protected:
        uint8 Calculate(Unit* target);
    };
}
