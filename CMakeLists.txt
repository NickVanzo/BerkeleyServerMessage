cmake_minimum_required(VERSION 3.17.3)
project(sockets)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(srcFromBook/headers)
file(GLOB_RECURSE SRC_FILES_CLASSES "srcFromBook/classes/*.cpp")
add_executable(sockets main.cpp ${SRC_FILES_CLASSES})