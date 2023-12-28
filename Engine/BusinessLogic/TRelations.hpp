//
// Created by ivo on 01/11/2023.
//
#ifndef SWARMIES_TRELATIONS_HPP
#define SWARMIES_TRELATIONS_HPP

#include <unordered_map>

namespace Engine {

    /**
     * Soient deux entités A et B, contient toutes les relations entre a's et b's
     * @tparam T1
     * @tparam T2
     */
    template<typename T1, typename T2>
    class TRelation {
        std::unordered_map<std::string, std::unordered_map<std::string, T2&>> a_to_b;
        std::unordered_map<std::string, std::unordered_map<std::string, T1&>> b_to_a;
    public:

        inline void addRelations(T1 & a, T2 & b) {
            a_to_b[a.name].insert({b.name, b});
            b_to_a[b.name].insert({a.name, a});
        }

        inline void removeRelations(const T1 & a,  T2 & b) {
            auto a_map = a_to_b[a.name];
            a_map.erase(b.name);

            auto b_map = b_to_a[b.name];
            b_map.erase(a.name);

            if(a_map.empty()) {
                a_to_b.erase(a.name);
            }

            if(b_map.empty()) {
                b_to_a.erase(b.name);
            }
        }


        static void testRelations();
    };
}

#ifndef NDEBUG

#include <cassert>
#include "../../Swarmies/BusinessObjects/Mesh.hpp"
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
#endif // SWARMIES_TRELATIONS_HPP
