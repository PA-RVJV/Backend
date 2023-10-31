//
// Created by ivo on 28/10/2023.
//

#include "RegisterUnityCallbacks.h"

#include "IUnityInterface.h"
#include "IUnityGraphics.h"
#include "IUnityLog.h"

IUnityLog* unityLog = nullptr;
// Unity plugin load event
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    IUnityGraphics* graphics = unityInterfaces->Get<IUnityGraphics>();
    unityLog = unityInterfaces->Get<IUnityLog>();

    UNITY_LOG(unityLog, "toto");
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityPluginUnload()
{
    unityLog = nullptr;

    //UNITY_LOG(unityLog, "toto");
}
