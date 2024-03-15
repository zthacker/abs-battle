cmake_minimum_required(VERSION 3.27)
project(battle)

set(CMAKE_CXX_STANDARD 17)

add_executable(battle main.cpp
        Entity.cpp
        Entity.h
        Battle.cpp
        Battle.h
)
