//
// Created by ivo on 01/11/2023.
//

#include <cstdio>

#include "BusinessObjects/Geometry/Geometry.hpp"
#include "BusinessObjects/TRepository.hpp"
#include "BusinessObjects/TRelations.hpp"

int main(int argc, char * argv[]) {

    puts("\n*** START TESTING ***");
    printf("Test program name %s\n", argv[0]);
    
    testFindExtremafromObj("Assets/test_topo.obj");
    testRepoWorks();
    Swarmies::TRelation<Swarmies::Mesh, Swarmies::Mobile>::testRelations();
}
