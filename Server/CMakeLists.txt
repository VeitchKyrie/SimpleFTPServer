cmake_minimum_required(VERSION 3.13)
project(Server C)

set(CMAKE_C_STANDARD 11)

IF (WIN32)
    link_libraries(ws2_32 wsock32)
endif(WIN32)

add_executable(Server main.c server.c server.h command.h command.c filesystem.c filesystem.h)