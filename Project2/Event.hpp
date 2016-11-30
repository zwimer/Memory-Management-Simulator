#ifndef EVENT_HPP
#define EVENT_HPP

#include "main.hpp"

//Small event class
class Event {
public:
    
	//Constructor
	Event(char _proc, int _event, int _time);

	//Representation
    const int event, time;
    const char proc;

	//Different states of event
    static const int LEAVE;
    static const int ARRIVE;
};

//Used to compare events
class EventCompare {
public:
	bool operator() (const Event, const Event); 
};

#endif
