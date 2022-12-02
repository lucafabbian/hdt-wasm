import path from 'path'
import fs   from 'fs'


import commonjs from '@rollup/plugin-commonjs';
import resolve from '@rollup/plugin-node-resolve';
import nodePolyfills from 'rollup-plugin-polyfill-node';




const patchedN3 = `
// Expose submodules
var exports = module.exports = {
  Lexer:        require('./lib/N3Lexer'),
  Parser:       require('./lib/N3Parser'),
  Writer:       require('./lib/N3Writer'),
  Store:        require('./lib/N3Store'),
  StreamParser: require('./lib/N3StreamParser'),
  StreamWriter: require('./lib/N3StreamWriter'),
  Util:         require('./lib/N3Util'),
};
`
function n3Patcher() {
  return {
    name: 'n3-patcher',
    resolveId(source, importer) {
      if (source.endsWith('N3.js')) {
        return path.resolve(path.dirname(importer), source);
      }
    },
    load(id) {
      if (id.endsWith('N3.js')) {
        return patchedN3;
      }
    }
  };
}



export default {
  input: './index.js',
  plugins: [
    resolve({ extensions: ['.js'], browser:true, preferBuiltins: true }),
    n3Patcher(),
    commonjs(),
    nodePolyfills(),
  ],

  output: [
  {
    file: "browser/sparqlEngine.js",
    format: 'iife',
    name: 'sparqlEngine',

    /* For some reason, the module tries to do some manipulations
    on the require global object and crashes if require is undefined.
    It looks like adding this line prevents any error from firing,
    while keeping the library working with no major issues.
    TODO: investigate and find a proper solution instead of this dirty hack */
    banner: `window.require = {}`,

  }],
};

