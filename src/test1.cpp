// Creating an HDT file (examples/generate.cpp)


#include <HDT.hpp>
#include "../hdt-cpp/libhdt/src/hdt/BasicModifiableHDT.hpp"

using namespace hdt;

int main(int argc, char *argv[]) {

	HDTSpecification spec;

    printf("Creating database and populating with a triple s\n");

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

    printf("Retrieving triple... s\n");


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


}
