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
            T1 a;
            T2 b;
        };

        void create(Payload payload) {
            auto mob_map = a_to_b[payload.a.name];
            auto mesh_map = b_to_a[payload.b.name];
            mob_map.insert({payload.b.name, payload.b});
            mesh_map.insert({payload.a.name, payload.a});
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

template<typename T1, typename T2>
void Swarmies::TRelation<T1, T2>::testRelations() {
    auto meshMobRelation = Swarmies::TRelation<T1, T2>();

    assert(meshMobRelation.a_to_b.empty());
    assert(meshMobRelation.b_to_a.empty());

    Swarmies::Mesh mesh {"mesh"};
    Swarmies::Mobile mobile {"mob"};

    meshMobRelation.create({mesh, mobile});

    assert(meshMobRelation.a_to_b.size() == 1);
    assert(meshMobRelation.b_to_a.size() == 1);

    meshMobRelation.remove({mesh, mobile});

    assert(meshMobRelation.a_to_b.empty());
    assert(meshMobRelation.b_to_a.empty());

    std::cout << "Relations work" << std::endl;
}