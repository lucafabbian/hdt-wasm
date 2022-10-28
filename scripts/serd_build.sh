#!/bin/bash
cd "$(dirname "$0")"

cd ../deps_src/serd


# Build serd files
mkdir -p out
emcc -c -I./include  'src/base64.c'      -o 'out/base64.o'                                               
emcc -c -I./include  'src/byte_source.c' -o 'out/byte_source.o'                                           
emcc -c -I./include  'src/env.c'         -o 'out/env.o'                                        
emcc -c -I./include  'src/n3.c'          -o 'out/n3.o'                                        
emcc -c -I./include  'src/node.c'        -o 'out/node.o'                                        
emcc -c -I./include  'src/reader.c'      -o 'out/reader.o'                                               
emcc -c -I./include  'src/string.c'      -o 'out/string.o'                                               
emcc -c -I./include  'src/system.c'      -o 'out/system.o'                                               
emcc -c -I./include  'src/uri.c'         -o 'out/uri.o'                                        
emcc -c -I./include  'src/writer.c'      -o 'out/writer.o'                                               

# Package them in a static lib
emar -s -r libserd-0.a out/*.o


mkdir -p ../../deps_compiled/libs/
mkdir -p ../../deps_compiled/pkgs/
cp libserd-0.a ../../deps_compiled/libs/


# Generate pkg-config manifest
cd ../../
echo "prefix=`realpath .`" > ./deps_compiled/pkgs/serd-0.pc

echo 'exec_prefix=${prefix}
libdir=${exec_prefix}/deps_compiled/libs
includedir=${prefix}/deps_src/serd/include

Name: serd
Description: serd compression library
Version: 0.30.17

Requires:
Libs: -L${libdir} -l:libserd-0.a
Cflags: -I${includedir}' >>  ./deps_compiled/pkgs/serd-0.pc
