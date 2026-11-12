// 策略值头文件：TargetValue（目标策略基类及 RPG、旅行、对话、拾取、进攻、拉怪、跟随等目标值）
#pragma once
#include "playerbot/strategy//AiObject.h"
#include "playerbot/strategy/Value.h"
#include "playerbot/TravelMgr.h"

namespace ai
{
    // 通用目标评分查找策略基类：遍历攻击者列表并缓存围绕目标的坦克/输出人数
    class FindTargetStrategy
    {
    public:
        FindTargetStrategy(PlayerbotAI* ai)
        {
            result = NULL;
            this->ai = ai;
        }

    public:
        Unit* GetResult() { return result; }

    public:
        virtual void CheckAttacker(Unit* attacker, ThreatManager* threatManager) = 0;
        void GetPlayerCount(Unit* creature, int* tankCount, int* dpsCount);

    protected:
        Unit* result;
        PlayerbotAI* ai;

    protected:
        std::map<Unit*, int> tankCountCache;
        std::map<Unit*, int> dpsCountCache;
    };

    // 非控场目标查找策略基类：过滤被队伍指定为 RTI CC 控场的目标
    class FindNonCcTargetStrategy : public FindTargetStrategy
    {
    public:
        FindNonCcTargetStrategy(PlayerbotAI* ai) : FindTargetStrategy(ai) {}

    protected:
        virtual bool IsCcTarget(Unit* attacker);

    };

