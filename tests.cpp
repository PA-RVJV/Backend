//
// Created by ivo on 01/11/2023.
//

#include "tests.hpp"

#define SWARMIES_TESTING
#include "BusinessObjects/Geometry/Geometry.hpp"
#include "BusinessObjects/TRepository.tpp"
#include "BusinessObjects/TRelations.tpp"
#undef SWARMIES_TESTING

void test() {
    testFindExtremafromObj("Assets/test_topo.obj");
    testRepoWorks();
    Swarmies::TRelation<Swarmies::Mesh, Swarmies::Mobile>::testRelations();
}
