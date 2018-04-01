/* Operating Systems Project 2
 * Alex Slanski, Owen Stenson, Zac Wimer
 */

#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#include "main.hpp"
#include "HardDrive.hpp"

#include <string>


//An abstract class to represent a MemoryManager
class Contiguous::MemoryManager {
public:

	//Constructor
    MemoryManager(const std::string& s);
	virtual ~MemoryManager();

	//User Interface methods
	//Reserve n memory units for process p
    //addProc returns true if the process was added
	bool addProc(char p, int n);
	void removeProc(char p);

protected:
	
	//Add or remove process p
	virtual void removeProcP(char p) = 0;
	virtual void addProcP(char p, int n) = 0;

    //Representation
    const std::string name;
	HardDrive m;
};

#endif
