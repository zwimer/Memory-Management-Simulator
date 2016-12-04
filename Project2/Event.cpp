#include "Event.hpp"

//Declare namespace
namespace Contiguous {

//Different states of event
const int Event::LEAVE = 0;
const int Event::ARRIVE = 1;

//Constructor
Event::Event(char a, int b, int c, int d) :
    proc(a), mem(b), event(c), time(d) {

	//Check for errors
    Assert(ARRIVE > LEAVE, "Invalid constants");
	Assert(isalpha(a), "proccess ID invalid!");
    Assert(b>=0, "process takes negative memory!");
	Assert(c==ARRIVE || c==LEAVE, "illegal event type!");
	Assert(d >= 0, "cannot have an event at negative time!");
}

//Used to compare events
bool EventCompare::operator() (const Event* a, const Event* b) {

    //Compare based on time
    //Then prioritize leaving over arriving
    //Finally break any ties with proc ID
    if (a->time == b->time) {
        if (a->event == b->event)
             return a->proc > b->proc;
        else return a->event > b->event;
    }
	else return a->time > b->time;
}
}