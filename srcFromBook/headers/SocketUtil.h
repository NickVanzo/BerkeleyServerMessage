//
// Created by Nicolò Vanzo on 04/02/25.
//

#pragma once

#include <sys/socket.h>
#include "UDPSocket.h"

enum SocketAddressFamily {
    INET = AF_INET,
    INET6 = AF_INET6
};

class TCPSocket;
using TCPSocketPtr = std::shared_ptr<TCPSocket>;

class SocketUtil {
public:
    static UDPSocketPtr CreateUDPSocket(const SocketAddressFamily& inFamily);
    static TCPSocketPtr CreateTCPSocket(const SocketAddressFamily& inFamily);
    static fd_set* FillSetFromVector(fd_set& outSet, const std::vector<TCPSocketPtr>* inSockets);
    static void FillVectorFromSet(std::vector<TCPSocketPtr>* outSockets, const std::vector<TCPSocketPtr>* inSockets, const fd_set& inSet);
    static int Select(
            const std::vector<TCPSocketPtr>* inReadSet,
            std::vector<TCPSocketPtr>* outReadSet,
            const std::vector<TCPSocketPtr>* inWriteSet,
            std::vector<TCPSocketPtr>* outWriteSet,
            const std::vector<TCPSocketPtr>* inExpectSet,
            std::vector<TCPSocketPtr>* outExpectSet
            );
};

