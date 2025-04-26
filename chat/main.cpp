#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

int main(int argc, char* argv[])
{
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    char* ip = "235.3.42.1";
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = 2000;
    inet_pton(AF_INET, ip, &address.sin_addr.s_addr);

    int result = connect(socketFD, (struct sockaddr*) &address, sizeof(address));
    if(result == 0)
        std::cout << "Connection successful" << std::endl;
}