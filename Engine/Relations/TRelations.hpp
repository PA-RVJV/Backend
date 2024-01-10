//
// Created by ivo on 01/11/2023.
//
#ifndef SWARMIES_TRELATIONS_HPP
#define SWARMIES_TRELATIONS_HPP

#include <unordered_map>

namespace Engine {

    // ne sert que a typer le vecteur dans l'ordonnanceur
    class RelationBase {};

    /**
     * Soient deux entités A et B, contient toutes les relations entre a's et b's
     * @tparam T1
     * @tparam T2
     */
    template<typename T1, typename T2>
    class TRelation: RelationBase {
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

#endif // SWARMIES_TRELATIONS_HPP
