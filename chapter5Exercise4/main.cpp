/**
 * Implement a simple game with five moving game objects in it. Replicate those objects
 * to a remote host by sending the remote host a world state packet 15 times a second.
 */

#include "./MovingObject.h"
#include "./GameServer.h"
#include <memory>

int main(int argc, char* argv[]) {
    bool isServer = false;

//    for (int i = 0; i < argc; i++) {
//        if(argv[i] == "server")
//            isServer = true;
//    }

    if(isServer)
    {
        std::unique_ptr<GameServer> server = std::make_unique<GameServer>();
//        server->Update();
    }

    return 0;
}