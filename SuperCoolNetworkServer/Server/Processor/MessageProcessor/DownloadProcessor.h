#pragma once
#include "IMessageProcessor.h"
#include <fstream>

namespace Server
{
    class DownloadProcessor : public IMessageProcessor
    {
    public:
        DownloadProcessor();
        ~DownloadProcessor() override = default;

        void InitProcessor(IMessage& cmdMessage) override;

        std::shared_ptr<IMessage> InitHolder() override;
        std::shared_ptr<IMessage> Process(IMessage& msg) override;

    private:
        std::ifstream file;
        size_t needSend;
    };

}
