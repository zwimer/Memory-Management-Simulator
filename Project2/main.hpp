/* Operating Systems Project 2
 * Alex Slanski, Owen Stenson, Zac Wimer
 */

#ifndef MAIN_HPP
#define MAIN_HPP

#include <iomanip>
#include <utility>

#include "Time.hpp"

//Declare global variables
extern const int t_memmove;

//Declare namespace
namespace Contiguous {
    
    //Declare global variables
    extern Time t;
    
    //Forward declerations
    class MemoryManager;
    class EventCompare;
    class HardDrive;
    class WorstFit;
    class BestFit;
    class NextFit;
    class Event;

	//A function used if an assert fails
	void Err(const char *s);

	//A function used to test assertions
	void Assert(bool b, const char *s);
}

//Forward declerations
class NonContiguous;

#endif
