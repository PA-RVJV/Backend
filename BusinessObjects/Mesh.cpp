//
// Created by ivo on 01/11/2023.
//

#include <iostream>

#include "Mesh.hpp"

namespace Swarmies {
    Mesh::~Mesh() {
        std::cout << "Mesh destroyed" << std::endl;
    }
}