#include "ServerTCP.h"
#include "Client/ClientTCP.h"

ServerTCP::ServerTCP() :
    IServer(Protocol::TCP)
{

}

bool ServerTCP::start()
{
    acceptor = std::unique_ptr<ip::tcp::acceptor>(
                new ip::tcp::acceptor(networkIO, ip::tcp::endpoint(ip::tcp::v4(), static_cast<uint16_t>(serverPort))));
    return acceptor->is_open();
}

void ServerTCP::stop()
{
    acceptor->close();
}

std::shared_ptr<IClient> ServerTCP::accept()
{
    ip::tcp::socket sock(networkIO);
    acceptor->accept(sock);
    printf("client connected");

    return std::shared_ptr<ClientTCP>(new ClientTCP(std::move(sock)));
}
