#include "MessageProcessor.h"
#include "OutputTimeStringProcessor.h"
#include "OutputEchoStringProcessor.h"
#include "DownloadProcessor.h"

namespace Server
{
    MessageProcessor::MessageProcessor()
    {

    }

    std::shared_ptr<IMessageProcessor> MessageProcessor::Get(IMessage &msg)
    {
        auto cmsg = dynamic_cast<CommandMessage*>(&msg);

        if(cmsg->getCommand() == Commands::TIME)
            return std::shared_ptr<IMessageProcessor>(new OutputTimeStringProcessor());

        else if(cmsg->getCommand() == Commands::ECHO)
            return std::shared_ptr<IMessageProcessor>(new OutputEchoStringProcessor());

        else if(cmsg->getCommand() == Commands::DOWLOAD) // Server send
            return std::shared_ptr<IMessageProcessor>(new DownloadProcessor());

        return nullptr;
    }
}
