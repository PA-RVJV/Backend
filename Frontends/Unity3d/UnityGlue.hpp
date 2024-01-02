//
// Created by ivo on 02/01/2024.
//

#ifndef SOLUTIONSWARMIES_UNITYGLUE_HPP
#define SOLUTIONSWARMIES_UNITYGLUE_HPP

#include "../IPlayGame.hpp"
#include "../../Swarmies/BusinessObjects/Mesh.hpp"

class UnityPlayGame: IPlayGame {
public:
    void LoadLevel(const char* name) final;
    void LoadMesh(const char* name, struct VertexWrapper *vw) final;
};


#endif //SOLUTIONSWARMIES_UNITYGLUE_HPP
