//
// Created by Nicolò Vanzo on 10/02/25.
//

#pragma once
#include "./TCPSocket.h"

class Server {
public:
    void DoTCPLoop(int port);
private:
    void HandleNewClientConnection(const TCPSocketPtr& listenSocket, std::vector<TCPSocketPtr>& readBlockSockets);
    void HandleDataFromClient(const TCPSocketPtr& socket, std::vector<TCPSocketPtr>& readBlockSockets);
};


