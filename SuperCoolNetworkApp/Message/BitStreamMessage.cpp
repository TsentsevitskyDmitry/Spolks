#include "BitStreamMessage.h"

BitStreamMessage::BitStreamMessage() :
    IMessage (MessageType::BITSTREAM)
{

}

size_t BitStreamMessage::getOffset()
{
    return offset;
}

size_t BitStreamMessage::getSize()
{
    return size;
}

uint8_t *BitStreamMessage::getBuffer(size_t size)
{
    data.reset();
    data = std::shared_ptr<uint8_t>(new uint8_t[size]);
    return data.get();
}

uint8_t* BitStreamMessage::getData()
{
    return data.get();
}

void BitStreamMessage::setOffset(size_t value)
{
    offset = value;
}

size_t BitStreamMessage::_getSerializedSize()
{
    return sizeof(offset) + sizeof(size) + size;
}

void BitStreamMessage::_serialize(uint8_t *userData)
{
    memcpy(userData, &offset, sizeof(offset));
    userData += sizeof(offset);
    memcpy(userData, &size, sizeof(size));
    userData += sizeof(size);
    memcpy(userData, data.get(), size);
}

void BitStreamMessage::_deserialize(uint8_t *userData)
{
    memcpy(&offset, userData, sizeof(offset));
    userData += sizeof(offset);
    memcpy(&size, userData, sizeof(size));
    userData += sizeof(size);
    data.reset();
    data = std::shared_ptr<uint8_t>(new uint8_t[size]);
    memcpy(data.get(), userData, size);
}
