// 策略值头文件：Stances（战斗站位姿态基类、姿态配置值与设置指令）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "Formations.h"

namespace ai
{
    // 战斗姿态基类：围绕当前攻击目标计算近战/卡位等相对站位坐标
    class Stance : public Formation
    {
    public:
        Stance(PlayerbotAI* ai, std::string name) : Formation (ai, name) {}
        virtual ~Stance() {}
    protected:
        virtual Unit* GetTarget();
        virtual WorldLocation GetLocationInternal() = 0;
        virtual WorldLocation GetNearLocation(float angle, float distance);

    public:
        virtual WorldLocation GetLocation() override;
        virtual std::string GetTargetName() override { return "current target"; }
        virtual float GetMaxDistance() override { return sPlayerbotAIConfig.contactDistance; }
    };

    // 动态站位姿态基类：按指定偏移角度计算绕目标站位坐标
    class MoveStance : public Stance
    {
    public:
        MoveStance(PlayerbotAI* ai, std::string name) : Stance (ai, name) {}

    protected:
        virtual WorldLocation GetLocationInternal() override;
        virtual float GetAngle() = 0;

    public:
    };


    // 手动设置值：管理机器人当前战斗站位姿态实例，支持存取序列化
    class StanceValue : public ManualSetValue<Stance*>
    {
    public:
        StanceValue(PlayerbotAI* ai);
        ~StanceValue() override { if (value) { delete value; value = NULL; } }
        virtual void Reset() override;
        virtual std::string Save() override;
        virtual bool Load(std::string value) override;
    };

    // 聊天命令动作：允许玩家通过指令查看或切换机器人战斗站位姿态
    class SetStanceAction : public ChatCommandAction
    {
    public:
        SetStanceAction(PlayerbotAI* ai) : ChatCommandAction(ai, "set Stance") {}
        virtual bool Execute(Event& event) override;
    };
};

