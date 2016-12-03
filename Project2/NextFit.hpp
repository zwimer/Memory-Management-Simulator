#include "MemoryManager.hpp"


//Next Fit algorithm
class Contiguous::NextFit : public MemoryManager {
public:

	//Constructor
	NextFit();
	
	//Destructor
	~NextFit();

private:
    
    //Interface methods
    void addProcP(char p, int n);
    void removeProcP(char p);

	//Representation
	int lastUsed;
};
