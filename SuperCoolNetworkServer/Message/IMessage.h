#pragma once
#include <stdint.h>
#include "Common/Common.h"
#include <string>

struct MessageMeta
{
    size_t messageSize;
    MessageType messageType;

    MessageMeta() :
        messageSize(0),
        messageType(MessageType::ERROR_TYPE)
        {}

    MessageMeta(MessageType type) :
        messageSize(0),
        messageType(type)
        {}
};

class IMessage
{
public:
    IMessage(MessageType _type);
    virtual ~IMessage();

    uint8_t* serialize();
    void deserialize(uint8_t* data);
    size_t getSerializedSize();

    MessageMeta getMeta() const;
    void setMeta(const MessageMeta &value);

protected:
    virtual size_t _getSerializedSize() = 0;
    virtual void _serialize(uint8_t* userData) = 0;
    virtual void _deserialize(uint8_t* userData) = 0;

    size_t serializedSize(std::string& string);
    void serializeString(uint8_t** buffer, std::string& string);
    void deserializeString(uint8_t** buffer, std::string& string);

private:
    uint8_t *prepareSerializeBuffer();

    uint8_t* serializedMessage = nullptr;
    MessageMeta meta;
};
