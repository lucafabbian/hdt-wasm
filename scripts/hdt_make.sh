c#!/bin/bash
cd "$(dirname "$0")"

cd ../deps_src/hdt-cpp



emmake make LDFLAGS=-all-static


mkdir -p ../../deps_compiled/libs/
cp libhdt/.libs/libhdt.a ../../deps_compiled/libs/
cp libcds/.libs/libcds.a ../../deps_compiled/libs/
