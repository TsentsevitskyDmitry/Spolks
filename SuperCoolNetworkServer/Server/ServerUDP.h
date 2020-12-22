#pragma once
#include "Server/IServer.h"
#include <mutex>

using namespace boost::asio;

class ServerUDP : public IServer
{
public:
    ServerUDP();
    ~ServerUDP() override = default;

    bool start() override;
    void stop() override;
    std::shared_ptr<IClient> accept() override;

private:
    std::mutex writeMutex;
    std::mutex readMutex;
    std::unique_ptr<ip::udp::socket> socket = nullptr;
};
