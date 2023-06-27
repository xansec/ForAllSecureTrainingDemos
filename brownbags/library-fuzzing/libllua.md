## Lab: Harnessing Lua

To practice what you've just learned, try to harness `libllua.so` using the example set by the provided `llua_simple` binary. Specifically, harness the `llual_newstate()`, `llual_loadfilex()`, and `lua_pcallk()` sequence. `libllua.so` is a C library, so unfortunately you'll have to guess more about function argument types than if it were in C++.

You may look at the `llua_simple.c` source code, but if you have reverse engineering experience, try this exercise without it at first (and look only at the `llua_simple` and `libllua.so` binaries). Either way, **avoid** going online (or to `/usr/include`) to look for the Lua header files! For the sake of practice, we're pretending like `libllua.so` is a closed-source library with no headers or source available (spoiler: it's not).

There's no specific intended vulnerability for your resulting harness to be able to hit in this exercise; but, it should be able to get lots of coverage.
