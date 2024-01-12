//
// Created by ivo on 01/11/2023.
//

#ifndef SWARMIES_TREPOSITORY_HPP
#define SWARMIES_TREPOSITORY_HPP

#include <string>
#include <unordered_map>

#if SWARMIES_TESTING
void testRepoWorks();
#endif

namespace Engine {

    // Cette classe ne sert que pour pouvoir déclarer un conteneur
    // de repository, eg std::vector<TRepository<RepositoryBase>>
    // car on ne peut pas déclarer un std::vector<TRepository>
    class RepositoryBase {};

    template<typename T>
    class TRepository: RepositoryBase {
        std::unordered_map<std::string, T> map; // pas <std::string, const T>,
        // on essayera plus tard avec un repo immutable + système de reducteurs
        // voir les perf que ca donne

    public:
        const T& add(const std::string &&name, T && object) {
            map.emplace(name, object);

            return map.at(name);
        }

        void remove(const std::string & name) {
            map.erase(name);
        }

        const T & get(const std::string & name) {
            return map.at(name);
        }

        [[nodiscard]] size_t _size() const {
            return map.size();
        }
    };
}

#endif //SWARMIES_TREPOSITORY_HPP
