cmake_minimum_required(VERSION 3.9)
project(Client C)

set(CMAKE_C_STANDARD 11)

IF (WIN32)
    link_libraries(ws2_32 wsock32)
endif(WIN32)

add_executable(Client main.c client.h client.c filesystem.c filesystem.h)