cmake_minimum_required(VERSION 3.26)
project(Swarmies_backend)

set(CMAKE_CXX_STANDARD 23)

# on veut que nos programmes puissent modifier
# les fichiers sur lequel on travaille
# une fois build
#file(COPY Assets DESTINATION $<TARGET_FILE_DIR:TestsSwarmiesServer>)

add_executable(Swarmies_Server
        main.cpp
        Swarmies/BusinessObjects/Geometry/Geometry.cpp
        Swarmies/BusinessObjects/Geometry/Geometry.hpp
        Engine/BusinessLogic/PlayGame.cpp
        Engine/BusinessLogic/PlayGame.hpp
        Frontends/IPlayGame.hpp
        Swarmies/BusinessObjects/GameLevel.hpp
        Swarmies/BusinessObjects/Mobile.hpp
        Swarmies/BusinessObjects/Mesh.hpp
        Swarmies/BusinessObjects/Mesh.cpp
        Engine/BusinessLogic/TRepository.hpp
        Engine/BusinessLogic/TRelations.hpp
        Engine/BusinessLogic/Ordonanceur.cpp
        Engine/BusinessLogic/Ordonanceur.hpp
        Engine/BusinessLogic/TSemantiqueRelation.hpp
        Swarmies/repositories.cpp
        Engine/BusinessLogic/Payload.hpp
        Engine/BusinessLogic/TRepository.cpp
        Engine/BusinessLogic/TRelations.cpp
        Engine/BusinessLogic/TSemantiqueRelation.cpp
)

add_library(UnityGlue SHARED
        Frontends/Unity3d/UnityGlue.cpp
        Frontends/IPlayGame.hpp
        Frontends/Unity3d/UnityGlue.hpp
        Swarmies/BusinessObjects/Geometry/Geometry.cpp
)

add_executable(TestsSwarmiesServer
        tests.cpp
        Engine/BusinessLogic/TRepository.hpp
        Engine/BusinessLogic/TRelations.hpp
        Swarmies/BusinessObjects/Mesh.hpp
        Swarmies/BusinessObjects/Mobile.hpp
        Swarmies/BusinessObjects/Mesh.cpp
        Swarmies/BusinessObjects/Geometry/Geometry.cpp
        Engine/BusinessLogic/TRepository.cpp
        Engine/BusinessLogic/TRelations.cpp
        Engine/BusinessLogic/Ordonanceur.cpp
        Engine/BusinessLogic/Ordonanceur.hpp
        Engine/BusinessLogic/TSemantiqueRelation.cpp
)

add_custom_command(TARGET TestsSwarmiesServer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/Swarmies/Assets"
        $<TARGET_FILE_DIR:TestsSwarmiesServer>/Assets
)

#get_target_property(otp TestsSwarmiesServer RUNTIME_OUTPUT_DIRECTORY_DEBUG)
set(otp "")
message(STATUS "Output dir ${otp}")

set(UNITY_VERSION "2022.3.13f1" CACHE STRING "The folder name of the unity editor you use")
set(UNITY_PROJECT_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/../UnityFront" CACHE STRING "The folder where the plugin should be copied to")

if(UNITY_VERSION EQUAL -1)
    message(FATAL_ERROR "You must specify the unity version you use")
endif ()

if(UNITY_PROJECT_FOLDER EQUAL -1)
    message(FATAL_ERROR "You must specify the folder where the plugin should be copied to")
endif ()

target_include_directories(
        UnityGlue PUBLIC "/Applications/Unity/Hub/Editor/${UNITY_VERSION}/Unity.app/Contents/PluginAPI"
)

target_link_libraries(Swarmies_Server UnityGlue)

add_custom_command(TARGET UnityGlue POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:UnityGlue> "${UNITY_PROJECT_FOLDER}/Assets/Plugins"
        COMMENT "Copying DLL file to output directory..."
)

add_custom_command(TARGET UnityGlue POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/Swarmies/Assets"
        "${UNITY_PROJECT_FOLDER}/Assets/Plugins"
        COMMENT "Copying DLL file to output directory..."
)

# Arbo plus lisible sous XCode
source_group("Engine/Source Files" REGULAR_EXPRESSION "Backend/Engine/.+cpp")
source_group("Engine/Header Files" REGULAR_EXPRESSION "Backend/Engine/.+hpp")
source_group("Swarmies/Source Files" REGULAR_EXPRESSION "Backend/Swarmies/.+cpp")
source_group("Swarmies/Header Files" REGULAR_EXPRESSION "Backend/Swarmies/.+hpp")
source_group("Frontends/Source Files" REGULAR_EXPRESSION "Backend/Frontends/.+cpp")
source_group("Frontends/Header Files" REGULAR_EXPRESSION "Backend/Frontends/.+hpp")
