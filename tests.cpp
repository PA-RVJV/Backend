//
// Created by ivo on 01/11/2023.
//

#include <cstdio>
#include <filesystem>

#include "Engine/Relations/TRepository.hpp"
#include "Engine/Relations/TRelations.hpp"
#include "Engine/Relations/TSemantiqueRelation.hpp"
#include "Engine/Relations/Ordonanceur.hpp"

#include "Swarmies/BusinessObjects/Geometry/Mesh.hpp"
#include "Swarmies/BusinessObjects/Geometry/Geometry.hpp"
#include "Swarmies/BusinessObjects/Mobile.hpp"
#include "Engine/3d/AutodeskObjLoader.hpp"

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

static int MyCppFunction(lua_State* L) {
    const int num = lua_tonumber(L, 1);
    const char* string = lua_tostring(L, 2);

    printf("from lua %d %s\n", num, string);


    return 0;   // number of params passed to lua
}

int main(int argc, char * argv[]) {


#if SWARMIES_TESTING
    puts("\n*** START TESTING ***");
    printf("Test program name %s\n", argv[0]);

    std::filesystem::path path(argv[0]);

    testMeshLoads((path.parent_path().append("./Assets/test_topo.obj")).string().c_str());
    testFindExtremafromObj((path.parent_path().append("./Assets/test_topo.obj")).string().c_str());
    testRepoWorks();

    Engine::TRelation<Swarmies::Mesh, Swarmies::Mobile>::testRelations();
    Engine::TSemantiqueRelation<Swarmies::Mesh, Engine::SemantiqueRelation::Kind::NO_TAG>::testSemantique();
    
    Engine::test_ordonnanceur_works();

    testMultiMesh();

    puts("testing lua");

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "CPPMyCppFunction", MyCppFunction);

    int status = luaL_dofile(L, (path.parent_path().append("./Assets/LuaScripts/script.lua")).string().c_str());
    if(status == LUA_OK) {
        puts("lua file successfully exexuted");
    } else {
        puts("lua error");
    }

#else
    puts("\n*** Not in testing mode ***");
#endif
}
