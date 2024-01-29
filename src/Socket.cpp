#include <cstring>
#include <sys/socket.h>
#include <system_error>
#include <unistd.h>

#include "Socket.h"


Network::Network(const char* ccIP, const unsigned short int cusiPort) {
    this->address.sin_family = AF_INET;
    this->address.sin_port = htons(cusiPort);
    this->address.sin_addr.s_addr = inet_addr(ccIP);
    this->length = sizeof(this->address);
}

extern "C" {
    Socket* SocketConstructor(const Network& network) {
        return new Socket(network);
    }

    Network NetworkConstructor(const char* ccIP, const unsigned short int cusiPort) {
        return Network(ccIP, cusiPort);
    }
}


Socket::Socket(const Network& network) {
    this->address.sin_family = network.address.sin_family;
    this->address.sin_port = network.address.sin_port;
    this->address.sin_addr.s_addr = network.address.sin_addr.s_addr;
    this->length = network.length;

    this->udpsocket = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (this->udpsocket == -1)
        throw std::runtime_error("failed to create socket");
    else
        bind(this->udpsocket, (sockaddr*)&this->address, this->length);
};


Socket::~Socket() {
    if (this->udpsocket > 0) close(this->udpsocket);
};


int Socket::Send(const char* ccData, const unsigned int cuiSize, const Network& sendto_network) {
    int bytes_sent = sendto(
        this->udpsocket,
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
        this->udpsocket,
        buffer, cuiBufferSize,
        0,
        (struct sockaddr*)&this->address, &this->length
    );

    if (bytes_read > 0) fnCallback(buffer, bytes_read);

    return bytes_read;
}
