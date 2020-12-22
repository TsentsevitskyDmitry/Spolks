#pragma once
#include "IMessage.h"
#include <memory>

class BitStreamMessage : public IMessage
{
public:
    BitStreamMessage();

    size_t getSize();
    size_t getOffset();

    uint8_t* getBuffer(size_t size);
    uint8_t* getData();

    void setOffset(size_t offset);

private:
    std::shared_ptr<uint8_t> data;
    size_t offset = 0;
    size_t size = 0;

    size_t _getSerializedSize() override;
    void _serialize(uint8_t* userData) override;
    void _deserialize(uint8_t* userData) override;
};
