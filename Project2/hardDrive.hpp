#include <iostream>
#include <vector>

//A struct that contains an index of memory
//and the amount of space there is in excess
typedef struct __nextFit_struct {
	int index;
	int space;
} nextFit;

//A class representing the hard drive
class hardDrive {
public:

	//Constructor
	hardDrive();

	//Finds the next location after index in memory that 
	//can fit n memory units and returns it's index in memory.
	//This function returns -1 if defragmentation is required
	int findNextFit(int index, int n) const;

	//Prints the memory
	void printMemory() const;
	
	//Returns true if size memory units are free
	bool canFit(int size) const;	

	//Defragments memory
	void deFrag();

	//Allocates n units of memory at index n for proc
	void allocateMemory(int index, int n, char proc);

private:
	
	//Representation
	int memoryUnused;
	std::vector<char> memory;
	static const int MemoryWidth;
	static const int MemoryHeight;
};
