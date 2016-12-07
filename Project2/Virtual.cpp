#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "Virtual.hpp"

namespace Virtual{

// prints memory "[mem: # # ... #] to stdout
void printMem( int mem[])
{
	int i = 0;
	printf("[mem:");
	for (i = 0; i < F; i++)
	{
		if (mem[i] == 0)
			printf(" .");
		else
			printf(" %d", mem[i]);
	}
	printf("]");
}


// pagefault algo interface: index_of_victum (*f)(int refs[], int cp, int n, int mem[], int F, void* algo_struct)
int OPTalgo(std::vector<int> refs, int cp, int mem[], void* st)
{
	int vic = -1;
	int vicI = 0;
	int i;
	int j;
	for (i = 0; i < F; i+=1)
	{
		for (j = cp; j < (int)refs.size(); j+=1)
		{
			if (refs[j] == mem[i]) break;
		}
		if (vic == -1 || vicI < j)// if no victum or viictum has a higher index
		{
			vic = i;
			vicI = j;
			//if victum is never refrenced again
			if (vicI == (int)refs.size()) return vic;
		}
	}
	return vic;
}

int LRUalgo(std::vector<int> refs, int cp, int mem[], void* st)
{//least recently used
	int vic = -1;
	int vicI = 0;
	int i;
	int j;
	for (i = 0; i < F; i+=1)
	{
		for (j = cp; j > 0; j-=1)
		{
			if (refs[j] == mem[i]) break;
		}
		if (vic == -1 || vicI > j)// if no victum or if the victum has a more recent index
		{
			vic = i;
			vicI = j;
		}
	}
	return vic;
}

struct LFUst
{
int ptr; //holds where the last swap occured
int* freqs; //holds the frequencies. same size as mem.
};

int LFUalgo(std::vector<int> refs, int cp, int mem[], void* st)
{//least frequently used
	int j;
	struct LFUst* state= (struct LFUst*) st;
	for (; state->ptr < cp; state->ptr +=1)
	{
		for (j = 0; j < F; j++)
		{
			if (mem[j] == refs[state->ptr]) 
			{	
				state->freqs[j] += 1;
				break;
			}
		}
	}
	int vic = 0;
	for (j = 1; j < F; j+=1)
	{
		if (state->freqs[vic] > state->freqs[j]) vic = j;
	}
	state->freqs[vic] = 0;
	return vic;
}

void Sim(std::vector<int> refs, std::string algoname, int (*algo)(std::vector<int>, int, int*, void* ), void* st)
{
	bool filled = false;
	int pages[F];
	int i = 0;
	int j;
	for (i = 0; i < F; i ++)
	{
		pages[i] = 0;
	}

	int state;
	int pagefaults = 0;
	int vic;
	std::cout <<"Simulating "<< algoname << " with fixed frame size of " << F << "\n";
	for (i = 0; i < (int)refs.size(); i++)
	{

		state = PAGE;
		for (j = 0; j < F; j++)
		{
			if ( pages[j] == refs[i])
			{
				state = GOOD;
				break;
			}
		}
		if (state == PAGE)
		{
			pagefaults +=1;
			// do pagefault
			if (filled)
			{
				state = (*algo)(refs, i,pages, st);
			} else {
				for (state = 0; state < F; state++)
				{
					if (pages[state] == 0)
					{
						if (state +1 == F) filled = true;
						break;
					}
				}
			}
			vic = pages[state];
			pages[state] = refs[i];
			// print
			printf("referencing page %d ", refs[i]);
			printMem(pages);
			if (vic == 0)
				printf(" PAGE FAULT (no victim page)\n");
			else
				printf(" PAGE FAULT (victim page %d)\n", vic);
		}

	}
	std::cout << "End of " << algoname <<" simulation (" << pagefaults << " page faults)\n";
}



int vmain (char file[])
{
	//open argv[1] (argv[2] in real)
	std::ifstream infile;
	infile.open(file);
	std::vector<int> refs;
	int tmp;
	while (infile.good())
	{
		infile >> tmp;
		refs.push_back(tmp);
	}
	// OPT
		// forward-looking, best possible

	Sim(refs, "OPT" , &OPTalgo , NULL);

	// LRU
		// Least recently used

	Sim(refs, "LRU" , &LRUalgo , NULL);
	// LFU
		// least-frequently used

	struct LFUst LFUstate;
	LFUstate.ptr = 0;
	LFUstate.freqs = (int*) calloc(sizeof(int), F);

	Sim(refs, "LFU" , &LFUalgo , &LFUstate);

//	free(refs);
	free(LFUstate.freqs);
    return EXIT_SUCCESS;
}

}
