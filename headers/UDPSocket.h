//
// Created by Nicolò Vanzo on 04/02/25.
//

#pragma once

#include "./SocketAddress.h"

/**
 * UDP is stateless and unreliable. It needs a single socket per host to send and receive datagrams.
 */
class UDPSocket
{
public:
    ~UDPSocket();
    /**
        When a socket gets created it exists only in a name space but has no address assigned to it.
        We bind the address to the socket.
        This process is called "assigning a name to a socket".
     */
    int Bind(const SocketAddress& inToAddress);
    int SendTo(const void* inData, int inLen, const SocketAddress& inTo);
    int ReceiveFrom(void* inBuffer, int inLen, SocketAddress& outFrom);
    int SetNonBlockingMode(bool inShouldBeNonBlocking);
private:
    friend class SocketUtil;
    UDPSocket(int inSocket) : mSocket(inSocket) {}
    int mSocket;
};

typedef std::shared_ptr<UDPSocket> UDPSocketPtr;
