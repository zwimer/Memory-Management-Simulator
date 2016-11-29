#ifndef TIME_HPP
#define TIME_HPP

#include "main.hpp"

//A class representing time
class Time {
public:

	//Constructor
	Time();

	//Getters
	int getTime() const;
	
	//---Only to be called by HardDrive---
	void increaseDeFragTime();

	//-----Only to be called by main-----
	void increaseTime(int n);
	void reset();

	//Used for printing!
	friend std::ostream& operator << (std::ostream& s, const Time& t);

private:

	//Representation
	int t, tDeFrag;
};

#endif
