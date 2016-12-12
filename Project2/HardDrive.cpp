#include "HardDrive.hpp"
#include "main.hpp"
#include <stdio.h>

#include <set>

//Declare namespace
namespace Contiguous {

//The size of the HardDrive
const int HardDrive::MemoryWidth = 32;
const int HardDrive::MemoryHeight = 8;

//Constructor
HardDrive::HardDrive() {
	
	//Create memory
	for(int i = 0; i < size(); i++)
		memory.push_back((char)0);
    
    //Initalize memoryUsed
    memoryUnused = size();
}

//Finds the next location after index in memory that 
//can fit n memory units and returns it's index in memory.
//This function returns -1 if defragmentation is required
std::pair<int, int> HardDrive::findNextFit(int index, int n) const {

	//Check for incorrect usage;
    Assert(canFit(n), "Out of memory");
    Assert(index>=0&&index<size(), "illegal index passed");

	//Record starting index
	int k, i = index;

	//Repeat for each index in memory
	do {
		
		//Check to see if n units of memory can fit
        for(k = 0; k < n && (i+k) < size(); k++) if (memory[i+k]) break;
        
        //If it can fit
        if (k == n) {
            
            //Find extra space
            for( k = 0; (k+i+n) < size(); k++ ) if (memory[k+i+n]) break;
            
            //Return the result
            return std::make_pair(i, k);
        }
				
		//Increment index, circularly in memory
		if (++i >= size()) i = 0;
	} while(i != index);
	
    //If it can't fit, return -1s
    return std::make_pair(-1,-1);
}

//Returns the location of the next free chunk
//of memory after index, assumes index is free
//Returns -1 if there is no free memory in the system
int HardDrive::findNextFreeChunk(int index) const {
    
    //Make sure this was called legally
    Assert(0<=index&&index<size(), "Index out of bounds");
    
    //Set true if a block of used memory has been found
    int i, foundUsed = false;
    
    //Repeat for each index in memory
    for(i=index+1; i < size(); i++) {
        
        //If a used block of memory has yet to be found
        if (!foundUsed) {
            if (memory[i]) foundUsed = true;
        }
        
        //If a new chunk was found, return it's index
        else if (!memory[i]) return i;
    }
    
    //If no memory is free
    return -1;
}

//Returns true if size memory units are free
bool HardDrive::canFit(int size) const { return size <= memoryUnused; }

//Returns size of memory
int HardDrive::size() const { return MemoryWidth * MemoryHeight; }

//Print memory
void HardDrive::printMemory() const {

	//Print top
	for(int k = 0; k < MemoryWidth; k++) std::cout<< '=';
	std::cout << '\n';

	//Print memory
	for(int i = 0; i < MemoryHeight; i++) {
		for(int k = 0; k < MemoryWidth; k++) {
			char tmp = memory[i*MemoryWidth+k];
            std::cout << (tmp?tmp:'.'); fflush(stdout);
		}
		std::cout << '\n';
	}

	//Print bottom
	for(int k = 0; k < MemoryWidth; k++) std::cout<< '=';
	std::cout << std::endl;
}

//Defragments memory
void HardDrive::deFrag() {

	//Keep track of what was moved
	int numMoved = 0; std::set<char> moved;

	//For each slot in memory 
	int firstFree = 0;
	for(int i = 0; i < size(); i++) {

		//If there is nothing to move, do nothing
		if (!memory[i] || i == firstFree++) continue;

		//Otherwise, move it to the first free slot
		memory[firstFree-1] = memory[i];
		t.increaseDeFragTime();

		//Keep track of what was moved
		numMoved++; moved.insert(memory[i]);
	}

	//Mark the rest of the memory as unused
	for(int i = firstFree; i < size(); i++)
		memory[i] = (char) 0;
    
    //Note what was moved, and how the memory looks now
    std::cout << t << "Defragmentation complete (moved " << numMoved << " frames:";
    for(std::set<char>::const_iterator i = moved.begin(); *i != *(moved.rbegin()); i++) 
		std::cout << ' ' << *i << ',';
    std::cout << " " << *(moved.rbegin()) << ")" << std::endl;
    printMemory();
}

//Allocates n units of memory at index n
void HardDrive::allocateMemory(int index, int n, char proc) {
	
	//For each memory unit
	for(int i = index; i < index+n; i++)
		if (!memory[i]) memory[i] = proc;
		else Err("allocateMemory called illegally");

    //Update memory used
    memoryUnused -= n;
}

void HardDrive::freeMem(char proc) {
    
    //Record the amount of memory freed
    int memFreed = 0;
    
    //Free each memory unit containing proc
    for(int i = 0; i < size(); i++)
        
        //If the proc was found, delete it
        if (memory[i] == proc) {
            memory[i] = (char) 0;
            memFreed++;
        }
        
    //If nothing was free, note so
    if (!memFreed) Err("process was not in memory");
    
    //Update memory used
    memoryUnused += memFreed;
}
}
