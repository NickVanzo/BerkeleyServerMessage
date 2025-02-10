cmake_minimum_required(VERSION 3.30)
project(sockets)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    classes/SocketAddress.cpp
        classes/SocketAddressFactory.cpp
        classes/SocketUtil.cpp
        classes/TCPSocket.cpp
        classes/UDPSocket.cpp
        classes/Server.cpp
        classes/Client.cpp
        main.cpp
)

include_directories(headers)
add_executable(sockets ${SOURCES})
target_link_libraries(sockets)