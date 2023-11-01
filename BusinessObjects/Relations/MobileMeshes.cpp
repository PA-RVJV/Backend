//
// Created by ivo on 01/11/2023.
//

#include "MobileMeshes.hpp"

namespace Swarmies {
    void MobileMeshes::addRelation(MeshMobilePayload payload) {
        auto mob_map = mobiles_to_meshes[payload.mobile.name];
        auto mesh_map = meshes_to_mobiles[payload.mesh.name];
        mob_map.insert({payload.mesh.name, payload.mesh});
        mesh_map.insert({payload.mobile.name, payload.mobile});
    }

    void MobileMeshes::removeRelation(MeshMobilePayload payload) {
        auto mob_map = mobiles_to_meshes[payload.mobile.name];
        mob_map.erase(payload.mesh.name);

        auto mesh_map = meshes_to_mobiles[payload.mesh.name];
        mesh_map.erase(payload.mobile.name);
    }

    void MobileMeshes::addMeshToMobile(MeshMobilePayload payload) {
        addRelation(payload);
    }

    void MobileMeshes::removeMeshFromMobile(MeshMobilePayload payload) {
        removeRelation(payload);
    }

    void MobileMeshes::addMobileToMesh(MeshMobilePayload payload) {
        addRelation(payload);
    }

    void MobileMeshes::removeMobileFromMesh(MeshMobilePayload payload) {
        removeRelation(payload);
    }
}