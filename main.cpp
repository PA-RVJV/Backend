#include <iostream>

#include "tests.hpp"

#include "BusinessObjects/TRepository.tpp"
#include "BusinessObjects/Mesh.hpp"
#include "BusinessObjects/Mobile.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

#ifndef NDEBUG
    // always run tests before launch the game in dev mode
    test();
#endif

    auto meshes = Swarmies::TRepository<Swarmies::Mesh>();
    auto mobiles = Swarmies::TRepository<Swarmies::Mobile>();

    return 0;
}
