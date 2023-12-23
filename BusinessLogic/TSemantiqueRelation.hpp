//
// Created by ivo on 22/12/2023.
//

#ifndef SOLUTIONSWARMIES_TSEMANTIQUERELATION_HPP
#define SOLUTIONSWARMIES_TSEMANTIQUERELATION_HPP

#include <unordered_map>

namespace Swarmies {

    template<typename TEnt, typename Trel>
    class TSemantiqueRelation {
        std::unordered_map<std::string, std::unordered_map<std::string, TEnt&>> a_to_b;
    };
}



#endif //SOLUTIONSWARMIES_TSEMANTIQUERELATION_HPP
