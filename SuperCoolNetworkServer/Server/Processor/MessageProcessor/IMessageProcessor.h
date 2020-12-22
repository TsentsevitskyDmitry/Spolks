#pragma once
#include "Message/IMessage.h"
#include <memory>

namespace Server
{
    class IMessageProcessor
    {
    public:
        IMessageProcessor();
        virtual ~IMessageProcessor() {}

        bool done();
        virtual void InitProcessor(IMessage& cmdMessage) = 0;

        virtual std::shared_ptr<IMessage> InitHolder() = 0;
        virtual std::shared_ptr<IMessage> Process(IMessage& msg) = 0;

    protected:
        bool isDone;

    };
}
