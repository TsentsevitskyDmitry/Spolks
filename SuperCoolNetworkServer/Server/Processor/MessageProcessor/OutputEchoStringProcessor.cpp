#include "OutputEchoStringProcessor.h"
#include "Message/CommandMessage.h"
#include "Message/StringDataMessage.h"

namespace Server
{
    OutputEchoStringProcessor::OutputEchoStringProcessor()
    {

    }

    void OutputEchoStringProcessor::InitProcessor(IMessage &cmdMessage)
    {
        auto cmd_msg = dynamic_cast<CommandMessage*>(&cmdMessage);
        echo = cmd_msg->getPayload();
    }

    std::shared_ptr<IMessage> OutputEchoStringProcessor::InitHolder()
    {
        return nullptr;
    }

    std::shared_ptr<IMessage> OutputEchoStringProcessor::Process(IMessage &msg)
    {
        auto out_msg = new StringDataMessage();

        out_msg->setData(echo);
        isDone = true;

        return std::shared_ptr<IMessage>(out_msg);
    }
}
