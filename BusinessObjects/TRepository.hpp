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
        std::unordered_map<std::string, const T> map;

    public:
        const T& add(const std::string &&name, T && object) {
            map.emplace(name, std::move(object));

            return map.at(name);
        }

        void remove(const std::string & name) {
            map.erase(name);
        }

        const T & get(const std::string & name) {
            return map.at(name);
        }

        [[nodiscard]] int _capacity() const {
            return map.size();
        }
    };
}

#endif //SWARMIES_TREPOSITORY_HPP

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
    auto f = repo.add(
            "toto", Foo{"toto"}
            );

    assert(f.name == "toto" && "foo name must be foo");
    puts("ok1");

    auto& foo2= repo.get("toto");

    assert(foo2.name == "toto" && "foo name must be foo");
    puts("ok2");

    repo.remove("toto");
    assert(repo._capacity() == 0 && "Repo should be empty");

    std::cout << "Repo works" << std::endl;
}
