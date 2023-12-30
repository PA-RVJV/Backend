//
// Created by ivo on 01/11/2023.
//

#ifndef SWARMIES_TREPOSITORY_HPP
#define SWARMIES_TREPOSITORY_HPP

#include <string>
#include <unordered_map>

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

#ifndef NDEBUG

#include <cassert>
#include <iostream>

void testRepoWorks() {
    struct Foo {
        std::string name;
        ~Foo() {
            std::cout << "destroy foo" << std::endl;
        }
    };

    auto repo = Engine::TRepository<Foo>();
    assert(repo._size() == 0);

    auto f = repo.add(
            "toto", Foo{"toto"}
            );
    assert(f.name == "toto" && "foo name must be foo");

    auto& foo2= repo.get("toto");
    assert(foo2.name == "toto" && "foo name must be foo");

    repo.remove("toto");
    assert(repo._size() == 0 && "Repo should be empty");

    std::cout << "Repo works" << std::endl;
}

#endif
#endif //SWARMIES_TREPOSITORY_HPP
