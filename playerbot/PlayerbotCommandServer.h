#ifndef _PlayerbotCommandServer_H
#define _PlayerbotCommandServer_H

#include "Common.h"
#include "PlayerbotAIBase.h"
#include "PlayerbotMgr.h"

/// 基于 TCP 套接字的远程指令服务器，监听端口接收并执行外部机器人管理命令
class PlayerbotCommandServer
{
public:
    PlayerbotCommandServer() {}
    virtual ~PlayerbotCommandServer() {}
    static PlayerbotCommandServer& instance()
    {
        static PlayerbotCommandServer instance;
        return instance;
    }

    void Start();
};

#define sPlayerbotCommandServer PlayerbotCommandServer::instance()

#endif
