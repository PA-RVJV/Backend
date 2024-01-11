//
// Created by ivo on 01/11/2023.
//

#include <cstdio>

#include "Engine/Relations/TRepository.hpp"
#include "Engine/Relations/TRelations.hpp"
#include "Engine/Relations/TSemantiqueRelation.hpp"
#include "Engine/Relations/Ordonanceur.hpp"

#include "Swarmies/BusinessObjects/Geometry/Mesh.hpp"
#include "Swarmies/BusinessObjects/Geometry/Geometry.hpp"
#include "Swarmies/BusinessObjects/Mobile.hpp"

int main(int argc, char * argv[]) {

    puts("\n*** START TESTING ***");
    printf("Test program name %s\n", argv[0]);

#if SWARMIES_TESTING
    testFindExtremafromObj("Assets/test_topo.obj");
    testRepoWorks();

    Engine::TRelation<Swarmies::Mesh, Swarmies::Mobile>::testRelations();
    Engine::TSemantiqueRelation<Swarmies::Mesh, Engine::SemantiqueRelation::Kind::NO_TAG>::testSemantique();
    
    Engine::test_ordonnanceur_works();
#endif
}
