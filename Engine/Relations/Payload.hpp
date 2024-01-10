//
// Created by ivo on 28/12/2023.
//

#ifndef SOLUTIONSWARMIES_PAYLOAD_HPP
#define SOLUTIONSWARMIES_PAYLOAD_HPP

#include "TRelations.hpp"

namespace Engine {
/**
 * Demande de mutation de l'état du jeu de
 * type création/suppression de lien, faisant
 * intervenir deux types d'entités
 * @tparam T1
 * @tparam T2
 */
    template<typename T1, typename T2>
    struct LinkPayload {
        T1 &a;
        T2 &b;
        Engine::TRelation<T1, T2>::Type a_tags;
        Engine::TRelation<T1, T2>::Type b_tags;
    };

}
#endif //SOLUTIONSWARMIES_PAYLOAD_HPP
