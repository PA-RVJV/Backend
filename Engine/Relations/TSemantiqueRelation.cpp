//
// Created by ivo on 02/01/2024.
//


#ifndef NDEBUG

#include <cassert>

#include "TSemantiqueRelation.hpp"
#include "../../Swarmies/BusinessObjects/Geometry/Mesh.hpp"

template<> void Engine::TSemantiqueRelation<Swarmies::Mesh, Engine::SemantiqueRelation::Kind::NO_TAG>::testSemantique() {

    auto meshMobRelation = Engine::TSemantiqueRelation<Swarmies::Mesh>();

    assert(meshMobRelation.tags.empty());

}

#endif //NDEBUG