#include <iostream>

#include "Client/ClientTCP.h"
#include "Client/ClientUDP.h"
#include "Client/Processor/CommandGenerator.h"
#include "Client/Processor/MessageProcessor/MessageProcessor.h"

#include "Message/CommandMessage.h"
#include <boost/algorithm/string.hpp>
#include <thread>

#define NetClient ClientUDP
using namespace std;

[[noreturn]] void cmdline()
{
    boost::asio::io_service networkIO;

    NetClient client(networkIO, "194.158.209.132", 27015);
    if(!client.isConnected()){
        cout << "kak bi error" << endl;
        cin.get();
        std::exit(-1);
    }

    while(1)
    {
        std::vector<std::string> cmd;
        std::string linecmd;
        std::cout << "> ";
        getline(std::cin, linecmd);
        boost::split(cmd, linecmd, boost::is_any_of(" "));

        auto cmdMessage = CommandGenerator::Generate(cmd);

        CommandGenerator::PrintLastError();
        if(cmdMessage == nullptr) continue;

        client.send(*cmdMessage);
        auto processor = Client::MessageProcessor::Get(*cmdMessage);
        if(!processor) continue;

        processor->InitProcessor(*cmdMessage);
        auto input = processor->InitHolder();

        while(!processor->done())
        {
            if(input)
            {
                bool res = client.recv(*input);
                if(!res) throw std::exception();
            }

            auto output = processor->Process(*input);
            //std::this_thread::sleep_for(1ms);

            if(output)
            {
                bool res = client.send(*output);
                if(!res) throw std::exception();
            }
        }
    }

}

int main()
{
    system("chcp 1251 > nul");

    while(1)
    {
        try
        {
            cmdline();
        }
        catch (std::exception e) {}
    }


    return 0;
}
