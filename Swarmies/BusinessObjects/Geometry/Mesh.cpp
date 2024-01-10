//
// Created by ivo on 01/11/2023.
//

#include <iostream>

#include "Mesh.hpp"

namespace Swarmies {
//    Mesh::~Mesh() {
//        std::cout << "Mesh destroyed " << name << '\n';
//    }
    Mesh::Mesh(std::string && name) noexcept: name(name) {}

    int Mesh::number_vertices() const {return static_cast<int>(vertices.size()); }
}
