#pragma once

#include <arpa/inet.h>
#include <functional>


class Socket {
private:
    sockaddr_in address{};

public:
    int udpsocket;
    Socket(const char* ccIP, unsigned short usPort);
    ~Socket();

    int Send(const char* ccData, unsigned short usSendToPort);
    int Receive(std::function<void(const char*, int)> fnCallback, const unsigned short usBufferSize);
};

extern "C" Socket* Constructor(const char* ccIP, unsigned short usPort);