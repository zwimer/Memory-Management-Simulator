#include "WorstFit.hpp"

//Declare namespace
namespace Contiguous {

//Constructor
WorstFit::WorstFit() : MemoryManager("Worst-Fit") {}

//Destructor
WorstFit::~WorstFit() {}

//Give process p n memory units
void WorstFit::addProcP(char p, int n) {

	int i,k;
	std::pair<int,int> worst, tmp;	

	//Check if defragging is needed
	worst = m.findNextFit(0, n);
	if (worst.first == -1) {

		//If so, note so, do just that, then re-find the first fit position
		std::cout << t << "Cannot place process " << p << " -- starting defragmentation\n";
		m.deFrag();
		worst = m.findNextFit(i=0, n);
	}

	//Check every free space
	i = m.findNextFreeChunk(k=0);
	while(i > k) {
        
		//Check the size of the next free chunk
		tmp = m.findNextFit(i, n);
		if (tmp.second > worst.second) worst = tmp;

		//Assign i and k
		k = i;
		i = m.findNextFreeChunk(i);
	}

    //Note that the process was placed
    std::cout << t << "Placed process " << p << ":\n";
    
	//Place the process and note where
	m.allocateMemory(worst.first, n ,p);
}

//Remove process p from memory
void WorstFit::removeProcP(char p) {
	m.freeMem(p);
}

}