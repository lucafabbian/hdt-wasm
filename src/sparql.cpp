#include <HDT.hpp>
#include <HDTManager.hpp>

using namespace hdt;


#include <emscripten.h>


extern "C" EMSCRIPTEN_KEEPALIVE void example() {
    int i = 12;
    EM_ASM_({ window.console.log("<br><br><p><b>Total triples:</b> " + $0 + "</p>") }, i);

}



const int MAX_TRIPLES_PRINTED = 30;

extern "C" EMSCRIPTEN_KEEPALIVE void loadHDT(char * subject, char * predicate, char* object) {
    HDTSpecification spec {};
 
    printf("loading file...%s %s %s\n", subject, predicate, object);
    // Read RDF into an HDT file.
    HDT *hdt = HDTManager::loadHDT(
                     "file.hdt"   // Input file
                     
                   );


    printf("file loaded\n");
 
    // Enumerate all triples matching a pattern ("" means any)
    int i = 0;
    IteratorTripleString *it = hdt->search(subject,predicate, object);
        printf("searching\n");

    while(it->hasNext()){
        TripleString *triple = it->next();
        printf("%d a %s %s %s\n", i++, triple->getSubject().c_str(), triple->getPredicate().c_str(), triple->getObject().c_str());

        /*
        if(i++ < MAX_TRIPLES_PRINTED){
            EM_ASM_({ window._HDTWasm.printHTML("<p>" + UTF8ToString($0) + ", " + UTF8ToString($1) + ", " + UTF8ToString($2) + "</p><hr>") },  triple->getSubject().c_str(), triple->getPredicate().c_str(), triple->getObject().c_str());
        }*/

        //EM_ASM_({   window.queryMatches.push({graph:"",subject: UTF8ToString($0), predicate: UTF8ToString($1), object:UTF8ToString($2) }) }, triple->getSubject().c_str(), triple->getPredicate().c_str(), triple->getObject().c_str());

    }

        printf("ended search\n");
        return;

/*
    if(i++ >= MAX_TRIPLES_PRINTED){
        EM_ASM_({ window._HDTWasm.printHTML("<p>... and many more ...</p>") });
    }

    EM_ASM_({ window._HDTWasm.printHTML("<br><br><p><b>Total triples:</b> " + $0 + "</p>") }, i);
*/
    // Save HDT to a file
    hdt->saveToHDT("/result.hdt");
    EM_ASM_({ window._HDTWasm.printHTML("<button onclick=\"window._HDTWasm.downloadFile('/result.hdt', 'result.hdt')\">Download resulting hdt file</button>") });


    delete it; // Remember to delete iterator to avoid memory leaks!
 
    delete hdt;


}


