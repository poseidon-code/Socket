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

    int Send(const char* ccData, const Network& sendto_network);
    int Receive(std::function<void(char*, int)> fnCallback, const unsigned short int cusiBufferSize);
};

extern "C" Socket* Constructor(const Network& network);