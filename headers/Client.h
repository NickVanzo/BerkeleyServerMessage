//
// Created by Nicolò Vanzo on 10/02/25.
//

#pragma once
#include "./TCPSocket.h"

class Client {
public:
    Client(int port);
    TCPSocketPtr Connect();
    void StartLoop(const TCPSocketPtr& serverSocket);
private:
    int port;
};
