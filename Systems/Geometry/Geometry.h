//
// Created by ivo on 27/10/2023.
//

#ifndef SWARMIES_GEOMETRY_H
#define SWARMIES_GEOMETRY_H

#include <cstdio>


void FindExtremafromObj(
        std::FILE * file,
        float * xmin, float * xmax,
        float * ymin, float * ymax,
        float * zmin, float * zmax
        );

#ifndef NDEBUG
void testFindExtremafromObj(const char * path);
#endif

#endif //SWARMIES_GEOMETRY_H
