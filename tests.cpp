//
// Created by ivo on 01/11/2023.
//

#include "BusinessObjects/Geometry/Geometry.hpp"
#include "BusinessObjects/TRepository.tpp"
#include "BusinessObjects/TRelations.tpp"

int main() {
    testFindExtremafromObj("Assets/test_topo.obj");
    testRepoWorks();
    Swarmies::TRelation<Swarmies::Mesh, Swarmies::Mobile>::testRelations();
}
