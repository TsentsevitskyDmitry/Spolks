#include "IServer.h"


IServer::IServer(Protocol _protocol) :
    currentProtocol(_protocol),
    serverPort(80)
{

}

uint32_t IServer::getPort() const
{
    return serverPort;
}

void IServer::setPort(const uint32_t &value)
{
    serverPort = value;
}
