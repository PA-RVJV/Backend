//
// Created by ivo on 27/10/2023.
// Stores the current geometry of the level
// Can be used for display it
// Or provide data for pathfinding
// We represent the world as a N dimension matrix
// of lines/squares/cubes which hold a pointer to arrays
// of vertices existing in them
//

#include "Geometry.hpp"
#include "Mesh.hpp"
#include "../../Frontends/IPlayGame.hpp"

#include <cstdio>
#include <cfloat>
#include <vector>

#ifndef NDEBUG
#include <cassert>
#endif

/**
 * A partir d'un descripteur de fichier, le parse
 * comme un fichier .obj et en calcule les extrema
 */
void FindExtremafromObj(
        std::FILE * file,
        float * movmin, float * movmax,
        float * depthmin, float * depthmax,
        float * elevmin, float * elevmax
) {
    char buf[256];

    *movmin = FLT_MAX;
    *depthmin = FLT_MAX;
    *elevmin = FLT_MAX;
    *movmax = -FLT_MAX;
    *depthmax = -FLT_MAX;
    *elevmax = -FLT_MAX;

    float mov = 0;
    float depth = 0;
    float elev = 0;

    while (std::fgets(buf, sizeof buf, file) != nullptr) {
        
        if(buf[1] == 'n') { // a vn on arrete
            break;
        }
        
        if(buf[0] != 'v') { // skip ce qui commence pas par v
            continue;
        }
        
        sscanf(buf, "v %f %f %f\n", &mov, &elev, &depth);

        if(mov < *movmin) { *movmin = mov; }
        if(mov > *movmax) { *movmax = mov; }
        if(elev < *elevmin) { *elevmin = elev; }
        if(elev > *elevmax) { *elevmax = elev; }
        if(depth < *depthmin) { *depthmin = depth; }
        if(depth > *depthmax) { *depthmax = depth; }

        printf("%f %f %f\n", mov, depth, elev);
    }

    printf("mmin mmax dmin dmax emin emax %f %f %f %f %f %f\n",
           *movmin, *movmax, *depthmin, *depthmax, *elevmin, *elevmax
           );
}

/**
 * Charge un mesh depuis un fichier .obj dans un format utilisable
 * par Unity (meme principe que Assimp)
 */
void LoadMesh(
        std::FILE * file,
        Swarmies::Mesh * mesh
) {
    char buf[256];

    float mov = 0;
    float depth = 0;
    float elev = 0;

    while (std::fgets(buf, sizeof buf, file) != nullptr) {

        if(buf[1] == 'n') { // a vn on arrete
            break;
        }

        if(buf[0] != 'v') { // skip ce qui commence pas par v
            continue;
        }

        sscanf(buf, "v %f %f %f\n", &mov, &elev, &depth);

        struct VertexWrapper vw {mov, elev, depth};
        mesh->vertices.push_back(vw);
    }
}

#if SWARMIES_TESTING
#include <string>
void testFindExtremafromObj(const char * path) {

    std::FILE * file = std::fopen(path, "rb");
    
    if(file == nullptr) assert(0 && (std::string("Can't open ") + path + ".").c_str());

    float movmin, movmax, depthmin, depthmax, elevmin, elevmax;

    const auto FLOAT_EPSILON = FLT_EPSILON;

    FindExtremafromObj(file,
        &movmin, &movmax,
        &depthmin, &depthmax,
        &elevmin, &elevmax);

    assert(movmin == -3.233417f);
    assert(movmax == 2.898613f);
    assert(depthmin == -12.474690f);
    assert(depthmax == 1.f);
    assert(elevmin == -1.0000f);
    assert(elevmax == 2.378370f);

    assert(movmin + -3.233417 < FLOAT_EPSILON);
    assert(movmax - 2.898613 < FLOAT_EPSILON);
    assert(depthmin + -12.474690 < FLOAT_EPSILON);
    assert(depthmax - 1 < FLOAT_EPSILON);
    assert(elevmin + -1.0000 < FLOAT_EPSILON);
    assert(elevmax - 2.378370 < FLOAT_EPSILON);
}
#endif
