//
// Created by ivo on 02/01/2024.
//

#ifndef SOLUTIONSWARMIES_UNITYGLUE_HPP
#define SOLUTIONSWARMIES_UNITYGLUE_HPP

#include "../IPlayGame.hpp"
#include "../../BusinessObjects/Geometry/Mesh.hpp"

class UnityPlayGame: IPlayGame {
public:
    void LoadLevel(const char* name) final;
    Swarmies::Mesh& LoadMesh(const char* name) final;
    int MeshVertexCount(const char* name) final;
    int MeshNormalsCount(const char* name) final;
    int MeshUVCount(const char* name) final;
    int MeshTrianglesCount(const char* name) final;
};


#endif //SOLUTIONSWARMIES_UNITYGLUE_HPP
