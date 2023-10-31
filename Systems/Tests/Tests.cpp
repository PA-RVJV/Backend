//
// Created by ivo on 31/10/2023.
//

#include <iostream>

#include "Tests.h"


extern "C" UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API float SayHello() {
    return 42;
}
