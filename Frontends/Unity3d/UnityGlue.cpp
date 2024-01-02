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
#include "IUnityInterface.h"
#include "IUnityGraphics.h"
#include "IUnityLog.h"
#include "IUnityEventQueue.h"
#include "UnityGlue.hpp"

#include "../../Swarmies/BusinessObjects/Geometry/Geometry.hpp"

void UnityPlayGame::LoadLevel(const char* name) {

}

void UnityPlayGame::LoadMesh(const char* name, struct VertexWrapper * vw) {
    std::FILE * file = std::fopen(name, "rb");
    Swarmies::Mesh mesh;
    ::LoadMesh(file, &mesh);
    *vw = *mesh.vertices.data();
}

IUnityLog* unityLog = nullptr;

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

extern "C" UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API void LoadLevelMesh(const char * name, struct VertexWrapper * vw) {
    UNITY_LOG(unityLog, name);

    UnityPlayGame().LoadMesh(name, vw);
    //return 24.f;

}

extern "C" UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API int MeshVerticesNumber(const char * name) {
    UNITY_LOG(unityLog, name);

    Swarmies::Mesh mesh;

    UnityPlayGame().LoadMesh(name, mesh.vertices.data());
    //return 24.f;
}

struct MyCustomEvent {};

// see https://makaka.org/unity-tutorials/guid
// https://docs.unity.com/ugs/manual/analytics/manual/event-manager
// https://forum.unity.com/threads/use-iunityeventqueue-from-a-native-plugin-to-call-send-a-message-to-c.1289540/
REGISTER_EVENT_ID(0xda75015ee8eb4719, 0xaa97c4855661637e, MyCustomEvent);
