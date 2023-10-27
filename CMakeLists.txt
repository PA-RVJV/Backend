cmake_minimum_required(VERSION 3.26)
project(Swarmies)

set(CMAKE_CXX_STANDARD 23)

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Swarmies main.cpp
        Systems/Geometry/Geometry.cpp
        Systems/Geometry/Geometry.h)
