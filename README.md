# hdt-wasm

Wasm port of the [hdt-cpp](https://github.com/rdfhdt/hdt-cpp) library to allow indexing graph databases on the browser.

## Status
The project is nowhere close to a production-ready build with a stable api.
Yet, it is already able to compile with no major issue and run a demo!

Check it here: [https://lucafabbian.github.io/hdt-wasm/dist/converter](https://lucafabbian.github.io/hdt-wasm/dist/converter)




## Getting started

Be sure to have [Node.js](https://nodejs.org/en/download/) and [emscripten](https://emscripten.org/docs/getting_started/downloads.html) on your system (test with `em++ --version`). Do not use the ones from Ubuntu repos, they are outdated.

The dependencies below are required too:
```bash
sudo apt-get install git autoconf libtool pkg-config
```

Build with:
```bash
# clone deps, rebuild and link them 
./build.sh

# build demo
bash scripts/converter_build.sh

```

## Known issues and patches
- wasm do no plays well with C++ exception. Thus, instead of relying on try/catch to handle non-existing keys in std::map, we use map.count(). This patch should not break anything, and neither have any relevant performance impact, since it's just a log(n) call performed once during setup.
- wasm has a different pointer size (size_t) than common architectures, thus a cast is mandatory. I'm not sure if it safe or if I'm doing it the right way, so I've chosen to add a stderr print everytime such cast are used, to help further debugging.



## License and authors
The code inside this repo is to be considered under MIT license. However, the overall library would be distributed under LGPL 2.1 license since the libhdt project is distributed under such license.

Author: Luca Fabbian <luca.fabbian.1999@gmail.com>