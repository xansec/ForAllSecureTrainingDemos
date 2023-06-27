// compile with: cc solution.c libllua.so -o solution
// test with: ./solution ./seed

#include <stdlib.h>
#include <stdio.h>

void *llual_newstate();
int llual_loadfilex(void *, char *, int);
int lua_pcallk(void *, int, int, int, int, int);
long lua_tolstring(void *, int, int);

int main(int argc, char *argv[]) {
    void *luastate = llual_newstate();

    if(argc < 2 || llual_loadfilex(luastate, argv[1], 0)) {
        puts("fail");
        abort();
    }

    lua_pcallk(luastate, 0, -1, 0, 0, 0);
    char *s = (char *)lua_tolstring(luastate, -1, 0);
    puts(s ? s : "nil");
    return 0;
}
