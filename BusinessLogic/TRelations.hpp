//
// Created by ivo on 01/11/2023.
//
#ifndef SWARMIES_TRELATIONS_HPP
#define SWARMIES_TRELATIONS_HPP

#include <unordered_map>


namespace Swarmies {

    struct Relation {
        enum Tag {
            NO_TAG = 0,
            FATHER = 1 << 0,    // set itself as "parent" of a relation, will impact cascading on delete
            SOLITARY = 1 << 1,  // will not accept other siblings after it
            CUCKOO = 1 << 2 | SOLITARY,    // like solitary but will also delete existing siblings on arrival
            CASCADE = 1 << 3 | FATHER,   // on delete, delete other descendant siblings
            SET_NULL = 1 << 4,  // on delete, keep relation but mark other end to itself as null
            ENUM_SIZE = 6,  // the number of relevant items in this enum
        };
    };

    template<typename T1, typename T2>
    class TRelation {
        std::unordered_map<std::string, std::unordered_map<std::string, T2&>> a_to_b;
        std::unordered_map<std::string, std::unordered_map<std::string, T1&>> b_to_a;
        std::unordered_map<std::string, std::bitset<Relation::Tag::ENUM_SIZE>> a_tags;
        std::unordered_map<std::string, std::bitset<Relation::Tag::ENUM_SIZE>> b_tags;
    public:

        struct Payload {
            T1& a;
            T2& b;
            Relation::Tag tags_a;
            Relation::Tag tags_b;
        };

        void create(const Payload & payload) {
            addRelations(payload);
            addTags(payload);
        }
        
        inline void addRelations(const Payload & payload) {
            a_to_b[payload.a.name].insert({payload.b.name, payload.b});
            b_to_a[payload.b.name].insert({payload.a.name, payload.a});
        }
        
        inline void addTags(const Payload & payload) {
            if(payload.tags_a) a_tags[payload.a.name] = payload.tags_a;
            if(payload.tags_b) b_tags[payload.b.name] = payload.tags_b;
        }

        void remove(const Payload & payload) {
            removeRelations(payload);
            removeTags(payload);
        }

        inline void removeRelations(const Payload & payload) {
            auto a_map = a_to_b[payload.a.name];
            a_map.erase(payload.b.name);

            auto b_map = b_to_a[payload.b.name];
            b_map.erase(payload.a.name);

            if(a_map.empty()) {
                a_to_b.erase(payload.a.name);
            }

            if(b_map.empty()) {
                b_to_a.erase(payload.b.name);
            }
        }

        inline void removeTags(const Payload & payload) {
            a_tags.erase(payload.a.name);
            b_tags.erase(payload.b.name);
        }

        static void testRelations();
    };
}

#endif

#ifndef NDEBUG

#include <cassert>
#include "../BusinessObjects/Mesh.hpp"
#include "../BusinessObjects/Mobile.hpp"

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

    assert(meshMobRelation.a_tags.empty());
    assert(meshMobRelation.b_tags.empty());

    std::cout << "Relations work" << std::endl;
}

#endif
