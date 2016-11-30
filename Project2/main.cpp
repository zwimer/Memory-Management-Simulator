#include "main.hpp"
#include "Event.hpp"
#include "NextFit.hpp"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <queue>

//Define t_memmove
extern const int t_memmove = 1;

//Declare global time
Time t;

//Helpful typedef
typedef std::priority_queue<Event, std::vector<Event>, EventCompare> eQueue;

//A function used if an assert fails
void Err(const char *s) {
   	fprintf(stderr, "%s\n", s); perror("Perror");
    exit(EXIT_FAILURE);
}

//A function used to test assertions
void Assert(bool b, const char *s) { if (!b) Err(s); }

//Read the input file
eQueue readFile(const char * inFile) {
    
    //Create a queue
    eQueue ret;
    
    
    
    //TODO: Do stuff here 
    
    
    
    //Return the queue
    return std::move(ret);
}

int main() {

    
    eQueue theQueue = readFile("fileName");
	NextFit a;
    
    a.addProc('A', 3);
	a.addProc('B', 3);
	a.addProc('C', 3);

	t.increaseTime(100);
	a.removeProc('B');

	t.increaseTime(100);
	a.addProc('Z' ,4);

    t.increaseTime(100);
    a.removeProc('Z');
    a.addProc('Z', 2);
    a.removeProc('A');
    
    t.increaseTime(100);    
    a.addProc('B', 4);

    
	return 0;
}
