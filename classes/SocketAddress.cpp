// SocketAddress.cpp
#include "../headers/SocketAddress.h"
#include <cstring>
#include <arpa/inet.h>

SocketAddress::SocketAddress(const uint32_t& inAddress, const uint16_t& inPort)
{
    memset(GetAsSockAddrIn()->sin_zero, 0, sizeof(GetAsSockAddrIn()->sin_zero));
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetAsSockAddrIn()->sin_addr.s_addr = htonl(inAddress);
    GetAsSockAddrIn()->sin_port = htons(inPort);
}

SocketAddress::SocketAddress(const std::string &ipAddress, const uint16_t& port) {
    memset(&mSockAddr, 0, sizeof(mSockAddr));
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetAsSockAddrIn()->sin_port = htons(port);

    if(inet_pton(AF_INET, ipAddress.c_str(), &GetAsSockAddrIn()->sin_addr.s_addr) <= 0) {
        std::cerr << "Invalid IP address: " << ipAddress << std::endl;
        return;
    }
}

SocketAddress::SocketAddress(const sockaddr& inSockAddr)
{
    memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
}

SocketAddress::SocketAddress()
{
    memset(&mSockAddr,0, sizeof(mSockAddr));
}

size_t SocketAddress::GetSize() const { return sizeof(sockaddr); }
const sockaddr* SocketAddress::GetSockAddr() const { return &mSockAddr; }
sockaddr* SocketAddress::GetMutableSockAddr() { return &mSockAddr; }

sockaddr_in* SocketAddress::GetAsSockAddrIn()
{
    return reinterpret_cast<sockaddr_in*>(&mSockAddr);
}
