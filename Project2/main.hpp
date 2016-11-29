#ifndef MAIN_HPP
#define MAIN_HPP

//Declare global variables
extern const int t_memmove;
extern Time t;

//A function used if an assert fails
void Err(const char *s);

//A function used to test assertions
void Assert(bool b, const char *s);

#endif
