//
// Created by ivo on 01/11/2023.
//

#ifndef SWARMIES_TREPOSITORY_HPP
#define SWARMIES_TREPOSITORY_HPP

#include <string>
#include <unordered_map>

namespace Swarmies {

    template<typename T>
    class TRepository {
        std::unordered_map<std::string, T> map; // pas <std::string, const T>,
        // on essayera plus tard avec un repo immutable + systeme de reducteurs
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

        auto _size() const {
            return map.size();
        }
    };
}

#endif //SWARMIES_TREPOSITORY_HPP

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

    auto repo = Swarmies::TRepository<Foo>();
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
