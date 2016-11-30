#ifndef HARD_DRIVE_HPP
#define HARD_DRIVE_HPP

#include <iostream>
#include <vector>
#include <set>


//A class representing the hard drive
class HardDrive {
public:

	//Constructor
	HardDrive();

	//Finds the next location after index in memory that 
	//can fit n memory units and returns it's index in memory.
	//This function returns -1 if defragmentation is required
    std::pair<int, int> findNextFit(int index, int n) const;
    
    //Returns the location of the next free chunk
    //of memory after index, assumes index is free
    //Returns -1 if there is no free memory in the system
    int findNextFreeChunk(int index) const;
    
	//Prints the memory
	void printMemory() const;
	
    //Returns size of memory
    int size() const;
    
	//Returns true if size memory units are free
	bool canFit(int size) const;	

	//Defragments memory
	void deFrag();

	//Allocates n units of memory at index n for proc
	void allocateMemory(int index, int n, char proc);

    //Removes proc from memory
    void freeMem(char proc);
    
private:
	
	//Representation
	int memoryUnused;
	std::vector<char> memory;
	static const int MemoryWidth;
	static const int MemoryHeight;
};

#endif
