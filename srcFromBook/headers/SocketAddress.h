// SocketAddress.h
#pragma once

#include <iostream>
#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/**
 * The core address data type of the Berkeley API is the sockaddr struct.
 * It is used when we have to specify a destination or source address.
 *
 * UDP: stateless and connectionless. They are created using the `socket` function. We can send datagrams to them by using
 * `sendto` function. To receive UDP packets on a UDP socket we first have to bind it with `bind`, then use the
 * `recvfrom` to retrieve incoming data.
 *
 * TCP: stateful and must connect before they transmit data. To initiate a connection use `connect`. To listen for incoming
 * connections call `listen`. When a connection comes in call the `accept` to create a new socket. Send data to sockets by
 * using `send` and receive it using `recv`.
 */
class SocketAddress
{
public:
    SocketAddress(const uint32_t& inAddress, const uint16_t& inPort);
    SocketAddress(const std::string& ipAddress, const uint16_t& port);
    SocketAddress(const sockaddr& inSockAddr);
    SocketAddress();

    size_t GetSize() const;
    const sockaddr* GetSockAddr() const;
    sockaddr* GetMutableSockAddr();

private:
    sockaddr mSockAddr;
    friend class UDPSocket;
    friend class TCPSocket;

    sockaddr_in* GetAsSockAddrIn();
};

typedef std::shared_ptr<SocketAddress> SocketAddressPtr;

