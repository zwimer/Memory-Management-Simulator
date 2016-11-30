#include "MemoryManager.hpp"

//Next Fit algorithm
class BestFit : public MemoryManager {
public:

	//Constructor
	BestFit();
	
	//Destructor
	~BestFit();

private:
    
    //Interface methods
    void addProcP(char p, int n);
    void removeProcP(char p);
};
