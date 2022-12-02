#include <HDT.hpp>
#include <HDTManager.hpp>

using namespace hdt;


#include <emscripten.h>



HDT *database =nullptr;

extern "C" EMSCRIPTEN_KEEPALIVE void loadHDT() {
    HDTSpecification spec {};
 
    // Read RDF into an HDT file.
    database = HDTManager::loadHDT(
                "file.hdt"   // Input file     
                );
}

extern "C" EMSCRIPTEN_KEEPALIVE void search(char * subject, char * predicate, char* object) {
    printf("searching for: %s, %s, %s\n", subject, predicate, object);

 
    // Enumerate all triples matching a pattern ("" means any)
    int i = 0;
    IteratorTripleString *it = database->search(subject,predicate, object);

    while(it->hasNext()){
        TripleString *triple = it->next();
        printf("%d a %s %s %s\n", i++, triple->getSubject().c_str(), triple->getPredicate().c_str(), triple->getObject().c_str());


        EM_ASM_({   window.queryMatches.push({graph:"",subject: UTF8ToString($0), predicate: UTF8ToString($1), object:UTF8ToString($2) }) }, triple->getSubject().c_str(), triple->getPredicate().c_str(), triple->getObject().c_str());

    }
    delete it; // Remember to delete iterator to avoid memory leaks!
 
}


