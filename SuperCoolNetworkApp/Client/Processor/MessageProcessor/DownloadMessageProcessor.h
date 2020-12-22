#pragma once
#include "IMessageProcessor.h"
#include <chrono>
#include <fstream>

namespace Client
{
    class DownloadMessageProcessor : public IMessageProcessor
    {
    public:
        DownloadMessageProcessor();
        ~DownloadMessageProcessor() override = default;

        void InitProcessor(IMessage& cmdMessage) override;

        std::shared_ptr<IMessage> InitHolder() override;
        std::shared_ptr<IMessage> Process(IMessage& msg) override;

    private:
        std::chrono::high_resolution_clock::time_point start;
        std::ofstream file;
        size_t currentPos;
        size_t startPos;

        size_t lastPos;
    };
}
