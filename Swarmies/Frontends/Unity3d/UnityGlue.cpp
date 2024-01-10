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
#include "IUnityInterface.h"
#include "IUnityGraphics.h"
#include "IUnityLog.h"
#include "IUnityEventQueue.h"
#include "UnityGlue.hpp"

#include "../../BusinessObjects/Geometry/Geometry.hpp"

IUnityLog* unityLog = nullptr;

void UnityPlayGame::LoadLevel(const char* name) {

}

Swarmies::Mesh UnityPlayGame::LoadMesh(const char* name) {

    std::string path = ".";
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        UNITY_LOG(unityLog, entry.path().c_str());
    }
    using namespace std::string_literals;

    std::FILE * file = std::fopen(("Assets/GameAssets/"s + name + ".obj").c_str(), "rb");
    Swarmies::Mesh mesh(name);

    ::LoadMesh(file, &mesh);

    return mesh;
}


int UnityPlayGame::MeshVertexCount(const char* name) {
    using namespace std::string_literals;

    std::FILE * file = std::fopen(("Assets/GameAssets/"s + name + ".obj").c_str(), "rb");
    Swarmies::Mesh mesh(name);

    ::LoadMesh(file, &mesh);

    return mesh.number_vertices();
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

extern "C" UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API void LoadLevelMesh(const char * name, float vw[]) {
    UNITY_LOG(unityLog, name);

    Swarmies::Mesh mesh = UnityPlayGame().LoadMesh(name);
    for (int i = 0; i < mesh.number_vertices(); ++i) {
        vw[i*3+0] = mesh.vertices.data()->abscisse;
        vw[i*3+1] = mesh.vertices.data()->ordonnee;
        vw[i*3+2] = mesh.vertices.data()->prof;
    }
    //return 24.f;
}

extern "C" UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API int MeshVerticesNumber(const char * name) {
    UNITY_LOG(unityLog, name);

    int ct = (UnityPlayGame().MeshVertexCount(name));
    //return 24.f;

    return ct;
}

struct MyCustomEvent {};

// see https://makaka.org/unity-tutorials/guid
// https://docs.unity.com/ugs/manual/analytics/manual/event-manager
// https://forum.unity.com/threads/use-iunityeventqueue-from-a-native-plugin-to-call-send-a-message-to-c.1289540/
REGISTER_EVENT_ID(0xda75015ee8eb4719, 0xaa97c4855661637e, MyCustomEvent);
