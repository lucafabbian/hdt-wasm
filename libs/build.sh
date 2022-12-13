#!/bin/bash
cd "$(dirname "$0")"

echo "Building libs..."
bash ./clone.sh
[ ! -f deps_compiled/libs/libserd-0.a ] && bash ./serd_build.sh
[ ! -f deps_compiled/libs/libz.a      ] && bash ./zlib_build.sh
[ ! -f deps_compiled/libs/libhdt.a    ] && bash ./hdt_build.sh
