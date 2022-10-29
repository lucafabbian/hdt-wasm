// Creating an HDT file (examples/generate.cpp)


#include <HDT.hpp>
#include <HDTManager.hpp>
#include "../hdt-cpp/libhdt/src/hdt/BasicModifiableHDT.hpp"

using namespace hdt;


#include <emscripten.h>


extern "C" EMSCRIPTEN_KEEPALIVE int testf() {

	HDTSpecification spec;

    printf("Creating database and populating with a triple\n");

	HDT *hdt = new BasicModifiableHDT(spec);

	// Add additional domain-specific properties to the header
	Header *header = hdt->getHeader();
	header->insert("myResource1", "hello", "world");


    /*
    	// Add additional domain-specific properties to the header
    TripleString *ts = new TripleString("http://ciao.og", "http://cia2o.og", "http://cia3o.og");
    cout << ts->getSubject();
	hdt->insert(*ts);
	hdt->insert(*ts);
	hdt->insert(*ts);
    */

    printf("Retrieving triple...\n");


    // Enumerate all triples matching a pattern ("" means any)
    IteratorTripleString *it = header->search("","","");
    while(it->hasNext()){
        TripleString *triple = it->next();
        cout << triple->getSubject() <<
        ", " << triple->getPredicate() <<
        ", " << triple->getObject() << endl;
    }

    printf("Done!\n");

    delete it; // Remember to delete iterator to avoid memory leaks!
    delete hdt; // Remember to delete instance when no longer needed!

    return 1345;

}


extern "C" EMSCRIPTEN_KEEPALIVE int testf2() {
    int num;
    FILE *fptr;

    fptr = fopen("/ciao.txt","w+");
    fprintf(fptr,"%d",356);

    fclose(fptr);


    fptr = fopen("/ciao.txt","r");
    fscanf(fptr,"%d", &num);

    printf("Value of n=%d\n", num);

    fclose(fptr);


    return num;
}


extern "C" EMSCRIPTEN_KEEPALIVE void testf3() {

    printf("Reading file...\n\n");
    std::ifstream f("file.txt");

    if (f.is_open())
        std::cout << f.rdbuf();


}



extern "C" EMSCRIPTEN_KEEPALIVE void ingestTurtle() {
    HDTSpecification spec {};
 
    // Read RDF into an HDT file.
    HDT *hdt = HDTManager::generateHDT(
                     "test.ttl",   // Input file
                     "http://example.org/test", // Base URI
                     TURTLE,         // Input Format
                     spec              // Additional HDT Options
                   );
 
    // OPTIONAL: Add additional domain-specific properties to the header
    Header *header = hdt->getHeader();
    header->insert("myResource1", "property", "value");
    // Enumerate all triples matching a pattern ("" means any)
    IteratorTripleString *it = hdt->search("","","");
    while(it->hasNext()){
        TripleString *triple = it->next();
        cout << triple->getSubject() <<
        ", " << triple->getPredicate() <<
        ", " << triple->getObject() << endl;
    }
    delete it; // Remember to delete iterator to avoid memory leaks!
 
    delete hdt;


}
