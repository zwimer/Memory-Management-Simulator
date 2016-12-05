#ifndef NONCONTIGUOUS_HPP
#define NONCONTIGUOUS_HPP

#include "MemoryManager.hpp"
#include <vector>

class Contiguous::NonContiguous : public MemoryManager {
    public:
        NonContiguous();
        ~NonContiguous();
    private:
        void addProcP(char p, int n);
        void removeProcP(char p);

        int lastUsed;
        std::vector<unsigned int> table; //translate logical to physical addresses
};




#endif 
