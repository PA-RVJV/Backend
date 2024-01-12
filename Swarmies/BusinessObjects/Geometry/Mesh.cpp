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

    /**
     * Charge un mesh depuis un fichier .obj dans un format utilisable
     * par Unity (meme principe que Assimp)
     */
    void LoadMesh(
            std::FILE * file,
            Swarmies::Mesh * mesh
    ) {
        char buf[256];

        float mov = 0;
        float depth = 0;
        float elev = 0;

        while (std::fgets(buf, sizeof buf, file) != nullptr) {

            if(buf[1] == 'n') { // a vn on arrete
                break;
            }

            if(buf[0] != 'v') { // skip ce qui commence pas par v
                continue;
            }

            sscanf(buf, "v %f %f %f\n", &mov, &elev, &depth);

            struct VertexWrapper vw {mov, elev, depth};
            mesh->vertices.push_back(vw);
        }
    }
}

