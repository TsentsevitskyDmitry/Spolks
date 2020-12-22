#include <iostream>
#include "Server/ServerTCP.h"
#include "Server/ServerUDP.h"
#include "Server/Processor/MessageProcessor/MessageProcessor.h"

#include "Client/ClientTCP.h"
#include "Client/ClientUDP.h"

#include "Message/CommandMessage.h"

#define ThreadPoolSize 10

#define NetServer ServerUDP

using namespace std;

int single_main();
int udp_thread_main(); // Thread pool version, mutex synchronization
int tcp_thread_main(); // Creating new thread for new client (not tested)
// write your own if needed

// `std::this_thread::sleep_for(3ms);` needded for stable udp stream (w/o error), in fact not needed for tcp, but exists for speed alignment
// with udp errors there are no speed speed difference between tcp/udp on i5-8250u && 100Mbps link
// edit `std::this_thread::sleep_for(3ms);` to achieve this difference if needded

int main()
{
    return udp_thread_main();
}

int single_main()
{
    cout << "Hello from server!" << endl;
    system("chcp 1251 > nul");

    NetServer server;
    server.setPort(27015);
    bool status = server.start();
    if(status)
        cout << "Running on " << server.getPort() << endl;

    while(1)
    {
        std::shared_ptr<IClient> client = server.accept();

        while(1)
        {
            CommandMessage cmdMessage;
            bool res = client->recv(cmdMessage);
            if(!res) break;

            auto processor = Server::MessageProcessor::Get(cmdMessage);
            if(!processor) break;

            processor->InitProcessor(cmdMessage);
            auto input = processor->InitHolder();

            while(!processor->done())
            {
                if(input)
                {
                    bool res = client->recv(*input);
                    if(!res) break;
                }

                auto output = processor->Process(*input);
                std::this_thread::sleep_for(3ms);

                if(output)
                {
                    bool res = client->send(*output);
                    if(!res) break;
                }
            }
        }

        cout << "client disconnected" << endl;
    }

    return 0;
}

int udp_thread_main()
{
    cout << "Hello from server!" << endl;
    system("chcp 1251 > nul");

    ServerUDP server;
    server.setPort(27015);
    bool status = server.start();
    if(status)
        cout << "Running on " << server.getPort() << endl;


    for(int i = 0; i < ThreadPoolSize; ++i)
    {
        std::shared_ptr<IClient> client = server.accept();

        auto lambda = [client]()
        {
            while(1)
            {
                CommandMessage cmdMessage;
                bool res = client->recv(cmdMessage);
                if(!res) break;

                auto processor = Server::MessageProcessor::Get(cmdMessage);
                if(!processor) break;

                processor->InitProcessor(cmdMessage);
                auto input = processor->InitHolder();

                while(!processor->done())
                {
                    if(input)
                    {
                        bool res = client->recv(*input);
                        if(!res) break;
                    }

                    auto output = processor->Process(*input);
                    std::this_thread::sleep_for(3ms);

                    if(output)
                    {
                        bool res = client->send(*output);
                        if(!res) break;
                    }
                }

                cout << "client done" <<  endl;
            }
        };

        thread t(lambda);
        t.detach();

        std::this_thread::sleep_for(100ms);
    }


    std::mutex m;
    m.lock();
    std::lock_guard l(m);

    return 0;
}

int tcp_thread_main()
{
    cout << "Hello from server!" << endl;
    system("chcp 1251 > nul");

    ServerTCP server;
    server.setPort(27015);
    bool status = server.start();
    if(status)
        cout << "Running on " << server.getPort() << endl;


    while(1)
    {
        std::shared_ptr<IClient> client = server.accept();

        auto lambda = [client]()
        {
            while(1)
            {
                CommandMessage cmdMessage;
                bool res = client->recv(cmdMessage);
                if(!res) break;

                auto processor = Server::MessageProcessor::Get(cmdMessage);
                if(!processor) break;

                processor->InitProcessor(cmdMessage);
                auto input = processor->InitHolder();

                while(!processor->done())
                {
                    if(input)
                    {
                        bool res = client->recv(*input);
                        if(!res) break;
                    }

                    auto output = processor->Process(*input);
                    std::this_thread::sleep_for(3ms);

                    if(output)
                    {
                        bool res = client->send(*output);
                        if(!res) break;
                    }
                }

                cout << "client done" <<  endl;
            }
        };

        thread t(lambda);
        t.detach();
    }

    return 0;
}