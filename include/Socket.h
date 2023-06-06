#pragma once

#include <arpa/inet.h>
#include <functional>


struct Network {
    sockaddr_in address{};
    socklen_t length;
    Network(const char* ip, const unsigned short int port);
};

class Socket {
private:
    sockaddr_in address{};
    socklen_t length;

public:
    int udpsocket;
    Socket(const Network& network);
    ~Socket();

    int Send(const char* ccData, const Network& network);
    int Receive(std::function<void(const char*, int)> fnCallback, const unsigned short int cusBufferSize);
};

extern "C" Socket* Constructor(const Network& network);