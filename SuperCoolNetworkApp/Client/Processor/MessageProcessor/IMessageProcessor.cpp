#include "IMessageProcessor.h"

namespace Client
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
