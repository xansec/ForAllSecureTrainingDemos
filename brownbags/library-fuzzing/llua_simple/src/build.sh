#!/bin/sh
set -xe
cd "`dirname "$0"`"
docker run --rm `docker build -q .` tar -cz libllua.so llua_simple | tar -xz
