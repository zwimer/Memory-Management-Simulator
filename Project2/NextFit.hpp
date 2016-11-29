#include "MemoryManager.hpp"

//Next Fit algorithm
class NextFit : public MemoryManager {
public:

	//Constructor
	NextFit();
	
	//Destructor
	~NextFit();

	//Interface methods
	void addProc(char p, int n);
	void removeProc(char p);

private:

	//Representation
	int lastUsed;
};
