#include "WorldPosition.h"

namespace ai
{
    typedef std::map<uint32, Player*> RealPlayers;

    class PlayerLoginInfo;

    typedef std::map<uint32, PlayerLoginInfo> BotPool;
    typedef std::vector<PlayerLoginInfo> RealPlayerInfos;
    typedef std::vector<PlayerLoginInfo*> BotInfos;

        /// 当前在线空间与职业/种族/等级分布统计快照
        struct LoginSpace
    {
        int32 currentSpace;
        int32 totalSpace;
        int32 classRaceBucket[MAX_CLASSES][MAX_RACES];
        int32 levelBucket[DEFAULT_MAX_LEVEL + 1];
        RealPlayerInfos realPlayerInfos;
    };

        /// 异步角色登录 SQL 查询句柄状态
        enum class HolderState : uint8
    {
        HOLDER_EMPTY = 0,
        HOLDER_SENT = 1,
        HOLDER_RECEIVED = 2
    };

        /// 机器人在线队列状态枚举
        enum class LoginState : uint8
    {
        BOT_OFFLINE = 0,
        BOT_ON_LOGINQUEUE = 1,
        BOT_ONLINE = 2,
        BOT_ON_LOGOUTQUEUE = 3
    };

        /// 空间占用计算阶段枚举
        enum class FillStep : uint8
    {
        NOW = 0,
        NEXT_STEP = 1,
        ALL_POTENTIAL = 2
    };

        /// 机器人登录准入条件校验结果枚举
        enum class LoginCriterionFailType : uint8
    {
        UNKNOWN = 0,
        MAX_BOTS = 1,
        SPARE_ROOM,
        ONLINE,
        RANDOM_TIMED_LOGOUT,
        RANDOM_TIMED_OFFLINE,
        CLASSRACE,
        LEVEL,
        RANGE,
        MAP,
        GROUP,
        GUILD,
        BG,
        ARENA,
        INSTANCE,
        LOGIN_OK
    };

    static std::unordered_map<LoginCriterionFailType, std::string> failName = {
         {LoginCriterionFailType::UNKNOWN, "UNKNOWN"}
        ,{LoginCriterionFailType::MAX_BOTS, "MAX_BOTS"}
        ,{LoginCriterionFailType::SPARE_ROOM, "SPARE_ROOM"}
        ,{LoginCriterionFailType::ONLINE, "ONLINE"}
        ,{LoginCriterionFailType::RANDOM_TIMED_LOGOUT, "RANDOM_TIMED_LOGOUT"}
        ,{LoginCriterionFailType::RANDOM_TIMED_OFFLINE , "RANDOM_TIMED_OFFLINE"}
        ,{LoginCriterionFailType::CLASSRACE, "CLASSRACE"}
        ,{LoginCriterionFailType::LEVEL, "LEVEL"}
        ,{LoginCriterionFailType::RANGE , "RANGE"}
        ,{LoginCriterionFailType::MAP , "MAP"}
        ,{LoginCriterionFailType::GUILD , "GUILD"}
        ,{LoginCriterionFailType::GROUP , "GROUP"}
        ,{LoginCriterionFailType::BG , "BG"}
        ,{LoginCriterionFailType::ARENA , "ARENA"}
        ,{LoginCriterionFailType::INSTANCE , "INSTANCE"}
        ,{LoginCriterionFailType::LOGIN_OK, "LOGIN_OK"} };

    typedef std::vector <std::pair<LoginCriterionFailType, std::function<bool(const PlayerLoginInfo&, const LoginSpace&)>>> LoginCriteria;

        /// 单个随机机器人的登录元数据、位置与异步登录状态包装类
        class PlayerLoginInfo
    {
    public:
        PlayerLoginInfo(const uint32 account, const uint32 guid, const uint8 race, const uint8 cls, const uint32 level, const bool isNew, const WorldPosition& position, const uint32 guildId);

        PlayerLoginInfo(Player* player);

        ObjectGuid GetGuid() const { return ObjectGuid(HIGHGUID_PLAYER, guid); }
        uint32 GetId() const { return guid; }
        uint8 GetRace() const { return race; }
        uint8 GetClass() const { return cls; }
        uint32 GetLevel() const;
        Player* GetPlayer() const { return sObjectMgr.GetPlayer(ObjectGuid(HIGHGUID_PLAYER, guid), false); }
        bool IsNearPlayer(const LoginSpace& space) const;
        bool IsOnPlayerMap(const LoginSpace& space) const;
        bool IsInPlayerGroup(const LoginSpace& space) const;
        bool IsInPlayerGuild(const LoginSpace& space) const;
        bool IsInBG() const;
        bool IsInArena() const;
        bool IsInInstance() const;
        bool IsOnline() const { return loginState == LoginState::BOT_ONLINE || loginState == LoginState::BOT_ON_LOGOUTQUEUE; }
        LoginState GetLoginState() const { return loginState; }

        bool SendHolder();
        void HandlePlayerBotLoginCallback(QueryResult* /*dummy*/, SqlQueryHolder* holder);

        void ResetLoginState();
        void FillLoginSpace(LoginSpace& space, FillStep step = FillStep::NOW) const;
        void EmptyLoginSpace(LoginSpace& space, FillStep step = FillStep::NOW) const;

        void SetQueue(bool isWanted, LoginSpace& space);
        bool IsQueued() const;

        LoginCriterionFailType MatchNoCriteria(const LoginSpace& space, const LoginCriteria& criteria) const;

        void Update(Player* player);
        bool LoginBot();
        bool LogoutBot();
    private:

        uint32 account;
        uint32 guid;
        uint8 race;
        uint8 cls;
        uint32 level;
        bool isNew = false;
        WorldPosition position;
        uint32 groupId;
        uint32 guildId;

        SqlQueryHolder* holder = nullptr;
        HolderState holderState = HolderState::HOLDER_EMPTY;
        LoginState loginState = LoginState::BOT_OFFLINE;
    };

        /// 随机机器人异步上下线调度管理器，根据真实玩家分布、等级和职业种族配额动态维护在线机器人池
        class PlayerBotLoginMgr
    {
    public:
        void Update(RealPlayers& realPlayers);
        void ToggleDebug() { debug = !debug; }
    private:
        static BotPool LoadBotsFromDb();
        void UpdateOnlineBots();
        static BotInfos FillLoginLogoutQueue(BotPool* pool, const RealPlayers& realPlayers);
        void LoginLogoutBots(const BotInfos& queue);

        static RealPlayerInfos GetPlayerInfos(const RealPlayers& realPlayers);
        static uint32 GetLoginCriteriaSize();
        static std::vector<std::string> GetVariableLoginCriteria(const uint8 attempt);
        static LoginCriteria GetLoginCriteria(const uint8 attempt);
        static bool CriteriaStillValid(const LoginCriterionFailType oldFailType, const LoginCriteria& criteria);

        static uint32 GetMaxOnlineBotCount();
        static uint32 GetMaxLevel();
        static uint32 GetClassRaceBucketSize(uint8 cls, uint8 race);
        static uint32 GetLevelBucketSize(uint32 level);
        static void FillLoginSpace(BotPool* pool, LoginSpace& space, FillStep step);

        static void SendHolders(const BotInfos& queue);
        static void SendHolders(BotPool* pool);

        std::future<BotInfos> futureQueue;
        std::future<BotPool> futurePool;

        bool debug = false;
        BotInfos onlineBots;
        BotPool botPool;
    };
}

#define sPlayerBotLoginMgr MaNGOS::Singleton<PlayerBotLoginMgr>::Instance()
