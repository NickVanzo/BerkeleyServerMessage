cmake_minimum_required(VERSION 3.17.3)
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
        classes/InputMemoryBitStream.cpp
        classes/OutputMemoryBitStream.cpp
        classes/OutputMemoryStream.cpp
        classes/RoboCat.cpp
)

add_subdirectory(ex8Chapter4) # Add the subdirectory
include_directories(headers)
add_library(sockets ${SOURCES})
