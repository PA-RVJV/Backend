//
// Created by ivo on 01/11/2023.
//
#ifndef SWARMIES_TRELATIONS_HPP
#define SWARMIES_TRELATIONS_HPP

#include <unordered_map>


namespace Swarmies {

    template<typename T1, typename T2>
    class TRelation {
        std::unordered_map<std::string, std::unordered_map<std::string, T2&>> a_to_b;
        std::unordered_map<std::string, std::unordered_map<std::string, T1&>> b_to_a;
    public:
        struct Payload {
            T1& a;
            T2& b;
        };

        void create(Payload payload) {
            a_to_b[payload.a.name].insert({payload.b.name, payload.b});
            b_to_a[payload.b.name].insert({payload.a.name, payload.a});
        }

        void remove(Payload payload) {
            auto mob_map = a_to_b[payload.a.name];
            mob_map.erase(payload.b.name);

            auto mesh_map = b_to_a[payload.b.name];
            mesh_map.erase(payload.a.name);

            if(mob_map.empty()) {
                a_to_b.erase(payload.a.name);
            }

            if(mesh_map.empty()) {
                b_to_a.erase(payload.b.name);
            }
        }

        static void testRelations();
    };
}

#endif

#include <cassert>
#include "Mesh.hpp"
#include "Mobile.hpp"

template<> void Swarmies::TRelation<Swarmies::Mesh, Swarmies::Mobile>::testRelations() {

    auto meshMobRelation = Swarmies::TRelation<Swarmies::Mesh, Swarmies::Mobile>();

    // test that our relations tables are empty
    assert(meshMobRelation.a_to_b.empty());
    assert(meshMobRelation.b_to_a.empty());

    Swarmies::Mesh mesh {"mesh1"};
    Swarmies::Mesh mesh2 {"mesh2"};
    Swarmies::Mobile mobile {"mob1"};

    meshMobRelation.create({mesh, mobile});

    // our relation created an entry
    assert(meshMobRelation.a_to_b.size() == 1);
    assert(meshMobRelation.b_to_a.size() == 1);

    meshMobRelation.remove({mesh, mobile});

    // remove acted on both tables
    assert(meshMobRelation.a_to_b.empty());
    assert(meshMobRelation.b_to_a.empty());

    meshMobRelation.create({mesh, mobile});
    meshMobRelation.create({mesh2, mobile});


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