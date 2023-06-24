#pragma once

#include <arpa/inet.h>
#include <functional>


struct Network {
    sockaddr_in address{};
    socklen_t length;
    Network(const char* ccIP, const unsigned short int cusiPort);
};


class Socket {
private:
    sockaddr_in address{};
    socklen_t length;

public:
    int udpsocket;
    Socket(const Network& network);
    ~Socket();

    int Send(const char* ccData, const unsigned int cuiSize, const Network& sendto_network);
    int Receive(std::function<void(unsigned char*, int)> fnCallback, const unsigned int cuiBufferSize);
};

extern "C" Socket* Constructor(const Network& network);
