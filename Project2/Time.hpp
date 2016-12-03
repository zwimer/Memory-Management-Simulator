#ifndef TIME_HPP
#define TIME_HPP

#include <ostream>

//Declare namespace
namespace Contiguous {
    class Time;
}

//A class representing time
class Contiguous::Time {
public:

	//Constructor
	Time();

	//Getters
	int getTime() const;
	
	//---Only to be called by HardDrive---
	void increaseDeFragTime();

	//------Only to be called by main-----
	void setTime(int n);

    //-Only to be called by MemoryManager-
    void reset();

	//Used for printing!
	friend std::ostream& operator << (std::ostream& s, const Time& t);

private:

	//Representation
	int t, tDeFrag;
};

#endif
