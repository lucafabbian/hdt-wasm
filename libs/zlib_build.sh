#!/bin/bash
cd "$(dirname "$0")"

cd ./deps_src/zlib

emconfigure ./configure
emmake make CPPFLAGS+="-fexceptions" LDFLAGS="-all-static"




mkdir -p ../../deps_compiled/libs/
mkdir -p ../../deps_compiled/pkgs/
cp libz.a ../../deps_compiled/libs/



# Generate pkg-config manifest
cd ../../
echo "prefix=`realpath .`" > ./deps_compiled/pkgs/zlib.pc

echo 'exec_prefix=${prefix}
libdir=${exec_prefix}/deps_compiled/libs
includedir=${prefix}/deps_src/zlib

Name: zlib
Description: zlib compression library
Version: 1.2.13

Requires:
Libs: -L${libdir} -l:libz.a
Cflags: -I${includedir}' >>  ./deps_compiled/pkgs/zlib.pc

