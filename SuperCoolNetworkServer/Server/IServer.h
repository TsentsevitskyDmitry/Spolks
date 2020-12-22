#pragma once
#include "Client/IClient.h"
#include "Common/Common.h"
#include <boost/asio.hpp>

class IServer
{
public:
    IServer(Protocol _protocol);
    virtual ~IServer() = default;

    uint32_t getPort() const;
    void setPort(const uint32_t &value);

protected:
    boost::asio::io_service networkIO;
    Protocol currentProtocol;
    uint32_t serverPort;

    virtual bool start() = 0;
    virtual void stop() = 0;
    virtual std::shared_ptr<IClient> accept() = 0;
};
