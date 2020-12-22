TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += D:\Shared\Libraries\include

LIBS += libws2_32

SOURCES += \
        main.cpp \
    Client/Processor/MessageProcessor/IMessageProcessor.cpp \
    Client/Processor/MessageProcessor/InputDataStringMessageProcessor.cpp \
    Client/Processor/MessageProcessor/MessageProcessor.cpp \
    Client/Processor/CommandGenerator.cpp \
    Client/ClientTCP.cpp \
    Client/ClientUDP.cpp \
    Client/IClient.cpp \
    Message/CommandMessage.cpp \
    Message/IMessage.cpp \
    Message/StringDataMessage.cpp \
    Message/BitStreamMessage.cpp \
    Client/Processor/MessageProcessor/DownloadMessageProcessor.cpp

HEADERS += \
    Client/Processor/MessageProcessor/IMessageProcessor.h \
    Client/Processor/MessageProcessor/InputDataStringMessageProcessor.h \
    Client/Processor/MessageProcessor/MessageProcessor.h \
    Client/Processor/CommandGenerator.h \
    Client/ClientTCP.h \
    Client/ClientUDP.h \
    Client/IClient.h \
    Common/Common.h \
    Message/CommandMessage.h \
    Message/IMessage.h \
    Message/StringDataMessage.h \
    Message/BitStreamMessage.h \
    Client/Processor/MessageProcessor/DownloadMessageProcessor.h
