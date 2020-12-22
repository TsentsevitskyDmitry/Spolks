#include "InputDataStringMessageProcessor.h"
#include "Message/StringDataMessage.h"
#include <iostream>

namespace Client
{
    InputDataStringMessageProcessor::InputDataStringMessageProcessor()
    {

    }

    std::shared_ptr<IMessage> InputDataStringMessageProcessor::InitHolder()
    {
        return std::shared_ptr<IMessage>(new StringDataMessage());
    }

    std::shared_ptr<IMessage> InputDataStringMessageProcessor::Process(IMessage &msg)
    {
        std::cout << dynamic_cast<StringDataMessage*>(&msg)->getData() << std::endl;
        isDone = true;

        return nullptr;
    }
}
