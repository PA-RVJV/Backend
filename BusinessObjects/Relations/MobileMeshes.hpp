//
// Created by ivo on 01/11/2023.
// Maintient la relation N-M entre Meshes et Mobiles
//

#ifndef SWARMIES_MOBILEMESHES_HPP
#define SWARMIES_MOBILEMESHES_HPP

#include <unordered_map>

#include "../Mesh.hpp"
#include "../Mobile.hpp"

namespace Swarmies {
    struct MeshMobilePayload {
        Swarmies::Mobile& mobile;
        Swarmies::Mesh& mesh;
    };

    class MobileMeshes final {
        std::unordered_map<std::string, std::unordered_map<std::string, Swarmies::Mesh&>> mobiles_to_meshes;
        std::unordered_map<std::string, std::unordered_map<std::string, Swarmies::Mobile&>> meshes_to_mobiles;

        void addRelation(MeshMobilePayload payload);
        void removeRelation(MeshMobilePayload payload);

    public:
        void addMeshToMobile(MeshMobilePayload payload);
        void addMobileToMesh(MeshMobilePayload payload);
        void removeMeshFromMobile(MeshMobilePayload payload);
        void removeMobileFromMesh(MeshMobilePayload payload);
    };

}

#endif //SWARMIES_MOBILEMESHES_HPP
