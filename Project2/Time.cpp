#include "Time.hpp"

//Constructor
Time::Time() { reset(); }

//Getters
int getTime() const { return t; }

//Only to be called by main
void Time::increaseTime(int n) { 
	Assert(n>0, "time did not increase.");
	t += n;
 }

//Only to be called by HardDrive
void increaseDeFragTime() {
	tDeFrag++;
}

//Reset's time
void reset() {
	t = tPrint = 0;
}

//Used for printing!
friend std::ostream& operator << (std::ostream& s, const Time& t) {
	return (s << "time " << (t+tDeFrag) << "ms: ");
}
