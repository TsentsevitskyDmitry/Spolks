#pragma once
#include "IClient.h"
#include <boost/asio.hpp>
#include <mutex>

using namespace boost::asio;

class ClientUDP : public IClient
{
public:
    ClientUDP(ip::udp::socket* _socket, std::mutex* _writeMutexp, std::mutex* _readMutex);
    ClientUDP(io_service& networkIO, std::string ipv4, uint16_t port);
    ~ClientUDP() override = default;

    bool send(IMessage& message) override;
    bool recv(IMessage& message) override;
    bool isConnected() override {return true;}

private:
    MessageMeta recvMessageMeta() override;

    uint8_t data[Config::InputBufferSize];
    size_t lastReaded = 0;

    std::mutex* writeMutex;
    std::mutex* readMutex;
    ip::udp::socket* socket;
    ip::udp::endpoint *ep;
};
