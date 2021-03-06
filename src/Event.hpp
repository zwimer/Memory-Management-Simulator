/* Operating Systems Project 2
 * Alex Slanski, Owen Stenson, Zac Wimer
 */

#ifndef EVENT_HPP
#define EVENT_HPP

#include "main.hpp"


//Small event class
class Contiguous::Event {
public:
    
	//Constructor
	Event(char _proc, int _mem, int _event, int _time);

	//Representation
    const char proc;
    const int mem, event, time;

	//Different states of event
    //Arrive > Leave is important
    static const int LEAVE;
    static const int ARRIVE;
};

//Used to compare events
class Contiguous::EventCompare {
public:
	bool operator() (const Event*, const Event*);
};

#endif
