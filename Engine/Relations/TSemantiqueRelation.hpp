//
// Created by ivo on 22/12/2023.
//

#ifndef SOLUTIONSWARMIES_TSEMANTIQUERELATION_HPP
#define SOLUTIONSWARMIES_TSEMANTIQUERELATION_HPP

#include <unordered_map>
#include <string>

namespace Engine {

    // ne sert que à typer le vecteur dans l'ordonnanceur
    struct SemantiqueRelationBase {};

    struct SemantiqueRelation {
        enum Kind {
            NO_TAG = 0,
            FATHER = 1 << 0,    // set itself as "parent" of a relation, will impact cascading on delete
            SOLITARY = 1 << 1,  // will not accept other siblings after it
            CUCKOO = 1 << 2 | SOLITARY,    // like solitary but will also delete existing siblings on arrival
            CASCADE = 1 << 3 | FATHER,   // on delete, delete other descendant siblings
            SET_NULL = 1 << 4,  // on delete, keep relation but mark other end to itself as null
            ENUM_SIZE = 6,  // the number of relevant items in this enum
        };
    };

    template<typename TEnt, SemantiqueRelation::Kind Trel=SemantiqueRelation::Kind::NO_TAG>
    class TSemantiqueRelation: SemantiqueRelationBase {
    public:
        std::unordered_map<std::string, SemantiqueRelation::Kind> tags;
#if SWARMIES_TESTING
        static void testSemantique();
#endif
    };
}

#endif //SOLUTIONSWARMIES_TSEMANTIQUERELATION_HPP
