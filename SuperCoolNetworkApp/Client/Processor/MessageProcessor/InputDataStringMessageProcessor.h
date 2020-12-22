#pragma once
#include "IMessageProcessor.h"

namespace Client
{
    class InputDataStringMessageProcessor : public IMessageProcessor
    {
    public:
        InputDataStringMessageProcessor();
        ~InputDataStringMessageProcessor() override = default;

        void InitProcessor(IMessage& cmdMessage) override {}

        std::shared_ptr<IMessage> InitHolder() override;
        std::shared_ptr<IMessage> Process(IMessage& msg) override;
    };
}
