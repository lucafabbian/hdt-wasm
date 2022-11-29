#include <HDT.hpp>
#include <HDTManager.hpp>

using namespace hdt;


#include <emscripten.h>


const int MAX_TRIPLES_PRINTED = 30;

extern "C" EMSCRIPTEN_KEEPALIVE void convertTurtle() {
    HDTSpecification spec {};
 
    // Read RDF into an HDT file.
    HDT *hdt = HDTManager::generateHDT(
                     "test.ttl",     // Input file
                     "http://example.org/test", // Base URI
                     TURTLE,         // Input Format
                     spec            // Additional HDT Options
                   );
 
    // Enumerate all triples matching a pattern ("" means any)
    int i = 0;
    IteratorTripleString *it = hdt->search("","","");
    while(it->hasNext()){
        TripleString *triple = it->next();
        EM_ASM_({ window.console.log( UTF8ToString($0), UTF8ToString($1), UTF8ToString($2)) },  triple->getSubject().c_str(), triple->getPredicate().c_str(), triple->getObject().c_str());

        if(i++ < MAX_TRIPLES_PRINTED){
            EM_ASM_({ window._HDTWasm.printHTML("<p>" + UTF8ToString($0) + ", " + UTF8ToString($1) + ", " + UTF8ToString($2) + "</p><hr>") },  triple->getSubject().c_str(), triple->getPredicate().c_str(), triple->getObject().c_str());
        }
    }

    if(i++ >= MAX_TRIPLES_PRINTED){
        EM_ASM_({ window._HDTWasm.printHTML("<p>... and many more (check the console for a full log) ...</p>") });
    }

    EM_ASM_({ window._HDTWasm.printHTML("<br><br><p><b>Total triples:</b> " + $0 + "</p>") }, i);

    // Save HDT to a file
    hdt->saveToHDT("/result.hdt");
    EM_ASM_({ window._HDTWasm.printHTML("<button onclick=\"window._HDTWasm.downloadFile('/result.hdt', 'result.hdt')\">Download resulting hdt file</button>") });


    delete it; // Remember to delete iterator to avoid memory leaks! 
    delete hdt;
}


