//
// Created by ivo on 01/11/2023.
//

#ifndef SWARMIES_MESH_HPP
#define SWARMIES_MESH_HPP

#include <string>
#include <vector>
#include <array>
#include <map>

#include <cstddef>
#include <cassert>

typedef int VertexHash;
template <typename T>
concept IsHashInt = std::is_same_v<T, VertexHash>;

struct VertexWrapper  {
    float abscisse;
    float ordonnee;
    float prof;
};

struct Vertex {
    int coordinates_ref;
    int normal_ref;
};

namespace Swarmies {
    static inline VertexHash vert_hash(int vert_pos, int norm_idx) {
        assert(vert_pos < (1 << 16));
        assert(norm_idx < (1 << 16));
        return ((vert_pos & ((1 << 16) - 1)) << 16) + (norm_idx & ((1 << 16) - 1));
    }

    /**
     * Stores vertex coordinates
     * vertex normals
     * map of vertices coordinates/normals couples
     * array of faces pointing to these
     */
    struct Mesh {
        Mesh(std::string &&name, auto vertices_pos, auto normals, auto uvs, auto faces, auto vertices) noexcept;

        const std::string name;
        std::vector<struct VertexWrapper> vertices_pos;
        std::vector<struct VertexWrapper> normals;
        std::vector<struct VertexWrapper> uvs;
        std::vector<std::array<std::array<int, 3>, 3>> faces;
        std::map<VertexHash, Vertex> vertices;


        explicit Mesh(std::string && name) noexcept;
        //Mesh(std::string && name, typeof(vertices) vertices, typeof(normals) normals, typeof(triangles) triangles) noexcept;
        Mesh& operator = (Mesh &&) noexcept;

        [[nodiscard]] int vertice_count() const;
        [[nodiscard]] int normals_count() const;
        [[nodiscard]] int texture_count() const;
        [[nodiscard]] int triangles_count() const;

        struct triangles_iterator {
            explicit triangles_iterator(decltype(Mesh::faces) & faces, decltype(Mesh::vertices) & verts): faces(faces), verts(verts), _current_face(0), _current_vertex(0) {}
        private:
            int _current_face;
            int _current_vertex;
            decltype(Mesh::faces) & faces;
            decltype(Mesh::vertices) & verts;
        public:
            bool operator!=(const triangles_iterator & other) const {
                return _current_face != other._current_face || _current_vertex != other._current_vertex;
            }

            int operator*() {
                int hash = vert_hash(faces[_current_face][_current_vertex][0], faces[_current_face][_current_vertex][2]);
                /// f 5/1/1 3/2/1 1/3/1
                auto it = verts.find(hash);
                int index = std::distance(verts.begin(), it);

                return index;
            }

            triangles_iterator & operator++() {
                if(_current_vertex < 2) {
                    _current_vertex++;
                } else {
                    _current_vertex = 0;
                    _current_face++;
                }

                return *this;
            }

            triangles_iterator begin() {
                return *this;
            }

            triangles_iterator end() {
                triangles_iterator iter = *this;
                iter._current_face = static_cast<int>(faces.size());
                iter._current_vertex = 0;
                return iter;
            }

            [[nodiscard]] std::size_t size() const {
                return faces.size() * 3;
            }
        } triangles_iterator;

    };

    Swarmies::Mesh LoadMesh(std::FILE * file, Swarmies::Mesh && old);

    /**
     * pack un couplet vertex pos vertex normal en un seul nombre de 32 bits
     * les deux parties etant tronquées a 16 bits. On part du principe
     * qu'un mesh aura en dessous de ~65000 sommets
     */
}

#if SWARMIES_TESTING
void testMeshLoads(const char * path);
#endif

#endif //SWARMIES_MESH_HPP
