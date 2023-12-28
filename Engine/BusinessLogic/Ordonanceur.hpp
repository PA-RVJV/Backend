//
// Created by ivo on 22/12/2023.
//

#ifndef SOLUTIONSWARMIES_ORDONANCEUR_HPP
#define SOLUTIONSWARMIES_ORDONANCEUR_HPP

#include <array>

#include "TRepository.hpp"
#include "Payload.hpp"
#include "TSemantiqueRelation.hpp"

namespace Engine {

    template<typename RepositoryTypes, int NbRepos>
    class Ordonanceur {

    private:
        std::array<RepositoryTypes, NbRepos> repos;

        template<class T1>
        Engine::TSemantiqueRelation getTagRepo();

    public:
        template <typename T1, typename T2>
        void createLink(const Engine::LinkPayload<T1, T2> & payload) {
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
            if(payload.tags_a) a_tags[payload.a.name] = payload.tags_a;
            if(payload.tags_b) b_tags[payload.b.name] = payload.tags_b;
        }

        template <typename T1, typename T2>
        inline void removeTags(const Engine::LinkPayload<T1, T2> & payload) {
            a_tags.erase(payload.a.name);
            b_tags.erase(payload.b.name);
        }

    public:
        void demarrer(std::array<RepositoryTypes, NbRepos> repos);
    };

    template<typename RepositoryTypes, int NbRepos>
    Engine::TSemantiqueRelation Ordonanceur<RepositoryTypes, NbRepos>::getTagRepo() {
        return Engine::TSemantiqueRelation<>();
    }
}

template<typename RepositoryTypes, int NbRepos>
void Ordonanceur<typename RepositoryTypes, int NbRepos>::demarrer(std::array<RepositoryTypes, NbRepos> repos) {
    this->repos = repos;
}

#endif //SOLUTIONSWARMIES_ORDONANCEUR_HPP
