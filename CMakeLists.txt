cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 11)

project(client)

include_directories(server/include client/include ./)

add_executable(client
        parser.cpp
        client/src/ClientNetworkHandler.cpp
        client/src/UserInterface.cpp
        client/src/MainClient.cpp
        client/src/main.cpp
)

project(server)

add_executable(server
        parser.cpp
        server/src/ServerNetworkHandler.cpp
        server/src/Number.cpp
        server/src/GameManager.cpp
        server/src/ClientHandler.cpp
        server/src/MainServer.cpp
        server/src/main.cpp
)
