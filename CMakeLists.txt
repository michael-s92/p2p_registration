cmake_minimum_required(VERSION 3.10)
project(p2p_registration)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

link_libraries(crypto)

add_executable(p2p_registration
        ClientSocket.cpp
        ClientSocket.hpp
        main.cpp Constants.h ComputeHash.cpp ComputeHash.h)
