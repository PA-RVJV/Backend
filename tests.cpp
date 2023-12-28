//
// Created by ivo on 01/11/2023.
//

#include <cstdio>

#include "Engine/BusinessLogic/TRepository.hpp"
#include "Engine/BusinessLogic/TRelations.hpp"
#include "Engine/BusinessLogic/TSemantiqueRelation.hpp"
#include "Swarmies/BusinessObjects/Mesh.hpp"
#include "Swarmies/BusinessObjects/Geometry/Geometry.hpp"
#include "Swarmies/BusinessObjects/Mobile.hpp"

int main(int argc, char * argv[]) {

    puts("\n*** START TESTING ***");
    printf("Test program name %s\n", argv[0]);
    
    testFindExtremafromObj("Assets/test_topo.obj");
    testRepoWorks();

    Engine::TRelation<Swarmies::Mesh, Swarmies::Mobile>::testRelations();
    Engine::TSemantiqueRelation<Swarmies::Mesh, Engine::SemantiqueRelation::Kind::NO_TAG>::testSemantique();
}
