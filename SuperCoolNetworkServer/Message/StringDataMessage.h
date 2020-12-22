#pragma once
#include "IMessage.h"
#include <string>

class StringDataMessage : public IMessage
{
public:
    StringDataMessage();

    std::string getData() const;
    void setData(const std::string &value);

private:
    size_t _getSerializedSize() override;
    void _serialize(uint8_t* userData) override;
    void _deserialize(uint8_t* userData) override;

    std::string data;
};
