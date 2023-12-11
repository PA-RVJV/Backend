#include <iostream>

#include "BusinessObjects/TRepository.tpp"
#include "BusinessObjects/TRelations.tpp"
#include "BusinessObjects/Mesh.hpp"
#include "BusinessObjects/Mobile.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto meshes = Swarmies::TRepository<Swarmies::Mesh>();
    auto mobiles = Swarmies::TRepository<Swarmies::Mobile>();

    auto mesh_mob_relation = Swarmies::TRelation<Swarmies::Mobile, Swarmies::Mesh>();

    return 0;
}
