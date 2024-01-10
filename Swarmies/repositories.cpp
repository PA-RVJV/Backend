//
// Created by ivo on 28/12/2023.
//

#include "../Engine/Relations/TRepository.hpp"
#include "BusinessObjects/Geometry/Mesh.hpp"
#include "BusinessObjects/Mobile.hpp"

namespace Swarmies {

    union RepositoriesTypes {
        Engine::TRepository<Swarmies::Mesh> meshes;
        Engine::TRepository<Swarmies::Mobile> mobiles;
    };
}
