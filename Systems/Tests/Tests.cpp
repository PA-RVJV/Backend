//
// Created by ivo on 31/10/2023.
//

#include <iostream>

#include "Tests.h"
#include "IUnityLog.h"

extern IUnityLog* unityLog;

extern "C" UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API float SayHello() {
    UNITY_LOG(unityLog, "tata");
    return 24;
}
