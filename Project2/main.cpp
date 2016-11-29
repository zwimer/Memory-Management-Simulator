#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "hardDrive.hpp"

//A function used if an assert fails
void Err(const char *s) {
   	fprintf(stderr, "%s\n", s); perror("Perror");
    exit(EXIT_FAILURE);
}

//A function used to test assertions
void Assert(bool b, const char *s) { if (!b) Err(s); }


int main() {


	hardDrive d;
	
	d.allocateMemory(0, 5, 'A');
	d.printMemory();
	d.allocateMemory(11, 2, 'B');
	d.printMemory();
	d.allocateMemory(20, 4, 'C');
	d.printMemory();
	d.allocateMemory(50, 2, 'D');
	d.printMemory();
	d.allocateMemory(60, 3, 'E');
for(int i = 0; i < 3; i++) std::cout << std::endl;
	d.printMemory();

	d.deFrag();
    for(int i = 0; i < 3; i++) std::cout << std::endl;
	d.printMemory();



	return 0;
}
