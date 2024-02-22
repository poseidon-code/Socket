#pragma once

#include <arpa/inet.h>
#include <functional>


struct Network {
    sockaddr_in address{};
    socklen_t length;
    Network(const char* ipv4_address, const unsigned short int port);
};


class Socket {
private:
    sockaddr_in address{};
    socklen_t length;
    int broadcast;

public:
    int udpsocket;
    Socket(const Network& network, bool broadcast);
    ~Socket();

    ssize_t Send(const unsigned char* data, const unsigned int size, const Network& send_to);
    ssize_t Receive(std::function<void(unsigned char*, int)> callback, const unsigned int size);
};

extern "C" {
    Socket* SocketConstructor(const Network& network, bool broadcast);
    Network NetworkConstructor(const char* ipv4_address, const unsigned short int port);
}
