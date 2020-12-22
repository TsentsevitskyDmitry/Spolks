#include "OutputTimeStringProcessor.h"
#include "Message/StringDataMessage.h"
#include <boost/date_time.hpp>

namespace Server
{
    OutputTimeStringProcessor::OutputTimeStringProcessor()
    {

    }

    std::shared_ptr<IMessage> OutputTimeStringProcessor::InitHolder()
    {
        return nullptr;
    }

    std::shared_ptr<IMessage> OutputTimeStringProcessor::Process(IMessage &msg)
    {
        auto out_msg = new StringDataMessage();
        boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();

        out_msg->setData(to_simple_string(timeLocal));
        isDone = true;

        return std::shared_ptr<IMessage>(out_msg);
    }
}
