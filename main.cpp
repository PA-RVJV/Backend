#include <iostream>

#include "BusinessLogic/TRepository.hpp"
#include "BusinessLogic/TRelations.hpp"
#include "BusinessObjects/Mesh.hpp"
#include "BusinessObjects/Mobile.hpp"

constexpr Swarmies::TRepository<Swarmies::Mesh> repos(void) {
    return Swarmies::TRepository<Swarmies::Mesh>();
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    auto meshes = Swarmies::TRepository<Swarmies::Mesh>();
    auto mobiles = Swarmies::TRepository<Swarmies::Mobile>();

    auto mesh_mob_relation = Swarmies::TRelation<Swarmies::Mobile, Swarmies::Mesh>();

    return 0;
}
