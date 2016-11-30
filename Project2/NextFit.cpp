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
	int index = m.findNextFit(lastUsed, n).index;

	//If de-fragmentation is required, do so
	if (index == -1) {

		//Note that defragmentation has begin
		std::cout << "Cannot place process " << p << " -- starting defragmentation\n";

		//DeFrag
		m.deFrag();
        lastUsed = 0;

		//Find where to place the process now
		index = m.findNextFit(lastUsed, n).index;
	}

    //Note that the process was placed
    std::cout << t << "Placed process " << p << ":\n";
    
	//Place the process and note where
	m.allocateMemory(index, n ,p);
    lastUsed = (index + n) % m.size();
}

//Remove process p from memory
void NextFit::removeProcP(char p) {
	m.freeMem(p);
}
