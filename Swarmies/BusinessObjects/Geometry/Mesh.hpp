//
// Created by ivo on 01/11/2023.
//

#ifndef SWARMIES_MESH_HPP
#define SWARMIES_MESH_HPP

#include <string>
#include <vector>
#include <array>

struct VertexWrapper  {
    float abscisse;
    float ordonnee;
    float prof;
};

namespace Swarmies {
    struct Mesh {
        const std::string name;
        std::vector<struct VertexWrapper> vertices;
        std::vector<struct VertexWrapper> normals;
        std::vector<struct VertexWrapper> triangles;

        Mesh(std::string && name) noexcept;
        [[nodiscard]] int number_vertices() const;
    };

    void LoadMesh(std::FILE * file, Swarmies::Mesh * mesh);
}

#endif //SWARMIES_MESH_HPP
