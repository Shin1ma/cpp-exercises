cmake_minimum_required(VERSION 3.30)
project(WumpusGame)

include_directories(header)
include_directories(source)

set(CMAKE_CXX_STANDARD 20)


add_executable(WumpusGame source/main.cpp
        source/Cave.cpp
        source/utils.cpp
        source/WumpusGame.cpp)
