// 策略值头文件：Arrow（箭头阵型单位位置、槽位与阵型构建）
#pragma once

namespace ai
{
    // 二维平面位置坐标封装（用于阵型计算）
    class UnitPosition
    {
    public:
        UnitPosition(float x, float y) : x(x), y(y) {}
        UnitPosition(const UnitPosition& other) { x = other.x; y = other.y; }
        float x, y;
    };

    // 阵型中的单个成员单元，记录小队索引、是否为主控及分配位置
    class FormationUnit
    {
    public:
        FormationUnit(uint32 groupIndex, bool master) : groupIndex(groupIndex), master(master), position(0, 0) {}
        FormationUnit(const FormationUnit& other) : position(other.position.x, other.position.y)
        {
            groupIndex = other.groupIndex;
            master = other.master;
        }

    public:
        uint32 GetGroupIdex() { return groupIndex; }
        void SetLocation(UnitPosition pos) { position = pos; }
        void SetLocation(float x, float y) { position.x = x; position.y = y; }
        float GetX() { return position.x; }
        float GetY() { return position.y; }

    private:
        uint32 groupIndex;
        bool master;
        UnitPosition position;
    };

    // 阵型单位布局器抽象基类，定义槽位内成员排布接口
    class UnitPlacer
    {
    public:
        UnitPlacer(float range) : range(range) {}

    public:
        virtual UnitPosition Place(FormationUnit *unit, uint32 index, uint32 count) = 0;
    protected:
        float range = 0;
    };

    // 阵型角色槽位（如坦克/近战/远程/治疗），负责管理并放置所属成员
    class FormationSlot
    {
    public:
        FormationSlot() {}
        virtual ~FormationSlot();

    public:
        void AddLast(FormationUnit* unit) { units.push_back(unit); }
        void InsertAtCenter(FormationUnit* unit) { units.insert(units.begin() + (units.size() + 1) / 2, unit); }
        void PlaceUnits(UnitPlacer* placer);
        void Move(float dx, float dy);
        int Size() { return units.size(); }

    private:
        WorldLocation center;
        std::vector<FormationUnit*> units;
    };


    // 多行排布器，将大量成员按每行最多 6 人分排部署
    class MultiLineUnitPlacer : public UnitPlacer
    {
    public:
        MultiLineUnitPlacer(float orientation, float range) : UnitPlacer(range), orientation(orientation) {}

    public:
        virtual UnitPosition Place(FormationUnit *unit, uint32 index, uint32 count) override;

    private:
        float orientation;
    };

    // 单行排布器，将成员按弧度/横向单排展开
    class SingleLineUnitPlacer
    {
    public:
        SingleLineUnitPlacer(float orientation, float range) : orientation(orientation), range(range) {}

    public:
        virtual UnitPosition Place(FormationUnit *unit, uint32 index, uint32 count);

    private:
        float orientation, range;
    };

    // 箭头阵型类：根据角色职责构建箭头状阵型并返回当前机器人的站位
    class ArrowFormation : public MoveAheadFormation
    {
    public:
        ArrowFormation(PlayerbotAI* ai) : MoveAheadFormation(ai, "arrow"), built(false), masterUnit(NULL), botUnit(NULL) {}

    public:
        virtual WorldLocation GetLocationInternal() override;

    private:
        void Build();
        void FillSlotsExceptMaster();
        void AddMasterToSlot();
        FormationSlot* FindSlot(Player* member);

    private:
        FormationSlot tanks, melee, ranged, healers;
        FormationUnit *masterUnit, *botUnit;
        bool built;
    };

}

