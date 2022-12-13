#!/bin/bash
cd "$(dirname "$0")"
export CPATH="$CPATH:$PWD/deps_src/zlib"


cd ./deps_src/hdt-cpp
emmake make CPPFLAGS+="-fexceptions" LDFLAGS="-all-static"


mkdir -p ../../deps_compiled/libs/
cp libhdt/.libs/libhdt.a ../../deps_compiled/libs/
cp libcds/.libs/libcds.a ../../deps_compiled/libs/
