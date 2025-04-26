//
// Created by Nicolò Vanzo on 27/03/25.
//

#pragma once
#include <vector>
#include "../srcFromBook/headers/GameObject.h"
#include "../srcFromBook/headers/LinkingContext.h"
#include "../srcFromBook/headers/TCPSocket.h"

class GameServer {
public:
    GameServer();
//    ~GameServer();
//    void Update();
//    void HandleNewClientConnection(const TCPSocketPtr& listenSocket, std::vector<TCPSocketPtr>& readBlockSockets);
//    void HandleDataFromClient(const TCPSocketPtr& socket, std::vector<TCPSocketPtr>& readBlockSockets);
private:
    // game objects will be added when received by the socket
    LinkingContext* mLinkingCtx;
};