#pragma once

#include <arpa/inet.h>
#include <functional>
#include <sys/socket.h>
#include <system_error>
#include <unistd.h>


struct Network {
    sockaddr_in address{};
    socklen_t length;

    Network(const char* ipv4_address, const unsigned short int port) {
        this->address.sin_family = AF_INET;
        this->address.sin_port = htons(port);
        this->address.sin_addr.s_addr = inet_addr(ipv4_address);
        this->length = sizeof(this->address);
    }
};


class Socket {
private:
    sockaddr_in address{};
    socklen_t length;
    int broadcast;

public:
    int udpsocket;

    Socket(const Network& network, bool broadcast) {
        this->address.sin_family = network.address.sin_family;
        this->address.sin_port = network.address.sin_port;
        this->address.sin_addr.s_addr = network.address.sin_addr.s_addr;
        this->length = network.length;
        this->broadcast = broadcast;

        this->udpsocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (this->udpsocket == -1)
            throw std::runtime_error("failed to create socket");

        if (
            this->broadcast &&
            setsockopt(this->udpsocket, SOL_SOCKET, SO_BROADCAST, &this->broadcast, sizeof(this->broadcast)) < 0
        ) {
            close(this->udpsocket);
            throw std::runtime_error("failed to enable broadcasting on socket");
        }

        bind(this->udpsocket, (sockaddr*)&this->address, this->length);
    }

    ~Socket() {
        if (this->udpsocket > 0) close(this->udpsocket);
    }


    ssize_t Send(const unsigned char* data, const unsigned int size, const Network& send_to) {
        ssize_t bytes_sent = sendto(
            this->udpsocket,
            data, size,
            MSG_CONFIRM | MSG_NOSIGNAL,
            (struct sockaddr*)&send_to.address, send_to.length
        );

        return bytes_sent;
    }


    ssize_t Receive(std::function<void(unsigned char*, int)> callback, const unsigned int size) {
        unsigned char buffer[size] = {0};

        ssize_t bytes_read = recvfrom(
            this->udpsocket,
            buffer, size,
            0,
            (struct sockaddr*)&this->address, &this->length
        );

        if (bytes_read > 0) callback(buffer, bytes_read);

        return bytes_read;
    }
};