    // 目标值计算器基类：通过 FindTargetStrategy 选出最佳攻击目标
    class TargetValue : public UnitCalculatedValue
    {
    public:
        TargetValue(PlayerbotAI* ai, std::string name = "target", int checkInterval = 1) : UnitCalculatedValue(ai, name, checkInterval) {}
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "target"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "target"; }
        virtual std::string GetHelpDescription() { return "This value contains a [h:object|unit] which is the best target based on the current target strategy."; }
        virtual std::vector<std::string> GetUsedValues() { return { "possible attack targets" }; }
#endif 
    protected:
        Unit* FindTarget(FindTargetStrategy* strategy);
    };

    // 手动设置值：存储当前选定的 RPG 交互对象（NPC 或游戏对象）GuidPosition
    class RpgTargetValue : public ManualSetValue<GuidPosition>
    {
    public:
        RpgTargetValue(PlayerbotAI* ai, std::string name = "rpg target") : ManualSetValue<GuidPosition>(ai, GuidPosition(), name) {}
#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "rpg target"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "rpg"; }
        virtual std::string GetHelpDescription() { return "This value contains the [h:object|objectGuid] of a [h:object|unit] or [h:object|gameObject] to move to and rpg with.\nThis value is manually set."; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 

        virtual std::string Format() override;
    };

    // 手动设置值：管理机器人当前的长途旅行目标（TravelTarget）指针
    class TravelTargetValue : public ManualSetValue<TravelTarget*>
    {
    public:
        TravelTargetValue(PlayerbotAI* ai, std::string name = "travel target") : ManualSetValue<TravelTarget*>(ai, new TravelTarget(ai), name) {}
        virtual ~TravelTargetValue() override { delete value; }
    };    

    // 值计算器：获取队长、主控或自身当前的旅行目标指针
    class LeaderTravelTargetValue : public CalculatedValue<TravelTarget*>
    {
    public:
        LeaderTravelTargetValue(PlayerbotAI* ai, std::string name = "leader travel target") : CalculatedValue<TravelTarget*>(ai, name) {};

        virtual TravelTarget* Calculate() override;
    };

    // 手动设置值：保存需暂时忽略的 RPG 交互对象 GUID 集合
    class IgnoreRpgTargetValue : public ManualSetValue<std::set<ObjectGuid>& >
    {
    public:
        IgnoreRpgTargetValue(PlayerbotAI* ai) : ManualSetValue<std::set<ObjectGuid>& >(ai, data, "ignore rpg targets") {}

    private:
        std::set<ObjectGuid> data;
    };

    // 手动设置值：保存正在或准备对话交互的目标 GUID
    class TalkTargetValue : public ManualSetValue<ObjectGuid>
    {
    public:
        TalkTargetValue(PlayerbotAI* ai, std::string name = "talk target") : ManualSetValue<ObjectGuid>(ai, ObjectGuid(), name) {}
    };

    // 手动设置值：保存需要走近并取回/收集的目标 GUID
    class FetchTargetValue : public ManualSetValue<ObjectGuid>
    {
    public:
        FetchTargetValue(PlayerbotAI* ai, std::string name = "fetch target") : ManualSetValue<ObjectGuid>(ai, ObjectGuid(), name) {}
    };

    // 手动设置值：保存命令或动作显式指定的进攻目标 GUID
    class AttackTargetValue : public ManualSetValue<ObjectGuid>
    {
    public:
        AttackTargetValue(PlayerbotAI* ai, std::string name = "attack target") : ManualSetValue<ObjectGuid>(ai, ObjectGuid(), name) {}
    };

    // 手动设置值：保存正在进行远程拉怪（Pull）的目标 GUID，并在脱离世界/死亡/换地图时失效
    class PullTargetValue : public UnitManualSetValue
    {
    public:
        PullTargetValue(PlayerbotAI* ai, std::string name = "pull target") : UnitManualSetValue(ai, ObjectGuid(), name) {}
        void Set(ObjectGuid unitGuid) override;
        ObjectGuid Get() override;

    private:
        ObjectGuid guid;
    };

    // 目标值计算器：根据跟队策略优先选择主控或队内非跟随（如坦克/近战）成员作为跟随目标
    class FollowTargetValue : public UnitCalculatedValue
    {
    public:
        FollowTargetValue(PlayerbotAI* ai, std::string name = "follow target") : UnitCalculatedValue(ai, name) {}
        ObjectGuid Calculate() override;
    };

    // 手动设置值：保存玩家手动指定的跟随目标坐标位置
    class ManualFollowTargetValue : public GuidPositionManualSetValue
    {
    public:
        ManualFollowTargetValue(PlayerbotAI* ai, std::string name = "manual follow target") : GuidPositionManualSetValue(ai, GuidPosition(), name) {}
    };

    // 目标值计算器：查找所有正攻击自己的敌人中距离最近的目标
    class ClosestAttackerTargetingMeTargetValue : public UnitCalculatedValue
    {
    public:
        ClosestAttackerTargetingMeTargetValue(PlayerbotAI* ai, std::string name = "closest attacker targeting me") : UnitCalculatedValue(ai, name) {}
        ObjectGuid Calculate() override;
    };

    // 手动设置值基类：管理主控手动指定的一组友方目标 GUID 列表（自动过滤无效或已切换地图目标）
    class FriendlyManualTargetsValue : public ManualSetValue<std::list<ObjectGuid>>
    {
    public:
        FriendlyManualTargetsValue(PlayerbotAI* ai) : ManualSetValue<std::list<ObjectGuid>>(ai, {}) {}
        std::list<ObjectGuid> Get() override;
        std::list<ObjectGuid> LazyGet() override;
    };

    // 手动设置值：主控指定的重点优先治疗目标列表
    class FocusHealTargetValue : public FriendlyManualTargetsValue
    {
    public:
        FocusHealTargetValue(PlayerbotAI* ai) : FriendlyManualTargetsValue(ai) {}
    };

    // 手动设置值：主控指定的重点增益/爆发协助目标列表
    class BoostTargetsValue : public FriendlyManualTargetsValue
    {
    public:
        BoostTargetsValue(PlayerbotAI* ai) : FriendlyManualTargetsValue(ai) {}
    };

    // 手动设置值：主控指定的优先复活/灵魂石目标列表
    class ReviveTargetsValue : public FriendlyManualTargetsValue
    {
    public:
        ReviveTargetsValue(PlayerbotAI* ai) : FriendlyManualTargetsValue(ai) {}
    };

    // 手动设置值：主控指定的优先群体/单体增益目标列表
    class BuffTargetsValue : public FriendlyManualTargetsValue
    {
    public:
        BuffTargetsValue(PlayerbotAI* ai) : FriendlyManualTargetsValue(ai) {}
    };

    // 位置计算器：根据生物或游戏对象 Entry 查找全图最近的刷新点坐标
    class ClosestEntryValue : public CalculatedValue<GuidPosition>,
                                    public Qualified
    {
    public:
        ClosestEntryValue(PlayerbotAI* ai, std::string name = "closest entry") : CalculatedValue<GuidPosition>(ai, name), Qualified() {}
        GuidPosition Calculate() override;
    };
}