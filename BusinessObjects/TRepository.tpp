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
        std::unordered_map<std::string, T> map;

    public:
        T& add(const std::string &name, T && object) {
            map[name] = object; // std::move

            return map[name];
        }

        void remove(const std::string & name) {
            map.erase(name);
        }

        T & get(const std::string & name) {
            return map[name];
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
    } foo {"foo"};

    auto repo = Swarmies::TRepository<Foo>();
    auto &f = repo.add(foo.name, std::move(foo));
    assert(f.name == "foo" && "foo name must be foo");

    auto &foo2 = repo.get("foo");

    assert(foo2.name == "foo" && "foo name must be foo");

    std::cout << "Repo works" << std::endl;
}
