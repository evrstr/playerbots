/// Playerbot 核心总头文件：汇总游戏基础头文件、机器人核心组件与字符串工具声明
#pragma once

#include "Spells/Spell.h"
#include "Server/WorldPacket.h"
#include "Loot/LootMgr.h"
#include "Entities/GossipDef.h"
#include "Chat/Chat.h"
#include "Common.h"
#include "World/World.h"
#include "Spells/SpellMgr.h"
#include "Globals/ObjectMgr.h"
#include "Entities/Unit.h"
#include "Globals/SharedDefines.h"
#include "MotionGenerators/MotionMaster.h"
#include "Spells/SpellAuras.h"
#include "Guilds/Guild.h"

#include "playerbotDefs.h"
#include "playerbot/PlayerbotAIAware.h"
#include "PlayerbotMgr.h"
#include "playerbot/RandomPlayerbotMgr.h"
#include "ChatHelper.h"
#include "BroadcastHelper.h"
#include "PlayerbotAI.h"
#include "PlayerbotDbStore.h"

/// Playerbot 版本号定义
#define MANGOSBOT_VERSION 2

/// 按单字符分隔符拆分字符串
std::vector<std::string> split(std::string const& s, char delim);
/// 按多字符分隔符拆分字符串并写入目标容器
void split(std::vector<std::string>& dest, std::string const& str, char const* delim);
#ifndef WIN32
/// 非 Windows 平台下的不区分大小写字符串比较
int strcmpi(std::string s1, std::string s2);
#endif
