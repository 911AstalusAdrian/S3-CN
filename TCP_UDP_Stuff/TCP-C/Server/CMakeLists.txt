cmake_minimum_required(VERSION 3.19)
project(Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server server.cpp server2.cpp serverC.c)