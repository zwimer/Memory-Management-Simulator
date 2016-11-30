#include "MemoryManager.hpp"

//Next Fit algorithm
class WorstFit : public MemoryManager {
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
