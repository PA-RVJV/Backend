//
// Created by ivo on 01/11/2023.
//

#include <iostream>

#include "Mesh.hpp"

namespace Swarmies {
//    Mesh::~Mesh() {
//        std::cout << "Mesh destroyed " << name << '\n';
//    }
    Mesh::Mesh(std::string && name) noexcept: name(name), triangles_iterator(faces) {}

    int Mesh::vertice_count() const {return static_cast<int>(vertices.size()); }
    int Mesh::normals_count() const {return static_cast<int>(normals.size()); }
    int Mesh::texture_count() const {return static_cast<int>(texture.size()); }
    int Mesh::triangles_count() const {return static_cast<int>(std::size(triangles_iterator)); }

    Mesh &Mesh::operator=(Mesh && o) noexcept {
        if(this != &o) {
            vertices = std::move(o.vertices);
            normals = std::move(o.normals);
            texture = std::move(o.texture);
            faces = std::move(o.faces);
        }
        return *this;
    }

    Mesh::Mesh(
            std::string &&name,
            auto vertices, auto normals, auto triangles,
            auto faces) noexcept
        : vertices(std::move(vertices)), normals(std::move(normals))
        , faces(std::move(faces)), triangles_iterator(this->faces)
        {}

    /**
     * Charge un mesh depuis un fichier .obj dans un format utilisable
     * par Unity (meme principe que Assimp)
     */
    Swarmies::Mesh LoadMesh(
            std::FILE * file,
            Swarmies::Mesh && old
    ) {
        char buf[256];

        while (std::fgets(buf, sizeof buf, file) != nullptr) {

            if(buf[0] == 'v') { // skip ce qui commence pas par v
                goto vertex;
            }
            else if(buf[0] == 'f') {
                goto face;
            }
            continue;

            vertex: {
                struct VertexWrapper vw{0, 0, 0};
                switch (buf[1]) {
                    case ' ':
                        sscanf(buf, "v %f %f %f\n", &vw.abscisse, &vw.ordonnee, &vw.prof);
                        old.vertices.push_back(vw);
                        break;
                    case 'n':
                        sscanf(buf, "vn %f %f %f\n", &vw.abscisse, &vw.ordonnee, &vw.prof);
                        old.normals.push_back(vw);
                        break;
                    case 't':
                        sscanf(buf, "vt %f %f\n", &vw.abscisse, &vw.ordonnee);
                        old.texture.push_back(vw);
                        break;
                }
            }
            continue;
            face: {
                auto a = std::array{std::array{0, 0, 0}, std::array{0, 0, 0}, std::array{0, 0, 0}};
                sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                       &a[0][0], &a[0][1], &a[0][2], &a[1][0], &a[1][1], &a[1][2], &a[2][0], &a[2][1], &a[2][2]);
                old.faces.push_back(a);
            };
            continue;
        }

        return {old.name.c_str(), old.vertices, old.normals, old.texture, old.faces};
    }
}

#if SWARMIES_TESTING
#include <cassert>
void testMeshLoads(const char * path) {
    std::FILE * file = std::fopen(path, "rb");

    if(file == nullptr) {
        std::cerr << (std::string("Can't open ") + path + ".").c_str();
        assert(0 && "Can't open asset file");
    }

    auto loaded_mesh = Swarmies::LoadMesh(file, Swarmies::Mesh("foo"));
    assert(!loaded_mesh.faces.empty());
    assert(loaded_mesh.faces.size() == 100);

    int i =0;
    for(auto f: loaded_mesh.triangles_iterator) {
        i = f;
    }

    assert(i ==52);
    puts("testMeshLoads ok");
}

#endif