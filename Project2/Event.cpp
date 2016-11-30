#include "Event.hpp"

//Different states of event
const int Event::LEAVE = 0;
const int Event::ARRIVE = 1;

//Constructor
Event::Event(char a, int b, int c) : proc(a), event(b), time(c) {

	//Check for errors
	Assert(isalpha(a), "proccess ID invalid!");
	Assert(b==ARRIVE || b==LEAVE, "illegal event type!");
	Assert(c >= 0, "cannot have an event at negative time!");
}

//Used to compare events
bool EventCompare::operator() (const Event a, const Event b) {
	if (a.time == b.time) return a.proc < b.proc; 
	else return a.time < b.time;
}
