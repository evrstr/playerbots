
#include "playerbot/playerbot.h"
#include "playerbot/PlayerbotAIConfig.h"
#include "playerbot/PlayerbotFactory.h"
#include "PlayerbotCommandServer.h"
#include <cstdlib>
#include <iostream>

INSTANTIATE_SINGLETON_1(PlayerbotCommandServer);

#include <boost/bind/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

using boost::asio::ip::tcp;
typedef boost::shared_ptr<tcp::socket> socket_ptr;

// 从 TCP 套接字缓冲按行读取远程命令
bool ReadLine(socket_ptr sock, std::string* buffer, std::string* line)
{
    // Do the real reading from fd until buffer has '\n'.
    std::string::iterator pos;
    while ((pos = find(buffer->begin(), buffer->end(), '\n')) == buffer->end())
    {
        char buf[1025];
        boost::system::error_code error;
        size_t n = sock->read_some(boost::asio::buffer(buf), error);
        if (n == -1 || error == boost::asio::error::eof)
            return false;
        else if (error)
            throw boost::system::system_error(error); // Some other error.

        buf[n] = 0;
        *buffer += buf;
    }

    *line = std::string(buffer->begin(), pos);
    *buffer = std::string(pos + 1, buffer->end());
    return true;
}

// 处理单个远程客户端 TCP 会话请求并回写执行结果
void session(socket_ptr sock)
{
    try
    {
        std::string buffer, request;
        while (ReadLine(sock, &buffer, &request)) {
            std::string response = sRandomPlayerbotMgr.HandleRemoteCommand(request) + "\n";
            boost::asio::write(*sock, boost::asio::buffer(response.c_str(), response.size()));
            request = "";
        }
    }
    catch (std::exception& e)
    {
        sLog.outError("%s",e.what());
    }
}

// 启动 TCP 监听循环并为每个连接分派工作线程
void server(boost::asio::io_context& io_context, short port)
{
    tcp::acceptor a(io_context, tcp::endpoint(tcp::v4(), port));
    for (;;)
    {
        socket_ptr sock(new tcp::socket(io_context));
        a.accept(*sock);
        boost::thread t(boost::bind(session, sock));
    }
}

void Run()
{
    if (!sPlayerbotAIConfig.commandServerPort) {
        return;
    }

    std::ostringstream s; s << "Starting Playerbot Command Server on port " << sPlayerbotAIConfig.commandServerPort;
    sLog.outString("%s",s.str().c_str());

    try
    {
        boost::asio::io_context io_context;
        server(io_context, sPlayerbotAIConfig.commandServerPort);
    }
    catch (std::exception& e)
    {
        sLog.outError("%s",e.what());
    }
}

// 在后台分离线程中启动远程指令监听服务
void PlayerbotCommandServer::Start()
{
    std::thread serverThread(Run);
    serverThread.detach();
}
