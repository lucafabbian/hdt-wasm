# hdt-wasm

Wasm port of the [hdt-cpp](https://github.com/rdfhdt/hdt-cpp) library to allow indexing graph databases on the browser.

## Status
The project is nowhere close to a production-ready build with a stable api.
Yet, it is already able to compile with no major issue and run some demos!

Check the demos here:
 - a turtle (ttl) to HDT converter: [https://lucafabbian.github.io/hdt-wasm/demo-converter/dist](https://lucafabbian.github.io/hdt-wasm/demo-converter/dist)
 - a sparql query over HDT playground: [https://lucafabbian.github.io/hdt-wasm/demo-sparql/dist](https://lucafabbian.github.io/hdt-wasm/demo-sparql/dist)




## Getting started

### With Docker
You find a Dockerfile with all dependencies already preconfigured. Just build it and run it with:
```bash
docker build -t hdt_emscripten .
docker run --rm -v $(pwd):/src -u $(id -u):$(id -g) hdt_emscripten bash build.sh
```


### Without Docker
(tested on Ubuntu 22.04)

Be sure to have [Node.js](https://nodejs.org/en/download/) and [emscripten](https://emscripten.org/docs/getting_started/downloads.html) on your system (test with `em++ --version`). Do not use the ones from Ubuntu repos, they are outdated.


You also need the following dependencies:
```bash
sudo apt-get install git autoconf libtool pkg-config
```

Build with:
```bash
# clone deps, rebuild and link them 
./build.sh
```

## What's next?
The main goal now is to provide a real binding to the WebAssembly file and distribute it as a npm package.



## License and authors
The code inside this repo is to be considered under MIT license. However, the overall library would be distributed under LGPL 2.1 license since the libhdt project is distributed under such license.

Author: Luca Fabbian <luca.fabbian.1999@gmail.com>