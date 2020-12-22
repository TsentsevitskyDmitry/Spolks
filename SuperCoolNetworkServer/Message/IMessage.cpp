#include "IMessage.h"
#include <cstring>

IMessage::IMessage(MessageType _type) :
    meta(_type)
{

}

IMessage::~IMessage()
{
    if(serializedMessage)
        delete [] serializedMessage;
}

MessageMeta IMessage::getMeta() const
{
    return meta;
}

void IMessage::setMeta(const MessageMeta &value)
{
    meta = value;
}

size_t IMessage::serializedSize(std::string &string)
{
    return sizeof(size_t) + string.size();
}

uint8_t *IMessage::serialize()
{
    uint8_t* userData = prepareSerializeBuffer();
    _serialize(userData);
    return serializedMessage;
}

void IMessage::deserialize(uint8_t *userData)
{
    // only user data! no meta
    _deserialize(userData);
}

size_t IMessage::getSerializedSize()
{
    return sizeof(MessageMeta) + _getSerializedSize();
}

uint8_t* IMessage::prepareSerializeBuffer()
{
    if (serializedMessage)
        delete [] serializedMessage;
    meta.messageSize = getSerializedSize();
    serializedMessage = new uint8_t[meta.messageSize];
    std::memcpy(serializedMessage, &meta, sizeof(meta));
    return serializedMessage + sizeof(meta);
}

void IMessage::serializeString(uint8_t **buffer, std::string &string)
{
    size_t size = string.size();
    std::memcpy(*buffer, &size, sizeof(size));
    *buffer += sizeof(size);
    std::memcpy(*buffer, string.data(), size);
    *buffer += size;
}

void IMessage::deserializeString(uint8_t **buffer, std::string &string)
{
    size_t size = **buffer;
    *buffer += sizeof(size);
    string.resize(size);
    std::memcpy(string.data(), *buffer, size);
    *buffer += size;
}
