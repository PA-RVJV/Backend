//
// Created by ivo on 01/11/2023.
//

#include <iostream>

#include "Mesh.hpp"

namespace Swarmies {
//    Mesh::~Mesh() {
//        std::cout << "Mesh destroyed " << name << '\n';
//    }
    Mesh::Mesh(std::string && name) noexcept: name(name), triangles_iterator(faces, vertices) {}

    int Mesh::vertice_count() const {return static_cast<int>(vertices.size()); }
    int Mesh::normals_count() const {return static_cast<int>(vertices.size()); }
    int Mesh::texture_count() const {return static_cast<int>(uvs.size()); }
    int Mesh::triangles_count() const {return static_cast<int>(std::size(triangles_iterator)); }

    Mesh::Mesh(Mesh && other) noexcept
    : name(other.name)
    , vertices_pos(std::move(other.vertices_pos))
    , normals(std::move(other.normals))
    , uvs(std::move(other.uvs)), faces(std::move(other.faces))
    , vertices(std::move(other.vertices)), triangles_iterator(faces, vertices){}

    Mesh &Mesh::operator=(Mesh && o) noexcept {
        if(this != &o) {
            vertices_pos = std::move(o.vertices_pos);
            normals = std::move(o.normals);
            uvs = std::move(o.uvs);
            faces = std::move(o.faces);
            vertices = std::move(o.vertices);
        }
        return *this;
    }

    Mesh::Mesh(
            std::string &&name,
            auto vertices_pos, auto normals, auto uvs,
            auto faces, auto vertices) noexcept
        :
        name(name), vertices_pos(std::move(vertices_pos)), normals(std::move(normals)), uvs(std::move(uvs))
        , faces(std::move(faces)), vertices(std::move(vertices))
        , triangles_iterator(this->faces, this->vertices)
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
        char name[256] = {0};

        while (std::fgets(buf, sizeof buf, file) != nullptr) {

            if(buf[0] == 'v') {
                struct VertexWrapper vw{0, 0, 0};
                switch (buf[1]) {
                    case ' ':
                        sscanf(buf, "v %f %f %f\n", &vw.abscisse, &vw.ordonnee, &vw.prof);
                        old.vertices_pos.push_back(vw);
                        break;
                    case 'n':
                        sscanf(buf, "vn %f %f %f\n", &vw.abscisse, &vw.ordonnee, &vw.prof);
                        old.normals.push_back(vw);
                        break;
                    case 't':
                        sscanf(buf, "vt %f %f\n", &vw.abscisse, &vw.ordonnee);
                        old.uvs.push_back(vw);
                        break;
                }
            }
            else if(buf[0] == 'f') {
                auto a = std::array{std::array{0, 0, 0}, std::array{0, 0, 0}, std::array{0, 0, 0}};
                sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                       &a[0][0], &a[0][1], &a[0][2], &a[1][0], &a[1][1], &a[1][2], &a[2][0], &a[2][1], &a[2][2]);
                old.faces.push_back(a);
                for (int i = 0; i < 3; ++i) {
                    old.vertices[vert_hash(a[i][0], a[i][2])] = Vertex{a[i][0], a[i][2]};
                }
            }
            /// quand on a un fichier où la ligne courante lue contient notre nom
            /// ou alors un fichier où on passe de l'entete
            if(strlen(name) == 0) {
                if(buf[0] == 'o') {
                    sscanf(buf, "o %255[^\n]", name);
                    continue;
                }
            } else { /// if strlen(name) > 0
                int c;
                if((c = std::getc(file)) == 'o') {
                    std::ungetc('o', file);
                    break;
                }
                std::ungetc(c, file);
                /// si on tombe sur une ligne "o Bonhomme", quand on parse
                /// un mesh, on a fini de parser ce mesh
            }
        }

        return {name, old.vertices_pos, old.normals, old.uvs, old.faces, old.vertices};
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
    assert(loaded_mesh.vertices_pos.size() == 54);
    assert(loaded_mesh.normals.size() == 6);
    assert(loaded_mesh.uvs.size() == 14);
    assert(loaded_mesh.faces.size() == 50);
    assert(loaded_mesh.vertices.size() == 113);

    int i =0;
    for(auto f: loaded_mesh.triangles_iterator) {
        i = f;
    }

    assert(i ==96);
    puts("testMeshLoads ok");
}

#endif