#include "ClientUDP.h"

ClientUDP::ClientUDP(ip::udp::socket* _socket, std::mutex* _writeMutexp, std::mutex* _readMutex) :
    IClient(Protocol::UDP)
{
    writeMutex = _writeMutexp;
    readMutex = _readMutex;
    socket = _socket;
}

ClientUDP::ClientUDP(io_service &networkIO, std::string ipv4, uint16_t port) :
    IClient(Protocol::UDP)
{
    static ip::udp::socket _socket(networkIO, ip::udp::endpoint(ip::udp::v4(), 0) );
    static ip::udp::endpoint _ep(ip::address::from_string(ipv4), port);
    static std::mutex _writeMutex;
    static std::mutex _readMutex;
    writeMutex = &_writeMutex;
    readMutex = &_readMutex;
    socket = &_socket;
    ep = &_ep;
}

bool ClientUDP::send(IMessage &message)
{
    std::lock_guard lock(*writeMutex);

    try
    {
        size_t size = message.getSerializedSize();
        uint8_t* data = message.serialize();
        size_t writed = socket->send_to(boost::asio::buffer(data, size), *ep);
        return writed == size;
    }
    catch (std::exception e) {
        printf("Send failed: %d\n", e.what());
        return false;
    }
}

MessageMeta ClientUDP::recvMessageMeta()
{
    std::lock_guard lock(*readMutex);
    MessageMeta meta;

    size_t recvd = socket->receive_from(boost::asio::buffer(data, Config::InputBufferSize), *ep);

    memcpy(&meta, data, sizeof(meta)); // read meta

    while(recvd != meta.messageSize)
        socket->receive_from(boost::asio::buffer(data, Config::InputBufferSize), *ep);

    return meta;
}

bool ClientUDP::recv(IMessage &message)
{
    try
    {
        MessageMeta meta = recvMessageMeta();
        if(!meta.messageSize || meta.messageType != message.getMeta().messageType){
            return false;
        }

        message.deserialize(data + sizeof(meta));
        return meta.messageSize == message.getSerializedSize();
    }
    catch (std::exception e)
    {
        printf("Recv failed: %d\n", e.what());
        return false;
    }
}
