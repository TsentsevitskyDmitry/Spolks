#pragma once
#include "Message/CommandMessage.h"
#include "Server/Processor/MessageProcessor/IMessageProcessor.h"

namespace Server
{
    class MessageProcessor
    {
    public:
        MessageProcessor();

        static std::shared_ptr<IMessageProcessor> Get(IMessage& msg);

    private:

    };
}
