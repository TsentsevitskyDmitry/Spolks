#pragma once
#include "IMessageProcessor.h"

namespace Server
{
    class OutputEchoStringProcessor : public IMessageProcessor
    {
    public:
        OutputEchoStringProcessor();
        ~OutputEchoStringProcessor() override = default;

        void InitProcessor(IMessage& cmdMessage) override;

        std::shared_ptr<IMessage> InitHolder() override;
        std::shared_ptr<IMessage> Process(IMessage& msg) override;

    private:
        std::string echo;

    };
}
