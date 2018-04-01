/* Operating Systems Project 2
 * Alex Slanski, Owen Stenson, Zac Wimer
 */

#include "MemoryManager.hpp"


//Next Fit algorithm
class Contiguous::WorstFit : public MemoryManager {
public:

	//Constructor
	WorstFit();
	
	//Destructor
	~WorstFit();

private:
    
    //Interface methods
    void addProcP(char p, int n);
    void removeProcP(char p);
};
