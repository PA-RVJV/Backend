//
// Created by ivo on 28/10/2023.
//

#ifndef NULL
#define NULL nullptr
#endif
#ifndef Assert
#define Assert(foo)
#endif

#include <cstdio>
#include <filesystem>
#include <iostream>
#include "IUnityInterface.h"
#include "IUnityGraphics.h"
#include "IUnityLog.h"
#include "IUnityEventQueue.h"
#include "UnityGlue.hpp"

static IUnityLog* unityLog = nullptr;
static Swarmies::Mesh loaded_mesh("");


void UnityPlayGame::LoadLevel(const char* name) {

}

static Swarmies::Mesh& load_mesh(const char* name) {

    if(loaded_mesh.name != name) {
        using namespace std::string_literals;
        std::FILE * file = std::fopen(("Assets/GameAssets/"s + name + ".obj").c_str(), "rb");
        loaded_mesh = Swarmies::LoadMesh(file, Swarmies::Mesh(name));
    }

    return loaded_mesh;
}

Swarmies::Mesh& UnityPlayGame::LoadMesh(const char* name) {
    std::string path = ".";
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        UNITY_LOG(unityLog, entry.path().c_str());
    }

    return load_mesh(name);
}


int UnityPlayGame::MeshVertexCount(const char* name) {

    return load_mesh(name).vertice_count();
}

int UnityPlayGame::MeshNormalsCount(const char* name) {

    return load_mesh(name).normals_count();
}

int UnityPlayGame::MeshUVCount(const char* name) {

    return load_mesh(name).texture_count();
}

int UnityPlayGame::MeshTrianglesCount(const char* name) {

    return load_mesh(name).triangles_count();
}

// Unity plugin load event
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    auto * graphics = unityInterfaces->Get<IUnityGraphics>();
    unityLog = unityInterfaces->Get<IUnityLog>();

    UNITY_LOG(unityLog, "loded unity glue");
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityPluginUnload()
{
    UNITY_LOG(unityLog, "unload unity glue");

    unityLog = nullptr;
}

extern "C" UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API float SayHello() {
    UNITY_LOG(unityLog, "say hello from glue");

    return 24.f;
}

extern "C" UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
void LoadLevelMesh(const char * name, float vertices[], float norms[], float uvs[], int tris[]) {
    UNITY_LOG(unityLog, name);

    Swarmies::Mesh & mesh = UnityPlayGame().LoadMesh(name);
    for (int i = 0; i < mesh.vertice_count(); ++i) {
        vertices[i*3+0] = mesh.vertices.at(i).abscisse;
        vertices[i*3+1] = mesh.vertices.at(i).ordonnee;
        vertices[i*3+2] = mesh.vertices.at(i).prof;
    }
    for (int i = 0; i < mesh.normals_count(); ++i) {
        norms[i*3+0] = mesh.normals.at(i).abscisse;
        norms[i*3+1] = mesh.normals.at(i).ordonnee;
        norms[i*3+2] = mesh.normals.at(i).prof;
    }
    for (int i = 0; i < mesh.texture_count(); ++i) {
        uvs[i*2+0] = mesh.texture.at(i).abscisse;
        uvs[i*2+1] = mesh.texture.at(i).ordonnee;
    }

    int i = 0;
    for (auto tri: mesh.triangles_iterator) {
        tris[i++] = tri - 1;
        // dans unity, les face doivent referencer des vertices en partant de zero,
        // dans le format.obj ca part de 1
    }

    std::cout << "toto" << std::endl;
    //return 24.f;
}

extern "C" UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
int MeshVerticesNumber(const char * name) {
    UNITY_LOG(unityLog, name);

    return (UnityPlayGame().MeshVertexCount(name));
}

extern "C" UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
int MeshNormalsNumber(const char * name) {
    UNITY_LOG(unityLog, name);

    return (UnityPlayGame().MeshNormalsCount(name));
}

extern "C" UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
int MeshUVNumber(const char * name) {
    UNITY_LOG(unityLog, name);

    return (UnityPlayGame().MeshUVCount(name));
}

extern "C" UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
int MeshTrianglesNumber(const char * name) {
    UNITY_LOG(unityLog, name);

    return (UnityPlayGame().MeshTrianglesCount(name));
}

struct MyCustomEvent {};

// see https://makaka.org/unity-tutorials/guid
// https://docs.unity.com/ugs/manual/analytics/manual/event-manager
// https://forum.unity.com/threads/use-iunityeventqueue-from-a-native-plugin-to-call-send-a-message-to-c.1289540/
REGISTER_EVENT_ID(0xda75015ee8eb4719, 0xaa97c4855661637e, MyCustomEvent);
