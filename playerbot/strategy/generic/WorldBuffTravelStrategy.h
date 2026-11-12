/// 世界增益自动旅行（World Buff Travel）步骤常量、辅助函数与策略头文件
#pragma once
#include "playerbot/strategy/Strategy.h"

namespace ai
{
    /// 世界增益收集状态机步骤枚举（龙头 -> 赞达拉 -> 厄运贡品 -> 轻歌花 -> 回城）
    enum class WorldBuffTravelStep : uint8
    {
        STEP_STORMWIND = 0,         // Rallying Cry of the Dragonslayer | 屠龙者的咆哮（暴风城/奥格瑞玛）
        STEP_GRYPHON_MASTER,        // Waypoint: travel to Stormwind flight master (Alliance only, Horde skips) | 航点：前往暴风城飞行管理员（仅联盟）
        STEP_BOOTY_BAY,             // Spirit of Zandalar | 赞达拉之魂（藏宝海湾）
        STEP_BRAGOK,                // Waypoint: travel to Ratchet flight master | 航点：前往棘齿城飞行管理员
        STEP_THYSSIANA,             // Waypoint: travel to flight master (Alliance: Thyssiana, Horde: Shyn) | 航点：前往菲拉斯飞行管理员（联盟：塞希亚娜，部落：什恩）
        STEP_FEATHERMOON,           // Waypoint: arrived in Feralas, head off the island (Alliance only, Horde skips) | 航点：抵达菲拉斯羽月要塞后离开岛屿（仅联盟）
        STEP_FORGOTTEN_COAST,       // Waypoint: reach Zorbin Fandazzle on Forgotten Coast (Alliance only, Horde skips) | 航点：前往遗忘海岸找佐尔宾（仅联盟）
        STEP_DM_TRAVEL,             // Travel to Dire Maul North door | 前往厄运之槌北门
        STEP_DM_INSIDE,             // Inside DM North — get tribute buffs | 进入厄运北领取三大贡品 Buff
        STEP_DM_EXIT,               // Leave instance back to overworld | 离开厄运之槌副本返回野外
        STEP_DM_PORTAL,             // Mages cast Portal (Alliance: Darnassus, Horde: Orgrimmar), everyone takes it | 法师施放传送门（联盟达纳苏斯 / 部落奥格瑞玛），全队点击传送
        STEP_FELWOOD,               // Waypoint: arrive in Felwood zone (Alliance: Mishellena, Horde: Brakkar) | 航点：抵达费伍德森林
        STEP_SONGFLOWER,            // Travel to a Cleansed Songflower GO and use it | 前往被净化的轻歌花并拾取风歌夜曲
        STEP_PORTAL_HOME,           // Mages cast Portal home (Alliance: Stormwind, Horde: Orgrimmar), everyone takes it | 法师施放回主城传送门，全队点击传送回家
        STEP_DONE,                  // All buffs collected | 全部世界增益收集完毕
        STEP_COUNT
    };

    // Spell IDs for the world buffs (Classic values) | 世界增益及传送门法术 ID（经典旧世）
    /// 经典旧世世界增益与法师传送门法术 ID 常量
    enum WorldBuffTravelSpells : uint32
    {
        SPELL_RALLYING_CRY = 22888,    // Rallying Cry of the Dragonslayer
        SPELL_SPIRIT_OF_ZANDALAR = 24425,    // Spirit of Zandalar
        SPELL_DM_TRIBUTE_FENGUS = 22817,    // Fengus' Ferocity (DMT)
        SPELL_DM_TRIBUTE_SLIPKIK = 22820,    // Slip'kik's Savvy (DMT)
        SPELL_DM_TRIBUTE_GORDOK = 22818,    // Mol'dar's Moxie (DMT)
        SPELL_SONGFLOWER = 15366,    // Songflower Serenade
        SPELL_WARCHIEFS_BLESSING = 16609,    // Warchief's Blessing (Horde only)
        SPELL_PORTAL_STORMWIND = 10059,    // Portal: Stormwind (Mage)
        SPELL_PORTAL_DARNASSUS = 11419,    // Portal: Darnassus (Mage)
        SPELL_PORTAL_ORGRIMMAR = 11417,    // Portal: Orgrimmar (Mage)
    };

