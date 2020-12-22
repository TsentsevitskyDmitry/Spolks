#include "ServerUDP.h"
#include "Client/ClientUDP.h"

ServerUDP::ServerUDP() :
    IServer(Protocol::UDP)
{

}

bool ServerUDP::start()
{
    socket = std::unique_ptr<ip::udp::socket>(
                new ip::udp::socket(networkIO, ip::udp::endpoint(ip::udp::v4(), serverPort)));

    return socket->is_open();
}

void ServerUDP::stop()
{
    socket->close();
}

std::shared_ptr<IClient> ServerUDP::accept()
{
    return std::shared_ptr<ClientUDP>(new ClientUDP(socket.get(), &writeMutex, &readMutex));
}
