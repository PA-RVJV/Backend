//
// Created by ivo on 22/12/2023.
//

#ifndef SOLUTIONSWARMIES_ORDONANCEUR_HPP
#define SOLUTIONSWARMIES_ORDONANCEUR_HPP

#include <array>

#include "TRepository.hpp"

namespace Swarmies {

    template<int NbRepos>
    class Ordonanceur {

    private:
        std::array<Swarmies::TRepository> repos;

    };

} // Swarmies

#endif //SOLUTIONSWARMIES_ORDONANCEUR_HPP
