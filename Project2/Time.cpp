#include "Time.hpp"
#include "main.hpp"

#include <ostream>

//Constructor
Time::Time() { reset(); }

//Getters
int Time::getTime() const { return t; }

//Only to be called by main
void Time::setTime(int n) {
	Assert(n>=t, "time decreased.");
	t = n;
 }

//Only to be called by HardDrive
void Time::increaseDeFragTime() {
	tDeFrag++;
}

//Reset's time
void Time::reset() {
	t = tDeFrag = 0;
}

//Used for printing!
std::ostream& operator << (std::ostream& s, const Time& t) {
	return (s << "time " << (t.t+t.tDeFrag) << "ms: ");
}
