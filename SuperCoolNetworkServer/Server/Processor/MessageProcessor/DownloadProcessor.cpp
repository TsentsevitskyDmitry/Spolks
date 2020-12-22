#include "DownloadProcessor.h"
#include "Message/CommandMessage.h"
#include "Message/BitStreamMessage.h"
#include <boost/algorithm/string.hpp>
#include <vector>

namespace Server
{
    DownloadProcessor::DownloadProcessor()
    {

    }

    void DownloadProcessor::InitProcessor(IMessage &cmdMessage)
    {
        auto cmdPtr = static_cast<CommandMessage*>(&cmdMessage);

        std::vector<std::string> data;
        boost::split(data, cmdPtr->getPayload(), boost::is_any_of(";"));

        try
        {
            file.open(Config::FilesPath + data[0], std::ios_base::binary | std::ios_base::ate);
            printf("Init file %s download\n", (Config::FilesPath + data[0]).c_str());
            if(!file.is_open()) throw std::exception();
            auto endPos = static_cast<size_t>(file.tellg());
            auto startPos = std::stoull(data[1]);
            needSend = endPos - startPos;
            file.seekg(static_cast<unsigned long>(startPos));

            printf("endPos = %d \n", (int)endPos);
            printf("startPos = %d \n", (int)startPos);
            printf("needSend = %d \n", (int)needSend);
        }
        catch (std::exception e)
        {
            needSend = 0;
        }
    }

    std::shared_ptr<IMessage> DownloadProcessor::InitHolder()
    {
        return nullptr;
    }

    std::shared_ptr<IMessage> DownloadProcessor::Process(IMessage &msg)
    {
        auto out_msg = new BitStreamMessage();

        if(needSend > 0)
        {
            size_t sendSize = needSend > Config::OutputBufferSize ? Config::OutputBufferSize : needSend;

            auto sendBuff = reinterpret_cast<char*>(out_msg->getBuffer(sendSize));
            auto needSendll = static_cast<long long>(sendSize);

            file.read(sendBuff, needSendll);
            needSend -= sendSize;
        }
        else
        {
            isDone = true;
        }

        return std::shared_ptr<IMessage>(out_msg);
    }
}
