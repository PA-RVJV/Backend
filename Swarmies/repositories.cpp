//
// Created by ivo on 28/12/2023.
//

#include "../Engine/BusinessLogic/TRepository.hpp"
#include "BusinessObjects/Mesh.hpp"
#include "BusinessObjects/Mobile.hpp"

namespace Swarmies {

    union RepositoriesTypes {
        Swarmies::TRepository<Swarmies::Mesh> meshes;
        Swarmies::TRepository<Swarmies::Mobile> mobiles;
    };
}
