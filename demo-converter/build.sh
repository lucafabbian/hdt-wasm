#!/bin/bash
cd "$(dirname "$0")"

bash ../libs/build.sh  # build HDT-cpp first

echo "Building converter demo..."
export PKG_CONFIG_PATH="`realpath ../libs/deps_compiled/pkgs`"
mkdir -p dist
cd dist
em++ ../converter.cpp -O3 `pkg-config --libs --static --cflags zlib serd-0 hdt cds` -fexceptions \
   -sWASM=1  -sEXPORTED_RUNTIME_METHODS='["FS","cwrap","ccall"]' -sALLOW_MEMORY_GROWTH \
   -sFORCE_FILESYSTEM=1
