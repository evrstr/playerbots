#pragma once

#include "playerbot/strategy/Action.h"
#include "playerbot/strategy/NamedObjectContext.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/TravelNode.h"
#include "MotionGenerators/WaypointMovementGenerator.h"
#include "playerbot/strategy/values/HazardsValue.h"
#include "playerbot/strategy/values/LastMovementValue.h"

namespace ai
{
    /// 移动动作基类：提供寻路、转向、上下坐骑、避障及跨载具移动的核心底层方法
    class MovementAction : public Action
    {
    public:
        /// 构造函数：初始化移动动作基类
        MovementAction(PlayerbotAI* ai, std::string name) : Action(ai, name) {}
        /// 判断是否为移动类动作
        virtual bool IsMovement() override { return true; }

        /// 执行最小位移微调以脱离危险区域或碰撞
        static bool MinimalMove(PlayerbotAI* ai);
        /// 处理乘坐船只、飞艇或电梯等交通载具的上下船与等待逻辑
        static bool UseTransport(PlayerbotAI* ai, uint32 entry, WorldPosition dockPosition, WorldPosition exitPosition, bool doTeleport);
    protected:
        /// 从码头或陆地移动登上停靠中的船只或飞艇载具
        static bool MoveOnTransport(PlayerbotAI* ai, GenericTransport* transport, bool doTeleport);
        /// 从船只或飞艇等移动载具上移动下船至陆地路径点
        static bool MoveOffTransport(PlayerbotAI* ai, WorldPosition exitPos, bool doTeleport);

        /// 在战斗中持续追击并保持在目标的有效攻击距离内
        bool ChaseTo(WorldObject *obj, float distance = 0.0f, float angle = 0.0f);
        /// 移动至指定坐标或对象周围一定半径内的可达点
        bool MoveNear(uint32 mapId, float x, float y, float z, float distance = sPlayerbotAIConfig.contactDistance);
        /// 在飞行状态下沿直线向目标坐标飞去
        bool FlyDirect(const WorldPosition &startPosition,  const WorldPosition &endPosition , WorldPosition& movePosition, TravelPath movePath);

        /// 规划路径并控制机器人移动至目标地图坐标
        inline bool MoveTo(const WorldLocation& location, bool idle = false, bool react = false, bool noPath = false, bool ignoreEnemyTargets = false)
        {
           return MoveTo(location.mapid, location.coord_x, location.coord_y, location.coord_z, idle, react, noPath, ignoreEnemyTargets);
        }

        /// 与飞行管理员交互并乘骑指定的飞行路线
        static bool UseTaxi(PlayerbotAI* ai, uint32 entry = 0, bool needNpc = true);


        /// 在码头或站点等待目标交通载具靠岸
        bool WaitForTransport();


        /// 通过寻路引擎解析并生成前往目标点的完整路径点序列
        TravelPath ResolveMovePath(const WorldPosition& startPosition,
            const WorldPosition& endPosition,
            Unit* mover,
            LastMovement& lastMove);

        /// 处理跨交通工具、跳跃捷径等特殊移动逻辑
        bool HandleSpecialMovement(TravelPath& path);

        /// 根据当前地形与移动模式更新飞行状态标志
        void UpdateFlyingState(WorldPosition& movePosition,
            float totalDistance,
            float originalZ,
            float maxDist,
            bool isWalking);

        /// 根据距离、地形与载具状态分发具体的移动执行方式
        void DispatchMovement(TravelPath movePath, bool generatePath, bool masterWalking);

        /// 获取当前实际控制移动的单位（机器人自身或所乘载具）
        Unit* GetMover(Player* bot);

        /// 使用备用或分段寻路逻辑移动至目标位置
        bool MoveTo2(const WorldPosition& endPos, bool idle = false, bool react = false, bool noPath = false, bool ignoreEnemyTargets = false);

        /// 规划路径并控制机器人移动至目标地图坐标
        bool MoveTo(uint32 mapId, float x, float y, float z, bool idle = false, bool react = false, bool noPath = false, bool ignoreEnemyTargets = false);
        /// 规划路径并控制机器人移动至目标地图坐标
        bool MoveTo(Unit* target, float distance = 0.0f);
        /// 移动至指定坐标或对象周围一定半径内的可达点
        bool MoveNear(WorldObject* target, float distance = sPlayerbotAIConfig.contactDistance);
        /// 获取机器人相对于跟随目标的期望方位角（结合阵型分布）
        float GetFollowAngle();
        /// 按设定距离与跟随角度持续跟随目标单位
        bool Follow(Unit* target, float distance = 0);
        /// 按设定距离与跟随角度持续跟随目标单位
        bool Follow(Unit* target, float distance, float angle);
        /// 在移动前处理或等待设定的移动反应延迟
        float MoveDelay(float distance);
        /// 处理目标位于船只或飞艇等移动载具上的跟随逻辑
        bool FollowOnTransport(Unit* target);

        /// 计算并等待到达目标位置所需的移动时间
        void WaitForReach(float distance);
        /// 计算并等待到达目标位置所需的移动时间
        void WaitForReach(const Movement::PointsArray& path);

