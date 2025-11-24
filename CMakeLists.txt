cmake_minimum_required(VERSION 3.10)
project(TCPSim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O2")

add_executable(tcp_sim
    src/main.cpp
    src/sender.cpp
    src/receiver.cpp
    src/channel.cpp
)

