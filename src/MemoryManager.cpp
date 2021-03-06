/* Operating Systems Project 2
 * Alex Slanski, Owen Stenson, Zac Wimer
 */

#include "MemoryManager.hpp"

namespace Contiguous {

//Constructor
MemoryManager::MemoryManager(const std::string& s) : name(s) {
    t.reset();
    if (s != "") std::cout << t << "Simulator started (Contiguous -- " << s;
    else std::cout << t << "Simulator started (Non-contiguous";
    std::cout << ")\n";
}

//Destructor
MemoryManager::~MemoryManager() {
    if (name != "") std::cout << t << "Simulator ended (Contiguous -- "<< name;
    else std::cout << t << "Simulator ended (Non-contiguous";
    std::cout << ")\n\n";
}

//Add process p to memory if possible
//Returns true if the process was added
bool MemoryManager::addProc(char p, int n) {
	
    //Return value
    bool ret;
    
	//Note that a process arrived
	std::cout << t << "Process " << p <<
				" arrived (requires " << n << " frames)\n";

	//If the process can fit, fit it
	if ((ret = m.canFit(n))) addProcP(p,n);

	//Else, note so
	else std::cout << t << "Cannot place process " 
					<< p << " -- skipped!\n";

	//Print out new memory then return the result
	m.printMemory();
    return ret;
}

//Remove process p from memory
void MemoryManager::removeProc(char p) {

	//Remove the process
	removeProcP(p);

	//Note the process' removal
	std::cout << t << "Process " << p << " removed:\n";
	m.printMemory();
}

}