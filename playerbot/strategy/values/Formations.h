// 策略值头文件：Formations（队伍阵型基类、阵型位置计算值与设置指令）
#pragma once
#include "playerbot/strategy/Value.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/strategy/actions/GenericActions.h"

namespace ai
{
    // 队伍阵型抽象基类，提供朝向角度、跟随偏移及空位置判定等通用接口
    class Formation : public AiNamedObject
    {
    public:
        Formation(PlayerbotAI* ai, std::string name) : AiNamedObject (ai, name) {}

    public:
        virtual std::string GetTargetName() { return ""; }
        virtual WorldLocation GetLocation() { return NullLocation; }
        virtual float GetAngle();
        virtual float GetOffset();
        virtual float GetMaxDistance();
        static WorldLocation NullLocation;
        static bool IsNullLocation(WorldLocation const& loc);

    protected:
        float GetFollowAngle();
    };

    // 跟随型阵型基类，基于参考目标方向计算自身偏移坐标
    class FollowFormation : public Formation
    {
    public:
        FollowFormation(PlayerbotAI* ai, std::string name) : Formation(ai, name) {}
        virtual WorldLocation GetLocation();
    };

    // 移动排布型阵型基类，提供多排与单排队伍落点计算工具方法
    class MoveFormation : public Formation
    {
    public:
        MoveFormation(PlayerbotAI* ai, std::string name) : Formation(ai, name) {}

    protected:
        WorldLocation MoveLine(std::vector<Player*> line, float diff, float cx, float cy, float cz, float orientation, float range);
        WorldLocation MoveSingleLine(std::vector<Player*> line, float diff, float cx, float cy, float cz, float orientation, float range);
    };

    // 前置移动型阵型基类，使队员保持在引导者前方或特定相对方位
    class MoveAheadFormation : public MoveFormation
    {
    public:
        MoveAheadFormation(PlayerbotAI* ai, std::string name) : MoveFormation(ai, name) {}
        virtual WorldLocation GetLocation() override;
        virtual WorldLocation GetLocationInternal() { return NullLocation; }
    };

    // 手动设置值：管理机器人当前使用的阵型实例，支持保存与切换
    class FormationValue : public ManualSetValue<Formation*>
    {
    public:
        FormationValue(PlayerbotAI* ai);
        ~FormationValue() override { if (value) { delete value; value = NULL; } }
        virtual void Reset() override;
        virtual std::string Save() override;
        virtual bool Load(std::string value) override;
    };

    // 位置计算器：将当前阵型返回的 WorldLocation 转换为 WorldPosition
    class FormationPositionValue : public CalculatedValue<WorldPosition>
    {
    public:
        FormationPositionValue(PlayerbotAI* ai, std::string name = "formation position") : CalculatedValue(ai, name) {}

        virtual WorldPosition Calculate() override {
            Formation* formation = AI_VALUE(Formation*, "formation");

            WorldLocation loc = formation->GetLocation();
            if (Formation::IsNullLocation(loc) || loc.mapid == -1)
                return WorldLocation();

            return loc;
        }
    };

    // 聊天命令动作：允许玩家通过指令查询或切换机器人的队伍阵型
    class SetFormationAction : public ChatCommandAction
    {
    public:
        SetFormationAction(PlayerbotAI* ai) : ChatCommandAction(ai, "set formation") {}
        virtual bool Execute(Event& event) override;
    };
};

