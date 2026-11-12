#pragma once
#include "GenericActions.h"

namespace ai
{
    /// 调试位置目标结构体：记录用于定位调试测试的位置目标信息
    struct PositionTarget
    {
        bool valid;
        uint32 mapId;
        float x, y, z;
        std::string name;
        
        /// 构造函数：初始化调试位置目标结构体
        PositionTarget() : valid(false), mapId(0), x(0), y(0), z(0) {}
    };

    /// 调试指令动作：提供路径、寻路网格、法术、单位、卡死原因等全套开发者调试命令
    class DebugAction : public ChatCommandAction
    {
    public:
        /// 构造函数：初始化调试指令动作
        DebugAction(PlayerbotAI* ai) : ChatCommandAction(ai, "debug") {}
        /// 执行动作主逻辑（调试指令动作）
        virtual bool Execute(Event& event) override;

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "debug"; }
        virtual std::string GetHelpDescription()
        {
            return "This command enables debug functionalities for testing bot behaviors.\n"
                   "Usage: cdebug [subcommand]\n"
                   "Please refer to the source code for specific uses.";
        }
        virtual std::vector<std::string> GetUsedActions() { return {}; }
        virtual std::vector<std::string> GetUsedValues() { return {}; }
#endif 

        /// 模拟执行法术施放视觉效果或占位测试
        void FakeSpell(uint32 spellId, Unit* truecaster, Unit* caster, ObjectGuid target = ObjectGuid(), std::list<ObjectGuid> otherTargets = {}, std::list<ObjectGuid> missTargets = {}, WorldPosition source = WorldPosition(), WorldPosition dest = WorldPosition(), bool forceDest = false);
        /// 在目标身上查找并确认或添加光环状态
        void addAura(uint32 spellId, Unit* target);
        /// 从指令参数中解析地图 ID 与三维坐标
        PositionTarget ParseLocation(const std::string& param, Player* bot);
    private:
        // Handler methods for each debug command (各调试指令对应的处理方法)
        bool HandleDebugHelp(Event& event, Player* requester, const std::string& text, bool isMod);
        /// 调试命令：扫描并输出周围已配置的寻路避让区域
        bool HandleAvoidScan(Event& event, Player* requester, const std::string& text);
        /// 调试命令：在当前位置添加一个寻路避让危险区域
        bool HandleAvoidAdd(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出机器人坐骑列表及当前骑乘可行性检查
        bool HandleMount(Event& event, Player* requester, const std::string& text);
        /// 调试命令：强制测试机器人下马与清除坐骑状态
        bool HandleUnmount(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出机器人当前所在区域与子区域信息
        bool HandleArea(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试与大语言模型（LLM）对话接口的连通性与提示词
        bool HandleLLM(Event& event, Player* requester, const std::string& text);
        /// 处理接收到的聊天消息并触发异步或同步回复
        bool HandleChatReplyDo(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试怪物喊话触发或文本解析
        bool HandleMonsterTalk(Event& event, Player* requester, const std::string& text);
        /// 调试命令：查找并输出距离最近的墓地与灵魂医者位置
        bool HandleGY(Event& event, Player* requester, const std::string& text);
        /// 调试命令：检查当前所在服务端网格（Grid）与单元格加载状态
        bool HandleGrid(Event& event, Player* requester, const std::string& text);
        /// 调试命令：运行内置动作或系统自检测试例程
        bool HandleTest(Event& event, Player* requester, const std::string& text);
        /// 调试命令：导出机器人 AI 黑板中的所有当前状态值
        bool HandleValues(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出机器人当前地图、区域、坐标与朝向信息
        bool HandleGPS(Event& event, Player* requester, const std::string& text);
        /// 调试命令：设置指定名称的 32 位无符号整型调试状态值
        bool HandleSetValueUInt32(Event& event, Player* requester, const std::string& text);
        /// 调试命令：直接触发执行指定的策略动作名称
        bool HandleDo(Event& event, Player* requester, const std::string& text);
        /// 调试命令：检查并调试当前交易状态与背包可交易物品
        bool HandleTrade(Event& event, Player* requester, const std::string& text);
        /// 调试命令：检查并调试机器人当前邮箱数据
        bool HandleMail(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试发送地图兴趣点（POI）标记封包
        bool HandlePOI(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出机器人当前 MotionMaster 移动生成器堆栈
        bool HandleMotion(Event& event, Player* requester, const std::string& text);
        /// 调试命令：列出附近船只/飞艇载具及其当前路径进度
        bool HandleTransport(Event& event, Player* requester, const std::string& text);
        /// 调试命令：计算并输出当前或目标点在载具局部坐标系中的坐标
        bool HandlePointOnTrans(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试交通载具上下船与路径衔接逻辑
        bool HandleDoTransport(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试登上移动载具的坐标转换逻辑
        bool HandleOnTrans(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试从移动载具下船的坐标转换逻辑
        bool HandleOffTrans(Event& event, Player* requester, const std::string& text);
        /// 调试命令：检测目标点是否可通过寻路网格（NavMesh）到达
        bool HandlePathable(Event& event, Player* requester, const std::string& text);
        /// 调试命令：在周围随机采样并测试可达坐标点
        bool HandleRandomSpot(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出当前地图及附近区块的地形/VMap 状态
        bool HandlePrintMap(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出尸体位置及跑尸路径诊断信息
        bool HandleCorpse(Event& event, Player* requester, const std::string& text);
        /// 调试命令：查询或调整随机机器人下线/在线时长计时器
        bool HandleLogoutTime(Event& event, Player* requester, const std::string& text);
        /// 调试命令：查询或调整机器人等级与经验调试状态
        bool HandleLevel(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出指定任务模板数据与机器人当前任务状态
        bool HandleQuest(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出或设置机器人当前调试坐标与朝向
        bool HandlePosition(Event& event, Player* requester, const std::string& text);
        /// 调试命令：查询附近或选中 NPC 的标志位、阵营与模板数据
        bool HandleNPC(Event& event, Player* requester, const std::string& text);
        /// 调试命令：查询附近指定游戏对象详细信息
        bool HandleGO(Event& event, Player* requester, const std::string& text);
        /// 调试命令：搜索并列出符合名称的生物、物品或节点
        bool HandleFind(Event& event, Player* requester, const std::string& text);
        /// 调试命令：查询背包或数据库中指定物品的详细属性
        bool HandleItem(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出当前 RPG 目标候选列表与各交互动作相关性评分
        bool HandleRPG(Event& event, Player* requester, const std::string& text);
        /// 调试命令：扫描并列出附近所有潜在 RPG 交互目标
        bool HandleRPGTargets(Event& event, Player* requester, const std::string& text);
        /// 调试命令：调试旅行目标选择与多段旅行路径规划
        bool HandleTravel(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出当前旅行目标候选评分与路径计算详情
        bool HandlePrintTravel(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出当前待拾取队列及尸体掉落分析
        bool HandleLoot(Event& event, Player* requester, const std::string& text);
        /// 调试命令：查询生物或宝箱的掉落表信息
        bool HandleDrops(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出当前已解锁飞行点与飞行路线图信息
        bool HandleTaxi(Event& event, Player* requester, const std::string& text);
        /// 调试命令：查询物品的商店价格及拍卖行历史估值
        bool HandlePrice(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出或测试非战斗（Non-Combat）策略执行情况
        bool HandleNC(Event& event, Player* requester, const std::string& text);
        /// 调试命令：在当前坐标添加一个新的旅行导航节点
        bool HandleAddNode(Event& event, Player* requester, const std::string& text);
        /// 调试命令：删除指定 ID 的旅行导航节点
        bool HandleRemNode(Event& event, Player* requester, const std::string& text);
        /// 调试命令：重置旅行导航节点及其连接路径数据
        bool HandleResetNode(Event& event, Player* requester, const std::string& text);
        /// 调试命令：清除当前调试路径显示与临时路径点
        bool HandleResetPath(Event& event, Player* requester, const std::string& text);
        /// 调试命令：根据地图数据自动生成旅行导航节点
        bool HandleGenNode(Event& event, Player* requester, const std::string& text);
        /// 调试命令：生成并可视化两点之间的寻路或旅行路径
        bool HandleGenPath(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试路径裁剪逻辑并可视化裁剪后的路径点
        bool HandleCropPath(Event& event, Player* requester, const std::string& text);
        /// 调试命令：将修改后的旅行导航节点数据保存至数据库
        bool HandleSaveNode(Event& event, Player* requester, const std::string& text);
        /// 调试命令：从数据库重新加载旅行导航节点图数据
        bool HandleLoadNode(Event& event, Player* requester, const std::string& text);
        /// 调试命令：在世界中召唤路标生物以可视化显示旅行导航节点
        bool HandleShowNode(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试或查询减益/防御法术状态
        bool HandleDSpell(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试或查询特定类别法术（V类）
        bool HandleVSpell(Event& event, Player* requester, const std::string& text);
        /// 调试命令：查询或测试奥术/指定类别法术映射
        bool HandleASpell(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试或查询施法相关状态
        bool HandleCSpell(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试或查询火焰/友好法术状态
        bool HandleFSpell(Event& event, Player* requester, const std::string& text);
        /// 调试命令：查询指定法术的法术模板、射程、消耗与施法条件
        bool HandleSpell(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出法术映射表（T类）
        bool HandleTSpellMap(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出法术映射表（U类）
        bool HandleUSpellMap(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出法术映射表（D类）
        bool HandleDSpellMap(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出法术映射表（V类）
        bool HandleVSpellMap(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出法术映射表（I类）
        bool HandleISpellMap(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出法术映射表（C类）
        bool HandleCSpellMap(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出法术映射表（A类）
        bool HandleASpellMap(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出法术映射表（G类）
        bool HandleGSpellMap(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出法术映射表（M类）
        bool HandleMSpellMap(Event& event, Player* requester, const std::string& text);
        /// 调试命令：查询或输出音效 ID 映射表
        bool HandleSoundMap(Event& event, Player* requester, const std::string& text);
        /// 调试命令：搜索并测试多个相关音效
        bool HandleSounds(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试播放或查询指定音效
        bool HandleDSound(Event& event, Player* requester, const std::string& text);
        /// 调试命令：在机器人位置触发播放指定 ID 的音效
        bool HandleSound(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出机器人当前详细的卡死诊断报告与上下文快照
        bool HandleStuck(Event& event, Player* requester, const std::string& text);
        /// 调试命令：分析并解释机器人刚刚为什么执行某项动作或为何停滞
        bool HandleWhy(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出 AI 引擎当前执行栈与各策略权重
        bool HandleEngine(Event& event, Player* requester, const std::string& text);
        /// 调试命令：输出机器人最近执行的动作与状态历史记录
        bool HandleHistory(Event& event, Player* requester, const std::string& text);

        // Shared debug snapshot helpers (used by HandleStuck and HandleWhy) (共享调试快照辅助函数（供 HandleStuck 与 HandleWhy 共用）)
        struct StuckFacts
        {
            WorldPosition pos;
            bool isMoving = false;
            bool isMounted = false;
            bool isTaxiFlying = false;
            bool isInCombat = false;
            bool isDead = false;

            bool hasTravel = false;
            int travelStatus = 0;                 // cast of TravelStatus (转换 TravelStatus 状态枚举)
            int32 travelTimeLeft = 0;             // ms
            bool hasTravelPos = false;
            WorldPosition travelPos;
            float travelDistance = 0.0f;
            uint32 travelRetryMove = 0;
            uint32 travelRetryTarget = 0;
            bool canFreeMove = false;
            bool differentMap = false;
            std::string travelTitle;
            std::vector<std::pair<std::string, bool>> travelConditions;

            bool canMoveAround = true;
            bool travelTargetActive = false;
            bool travelTargetTraveling = false;

            uint32 posLastChange = 0;
            bool isStuck = false;

            bool hasGroup = false;
            bool groupIsLeader = false;
        };
        /// 采集机器人移动/战斗卡死时的位置、路径、目标与动作历史快照
        StuckFacts GatherStuckFacts();
        /// 将采集到的卡死诊断事实格式化为多行可读文本
        std::vector<std::string> FormatStuckFactsLines(const StuckFacts& facts);
        /// 将旅行状态枚举值转换为可读的字符串名称
        static std::string TravelStatusName(int status, bool lower = false);
        /// 调试命令：输出或切换机器人战斗调试状态与仇恨信息
        bool HandleCombat(Event& event, Player* requester, const std::string& text);
        /// 调试命令：列出并统计当前地图中的旅行导航节点
        bool HandleNodes(Event& event, Player* requester, const std::string& text);
        /// 调试命令：查询或设置机器人活跃度系统状态
        bool HandleActivity(Event& event, Player* requester, const std::string& text);
        /// 调试命令：分析并调试跨地图交通载具航线数据
        bool HandleTransanal(Event& event, Player* requester, const std::string& text);
        /// 调试命令：检测当前位置上下的垂直空间与 VMap 高度
        bool HandleUpdownspace(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试绕开障碍物生成弧形/避让路径的算法
        bool HandlePatharound(Event& event, Player* requester, const std::string& text);
        /// 调试命令：测试指定坐标点的地面高度与视线（LOS）检测
        bool HandleHeightForLos(Event& event, Player* requester, const std::string& text);
    };
}
