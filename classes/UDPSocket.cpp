//
// Created by Nicolò Vanzo on 04/02/25.
//

#include "../headers/UDPSocket.h"
#include <fcntl.h>
int UDPSocket::Bind(const SocketAddress& inBindAddress)
{
    int err = bind(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());

    if(err != 0)
    {
        std::cout << "ERROR UDPSocket::Bind" << std::endl;
        return errno;
    }
    return 0;
}

int UDPSocket::SendTo(const void *inData, int inLen, const SocketAddress &inTo)
{
    int byteSentCount = sendto(mSocket, static_cast<const char*>(inData), inLen, 0, inTo.GetSockAddr(), inTo.GetSize());

    if(byteSentCount < 0)
    {
        std::cout << "UDPSocket::SendTo" << std::endl;
        return -errno;
    }

    return byteSentCount;
}

int UDPSocket::ReceiveFrom(void *inBuffer, int inLen, SocketAddress &outFrom)
{
    socklen_t fromLength = outFrom.GetSize();

    int readByteCount = recvfrom(mSocket,
                                 static_cast<char*>(inBuffer),
                                 inLen,
                                 0, &outFrom.mSockAddr,
                                 &fromLength);
    if(readByteCount < 0) {
        std::cout << "UDPSocket::ReceiveFrom" << std::endl;
        return -errno;
    }

    return readByteCount;
}

/**
 * The game loop consumes an X amount of non-blocking sockets every frame before updating the simulation world.
 * When the game loop consumes the non-blocking sockets we must also put a limit to it, otherwise a malicious client
 * could spam us with blocking calls.
 *
 * When the number of sockets is large, this can become inefficient. This can be solved by using select.
 * @param inShouldBeNonBlocking
 * @return
 */
int UDPSocket::SetNonBlockingMode(bool inShouldBeNonBlocking)
{
    int result = 0;
#if _WIN32
    u_long arg = inShouldBeNonBlocking ? 1 : 0;
    result = ioctlsocket(mSocket, FIONBIO, &arg);
#else
    int flags = fcntl(mSocket, F_GETFL, 0);
    // BITWISE OR with the O_NONBLOCK mask
    flags = inShouldBeNonBlocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    result = fcntl(mSocket, F_SETFL, flags);
#endif
    if(result == -1) {
        std::cout << "UDPSocket::SetNonBlockingMode" << std::endl;
        return errno;
    }
    return 0;
}

UDPSocket::~UDPSocket()
{
    close(mSocket);
}
