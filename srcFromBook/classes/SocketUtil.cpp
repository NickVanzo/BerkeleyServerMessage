//
// Created by Nicolò Vanzo on 04/02/25.
//
#include "../headers/SocketUtil.h"
#include "../headers/TCPSocket.h"

/**
 * The UDPSocket constructor is called only AFTER the socket function call succeeds.
 *
 * @param inFamily
 * @return
 */
UDPSocketPtr SocketUtil::CreateUDPSocket(const SocketAddressFamily& inFamily)
{
    /**
     * inFamily specifies if we are using IPv4 or IPv6
     *
     * The second argument specifies the type of socket we are creating. SOCK_DRAM specifies we are using
     * datagrams (connectionless, unreliable messages of a fixed amount length)
     *
     * IPPROTO_UDP is a macro defined in <in.h> that specified we want to use UDP
     *
     */
    int s = socket(inFamily, SOCK_DGRAM, IPPROTO_UDP);

    if(s == -1)
    {
        std::cout << "SocketUtil::CreateUDPSocket" << std::endl;
        return nullptr;
    }

    return UDPSocketPtr(new UDPSocket(s));
}

TCPSocketPtr SocketUtil::CreateTCPSocket(const SocketAddressFamily& inFamily) {
    int s = socket(inFamily, SOCK_STREAM, 0);

    if(s == -1)
    {
        std::cout << "SocketUtil::CreateTCPSocket" << std::endl;
        return nullptr;
    }

    return TCPSocketPtr(new TCPSocket(s));
}

fd_set *SocketUtil::FillSetFromVector(fd_set &outSet, const std::vector<TCPSocketPtr> *inSockets)
{
    if(inSockets)
    {
        FD_ZERO(&outSet);
        for(const TCPSocketPtr& socket : *inSockets) {
            FD_SET(socket->mSocket, &outSet);
        }
        return &outSet;
    } else {
        return nullptr;
    }
}

void SocketUtil::FillVectorFromSet(std::vector<TCPSocketPtr> *outSockets, const std::vector<TCPSocketPtr> *inSockets,
                                   const fd_set &inSet) {
    if(inSockets && outSockets) {
        outSockets->clear();
        for(const TCPSocketPtr& socket : *inSockets) {
            if(FD_ISSET(socket->mSocket, &inSet)) {
                outSockets->push_back(socket);
            }
        }
    }
}

int SocketUtil::Select(const std::vector<TCPSocketPtr> *inReadSet, std::vector<TCPSocketPtr> *outReadSet,
                       const std::vector<TCPSocketPtr> *inWriteSet, std::vector<TCPSocketPtr> *outWriteSet,
                       const std::vector<TCPSocketPtr> *inExpectSet, std::vector<TCPSocketPtr> *outExpectSet) {

    fd_set read, write, expect;
    int maxFD = 0;

    fd_set *readPtr = FillSetFromVector(read, inReadSet);
    if(readPtr && inReadSet) {
        for (const TCPSocketPtr& socket: *inReadSet) {
            maxFD = std::max(maxFD, socket->mSocket);
        }
    }

    fd_set *writePtr = FillSetFromVector(write, inWriteSet);
    if(writePtr && inWriteSet) {
        for(const TCPSocketPtr& socket: *inWriteSet) {
            maxFD = std::max(maxFD, socket->mSocket);
        }
    }
    fd_set *expectPtr = FillSetFromVector(expect, inExpectSet);
    if(expectPtr && inExpectSet) {
        for(const TCPSocketPtr& socket: *inExpectSet) {
            maxFD = std::max(maxFD, socket->mSocket);
        }
    }

    int toRet = select(maxFD + 1, readPtr, writePtr, expectPtr, nullptr);

    if(toRet > 0) {
        FillVectorFromSet(outReadSet, inReadSet, read);
        FillVectorFromSet(outWriteSet, inWriteSet, write);
        FillVectorFromSet(outExpectSet, inExpectSet, expect);
    }

    return toRet;
}