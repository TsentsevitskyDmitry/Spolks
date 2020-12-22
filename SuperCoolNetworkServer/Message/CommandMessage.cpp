#include "CommandMessage.h"
#include <cstring>

CommandMessage::CommandMessage() :
    IMessage(MessageType::COMMAND)
{

}

std::string CommandMessage::getPayload() const
{
    return payload;
}

std::string CommandMessage::getCommand() const
{
    return command;
}

void CommandMessage::setPayload(const std::string &value)
{
    payload = value;
}

void CommandMessage::setCommand(const std::string &value)
{
    command = value;
}

size_t CommandMessage::_getSerializedSize()
{
    return serializedSize(command) + serializedSize(payload);
}

void CommandMessage::_serialize(uint8_t* userData)
{
    serializeString(&userData, command);
    serializeString(&userData, payload);
}

void CommandMessage::_deserialize(uint8_t *userData)
{
    deserializeString(&userData, command);
    deserializeString(&userData, payload);
}
