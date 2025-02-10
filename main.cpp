#include <iostream>
#include "headers/TCPSocket.h"
#include "headers/Server.h"
#include "headers/Client.h"
#include <arpa/inet.h>

#define PORT 48000

int main(int argc, char* argv[]) {
    bool isServer = false;

    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;

        if (std::string(argv[i]) == "server") {
            isServer = true;
        }
    }

    if(isServer) {
        std::unique_ptr<Server> server = std::make_unique<Server>();
        std::cout << "Starting server" << std::endl;
        server->DoTCPLoop(PORT);
    } else {
        std::unique_ptr<Client> client = std::make_unique<Client>(PORT);
        auto socket = client->Connect();
        client->StartLoop(socket);
    }

    return 0;
}

