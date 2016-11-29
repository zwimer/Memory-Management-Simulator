#include "NextFit.hpp"

//Constructor
NextFit::NextFit() : MemoryManager() {
	lastUsed = 0;
}

//Destructor
NextFit::~NextFit() {}

//Give process p n memory units
void NextFit::addProcP(char p, int n) {

	//Find the next place the process can be placed
	int index = findNextFit(lastUsed, n).index;

	//If de-fragmentation is required, do so
	if (index == -1) {

		//Note that defragmentation has begin
		std::cout << "Cannot place process " << p << " -- starting defragmentation";

		//DeFrag
		deFrag();

		//Find where to place the process now
		index = findNextFit(lastUsed, n).index;
	}

	//Place the process and note where
	allocateMemory(lastUsed = index, n ,p);
}

//Remove process p from memory
void NextFit::removeProcP(char p) {
	freeMem(p);
}
