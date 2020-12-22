#include "ClientUDP.h"
#include <chrono>
#include <thread>

ClientUDP::ClientUDP(ip::udp::socket* _socket, std::mutex* _writeMutexp, std::mutex* _readMutex) :
    IClient(Protocol::UDP)
{
    writeMutex = _writeMutexp;
    readMutex = _readMutex;
    socket = _socket;

    printf("UDP instance created!\n");
}

ClientUDP::ClientUDP(io_service &networkIO, std::string ipv4, uint16_t port) :
    IClient(Protocol::UDP)
{
    static ip::udp::socket _socket(networkIO, ip::udp::endpoint(ip::udp::v4(), 0) );
    static std::mutex _writeMutex;
    static std::mutex _readMutex;
    writeMutex = &_writeMutex;
    readMutex = &_readMutex;
    socket = &_socket;

    ep = ip::udp::endpoint(ip::address::from_string(ipv4), port);
}

bool ClientUDP::send(IMessage &message)
{
    std::lock_guard l(*writeMutex);

    try
    {
        size_t size = message.getSerializedSize();
        uint8_t* data = message.serialize();
        size_t writed = socket->send_to(boost::asio::buffer(data, size), ep);
        return writed == size;
    }
    catch (std::exception e) {
        printf("Send failed: %d\n", e.what());
        return false;
    }
}

void ClientUDP::_recvUDP()
{
    std::lock_guard l(*readMutex);
    lastReaded = socket->receive_from(buffer(data, Config::InputBufferSize), ep);
}

MessageMeta ClientUDP::recvMessageMeta()
{
    MessageMeta meta;
    memcpy(reinterpret_cast<uint8_t*>(&meta), data, sizeof(meta));
    return meta;
}

bool ClientUDP::recv(IMessage &message)
{
    try
    {
        _recvUDP();

        MessageMeta meta = recvMessageMeta();
        if(!meta.messageSize || meta.messageType != message.getMeta().messageType){
            return false;
        }

        message.deserialize(data +  sizeof(meta));
        return meta.messageSize == message.getSerializedSize();
    }
    catch (std::exception e)
    {
        printf("Recv failed: %d\n", e.what());
        return false;
    }
}
