#pragma once
#include "Server/IServer.h"

using namespace boost::asio;

class ServerTCP : public IServer
{
public:
    ServerTCP();
    ~ServerTCP() override = default;

    bool start() override;
    void stop() override;
    std::shared_ptr<IClient> accept() override;

private:
    std::unique_ptr<ip::tcp::acceptor> acceptor = nullptr;

};
