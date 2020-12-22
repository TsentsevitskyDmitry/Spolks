#include "IMessageProcessor.h"

namespace Server
{
    IMessageProcessor::IMessageProcessor()
    {
        isDone = false;
    }

    bool IMessageProcessor::done()
    {
        return isDone;
    }
}
