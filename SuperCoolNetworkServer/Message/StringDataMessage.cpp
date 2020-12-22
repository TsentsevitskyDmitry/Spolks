#include "StringDataMessage.h"

StringDataMessage::StringDataMessage():
    IMessage (MessageType::STRING_DATA)
{

}

std::string StringDataMessage::getData() const
{
    return data;
}

void StringDataMessage::setData(const std::string &value)
{
    data = value;
}

size_t StringDataMessage::_getSerializedSize()
{
    return serializedSize(data);
}

void StringDataMessage::_serialize(uint8_t* userData)
{
    serializeString(&userData, data);
}

void StringDataMessage::_deserialize(uint8_t *userData)
{
    deserializeString(&userData, data);
}
