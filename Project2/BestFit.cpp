#include "BestFit.hpp"

//Constructor
BestFit::BestFit() : MemoryManager("BestFit") {}

//Destructor
BestFit::~BestFit() {}

//Give process p n memory units
void BestFit::addProcP(char p, int n) {

	int i,k;
	std::pair<int,int> best, tmp;	

	//Check if defragging is needed
	best = m.findNextFit(0, n);
	if (best.first == -1) {

		//If so, note so, do just that, then re-find the first fit position
		std::cout << t << "Cannot place process " << p << " -- starting defragmentation\n";
		m.deFrag();
		best = m.findNextFit(i=0, n);
	}

	//Check every free space
	i = m.findNextFreeChunk(k=0);
	while(i > k) {
		//Check the size of the next free chunk
		tmp = m.findNextFit(i, n);
		if (tmp.second > best.second) best = tmp;

		//Assign i and k
		k = i;
		i = m.findNextFreeChunk(i);
	}

    //Note that the process was placed
    std::cout << t << "Placed process " << p << ":\n";
    
	//Place the process and note where
	m.allocateMemory(best.first, n ,p);
}

//Remove process p from memory
void BestFit::removeProcP(char p) {
	m.freeMem(p);
}
