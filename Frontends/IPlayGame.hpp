//
// Created by ivo on 01/11/2023.
// C'est l'interface que toutes les "glues"
// doivent implémenter pour interagir avec
// le jeu
//

#ifndef SWARMIES_IPLAYGAME_HPP
#define SWARMIES_IPLAYGAME_HPP

class IPlayGame {
    virtual void LoadMesh() = 0;
    virtual void LoadLevel() = 0;
};

#endif //SWARMIES_IPLAYGAME_HPP
