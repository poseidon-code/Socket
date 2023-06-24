#include <cstring>
#include <sys/socket.h>
#include <system_error>
#include <unistd.h>

#include "Socket.h"


Network::Network(const char* ccIP, const unsigned short int cusiPort) {
    address.sin_family = AF_INET;
    address.sin_port = htons(cusiPort);
    address.sin_addr.s_addr = inet_addr(ccIP);
    length = sizeof(address);
}

extern "C" Socket* Constructor(const Network& network) {
    return new Socket(network);
}


Socket::Socket(const Network& network) {
    address.sin_family = network.address.sin_family;
    address.sin_port = network.address.sin_port;
    address.sin_addr.s_addr = network.address.sin_addr.s_addr;
    length = network.length;

    udpsocket = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (udpsocket == -1)
        throw std::runtime_error("failed to create sender socket");
    else
        bind(udpsocket, (sockaddr*)&address, length);
};


Socket::~Socket() {
    if (udpsocket > 0) close(udpsocket);
};


int Socket::Send(const char* ccData, const unsigned int cuiSize, const Network& sendto_network) {
    int bytes_sent = sendto(
        udpsocket,
        ccData, cuiSize,
        MSG_CONFIRM | MSG_NOSIGNAL,
        (struct sockaddr*)&sendto_network.address, sendto_network.length
    );

    return bytes_sent;
}


int Socket::Receive(std::function<void(unsigned char*, int)> fnCallback, const unsigned int cuiBufferSize) {
    unsigned char buffer[cuiBufferSize];
    std::memset(&buffer, 0x00, cuiBufferSize);
    
    int bytes_read = recvfrom(
        udpsocket,
        buffer, cuiBufferSize,
        0,
        (struct sockaddr*)&address, &length
    );

    if (bytes_read > 0)
        fnCallback(buffer, bytes_read);

    return bytes_read;
}
