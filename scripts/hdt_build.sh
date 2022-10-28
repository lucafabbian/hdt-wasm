#!/bin/bash
cd "$(dirname "$0")"

cd ..
export prefix="`realpath .`"

cd ./deps_src/hdt-cpp


autoreconf -fi
emconfigure ./configure "PKG_CONFIG_PATH=$prefix/deps_compiled/pkgs"

cd ../../scripts

bash ./hdt_make.sh

# Generate pkg-config manifests
cd ../
echo "prefix=`realpath .`" > ./deps_compiled/pkgs/hdt.pc
echo 'exec_prefix=${prefix}
libdir=${exec_prefix}/deps_compiled/libs
includedir=${prefix}/deps_src/hdt-cpp/libhdt/include
extraincludedir=${prefix}/deps_src/hdt-cpp/libhdt/src/hdt

Name: hdt
Description: HDT library
Version: 1.0.0

Requires:
Libs: -L${libdir} -l:libhdt.a
Cflags: -I${includedir} -I${extraincludedir}' >>  ./deps_compiled/pkgs/hdt.pc

echo "prefix=`realpath .`" > ./deps_compiled/pkgs/cds.pc
echo 'exec_prefix=${prefix}
libdir=${exec_prefix}/deps_compiled/libs
includedir=${prefix}/deps_src/hdt-cpp/libcds/include

Name: cds
Description: CDS library
Version: 1.0.0

Requires:
Libs: -L${libdir} -l:libcds.a
Cflags: -I${includedir}' >>  ./deps_compiled/pkgs/cds.pc