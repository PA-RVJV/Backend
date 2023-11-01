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
        void add(const std::string &name, T && object) {
            map[name] = std::move(object);
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
    } foo {"foo"};
    auto repo = Swarmies::TRepository<Foo>();
    repo.add(foo.name, std::move(foo));

    auto foo2 = repo.get("foo");

    assert(foo2.name == "foo" && "foo name must be foo");

    std::cout << "Repo works" << std::endl;
}
