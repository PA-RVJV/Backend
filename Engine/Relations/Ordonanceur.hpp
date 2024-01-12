//
// Created by ivo on 22/12/2023.
//

#ifndef SOLUTIONSWARMIES_ORDONANCEUR_HPP
#define SOLUTIONSWARMIES_ORDONANCEUR_HPP

#include <array>
#include <vector>

#include "TRepository.hpp"
#include "Payload.hpp"
#include "TSemantiqueRelation.hpp"

template <typename Derived>
concept IsDerivedFromRepository = std::is_base_of<Engine::RepositoryBase, Derived>::value;

namespace Engine {

#if SWARMIES_TESTING
    void test_ordonnanceur_works();
#endif

    /**
     * La classe qui gere tous les repos, les liens
     * entre eux et la semantique de la mutation desdits
     */
    class Ordonnanceur {

    private:
        std::vector<RepositoryBase> repos;
        std::vector<RelationBase> relations;
        std::vector<SemantiqueRelationBase> semantiques;

    public:
        /**
         * Ajoute un repo a la base
         * todo: ca serait bien d'avoir une version constexpr
         *       vu que ca va pas changer au cours de l'exécution
         *       du programme
         */
        void addRepo(RepositoryBase && repo) {
            repos.push_back(repo);
        }

        /**
         * Donne la possibilité de créer des relations entre deux repos
         * todo: meme remarque qu'au dessus
         */
        template <IsDerivedFromRepository T1, IsDerivedFromRepository T2>
        void addRelation(T1 & r1, T2 & r2) {
            relations.push_back(TRelation<T1, T2>());
        }

        template <class TRepository, typename T2>
        void createLink(const Engine::LinkPayload<TRepository, T2> & payload) {
            addRelations(payload);
            addTags(payload);
        }

        template <typename T1, typename T2>
        void removeLink(const Engine::LinkPayload<T1, T2> & payload) {
            removeRelations(payload);
            removeTags(payload);
        }

        template <typename T1, typename T2>
        inline void addTags(const Engine::LinkPayload<T1, T2> & payload) {
            //if(payload.tags_a) a_tags[payload.a.name] = payload.tags_a;
            //if(payload.tags_b) b_tags[payload.b.name] = payload.tags_b;
        }

        template <typename T1, typename T2>
        inline void removeTags(const Engine::LinkPayload<T1, T2> & payload) {
            //a_tags.erase(payload.a.name);
            //b_tags.erase(payload.b.name);
        }

    public:


    };
}

#endif //SOLUTIONSWARMIES_ORDONANCEUR_HPP
