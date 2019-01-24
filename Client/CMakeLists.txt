cmake_minimum_required(VERSION 3.9)
project(Client C)

set(CMAKE_C_STANDARD 11)

add_executable(Client main.c client.h client.c filesystem.c filesystem.h)