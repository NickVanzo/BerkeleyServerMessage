//
// Created by Nicolò Vanzo on 05/02/25.
//
#include "../headers/TCPSocket.h"
#include <arpa/inet.h>

int TCPSocket::Connect(const SocketAddress &inAddress)
{
    std::cout << "Attempting to connect to address: "
              << inet_ntoa(((struct sockaddr_in*)&inAddress.mSockAddr)->sin_addr)
              << " on port: "
              << ntohs(((struct sockaddr_in*)&inAddress.mSockAddr)->sin_port)
              << std::endl;
    int err = connect(mSocket, &inAddress.mSockAddr, inAddress.GetSize());

    if(err < 0)
    {
        std::cout << "TCPSocket::Connect Error: " << strerror(errno) << " (" << errno << ")" << std::endl;
        return -errno;
    }

    std::cout << "Client connected" << std::endl;

    return 0;
}

int TCPSocket::Listen(int inBackLog)
{
    int err = listen(mSocket, inBackLog);

    if(err < 0)
    {
        std::cout << "TCPSocket::Listen" << std::endl;
        return -errno;
    }

    return 0;
}

TCPSocketPtr TCPSocket::Accept(SocketAddress &inFromAddress) {
    socklen_t length = inFromAddress.GetSize();

    int newSocket = accept(mSocket, &inFromAddress.mSockAddr, &length);
    if(newSocket != -1)
    {
        return TCPSocketPtr(new TCPSocket(newSocket));
    } else {
        std::cout << "TCPSocket::Accept" << std::endl;
        return nullptr;
    }
}

int TCPSocket::Send(const void *inData, int inLen) {
    int bytesSentCount = send(mSocket, static_cast<const char*>(inData), inLen, 0);


    if(bytesSentCount < 0) {
        std::cout << "TCPSocket::Send Error: " << strerror(errno) << " (" << errno << ")" << std::endl;
        return -errno;
    }
    return bytesSentCount;
}

int TCPSocket::Receive(void *inData, int inLen) {
    int bytesReceivedCount = recv(mSocket, static_cast<char*>(inData), inLen, 0);

    if(bytesReceivedCount < 0) {
        std::cout << "TCPSocket::Receive" << std::endl;
        return -errno;
    }

    return bytesReceivedCount;
}

int TCPSocket::Bind(const SocketAddress& inBindAddress)
{
    int err = bind(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());

    if(err != 0)
    {
        std::cout << "ERROR UDPSocket::Bind" << std::endl;
        return errno;
    }
    return 0;
}

TCPSocket::~TCPSocket() {
    close(mSocket);
}
