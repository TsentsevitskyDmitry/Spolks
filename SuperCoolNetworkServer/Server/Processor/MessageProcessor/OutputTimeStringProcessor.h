#pragma once
#include "IMessageProcessor.h"

namespace Server
{
    class OutputTimeStringProcessor : public IMessageProcessor
    {
    public:
        OutputTimeStringProcessor();
        ~OutputTimeStringProcessor() override = default;

        void InitProcessor(IMessage& cmdMessage) override {};

        std::shared_ptr<IMessage> InitHolder() override;
        std::shared_ptr<IMessage> Process(IMessage& msg) override;
    };
}
