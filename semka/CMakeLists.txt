cmake_minimum_required(VERSION 3.18)
project(semka)

set(CMAKE_CXX_STANDARD 17)

add_executable(semka
        Simulacia.cpp
        Simulacia.h
        Bunka.cpp
        Bunka.h
        Mapa.cpp
        Mapa.h
        MySocket.h
        MySocket.cpp
        main.cpp)

target_link_libraries(semka wsock32 ws2_32)