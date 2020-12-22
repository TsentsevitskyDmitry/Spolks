#pragma once
#include "Message/CommandMessage.h"
#include "Common/Common.h"
#include <memory>
#include <vector>

class CommandGenerator
{
public:
    CommandGenerator();

    static std::shared_ptr<IMessage> Generate(const std::vector<std::string>& cmd);
    static std::string GetLastError();
    static void PrintLastError();

private:
    static void infoCreateFile();
    static void infoContinueFile(size_t pos);

    static void errorFile();
    static void errorBadInput();
    static void errorFileNotFound();
    static void errorUnknown(const std::string& str);
    static void errorTooFewArgs(const std::string& cmdName);
    static void errorPassingAfter(const std::string& cmd);

    static std::string error;
};
