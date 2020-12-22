#include "ClientTCP.h"

ClientTCP::ClientTCP(ip::tcp::socket &&_socket) :
    IClient(Protocol::TCP),
    socket(std::move(_socket))
{
    this->connected = true;
}

ClientTCP::ClientTCP(io_service &networkIO, std::string ipv4, uint16_t port) :
    IClient(Protocol::TCP),
    socket(networkIO)
{
    ip::tcp::endpoint ep(ip::address::from_string(ipv4), port);
    boost::system::error_code ec;
    socket.connect(ep, ec);
    if(ec)
        this->connected = false;
    else
        this->connected = true;
}

bool ClientTCP::isConnected()
{
    return connected;
}

bool ClientTCP::send(IMessage &message)
{
    try
    {
        size_t size = message.getSerializedSize();
        uint8_t* data = message.serialize();
        boost::system::error_code ec;
        size_t writed = socket.write_some(boost::asio::buffer(data, size), ec);
        //printf("Sended: %d\n", writed);
        return writed == size;
    }
    catch (std::exception e) {
        printf("Send failed: %d\n", e.what());
        return false;
    }
}

MessageMeta ClientTCP::recvMessageMeta()
{
    MessageMeta meta;
    socket.read_some(boost::asio::buffer(reinterpret_cast<uint8_t*>(&meta), sizeof(meta)));
    return meta;
}

bool ClientTCP::recv(IMessage& message)
{
    try
    {
        MessageMeta meta = recvMessageMeta();
        if(!meta.messageSize || meta.messageType != message.getMeta().messageType){
            return false;
        }

        size_t dataSize = meta.messageSize - sizeof(meta);
        uint8_t* data = new uint8_t[dataSize];

        size_t readed = 0;
        while(readed != dataSize)
        {
            readed += socket.read_some(boost::asio::buffer(data+readed, dataSize-readed));
        }

        message.deserialize(data);
        return meta.messageSize == message.getSerializedSize();
    }
    catch (std::exception e)
    {
        printf("Recv failed: %d\n", e.what());
        return false;
    }
}