    // NPC entry IDs for waypoint steps | 沿途航点 NPC Entry ID
    /// 旅行沿途各导航点与飞行管理员 NPC Entry ID
    enum WorldBuffTravelNpcs : uint32
    {
        NPC_DUNGAR_LONGDRINK = 352,      // Stormwind gryphon master (Alliance)
        NPC_BRAGOK = 16227,    // Ratchet flight master
        NPC_THYSSIANA = 4319,     // Thalanaar flight master (Alliance)
        NPC_ZORBIN_FANDAZZLE = 14637,    // Forgotten Coast, Feralas (Alliance mainland waypoint)
        NPC_MISHELLENA = 12578,    // Felwood waypoint NPC (Alliance)
        NPC_SHYN = 8020,     // Camp Mojache flight master (Horde)
        NPC_BRAKKAR = 11900,    // Felwood waypoint NPC (Horde)
    };

    // Taxi node IDs for flight destinations | 飞行路线目的节点 ID
    /// 沿途搭乘鸟点所使用的 Taxi Node ID
    enum WorldBuffTravelTaxiNodes : uint32
    {
        TAXI_NODE_BOOTY_BAY = 19,     // Booty Bay, Stranglethorn
        TAXI_NODE_THALANAAR = 42,     // Thalanaar, Feralas (Alliance)
        TAXI_NODE_FEATHERMOON = 31,     // Feathermoon, Feralas (Alliance)
        TAXI_NODE_CAMP_MOJACHE = 44,     // Camp Mojache, Feralas (Horde)
    };

    // Game object entry IDs | 相关游戏对象 Entry ID
    /// 厄运北门与菲拉斯篝火游戏对象 Entry ID
    enum WorldBuffTravelGameObjects : uint32
    {
        GO_DM_NORTH_DOOR = 177192,      // Dire Maul North door (guid 49948)
        GO_BONFIRE_FERALAS = 176318,     // Bonfire near DM, Feralas (Horde waypoint for STEP_FORGOTTEN_COAST)
    };

    constexpr uint32 GO_DM_NORTH_DOOR_GUID = 49948;

    constexpr uint32 GO_SONGFLOWER_ENTRIES[] =
    {
        164886, 171939, 171942, 174594, 174595,
        174596, 174597, 174598, 174712, 174713
    };
    constexpr uint32 GO_SONGFLOWER_ENTRY_COUNT = sizeof(GO_SONGFLOWER_ENTRIES) / sizeof(GO_SONGFLOWER_ENTRIES[0]);

    /// 沿途相关主城与野外地图/区域 ID 常量
    enum WorldBuffTravelZones : uint32
    {
        ZONE_STORMWIND = 1519,
        ZONE_ORGRIMMAR = 1637,
        AREA_BOOTY_BAY = 35,
        MAP_DIRE_MAUL = 429,
        ZONE_DIRE_MAUL = 2557,
        ZONE_FERALAS = 357,
        ZONE_FELWOOD = 361,
        ZONE_DARNASSUS = 1657,
    };

    constexpr uint32 AREATRIGGER_DM_NORTH = 3193;

    constexpr float PORTAL_REGROUP_DISTANCE = 100.0f;

    /// 判断玩家是否属于部落阵营
    inline bool IsHordeFaction(Player* player)
    {
        return player->GetTeam() == HORDE;
    }

    /// 获取阵营对应的主城区域 ID（奥格瑞玛/暴风城）
    inline uint32 GetHomeZone(Player* player)
    {
        return IsHordeFaction(player) ? ZONE_ORGRIMMAR : ZONE_STORMWIND;
    }

    /// 获取厄运之槌传送门的目标区域 ID
    inline uint32 GetDMPortalDestZone(Player* player)
    {
        return IsHordeFaction(player) ? ZONE_ORGRIMMAR : ZONE_DARNASSUS;
    }

    /// 获取厄运之槌阶段法师应施放的传送门法术 ID
    inline uint32 GetDMPortalSpell(Player* player)
    {
        return IsHordeFaction(player) ? SPELL_PORTAL_ORGRIMMAR : SPELL_PORTAL_DARNASSUS;
    }

    /// 获取最终回城阶段法师应施放的传送门法术 ID
    inline uint32 GetHomePortalSpell(Player* player)
    {
        return IsHordeFaction(player) ? SPELL_PORTAL_ORGRIMMAR : SPELL_PORTAL_STORMWIND;
    }

    /// 获取厄运传送门名称匹配关键字
    inline const char* GetDMPortalKeyword(Player* player)
    {
        return IsHordeFaction(player) ? "Orgrimmar" : "Darnassus";
    }

    /// 获取回城传送门名称匹配关键字
    inline const char* GetHomePortalKeyword(Player* player)
    {
        return IsHordeFaction(player) ? "Orgrimmar" : "Stormwind";
    }

