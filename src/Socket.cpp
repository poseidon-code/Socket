#include <cstring>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <system_error>
#include <unistd.h>

#include "Socket.h"


extern "C" Socket* Constructor(const char* ccIP, const unsigned short cusPort) {
    return new Socket(ccIP, cusPort);
}


Socket::Socket(const char* ccIP, const unsigned short cusPort) {
    address.sin_family = AF_INET;
    address.sin_port = htons(cusPort);
    address.sin_addr.s_addr = inet_addr(ccIP);

    udpsocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpsocket == -1)
        throw std::runtime_error("failed to create sender socket");
    else
        bind(udpsocket, (sockaddr*)&address, sizeof(address));
};


Socket::~Socket() {
    if (udpsocket > 0) close(udpsocket);
};


int Socket::Send(const char* ccData, const char* ccSendToIP, const unsigned short cusSendToPort) {
    sockaddr_in sendto_address{};
    sendto_address.sin_family = AF_INET;
    sendto_address.sin_port = htons(cusSendToPort);
    sendto_address.sin_addr.s_addr = inet_addr(ccSendToIP);

    int bytes_sent = sendto(
        udpsocket,
        ccData, std::strlen(ccData),
        MSG_CONFIRM | MSG_NOSIGNAL,
        (struct sockaddr*)&sendto_address, sizeof(sendto_address)
    );

    return bytes_sent;
}


int Socket::Receive(std::function<void(const char*, int)> fnCallback, const unsigned short cusBufferSize) {
    char buffer[cusBufferSize];
    socklen_t address_length = sizeof(address);
    
    int bytes_read = recvfrom(
        udpsocket,
        buffer, sizeof(buffer), 
        0,
        (struct sockaddr*)&address, &address_length);

    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        fnCallback(buffer, bytes_read);
    }

    return bytes_read;
}
