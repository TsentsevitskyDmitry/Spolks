#pragma once
#include "Common/Common.h"
#include "Message/IMessage.h"
#include <memory>

class IClient
{
public:
    IClient(Protocol _protocol);
    virtual ~IClient() = default;

    virtual bool send(IMessage& message) = 0;
    virtual bool recv(IMessage& message) = 0;
    virtual MessageMeta recvMessageMeta() = 0;
    virtual bool isConnected() = 0;

protected:
    Protocol currentProtocol;
    // boost
};
