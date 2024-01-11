//
// Created by ivo on 02/01/2024.
//


#if SWARMIES_TESTING

#include <cassert>
#include <iostream>

#include "TRelations.hpp"
#include "../../Swarmies/BusinessObjects/Geometry/Mesh.hpp"
#include "../../Swarmies/BusinessObjects/Mobile.hpp"

template<> void Engine::TRelation<Swarmies::Mesh, Swarmies::Mobile>::testRelations() {

    auto meshMobRelation = Engine::TRelation<Swarmies::Mesh, Swarmies::Mobile>();

    // test that our relations tables are empty
    assert(meshMobRelation.a_to_b.empty());
    assert(meshMobRelation.b_to_a.empty());

    Swarmies::Mesh mesh {"mesh1"};
    Swarmies::Mesh mesh2 {"mesh2"};
    Swarmies::Mobile mobile {"mob1"};

    meshMobRelation.addRelations(mesh, mobile);

    // our relation created an entry
    assert(meshMobRelation.a_to_b.size() == 1);
    assert(meshMobRelation.b_to_a.size() == 1);

    meshMobRelation.removeRelations(mesh, mobile);

    // remove acted on both tables
    assert(meshMobRelation.a_to_b.empty());
    assert(meshMobRelation.b_to_a.empty());

    meshMobRelation.addRelations(mesh, mobile);
    meshMobRelation.addRelations(mesh2, mobile);

    assert(meshMobRelation.a_to_b.size() == 2);
    assert(meshMobRelation.b_to_a.size() == 1);

    {
        auto meshes = meshMobRelation.b_to_a["mob1"];
        assert(meshes.size() == 2);

        auto mobs = meshMobRelation.a_to_b["mesh1"];
        assert(mobs.size() == 1);
        assert(mobs.at("mob1").name == "mob1");
    }

    std::cout << "Relations work" << std::endl;
}

#endif // NDEBUG