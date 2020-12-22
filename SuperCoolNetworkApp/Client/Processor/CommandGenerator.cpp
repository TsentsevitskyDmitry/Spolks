#include "CommandGenerator.h"
#include <fstream>

std::string CommandGenerator::error;

CommandGenerator::CommandGenerator()
{

}

std::shared_ptr<IMessage> CommandGenerator::Generate(const std::vector<std::string> &cmd)
{
    auto msg = std::shared_ptr<IMessage>(new CommandMessage());

    if(!cmd.size() || cmd[0].empty())
    {
        errorBadInput();
        return nullptr;
    }

    auto& cmdName = cmd[0];
    if(cmdName == Commands::ECHO)
    {
        if(cmd.size() < 2){
            errorTooFewArgs(Commands::ECHO);
            return nullptr;
        }
        else if (cmd.size() > 2) {
            errorPassingAfter(cmd[1]);
        }

        dynamic_cast<CommandMessage*>((msg.get()))->setCommand(cmdName);
        dynamic_cast<CommandMessage*>((msg.get()))->setPayload(cmd[1]);
    }
    else if (cmdName == Commands::TIME)
    {
        if(cmd.size() < 1){
            errorTooFewArgs(Commands::TIME);
            return nullptr;
        }
        else if (cmd.size() > 1) {
            errorPassingAfter(cmd[0]);
        }

        dynamic_cast<CommandMessage*>((msg.get()))->setCommand(cmdName);
    }
    else if(cmdName == Commands::DOWLOAD)
    {
        if(cmd.size() < 2){
            errorTooFewArgs(Commands::DOWLOAD);
            return nullptr;
        }
        else if (cmd.size() > 2) {
            errorPassingAfter(cmd[1]);
        }

        std::string sPos;
        try
        {
            std::ofstream file(Config::FilesPath + cmd[1], std::ios_base::binary | std::ios_base::app | std::ios_base::ate);
            size_t pos = static_cast<size_t>(file.tellp());
            if(!pos) infoCreateFile();
            else infoContinueFile(pos);
            sPos = std::to_string(pos);
            file.close();
        }
        catch (std::exception e)
        {
            errorFile();
            return nullptr;
        }

        dynamic_cast<CommandMessage*>((msg.get()))->setCommand(cmdName);
        dynamic_cast<CommandMessage*>((msg.get()))->setPayload(cmd[1] + ";" + sPos);
    }
    else
    {
        errorUnknown(cmd[0]);
        return nullptr;
    }

    return msg;
}

std::string CommandGenerator::GetLastError()
{
    return error;
}

void CommandGenerator::PrintLastError()
{
    if(!error.empty())
        printf("%s\n", error.c_str());
    error = "";
}

void CommandGenerator::infoCreateFile()
{
    error = "Creating new file";
}

void CommandGenerator::infoContinueFile(size_t pos)
{
    error = "Continue writing after " + std::to_string(pos) + " bytes";
}

void CommandGenerator::errorBadInput()
{
    error = "Bad input";
}

void CommandGenerator::errorFile()
{
    error = "Filesystem error";
}

void CommandGenerator::errorFileNotFound()
{
    error = "File not found";
}

void CommandGenerator::errorUnknown(const std::string &str)
{
    error = "Unknown command: " + str + "";
}

void CommandGenerator::errorTooFewArgs(const std::string& cmdName)
{
    error = "Too few args for " + cmdName + " command";
}

void CommandGenerator::errorPassingAfter(const std::string &cmd)
{
    error = "Passing args after " + cmd + "";
}
