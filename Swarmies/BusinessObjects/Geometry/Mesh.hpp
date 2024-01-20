//
// Created by ivo on 01/11/2023.
//

#ifndef SWARMIES_MESH_HPP
#define SWARMIES_MESH_HPP

#include <string>
#include <vector>
#include <array>

#include <cstddef>

struct VertexWrapper  {
    float abscisse;
    float ordonnee;
    float prof;
};

namespace Swarmies {
    struct Mesh {
        Mesh(std::string &&name, auto vertices, auto normals, auto triangles, auto meshes) noexcept;

        const std::string name;
        std::vector<struct VertexWrapper> vertices;
        std::vector<struct VertexWrapper> normals;
        std::vector<struct VertexWrapper> texture;
        std::vector<std::array<std::array<int, 3>, 3>> faces;


        explicit Mesh(std::string && name) noexcept;
        //Mesh(std::string && name, typeof(vertices) vertices, typeof(normals) normals, typeof(triangles) triangles) noexcept;
        Mesh& operator = (Mesh &&) noexcept;

        [[nodiscard]] int vertice_count() const;
        [[nodiscard]] int normals_count() const;
        [[nodiscard]] int texture_count() const;
        [[nodiscard]] int triangles_count() const;

        struct triangles_iterator {
            explicit triangles_iterator(decltype(Mesh::faces) & faces): faces(faces), _current_face(0), _current_vertex(0) {}
        private:
            int _current_face;
            int _current_vertex;
            decltype(Mesh::faces) & faces;
        public:
            bool operator!=(const triangles_iterator & other) const {
                return _current_face != other._current_face || _current_vertex != other._current_vertex;
            }

            int operator*() {
                return faces[_current_face][_current_vertex][0]; /// f 5/1/1 3/2/1 1/3/1
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
}

#if SWARMIES_TESTING
void testMeshLoads(const char * path);
#endif

#endif //SWARMIES_MESH_HPP
