//
// Created by ivo on 02/01/2024.
//


#if SWARMIES_TESTING

#include <cassert>
#include <iostream>

#include "TRepository.hpp"

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