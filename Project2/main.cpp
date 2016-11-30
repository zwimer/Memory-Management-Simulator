#include "main.hpp"
#include "Event.hpp"
#include "NextFit.hpp"
#include "BestFit.hpp"
#include "WorstFit.hpp"

#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <map>

//Define t_memmove
extern const int t_memmove = 1;

//Declare global time
Time t;

//Helpful typedef
typedef std::priority_queue<Event*, std::vector<Event*>, EventCompare> eQueue;

//A function used if an assert fails
void Err(const char *s) {
   	fprintf(stderr, "%s\n", s); perror("Perror");
    exit(EXIT_FAILURE);
}

//A function used to test assertions
void Assert(bool b, const char *s) { if (!b) Err(s); }

//Read the input file
eQueue readFile(const char * inFileName) {
    
    //Create a queue
    eQueue ret;
    
    //Open the file
    std::ifstream inFile(inFileName);
    
    //For each line
    std::string line;
    while(std::getline(inFile, line)) {
        
        //Skip empty, and comment lines
        if (!line.size()) continue;
        if (line[0] == '#') continue;
        
        //Variables to be read
        int mem, t1, t2;
        char proc;
        
        //Prepare the line to be read
        for(int i = 0; i < line.size(); i++)
            if (line[i] == '/') line[i] = ' ';
        std::istringstream theLine(line);
        
        //Read line in, if it is formatted correctly
        if (!(theLine >> proc >> mem)) continue;
        while (theLine >> t1 >> t2) {
            ret.push(new Event(proc, mem, Event::ARRIVE, t1));
            ret.push(new Event(proc, mem, Event::LEAVE, t1+t2));
        }
    }

    //Return the queue
    return ret;
}

//Perform simulation
void simulate(const eQueue& q, MemoryManager* algo) {
    
    //Keeps track of whether or not to skip a process
    std::map<char, bool> skipProcess;
    
    //Run each event
    for(eQueue theQueue(q);theQueue.size(); theQueue.pop()) {

        //For readability
        Event * e = theQueue.top();
        
        //Adjust time
        t.setTime(e->time);
        
        //If a process needs memory, allocate memory if possible
        //Record whether or not the proces was added and will leave memory later
        if (theQueue.top()->event==Event::ARRIVE)
            skipProcess[e->proc] = !algo->addProc(theQueue.top()->proc, theQueue.top()->mem);
        
        //If a process is ready to leave memory, free up the space
        else if(!skipProcess[e->proc]) algo->removeProc(theQueue.top()->proc);
    }
    
    //Prevent leaks
    delete algo;
}

//Main function
int main(int argc, char* argv[]) {
    
    //Make the queue of events
    eQueue theQueue = readFile(argv[1]);
    
    //Simulate each algorithm
//    simulate(theQueue, new NextFit()); std::cout << "\n";
    simulate(theQueue, new BestFit()); std::cout << "\n";
    simulate(theQueue, new WorstFit());
    
    //Success
    return EXIT_SUCCESS;
}
