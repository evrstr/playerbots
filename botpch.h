//add here most rarely modified headers to speed up debug build compilation | 在此处添加极少修改的头文件以加速调试构建编译
#include "Server/WorldSocket.h"
#include "Common.h"

// Core game systems | 核心游戏系统
#include "Maps/MapManager.h"
#include "Log/Log.h"
#include "Globals/ObjectAccessor.h"
#include "Entities/ObjectGuid.h"
#include "Server/SQLStorages.h"
#include "Server/Opcodes.h"
#include "Globals/SharedDefines.h"
#include "Guilds/GuildMgr.h"
#include "Globals/ObjectMgr.h"
#include "DBScripts/ScriptMgr.h"

// Heavy game headers (frequently used, rarely modified) | 高频使用但极少修改的重型游戏头文件
#include "Spells/Spell.h"
#include "Spells/SpellMgr.h"
#include "Spells/SpellAuras.h"
#include "Server/WorldPacket.h"
#include "Loot/LootMgr.h"
#include "Entities/GossipDef.h"
#include "Chat/Chat.h"
#include "World/World.h"
#include "Entities/Unit.h"
#include "MotionGenerators/MotionMaster.h"
#include "Guilds/Guild.h"
#include "Entities/Player.h"
#include "Groups/Group.h"
#include "Database/DatabaseEnv.h"

// Grid system (used in many playerbot files) | 网格系统（广泛用于多个 PlayerBot 文件）
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"

// Boost headers (used across multiple files) | Boost 头文件（跨多文件复用）
#include <boost/algorithm/string.hpp>
#include <boost/functional/hash.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>

// STL headers | 标准模板库头文件
#include <stack>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <memory>
#include <regex>
#include <numeric>

// Playerbot core | PlayerBot 核心入口
#include "playerbot/playerbot.h"

// Playerbot AI framework (included 40-60+ times each, rarely modified) | PlayerBot AI 框架头文件（高频包含、极少修改）
#include "playerbot/strategy/AiObject.h"
#include "playerbot/strategy/Value.h"
#include "playerbot/strategy/Action.h"
#include "playerbot/strategy/Trigger.h"
#include "playerbot/strategy/Strategy.h"
#include "playerbot/strategy/NamedObjectContext.h"
#include "playerbot/strategy/AiObjectContext.h"