        /// 检查当前策略与控制状态是否允许机器人移动
        bool IsMovingAllowed(Unit* target);
        /// 检查当前策略与控制状态是否允许机器人移动
        bool IsMovingAllowed(uint32 mapId, float x, float y, float z);
        /// 寻找安全逃跑方向并控制机器人脱离当前威胁目标
        bool Flee(Unit *target);
        /// 清除机器人当前的空闲或坐下状态以便开始移动
        void ClearIdleState();
        /// 刷新机器人移动状态与移动生成器信息
        void UpdateMovementState();

        /// 判断执行该动作的前置条件是否满足（移动动作基类）
        bool isPossible() override;
        /// 判断当前状态下该动作是否可用/有效（移动动作基类）
        bool isUseful() override;

        /// 在世界坐标召唤一个临时路标光球用于可视化调试路径点
        void CreateWp(Player* wpOwner, float x, float y, float z, float o, uint32 entry, bool important = false);
        float GetAngle(const float x1, const float y1, const float x2, const float y2);

        // Used when this action is executed as a reaction (当该动作作为反应（Reaction）触发执行时使用)
        bool ShouldReactionInterruptCast() const override { return true; }
        /// 判断作为反应动作触发时是否应中断当前移动
        bool ShouldReactionInterruptMovement() const override { return true; }

    private:
        /// 验证目标位置指针与坐标数据是否有效可达
        bool IsValidPosition(const WorldPosition& position, const WorldPosition& visibleFromPosition);
        /// 检查指定坐标周围是否存在地面危险区域（如火圈/毒云）
        bool IsHazardNearPosition(const WorldPosition& position, HazardPosition* outHazard = nullptr);
        /// 生成绕开地面危险区域的替代移动路径
        bool GeneratePathAvoidingHazards(std::vector<WorldPosition>& movePath);
    };

    /// 逃跑撤退动作：寻找远离敌人的安全位置并控制机器人撤退
    class FleeAction : public MovementAction
    {
    public:
        /// 构造函数：初始化逃跑撤退动作
        FleeAction(PlayerbotAI* ai, float distance = sPlayerbotAIConfig.spellDistance) : MovementAction(ai, "flee"), distance(distance) {}
        /// 执行动作主逻辑（逃跑撤退动作）
        virtual bool Execute(Event& event) override;

    private:
        float distance;
    };

    /// 携宠物撤退动作：在让宠物掩护或召回的同时执行撤退移动
    class FleeWithPetAction : public MovementAction
    {
    public:
        /// 构造函数：初始化携宠物撤退动作
        FleeWithPetAction(PlayerbotAI* ai) : MovementAction(ai, "flee with pet") {}
        /// 执行动作主逻辑（携宠物撤退动作）
        virtual bool Execute(Event& event) override;
    };

    /// 风筝拉扯动作：与近战目标保持安全距离并向后风筝移动
    class RunAwayAction : public MovementAction
    {
    public:
        /// 构造函数：初始化风筝拉扯动作
        RunAwayAction(PlayerbotAI* ai) : MovementAction(ai, "runaway") {}
        /// 执行动作主逻辑（风筝拉扯动作）
        virtual bool Execute(Event& event) override;
    };

    /// 移动至战利品动作：向待拾取的尸体或宝箱位置移动
    class MoveToLootAction : public MovementAction
    {
    public:
        /// 构造函数：初始化移动至战利品动作
        MoveToLootAction(PlayerbotAI* ai) : MovementAction(ai, "move to loot") {}
        /// 执行动作主逻辑（移动至战利品动作）
        virtual bool Execute(Event& event) override;
    };

    /// 脱离近战接触动作：与过近的敌对目标拉开距离以方便远程施法或射击
    class MoveOutOfEnemyContactAction : public MovementAction
    {
    public:
        /// 构造函数：初始化脱离近战接触动作
        MoveOutOfEnemyContactAction(PlayerbotAI* ai) : MovementAction(ai, "move out of enemy contact") {}
        /// 执行动作主逻辑（脱离近战接触动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（脱离近战接触动作）
        virtual bool isUseful() override;
    };

    /// 面向目标动作：调整机器人朝向使其正对当前目标或攻击方向
    class SetFacingTargetAction : public Action
    {
    public:
        /// 构造函数：初始化面向目标动作
        SetFacingTargetAction(PlayerbotAI* ai) : Action(ai, "set facing") {}
        /// 执行动作主逻辑（面向目标动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（面向目标动作）
        virtual bool isUseful() override;
        /// 判断执行该动作的前置条件是否满足（面向目标动作）
        virtual bool isPossible() override;
    };

    /// 绕背站位动作：移动至目标背后以利于盗贼背刺或避免正面顺劈伤害
    class SetBehindTargetAction : public MovementAction
    {
    public:
        /// 构造函数：初始化绕背站位动作
        SetBehindTargetAction(PlayerbotAI* ai) : MovementAction(ai, "set behind") {}
        /// 执行动作主逻辑（绕背站位动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（绕背站位动作）
        virtual bool isUseful() override;
        /// 判断执行该动作的前置条件是否满足（绕背站位动作）
        virtual bool isPossible() override;
    };