    /// 判断游戏对象 Entry 是否为任意可拾取的轻歌花节点
    inline bool IsSongflowerEntry(uint32 entry)
    {
        for (uint32 i = 0; i < GO_SONGFLOWER_ENTRY_COUNT; ++i)
            if (GO_SONGFLOWER_ENTRIES[i] == entry)
                return true;
        return false;
    }

    /// 判断玩家是否已集齐全部三项厄运之槌贡品 Buff
    inline bool HasAllDMTributeBuffs(Player* player)
    {
        return player->HasAura(SPELL_DM_TRIBUTE_FENGUS)
            && player->HasAura(SPELL_DM_TRIBUTE_SLIPKIK)
            && player->HasAura(SPELL_DM_TRIBUTE_GORDOK);
    }

    /// 判断给定旅行步骤是否为仅限联盟的过渡步
    inline bool IsAllianceOnlyStep(WorldBuffTravelStep step)
    {
        return step == WorldBuffTravelStep::STEP_GRYPHON_MASTER
            || step == WorldBuffTravelStep::STEP_FEATHERMOON;
    }

    /// 检查队伍所有存活成员是否均在同一地图且位于传送门集结距离内
    inline bool AreAllGroupMembersNearby(Player* player)
    {
        Group* group = player->GetGroup();
        if (!group)
            return true;

        for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
        {
            Player* member = ref->getSource();
            if (member == player)
                continue;

            if (!member)
                return false;

            if (!member->IsAlive())
                continue;

            if (member->GetMapId() != player->GetMapId())
                return false;

            if (member->IsTaxiFlying())
                return false;

            if (player->GetDistance(member) > PORTAL_REGROUP_DISTANCE)
                return false;
        }
        return true;
    }

    /// 根据玩家当前身上已有的 Buff 与位置确定应当开始执行的步骤
    inline WorldBuffTravelStep GetFirstNeededStep(Player* player)
    {
        bool horde = IsHordeFaction(player);

        if (!player->HasAura(SPELL_RALLYING_CRY))
            return WorldBuffTravelStep::STEP_STORMWIND;

        if (!player->HasAura(SPELL_SPIRIT_OF_ZANDALAR))
        {
            return horde ? WorldBuffTravelStep::STEP_BOOTY_BAY
                : WorldBuffTravelStep::STEP_GRYPHON_MASTER;
        }

        if (!HasAllDMTributeBuffs(player))
            return WorldBuffTravelStep::STEP_BRAGOK;

        uint32 zoneId = player->GetZoneId();
        uint32 portalDestZone = GetDMPortalDestZone(player);
        if (zoneId != ZONE_FELWOOD && zoneId != portalDestZone)
        {
            if (!player->HasAura(SPELL_SONGFLOWER))
                return WorldBuffTravelStep::STEP_DM_INSIDE;
        }

        if (!player->HasAura(SPELL_SONGFLOWER))
            return WorldBuffTravelStep::STEP_FELWOOD;

        uint32 homeZone = GetHomeZone(player);
        if (zoneId != homeZone)
            return WorldBuffTravelStep::STEP_PORTAL_HOME;

        return WorldBuffTravelStep::STEP_DONE;
    }

    /// 乘数：在世界增益旅行过程中屏蔽普通旅行、RPG 与刷怪干扰
    class WorldBuffTravelMultiplier : public Multiplier
    {
    public:
        WorldBuffTravelMultiplier(PlayerbotAI* ai) : Multiplier(ai, "world buff travel") {}
        float GetValue(Action* action) override;
    };

    /// 策略：按脚本化路线自动跨地图旅行收集经典旧世各大世界增益（wbuff travel）
    class WorldBuffTravelStrategy : public Strategy
    {
    public:
        WorldBuffTravelStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_NONCOMBAT; }
        std::string getName() override { return "wbuff travel"; }

#ifdef GenerateBotHelp
        virtual std::string GetHelpName() { return "wbuff travel"; }
        virtual std::string GetHelpDescription() {
            return "This strategy makes bots travel to specific zones in a scripted sequence to collect world buffs.";
        }
        virtual std::vector<std::string> GetRelatedStrategies() { return { "wbuff", "travel" }; }
#endif

    protected:
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatMultipliers(std::list<Multiplier*>& multipliers) override;
        void OnStrategyAdded(BotState state) override;
        void OnStrategyRemoved(BotState state) override;
    };
}