#pragma once
#include "IClient.h"
#include <boost/asio.hpp>

using namespace boost::asio;

class ClientTCP : public IClient
{
public:
    ClientTCP(ip::tcp::socket&& _socket);
    ClientTCP(io_service& networkIO, std::string ipv4, uint16_t port);

    ~ClientTCP() override = default;

    bool send(IMessage& message) override;
    bool recv(IMessage& message) override;

    bool isConnected() override;

private:
    MessageMeta recvMessageMeta() override;

    ip::tcp::socket socket;
    bool connected;
};