    /// 脱离碰撞重叠动作：与其他单位重叠时微调站位以保持合理间距
    class MoveOutOfCollisionAction : public MovementAction
    {
    public:
        /// 构造函数：初始化脱离碰撞重叠动作
        MoveOutOfCollisionAction(PlayerbotAI* ai) : MovementAction(ai, "move out of collision") {}
        /// 执行动作主逻辑（脱离碰撞重叠动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（脱离碰撞重叠动作）
        virtual bool isUseful() override;
    };

    /// 随机移动动作：在原地附近随机挑选可达点进行小范围走动
    class MoveRandomAction : public MovementAction
    {
    public:
        /// 构造函数：初始化随机移动动作
        MoveRandomAction(PlayerbotAI* ai) : MovementAction(ai, "move random") {}
        /// 执行动作主逻辑（随机移动动作）
        virtual bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（随机移动动作）
        virtual bool isUseful() override;
    };

    /// 定点移动动作：向指定坐标点位移动
    class MoveToAction : public MovementAction, public Qualified
    {
    public:
        /// 构造函数：初始化定点移动动作
        MoveToAction(PlayerbotAI* ai, std::string name = "move to") : MovementAction(ai, "name"), Qualified() {}
        /// 执行动作主逻辑（定点移动动作）
        virtual bool Execute(Event& event) override;
    };

    /// 跳跃动作：检测障碍或高差并执行原地跳跃、加速跳或路径快捷跳跃
    class JumpAction : public MovementAction, public Qualified
    {
    public:
        /// 构造函数：初始化跳跃动作
        JumpAction(PlayerbotAI* ai) : MovementAction(ai, "jump"), Qualified() {}
        /// 执行动作主逻辑（跳跃动作）
        bool Execute(Event& event) override;
        /// 判断当前状态下该动作是否可用/有效（跳跃动作）
        bool isUseful() override;

        /// 计算跳跃所需的起跳速度、垂直高度与水平矢量参数
        static WorldPosition CalculateJumpParameters(const WorldPosition& src, Unit* jumper, float angle, float vSpeed, float hSpeed, float &timeToLand, float &distanceToLand, float &maxHeight, bool &goodLanding, std::vector<WorldPosition> &path, float maxJumpHeight = sPlayerbotAIConfig.jumpHeightLimit);

    private:
        /// 执行实际的跳跃运动与跳跃网络封包发送
        bool DoJump(const WorldPosition& dest, const WorldPosition& highestPoint, float angle, float vSpeed, float hSpeed, float timeToLand, float distanceToLand, float maxHeight, bool goodLanding, bool jumpInPlace, bool jumpBackward, bool showOnly);
        /// 朝向指定坐标执行定向跳跃
        bool JumpTowards(const WorldPosition& src, const WorldPosition& dest, Unit* jumper, float jumpSpeed, bool preSetLanding = false);
        /// 计算完成指定跳跃轨迹所需的空中滞空时间
        static float CalculateJumpTime(float srcZ, float destZ, float vSpeed, float hSpeed, float distance);
        /// 计算完成指定跳跃轨迹所需的空中滞空时间
        static float CalculateJumpTime(float z_diff, float vSpeed, bool ascending);

        /// 搜寻能够跳向目标点的可行起跳位置
        WorldPosition GetPossibleJumpStartFor(const WorldPosition& src, const WorldPosition& dest, WorldPosition& possiblelanding, Unit* jumper, float &requiredSpeed, float distanceTo, float distanceFrom);
        /// 在指定范围内搜索可用于起跳到达目标点的起跳位置
        WorldPosition GetPossibleJumpStartForInRange(const WorldPosition& src, const WorldPosition& dest, WorldPosition& possiblelanding, Unit* jumper, float& requiredSpeed, float distanceTo, float distanceFrom);
        /// 判断机器人是否能够从当前位置跳跃至目标位置
        bool CanJumpTo(const WorldPosition& src, const WorldPosition& dest, WorldPosition& possiblelanding, float& jumpAngle, Unit* jumper, float jumpSpeed, float maxDistance = 10.0f);
        /// 使用寻路器检查从当前位置能否步行到达目标坐标
        bool CanWalkTo(const WorldPosition& src, const WorldPosition& dest, Unit* jumper, float maxDistance = sPlayerbotAIConfig.sightDistance);
        /// 判断通过跳跃捷径是否比普通寻路步行更节省时间
        bool IsJumpFasterThanWalking(const WorldPosition& src, const WorldPosition& dest, const WorldPosition& jumpLanding, Unit* jumper, float maxDistance = sPlayerbotAIConfig.sightDistance);

        /// 检查跳跃轨迹与落点是否安全（避免坠落伤害或跳入深渊）
        static bool IsJumpSafe(const WorldPosition& src, const WorldPosition& dest, Unit* jumper);
        /// 判断飞行中的机器人当前位置下方是否适合降落
        static bool CanLand(const WorldPosition& dest, Unit* jumper);
        /// 过滤掉岩浆软泥等特殊干扰生物的判定函数
        static bool IsNotMagmaSlime(const WorldPosition& dest, Unit* jumper);
    };
}
