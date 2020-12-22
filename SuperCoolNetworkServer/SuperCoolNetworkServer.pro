TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += D:\Shared\Libraries\include

LIBS += libws2_32

SOURCES += \
        main.cpp \
    Server/IServer.cpp \
    Server/ServerTCP.cpp \
    Server/ServerUDP.cpp \
    Message/IMessage.cpp \
    Message/CommandMessage.cpp \
    Message/StringDataMessage.cpp \
    Server/Processor/MessageProcessor/IMessageProcessor.cpp \
    Server/Processor/MessageProcessor/MessageProcessor.cpp \
    Server/Processor/MessageProcessor/OutputTimeStringProcessor.cpp \
    Client/ClientTCP.cpp \
    Client/ClientUDP.cpp \
    Client/IClient.cpp \
    Server/Processor/MessageProcessor/OutputEchoStringProcessor.cpp \
    Message/BitStreamMessage.cpp \
    Server/Processor/MessageProcessor/DownloadProcessor.cpp

HEADERS += \
    Server/IServer.h \
    Server/ServerTCP.h \
    Server/ServerUDP.h \
    Common/Common.h \
    Message/IMessage.h \
    Message/CommandMessage.h \
    Message/StringDataMessage.h \
    Server/Processor/MessageProcessor/IMessageProcessor.h \
    Server/Processor/MessageProcessor/MessageProcessor.h \
    Server/Processor/MessageProcessor/OutputTimeStringProcessor.h \
    Client/ClientTCP.h \
    Client/ClientUDP.h \
    Client/IClient.h \
    Server/Processor/MessageProcessor/OutputEchoStringProcessor.h \
    Message/BitStreamMessage.h \
    Server/Processor/MessageProcessor/DownloadProcessor.h
