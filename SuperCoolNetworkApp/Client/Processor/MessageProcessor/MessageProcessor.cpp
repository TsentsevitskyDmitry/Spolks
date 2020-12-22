#include "MessageProcessor.h"
#include "InputDataStringMessageProcessor.h"
#include "DownloadMessageProcessor.h"

namespace Client
{
    MessageProcessor::MessageProcessor()
    {

    }

    std::shared_ptr<IMessageProcessor> MessageProcessor::Get(IMessage &msg)
    {
        auto cmsg = dynamic_cast<CommandMessage*>(&msg);

        if(cmsg->getCommand() == Commands::TIME)
            return std::shared_ptr<IMessageProcessor>(new InputDataStringMessageProcessor());

        else if(cmsg->getCommand() == Commands::ECHO)
            return std::shared_ptr<IMessageProcessor>(new InputDataStringMessageProcessor());

        else if(cmsg->getCommand() == Commands::DOWLOAD) // Server send
            return std::shared_ptr<IMessageProcessor>(new DownloadMessageProcessor());

        return nullptr;
    }    
}
