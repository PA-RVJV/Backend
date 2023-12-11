//
// Created by ivo on 28/10/2023.
//

#ifndef NULL
#define NULL nullptr
#endif
#ifndef Assert
#define Assert(foo)
#endif

#include "IUnityInterface.h"
#include "IUnityGraphics.h"
#include "IUnityLog.h"
#include "IUnityEventQueue.h"

#include "../IPlayGame.hpp"

class UnityPlayGame: IPlayGame {
    void LoadLevel() final;
};

void UnityPlayGame::LoadLevel() {

}

IUnityLog* unityLog = nullptr;
// Unity plugin load event
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    auto * graphics = unityInterfaces->Get<IUnityGraphics>();
    unityLog = unityInterfaces->Get<IUnityLog>();

    UNITY_LOG(unityLog, "toto");
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityPluginUnload()
{
    unityLog = nullptr;

    //UNITY_LOG(unityLog, "toto");
}

extern "C" UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API float SayHello() {
    UNITY_LOG(unityLog, "tata");
    return 24;
}

struct MyCustomEvent {};

REGISTER_EVENT_ID(0xda75015ee8eb4719, 0xaa97c4855661637e, MyCustomEvent);