cmake_minimum_required(VERSION 3.26)
project(Swarmies)

set(CMAKE_CXX_STANDARD 23)

#option(UNITY_VERSION "The folder name of the unity editor you use" -1)
set(UNITY_VERSION "-1" CACHE STRING "The folder name of the unity editor you use")
set(UNITY_PROJECT_FOLDER "-1" CACHE STRING "The folder where the plugin should be copied to")

if(UNITY_VERSION EQUAL -1)
    message(FATAL_ERROR "You must specify the unity version you use")
endif ()

if(UNITY_PROJECT_FOLDER EQUAL -1)
    message(FATAL_ERROR "You must specify the folder where the plugin should be copied to")
endif ()

file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})


add_executable(Swarmies main.cpp
        BusinessObjects/Geometry/Geometry.cpp
        BusinessObjects/Geometry/Geometry.hpp
        BusinessLogic/PlayGame.cpp
        BusinessLogic/PlayGame.hpp
        Frontends/IPlayGame.hpp
        tests.cpp
        tests.hpp
        BusinessObjects/GameLevel.hpp
        BusinessObjects/Mobile.hpp
        BusinessObjects/Mesh.hpp
        BusinessObjects/Mesh.cpp
        BusinessObjects/TRepository.tpp
        BusinessObjects/TRelations.tpp
)

add_library(UnityGlue SHARED
        Frontends/Unity3d/UnityGlue.cpp
        Frontends/IPlayGame.hpp
)

target_include_directories(UnityGlue PUBLIC "/Applications/Unity/Hub/Editor/${UNITY_VERSION}/Unity.app/Contents/PluginAPI")

target_link_libraries(Swarmies UnityGlue)

add_custom_command(TARGET UnityGlue POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:UnityGlue> "${UNITY_PROJECT_FOLDER}/Assets/Plugins"
        COMMENT "Copying DLL file to output directory..."
)