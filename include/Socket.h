#pragma once

#include <arpa/inet.h>
#include <functional>


class Socket {
private:
    sockaddr_in address{};

public:
    int udpsocket;
    Socket(const char* ccIP, const unsigned short cusPort);
    ~Socket();

    int Send(const char* ccData, const char* ccSendToIP, const unsigned short cusSendToPort);
    int Receive(std::function<void(const char*, int)> fnCallback, const unsigned short cusBufferSize);
};

extern "C" Socket* Constructor(const char* ccIP, const unsigned short cusPort);