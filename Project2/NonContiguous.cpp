/* Non-contiguous memory management
 *  Implementation mostly handled via Contiguous namespace
 *  Memory doesn't have to be contiguous if we can keep track of 
 *      the mapping between logical and physical addresses, which is
 *      trivial in a vector (which maps unsigned ints to unsigned ints)
 *  The lookup table isn't actually necessary for this trivial 
 *      implementation (it doesn't require the memory to actually do
 *      anything), but it is shown.
 */

#include "NonContiguous.hpp"
#include <stdio.h>

using namespace Contiguous;

NonContiguous::NonContiguous() : MemoryManager("") {
    //set up our table for access (we know the exact length)
	table.resize(m.size());
	lastUsed = 0;
}
NonContiguous::~NonContiguous() {}

void NonContiguous::addProcP(char p, int n) {
	lastUsed = 0;
    std::cout << t << "Placed process " << p << ":\n";
    //request MemoryManager for one frame at a time
    //keep track of the proper mapping in self.table[i]
	for (/*unsigned*/ int i=0; i<n; ++i) {
		lastUsed = m.findNextFit(lastUsed, 1).first;
		if (lastUsed < 0) {
            perror("Not enough memory; only call NonContiguous::addProcP if we have the memory");
		}
		m.allocateMemory(lastUsed, 1, p);
		table[i] = lastUsed;
	}
}

void NonContiguous::removeProcP(char p) {
    //we don't even need our table of data because MemoryManager removes 
    // processes by checking every frame
	m.freeMem(p);
    //zero out our table (just good practice)
    for (unsigned int i=0; i<table.size(); ++i) {
        table[i] = 0;
    }
}
