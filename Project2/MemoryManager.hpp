#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#include "main.hpp"
#include "HardDrive.hpp"

//Forward declerations
class Process;

//An abstract class to represent a MemoryManager
class MemoryManager {
public:

	//Constructor
	MemoryManager();
	virtual ~MemoryManager();

	//User Interface methods
	//Reserve n memory units for process p
	void addProc(char p, int n);
	void removeProc(char p);

protected:
	
	//Add process p, it is possible
	virtual void removeProcP(char p) = 0;
	virtual void addProcP(char p, int n) = 0;

	//Representation
	HardDrive m;
};

#endif
