//
// Created by ivo on 27/01/2024.
//

#ifndef SOLUTIONSWARMIES_AUTODESKOBJLOADER_HPP
#define SOLUTIONSWARMIES_AUTODESKOBJLOADER_HPP

#include <unordered_map>
#include <string>
#include "../../Swarmies/BusinessObjects/Geometry/Mesh.hpp"

namespace Engine {

    class AutodeskObjLoader {
        std::unordered_map<std::string, Swarmies::Mesh&> objects;
    public:
        static std::vector<Swarmies::Mesh> load_obj(const char * path);
    };

} // Engine

#if SWARMIES_TESTING
void testMultiMesh();
#endif

#endif //SOLUTIONSWARMIES_AUTODESKOBJLOADER_HPP
