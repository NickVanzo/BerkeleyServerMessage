//
// Created by Nicolò Vanzo on 27/03/25.
//

#include "GameServer.h"
#include "../srcFromBook/headers/SocketUtil.h"

GameServer::GameServer(){}

//GameServer::~GameServer()
//{
//    delete mLinkingCtx;
//}
//
//void GameServer::Update()
//{
//    TCPSocketPtr listenSocket = SocketUtil::CreateTCPSocket(INET);
//    SocketAddress receivingAddress(INADDR_ANY, 8080);
//
//    if(listenSocket->SetTCPWinSize(5) != 0)
//    {
//        std::cerr << "Server failed to bind! Error: " << errno << " (" << strerror(errno) << ")" << std::endl;
//        return;
//    }
//    if(listenSocket->Bind(receivingAddress) != 0)
//    {
//        std::cerr << "Server failed to bind! Error: " << errno << " (" << strerror(errno) << ")" << std::endl;
//        return;
//    }
//    if(listenSocket->Listen() != 0) {
//        std::cerr << "Server failed to connect! Error: " << errno << " (" << strerror(errno) << ")" << std::endl;
//        return;
//    }
//    std::vector<TCPSocketPtr> readBlockSockets;
//    readBlockSockets.push_back(listenSocket);
//    std::vector<TCPSocketPtr> readableSockets;
//
//    while(true)
//    {
//        if(SocketUtil::Select(&readableSockets, &readBlockSockets, nullptr, nullptr, nullptr, nullptr))
//        {
//            for(const TCPSocketPtr& socket: readableSockets) {
//                if(socket == listenSocket)
//                    HandleNewClientConnection(listenSocket, readBlockSockets);
//                else
//                    HandleDataFromClient(socket, readBlockSockets);
//            }
//        }
//    }
//}
//
//void GameServer::HandleDataFromClient(const TCPSocketPtr &socket, std::vector<TCPSocketPtr> &readBlockSockets)
//{
//    char segment[1300];
//    int dataReceived = socket->Receive(segment, 1300);
//    if(dataReceived > 0) {
//        segment[dataReceived] = '\0';
//        std::cout << "Received " << dataReceived << " bytes: " << segment << std::endl;
//    } else if(dataReceived == 0) {
//        std::cout << "Client disconnected" << std::endl;
//        auto it = std::find(readBlockSockets.begin(), readBlockSockets.end(), socket);
//        if(it != readBlockSockets.end())
//            readBlockSockets.erase(it);
//    } else {
//        std::cout << "Error receiving data" << std::endl;
//    }
//}
//
//void GameServer::HandleNewClientConnection(const TCPSocketPtr &listenSocket,
//                                           std::vector<TCPSocketPtr> &readBlockSockets) {
//    std::cout << "New client connected" << std::endl;
//    SocketAddress newClientAddress;
//    auto newSocket = listenSocket->Accept(newClientAddress);
//    readBlockSockets.push_back(newSocket);
//}
//
