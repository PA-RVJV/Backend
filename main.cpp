#include <iostream>

#include "Engine/BusinessLogic/TRepository.hpp"
#include "Engine/BusinessLogic/TRelations.hpp"
#include "Swarmies/BusinessObjects/Mesh.hpp"
#include "Swarmies/BusinessObjects/Mobile.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto meshes = Engine::TRepository<Swarmies::Mesh>();
    auto mobiles = Engine::TRepository<Swarmies::Mobile>();

    auto mesh_mob_relation = Engine::TRelation<Swarmies::Mobile, Swarmies::Mesh>();

    mobiles.add("monde", Swarmies::Mobile{"monde"});

    return 0;
}
