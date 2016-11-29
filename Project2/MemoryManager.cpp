#include "MemoryManager.hpp"

//Constructor
MemoryManager::MemoryManager() {
	Assert(!t.getTime(), "time not reset!");
}

//Destructor
MemoryManager::~MemoryManager() {}

//Add process p to memory if possible
void MemoryManager::addProc(char p, int n) {
	
	//Note that a process arrived
	std::cout << t << "Process " << p <<
				" arrived (requires " << n << " frames)\n";

	//If the process can fit, fit it
	if (m.canFit(n)) addProcP(p,n);

	//Else, note so
	else std::cout << t << "Cannot place process " 
					<< p << " -- skipped!\n";

	//Print out new memory
	m.printMemory();
}

//Remove process p from memory
void MemoryManager::removeProc(char p) {

	//Remove the process
	removeProcP(p);

	//Note the process' removal
	std::cout << t << "Process " << p << " removed:\n";
	m.printMemory();
}
