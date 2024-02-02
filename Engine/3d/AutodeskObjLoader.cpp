//
// Created by ivo on 27/01/2024.
//

#include "AutodeskObjLoader.hpp"

namespace Engine {
    std::vector<Swarmies::Mesh> AutodeskObjLoader::load_obj(const char *path) {
        auto meshes = std::vector<Swarmies::Mesh>();

        using namespace std::string_literals;
        std::FILE * file = std::fopen( path, "rb");

        char buf[256];

        while (!std::feof(file)) {
            meshes.push_back(Swarmies::LoadMesh(file, Swarmies::Mesh("*replace*")));
        }

        return meshes;
    }
} // ::Engine

#if SWARMIES_TESTING
#include <cstdio>
#include <cassert>

void testMultiMesh() {
    auto meshes = Engine::AutodeskObjLoader::load_obj("Assets/test_topo3.obj");
    assert(!meshes.empty());
    assert(meshes.size() == 3);
    assert(meshes[0].name == "Terrain");
    assert(meshes[1].name == "Bonhomme");
    assert(meshes[2].name == "Bataille");

    puts("testMultiMesh works");
}

#endif