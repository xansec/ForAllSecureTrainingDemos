#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
// ^ Don't go look these up; in this excercise, you're supposed to
// re-create the definitions you need in order to compile something
// like the below.

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int status;
    const char *msg;

    // Ignore this. It's just a bad excuse for why the llua_simple
    // binary isn't already a harness by itself.
    uint32_t hash = 5381;
    unsigned char *str = argc < 2 ? "" : argv[1];
    uint32_t c;
    while ((c = *str++))
      hash = ((hash << 5) + hash) + c;
    if(hash != 0x94513dbb) {
        fprintf(stderr, "create a harness for me!\n");
        return 1;
    }

    //
    // Assume that we're at a annoying-to-reach point in the middle of
    // a large program that is not naturally a harness.
    //
    // You want to re-write the below code to be on its own, to create
    // a harness on the luaL_newstate() / luaL_loadfile() / lua_pcall()
    // sequence of function calls.
    //

    lua_State *L = llual_newstate(); // Note: You don't need to care what lua_State is.
                                     // This code only uses pointers to lua_State, and
                                     // all pointers are the same, so "void *" is as
                                     // good as "lua_State *"

    status = llual_loadfilex(L, argv[1], 0); // Use your fuzz file here.
    if(status) {
        // When writing harnesses, feel free to just use abort() for any fail
        // cases that you don't think you'll actually run into (like this one).
        msg = lua_tolstring(L, -1, NULL);
        fputs(msg ? msg : "failed to load file\n", stderr);
        return 1;
    }

    status = lua_pcallk(L, 0, -1, 0, 0, NULL); // LUA_MULTRET is -1
    msg = lua_tolstring(L, -1, NULL);
    puts(msg ? msg : "nil");
    lua_close(L);
    return 0;
}
