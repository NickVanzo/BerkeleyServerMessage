//
// Created by Nicolò Vanzo on 05/02/25.
//

#pragma once

#include "./SocketAddress.h"
#include "./SocketUtil.h"

class SocketUtil;

class TCPSocket {
public:
    ~TCPSocket();
    int Connect(const SocketAddress& inAddress);
    int Bind(const SocketAddress& inToAddress);
    int Listen(int inBackLog = 32);
    std::shared_ptr<TCPSocket> Accept(SocketAddress& inFromAddress);
    int Send(const void* inData, int inLen);
    /**
     * Receiving data from a socket is a blocking operation. If there's no data to receive the thread will block until
     * new data comes in.
     * We don't want this behaviour in a game server. If there are five clients trying to send data to the server and the
     * server is waiting for a blocking thread then it can't serve all the clients.
     *
     * This can be solved in three ways: multithreading, non blocking I/O and select function.
     *
     * Multithreading does not scale well because we need: 1 thread for each client, 1 thread for the listen socket and one
     * or more for the simulation. Plus, the client threads must send data to the simulation thread in a safe way, this
     * can add complexity. There are simpler alternatives.
     *
     * @param inBuffer
     * @param inLen
     * @return
     */
    int Receive(void* inBuffer, int inLen);
private:
    friend class SocketUtil;
    TCPSocket(int inSocket) : mSocket(inSocket) {}
    int mSocket;
};

typedef std::shared_ptr<TCPSocket> TCPSocketPtr;
