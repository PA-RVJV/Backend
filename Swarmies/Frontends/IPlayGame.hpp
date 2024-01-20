//
// C'est l'interface que toutes les "glues"
// doivent implémenter pour interagir avec
// le jeu
//

#ifndef SWARMIES_IPLAYGAME_HPP
#define SWARMIES_IPLAYGAME_HPP

#include <vector>
#include "../BusinessObjects/Geometry/Mesh.hpp"

class IPlayGame {
    virtual Swarmies::Mesh& LoadMesh(const char* name) = 0;
    virtual void LoadLevel(const char* name) = 0;
    virtual int MeshVertexCount(const char* name) = 0;
    virtual int MeshNormalsCount(const char* name) = 0;
    virtual int MeshUVCount(const char* name) = 0;
    virtual int MeshTrianglesCount(const char* name) = 0;

};

#endif //SWARMIES_IPLAYGAME_HPP
