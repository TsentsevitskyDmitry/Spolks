#pragma once
#include "IMessage.h"
#include <string>

class CommandMessage : public IMessage
{
public:
    CommandMessage();

    std::string getCommand() const;
    std::string getPayload() const;

    void setCommand(const std::string &value);
    void setPayload(const std::string &value);

private:
    size_t _getSerializedSize() override;
    void _serialize(uint8_t* userData) override;
    void _deserialize(uint8_t* data) override;

    std::string command;
    std::string payload;
};
