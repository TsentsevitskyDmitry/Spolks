#pragma once
#include "Message/CommandMessage.h"
#include "Client/Processor/MessageProcessor/IMessageProcessor.h"

namespace Client
{
    class MessageProcessor
    {
    public:
        MessageProcessor();

        static std::shared_ptr<IMessageProcessor> Get(IMessage& msg);

    private:

    };
}
