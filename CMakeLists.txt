cmake_minimum_required(VERSION 3.26)
project(Swarmies_backend)

set(CMAKE_CXX_STANDARD 23)

include(CTest)
enable_testing()

add_executable(Swarmies_Server
        main.cpp
        Swarmies/BusinessObjects/Geometry/Geometry.cpp
        Swarmies/BusinessObjects/Geometry/Geometry.hpp
        Engine/Relations/PlayGame.cpp
        Engine/Relations/PlayGame.hpp
        Swarmies/BusinessObjects/GameLevel.hpp
        Swarmies/BusinessObjects/Mobile.hpp
        Swarmies/BusinessObjects/Geometry/Mesh.hpp
        Swarmies/BusinessObjects/Geometry/Mesh.cpp
        Engine/Relations/TRepository.hpp
        Engine/Relations/TRelations.hpp
        Engine/Relations/Ordonanceur.cpp
        Engine/Relations/Ordonanceur.hpp
        Engine/Relations/TSemantiqueRelation.hpp
        Swarmies/repositories.cpp
        Engine/Relations/Payload.hpp
        Engine/Relations/TRepository.cpp
        Engine/Relations/TRelations.cpp
        Engine/Relations/TSemantiqueRelation.cpp
        Engine/3d/AutodeskObjLoader.cpp
        Engine/3d/AutodeskObjLoader.hpp
)

option(ADD_UNITY_GLUE "Build the unity layer ?" OFF)
if(ADD_UNITY_GLUE)
    add_library(UnityGlue SHARED
            Swarmies/Frontends/Unity3d/UnityGlue.cpp
            Swarmies/Frontends/IPlayGame.hpp
            Swarmies/Frontends/Unity3d/UnityGlue.hpp
            Swarmies/BusinessObjects/Geometry/Geometry.cpp
            Swarmies/BusinessObjects/Geometry/Geometry.hpp
            Swarmies/BusinessObjects/Geometry/Mesh.cpp
            Swarmies/BusinessObjects/Geometry/Mesh.hpp
            Engine/3d/AutodeskObjLoader.cpp
            Engine/3d/AutodeskObjLoader.hpp
    )


    set(UNITY_VERSION "2022.3.13f1" CACHE STRING "The folder name of the unity editor you use")
    set(UNITY_PROJECT_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/../UnityFront" CACHE PATH "The folder where the plugin should be copied to")

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
            "${UNITY_PROJECT_FOLDER}/Assets/GameAssets"
            COMMENT "Copying Game Assets to output directory..."
    )

endif (ADD_UNITY_GLUE)

if(BUILD_TESTING)

    set(TEST_EXECUTABLE_NAME "TestsSwarmiesServer")
    add_executable(${TEST_EXECUTABLE_NAME}
            tests.cpp
            Engine/Relations/TRepository.hpp
            Engine/Relations/TRelations.hpp
            Swarmies/BusinessObjects/Geometry/Mesh.hpp
            Swarmies/BusinessObjects/Mobile.hpp
            Swarmies/BusinessObjects/Geometry/Mesh.cpp
            Swarmies/BusinessObjects/Geometry/Geometry.cpp
            Engine/Relations/TRepository.cpp
            Engine/Relations/TRelations.cpp
            Engine/Relations/Ordonanceur.cpp
            Engine/Relations/Ordonanceur.hpp
            Engine/Relations/TSemantiqueRelation.cpp
            Engine/3d/AutodeskObjLoader.cpp
            Engine/3d/AutodeskObjLoader.hpp
    )
    target_compile_definitions(${TEST_EXECUTABLE_NAME} PRIVATE SWARMIES_TESTING)
    target_compile_definitions(${TEST_EXECUTABLE_NAME} PRIVATE SWARMIES_TESTING)
    add_custom_command(TARGET "${TEST_EXECUTABLE_NAME}" POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/Swarmies/Assets"
            $<TARGET_FILE_DIR:${TEST_EXECUTABLE_NAME}>/Assets
    )
    add_test(NAME ${TEST_EXECUTABLE_NAME} COMMAND ${TEST_EXECUTABLE_NAME})
endif (BUILD_TESTING)

if (SWARMIES_TESTING)
    add_definitions(-DSWARMIES_TESTING=1)
endif (SWARMIES_TESTING)

# Arbo plus lisible sous XCode
source_group("Engine/Source Files" REGULAR_EXPRESSION "Backend/Engine/.+cpp")
source_group("Engine/Header Files" REGULAR_EXPRESSION "Backend/Engine/.+hpp")
source_group("Swarmies/Source Files" REGULAR_EXPRESSION "Backend/Swarmies/.+cpp")
source_group("Swarmies/Header Files" REGULAR_EXPRESSION "Backend/Swarmies/.+hpp")
source_group("Swarmies/Frontends/Source Files" REGULAR_EXPRESSION "Backend/Frontends/.+cpp")
source_group("Swarmies/Frontends/Header Files" REGULAR_EXPRESSION "Backend/Frontends/.+hpp")
