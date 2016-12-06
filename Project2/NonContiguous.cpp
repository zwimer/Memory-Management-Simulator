#include "NonContiguous.hpp"

using namespace Contiguous;

NonContiguous::NonContiguous() : MemoryManager("") {
	//std::cout << m.size() << "!!!\n";
	table.resize(m.size());
	lastUsed = 0;
}
NonContiguous::~NonContiguous() {}

void NonContiguous::addProcP(char p, int n) {
	//insert wherever possible
	//std::cout << t << "Process " << p << " arrived (requires " 
	//        << n << " frames)\n";

	//int last_used = 0;
	lastUsed = 0;
	for (unsigned int i=0; i<n; ++i) {
		//lastUsed = m.findNextFreeChunk(lastUsed);
		lastUsed = m.findNextFit(lastUsed, 1).first;
		if (lastUsed < 0) {
			std::cout << "No more memory! Mama mia!\n";
		}
		m.allocateMemory(lastUsed, 1, p);
		table[i] = lastUsed;
	}
}

void NonContiguous::removeProcP(char p) {
	//removeProcP(p);
	//std::cout << t << "Process " << p << " removed:\n";
	m.freeMem(p);
	//m.printMemory();

}
