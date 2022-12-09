FROM emscripten/emsdk:3.1.27

RUN apt-get update && apt-get install -y autoconf libtool pkg-config zlib
