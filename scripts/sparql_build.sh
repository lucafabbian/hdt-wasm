#!/bin/bash
cd "$(dirname "$0")"

cd ..

export PKG_CONFIG_PATH="`realpath deps_compiled/pkgs`"
mkdir -p dist/sparql
cd dist/sparql
em++ ../../src/sparql.cpp -O3 `pkg-config --libs --static --cflags zlib serd-0 hdt cds` -fexceptions \
   -sWASM=1  -sEXPORTED_RUNTIME_METHODS='["FS","cwrap","ccall"]' -sALLOW_MEMORY_GROWTH  -sNO_DISABLE_EXCEPTION_CATCHING\
   -sFORCE_FILESYSTEM=1
