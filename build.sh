#!/bin/bash
cd "$(dirname "$0")"


bash scripts/clone_deps.sh
[ ! -f deps_compiled/libs/libserd-0.a ] && bash scripts/serd_build.sh
[ ! -f deps_compiled/libs/libz.a      ] && bash scripts/zlib_build.sh
[ ! -f deps_compiled/libs/libhdt.a    ] && bash scripts/hdt_build.sh

bash scripts/converter_build.sh
bash scripts/sparql_build.sh