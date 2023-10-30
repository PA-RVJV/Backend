cmake_minimum_required(VERSION 3.26)
project(Swarmies)

set(CMAKE_CXX_STANDARD 23)

#option(UNITY_VERSION "The folder name of the unity editor you use" -1)
set(UNITY_VERSION "-1" CACHE STRING "The folder name of the unity editor you use")

if(UNITY_VERSION EQUAL -1)
    message(FATAL_ERROR "You must specify the unity version you use")
endif ()

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(Swarmies main.cpp
        Systems/Geometry/Geometry.cpp
        Systems/Geometry/Geometry.h)

add_library(UnityGlue
        Frontends/Unity3d/RegisterUnityCallbacks.cpp
        Frontends/Unity3d/RegisterUnityCallbacks.h)

target_include_directories(UnityGlue PUBLIC "/Applications/Unity/Hub/Editor/${UNITY_VERSION}/Unity.app/Contents/PluginAPI")

target_link_libraries(Swarmies UnityGlue)