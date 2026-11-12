// 策略值头文件：GuidPositionValues（游戏对象查找及 Entry/GUID/距离/可用/陷阱过滤器）
#pragma once

#include "playerbot/playerbot.h"
#include "playerbot/strategy/Value.h"


namespace ai
{
    // 坐标列表计算器：扫描反应距离内的所有 GameObject 并返回其 GuidPosition 列表
    class GameObjectsValue : public GuidPositionListCalculatedValue
    {
    public:
        GameObjectsValue(PlayerbotAI* ai, std::string name = "gos") : GuidPositionListCalculatedValue(ai, name, 1) {}

        virtual std::list<GuidPosition> Calculate() override;
    };


    // 过滤器计算器：按指定的模板 Entry ID 列表过滤 GuidPosition 列表
    class EntryFilterValue : public GuidPositionListCalculatedValue, public Qualified
    {
    public:
        EntryFilterValue(PlayerbotAI* ai, std::string name = "entry filter") : GuidPositionListCalculatedValue(ai, name, 1), Qualified() {}

        virtual std::list<GuidPosition> Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "entry filter"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "entry"; }
        virtual std::string GetHelpDescription()
        {
            return "This value will returns only the ObjectGuids of specific entries.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };

    // 过滤器计算器：按实例 GUID 计数器或对象链接过滤 GuidPosition 列表
    class GuidFilterValue : public GuidPositionListCalculatedValue, public Qualified
    {
    public:
       GuidFilterValue(PlayerbotAI* ai, std::string name = "guid filter") : GuidPositionListCalculatedValue(ai, name, 1), Qualified() {}

       virtual std::list<GuidPosition> Calculate() override;

#ifdef GenerateBotHelp
       virtual std::string GetHelpName() { return "guid filter"; } //Must equal iternal name | 必须与内部名称一致
       virtual std::string GetHelpTypeName() { return "guid"; }
       virtual std::string GetHelpDescription()
       {
          return "This value will returns only the ObjectGuids of specific entries.";
       }
       virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 

    private:
       std::vector<std::string> QualifierToEntryList(const std::string& qualifier);
    };

    // 过滤器计算器：按距离参考玩家的范围上限过滤 GuidPosition 列表
    class RangeFilterValue : public GuidPositionListCalculatedValue, public Qualified
    {
    public:
        RangeFilterValue(PlayerbotAI* ai, std::string name = "range filter") : GuidPositionListCalculatedValue(ai, name, 1), Qualified() {}

        virtual std::list<GuidPosition> Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "range filter"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "entry"; }
        virtual std::string GetHelpDescription()
        {
            return "This value will returns only the ObjectGuids within a specific range.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };

    // 过滤器计算器：筛出当前可交互/可点击（未上锁、无冷却等）的 GameObject
    class GoUsableFilterValue : public GuidPositionListCalculatedValue, public Qualified
    {
    public:
        GoUsableFilterValue(PlayerbotAI* ai, std::string name = "go usable filter") : GuidPositionListCalculatedValue(ai, name, 1), Qualified() {}

        virtual std::list<GuidPosition> Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "go usable filter"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "entry"; }
        virtual std::string GetHelpDescription()
        {
            return "This value will returns only the ObjectGuids within a specific range.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };

    // 过滤器计算器：筛出当前有关联陷阱（需拆陷阱或避开）的 GameObject
    class GoTrappedFilterValue : public GuidPositionListCalculatedValue, public Qualified
    {
    public:
        GoTrappedFilterValue(PlayerbotAI* ai, std::string name = "go trapped filter") : GuidPositionListCalculatedValue(ai, name, 1), Qualified() {}

        virtual std::list<GuidPosition> Calculate() override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "go trapped filter"; } //Must equal iternal name | 必须与内部名称一致
        virtual std::string GetHelpTypeName() { return "entry"; }
        virtual std::string GetHelpDescription()
        {
            return "This value will returns only the ObjectGuids that are not trapped.";
        }
        virtual std::vector<std::string> GetUsedValues() { return { }; }
#endif 
    };


    // 坐标列表计算器：查找视距内或指定参数范围内的 GameObject
    class GosInSightValue : public GuidPositionListCalculatedValue, public Qualified
    {
    public:
        GosInSightValue(PlayerbotAI* ai, std::string name = "gos in sight") : GuidPositionListCalculatedValue(ai, name, 3), Qualified() {}

        virtual std::list<GuidPosition> Calculate() override;
    };

    // 坐标列表计算器：查找交互距离（INTERACTION_DISTANCE）内的 GameObject
    class GoSCloseValue : public GuidPositionListCalculatedValue, public Qualified
    {
    public:
        GoSCloseValue(PlayerbotAI* ai, std::string name = "gos close") : GuidPositionListCalculatedValue(ai, name, 3), Qualified() {}

        virtual std::list<GuidPosition> Calculate() override{ return AI_VALUE2(std::list<GuidPosition>, "range filter", "gos," + std::to_string(INTERACTION_DISTANCE)); }
    };



    // 布尔值计算器：判断指定 GuidPosition 列表值是否非空
    class HasObjectValue : public BoolCalculatedValue, public Qualified
    {
    public:
        HasObjectValue(PlayerbotAI* ai, std::string name = "has object") : BoolCalculatedValue(ai, name, 3), Qualified() {}

        virtual bool Calculate() override { return !AI_VALUE(std::list<GuidPosition>, getQualifier()).empty(); }
    };
}
