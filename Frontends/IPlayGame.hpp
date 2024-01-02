//
// Created by ivo on 01/11/2023.
// C'est l'interface que toutes les "glues"
// doivent implémenter pour interagir avec
// le jeu
//

#ifndef SWARMIES_IPLAYGAME_HPP
#define SWARMIES_IPLAYGAME_HPP

struct VertexWrapper { // this is just so you
    float vtx[3];
};

class IPlayGame {
    virtual void LoadMesh(const char* name, struct VertexWrapper *vw) = 0;
    virtual void LoadLevel(const char* name) = 0;
};

#endif //SWARMIES_IPLAYGAME_HPP
