#include "hardDrive.hpp"
#include "main.hpp"

//The size of the hardDrive
const int hardDrive::MemoryWidth = 32;
const int hardDrive::MemoryHeight = 8;

//Constructor
hardDrive::hardDrive() {
	
	//Create memory
	for(int i = 0; i < MemoryWidth*MemoryHeight; i++)
		memory.push_back((char)0);
}

//Finds the next location after index in memory that 
//can fit n memory units and returns it's index in memory.
//This function returns -1 if defragmentation is required
int hardDrive::findNextFit(int index, int n) const {

	//Check for incorrect usage
	Assert(canFit(n), "Out of memory");

	//Record starting index
	int k, i = index;

	//Repeat for each index in memory
	//Or until the item can fit
	bool canFit = false;
	do {
		
		//Check to see if n units of memory can fit
		for(k = 0; k < n; k++) if (memory[k]) break;
		if (k == n) canFit = true;
				
		//Increment index, circularly in memory
		if (++i > (int)memory.size()) i = 0;	
	} while(i != index && !canFit);
	
	//Return the result found, or -1 if none was found
	return (i == index) ? -1 : i;
}

//Returns true if size memory units are free
bool hardDrive::canFit(int size) const { return size <= memoryUnused; }

//Print memory
void hardDrive::printMemory() const {

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
void hardDrive::deFrag() {

	//For each slot in memory 
	int firstFree = 0;
	for(int i = 0; i < (int)memory.size(); i++) {

		//If the memory is empty, do nothing
		if (!memory[i]) continue;

		//Otherwise, move it to the first free slot
		memory[firstFree++] = memory[i];
	}

	//Mark the rest of the memory as unused
	for(int i = firstFree; i < (int)memory.size(); i++)
		memory[i] = (char) 0;
}

//Allocates n units of memory at index n
void hardDrive::allocateMemory(int index, int n, char proc) {
	
	//For each memory unit
	for(int i = index; i < index+n; i++)
		if (!memory[i]) memory[i] = proc;
		else Err("allocateMemory called illegally");
}
