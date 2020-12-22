#include "DownloadMessageProcessor.h"
#include "Message/CommandMessage.h"
#include "Message/BitStreamMessage.h"
#include <boost/algorithm/string.hpp>
#include <vector>

namespace Client
{
    DownloadMessageProcessor::DownloadMessageProcessor()
    {

    }

    void DownloadMessageProcessor::InitProcessor(IMessage &cmdMessage)
    {
        auto cmdPtr = static_cast<CommandMessage*>(&cmdMessage);

        std::vector<std::string> data;
        boost::split(data, cmdPtr->getPayload(), boost::is_any_of(";"));

        try
        {
            file.open(Config::FilesPath + data[0], std::ios_base::binary | std::ios_base::app | std::ios_base::ate);
            if(!file.is_open()) throw std::exception();
            currentPos = std::stoull(data[1]);
            startPos = currentPos;
            start = std::chrono::high_resolution_clock::now();
        }
        catch (std::exception e)
        {
            isDone = true;
        }
    }

    std::shared_ptr<IMessage> DownloadMessageProcessor::InitHolder()
    {
        return std::shared_ptr<IMessage>(new BitStreamMessage());
    }

    std::shared_ptr<IMessage> DownloadMessageProcessor::Process(IMessage &msg)
    {
        auto in_msg = static_cast<BitStreamMessage*>(&msg);

        currentPos += in_msg->getSize();
        auto size = static_cast<long long>(in_msg->getSize());

        if(size <= 0)
        {
            isDone = true;
            auto time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start);
            double speed = (currentPos - startPos) / (time.count() / 1'000'000.);
            printf("%lu bytes transfered\n", currentPos - startPos);
            printf("Speed = %f Mbps\n", speed / 1024. / 1024.);
            file.close();
            return nullptr;
        }

        file.seekp(static_cast<long long>(in_msg->getOffset()));

        if(lastPos > in_msg->getOffset())
            printf("EROROR");

        lastPos = in_msg->getOffset();

        auto data = reinterpret_cast<char*>(in_msg->getData());
        file.write(data, size);

        return nullptr;
    }
}
