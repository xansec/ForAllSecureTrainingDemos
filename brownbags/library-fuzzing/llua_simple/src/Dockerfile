FROM debian:jessie-slim

RUN apt-get -y update && apt-get -y install build-essential

WORKDIR /root
COPY lua-5.3.5.tar.gz ./

# Screw with some names, enable shared library build.
RUN tar -xf lua-5.3.5.tar.gz && \
    find ./lua-5.3.5/src -name '*.[ch]' -print0 | xargs -0 sed -i -e 's/luaL_/llual_/g' && \
    sed -i -e 's/^ALL_T.*$/\0 libllua.so/' lua-5.3.5/src/Makefile && \
    echo 'libllua.so: $(BASE_O)' >> lua-5.3.5/src/Makefile && \
    echo '	$(CC) -o $@ $(LDFLAGS) -shared $^ $(LIBS)' >> lua-5.3.5/src/Makefile && \
    make -C lua-5.3.5 generic MYCFLAGS=-fPIC && \
    mv lua-5.3.5/src/libllua.so . && \
    strip libllua.so && \
    make -C lua-5.3.5 clean

COPY llua_simple.c ./
RUN gcc llua_simple.c -I./lua-5.3.5/src ./libllua.so -o llua_simple && strip llua_simple
RUN echo 'return "Hello World"' > test.lua && \
    test "`./llua_simple test.lua 2>&1`" = "create a harness for me!" && \
    mv test.lua secret.lua && \
    test "`./llua_simple secret.lua 2>&1`" = "Hello World" && \
    rm secret.lua
