//
// Created by Nicolò Vanzo on 10/02/25.
//

#include "../headers/Server.h"

void Server::DoTCPLoop(int port) {
    TCPSocketPtr listenSocket = SocketUtil::CreateTCPSocket(INET);
    SocketAddress receivingAddress(INADDR_ANY, port);
    if(listenSocket->Bind(receivingAddress) != 0)
    {
        std::cerr << "Server failed to bind! Error: " << errno << " (" << strerror(errno) << ")" << std::endl;
        return;
    }
    if(listenSocket->Listen() != 0) {
        std::cerr << "Server failed to connect! Error: " << errno << " (" << strerror(errno) << ")" << std::endl;
        return;
    }
    //Useful DS for the select
    std::vector<TCPSocketPtr> readBlockSockets;
    //Add the listen socket in the vector to check for readability
    readBlockSockets.push_back(listenSocket);
    std::vector<TCPSocketPtr> readableSockets;

    while(true)
    {
        // Block process until a packet comes in on any socket in the readBlockSockets vector.
        if(SocketUtil::Select(&readBlockSockets, &readableSockets, nullptr, nullptr, nullptr, nullptr)) {
            for(const TCPSocketPtr& socket: readableSockets) {
                if(socket == listenSocket)
                    HandleNewClientConnection(listenSocket, readBlockSockets);
                else
                    HandleDataFromClient(socket, readBlockSockets);
            }
        }
    }
}


void Server::HandleNewClientConnection(const TCPSocketPtr& listenSocket, std::vector<TCPSocketPtr>& readBlockSockets) {
    std::cout << "New client connected" << std::endl;
    SocketAddress newClientAddress;
    auto newSocket = listenSocket->Accept(newClientAddress);
    readBlockSockets.push_back(newSocket);
}

void Server::HandleDataFromClient(const TCPSocketPtr& socket, std::vector<TCPSocketPtr>& readBlockSockets) {
    char segment[1300];
    int dataReceived = socket->Receive(segment, 1300);
    if(dataReceived > 0) {
        segment[dataReceived] = '\0';
        std::cout << "Received " << dataReceived << " bytes: " << segment << std::endl;
        socket->Send(segment, sizeof(segment));
    } else if(dataReceived == 0) {
        std::cout << "Client disconnected" << std::endl;
        auto it = std::find(readBlockSockets.begin(), readBlockSockets.end(), socket);
        if(it != readBlockSockets.end()) {
            readBlockSockets.erase(it);
        }
    } else {
        std::cout << "Error receiving data" << std::endl;
    }
}

