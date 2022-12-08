#!/bin/bash
cd "$(dirname "$0")"

cd ..

export PKG_CONFIG_PATH="`realpath deps_compiled/pkgs`"
mkdir -p dist/converter
cd dist/converter
em++ ../../src/converter.cpp -O3 `pkg-config --libs --static --cflags zlib serd-0 hdt cds` -fexceptions \
   -sWASM=1  -sEXPORTED_RUNTIME_METHODS='["FS","cwrap","ccall"]' -sALLOW_MEMORY_GROWTH \
   -sFORCE_FILESYSTEM=1
