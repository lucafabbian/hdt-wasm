#!/bin/bash
cd "$(dirname "$0")"


mkdir -p ./deps_src
cd ./deps_src

[ ! -d "./hdt-cpp" ] && git clone https://github.com/lucafabbian/hdt-cpp.git
[ ! -d "./serd" ] && git clone https://github.com/drobilla/serd.git
[ ! -d "./zlib" ] && git clone https://github.com/madler/zlib.git

