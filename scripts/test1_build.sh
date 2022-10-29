#!/bin/bash
cd "$(dirname "$0")"

cd ..

export PKG_CONFIG_PATH="`realpath deps_compiled/pkgs`"
mkdir -p dist/test1
cd dist/test1
em++ ../../src/test1.cpp -O3 `pkg-config --libs --static --cflags zlib serd-0 hdt cds` -fexceptions \
   -sWASM=1 -sEXPORTED_RUNTIME_METHODS='["cwrap","ccall"]' -sALLOW_MEMORY_GROWTH  -sNO_DISABLE_EXCEPTION_CATCHING\
   -sFORCE_FILESYSTEM=1
