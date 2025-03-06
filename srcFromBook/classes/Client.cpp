//
// Created by Nicolò Vanzo on 10/02/25.
//
#include "../headers/Client.h"

Client::Client(int port): port(port) {}

TCPSocketPtr Client::Connect() {
    TCPSocketPtr serverSocket = SocketUtil::CreateTCPSocket(INET);
    SocketAddress receivingAddress("127.0.0.1", port);
    int connectRes = serverSocket->Connect(receivingAddress);
    if(connectRes < 0)
    {
        std::cout << "Client did not connect properly" << std::endl;
        return nullptr;
    }

    return serverSocket;
}

void Client::StartLoop(const TCPSocketPtr& serverSocket) {
    std::string option;
    while(option != "quit") {
        std::cout << "Enter a message: ";
        std::getline(std::cin, option);

        if(serverSocket->Send(option.c_str(), option.length()) > 0) {
            char buff[1300];
            int bytesReceived = serverSocket->Receive(buff, sizeof(buff));
            if(bytesReceived > 0) {
                buff[bytesReceived] = '\0';
                std::cout << "Server responded: " << buff << std::endl;
            } else if(bytesReceived == 0) {
                std::cout << "Server closed connection" << std::endl;
            } else {
                std::cout << "Something unexpected happened" << std::endl;
            }
        }
    }
}