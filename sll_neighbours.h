#ifndef SLL_NEIGHBOURS
#define SLL_NEIGHBOURS
#include "sll.h"
#include "neighbour.h"

class SLLNeighbours : public SLL<unsigned int, Neighbour>{

public:
	SLLNeighbours();
	bool add(unsigned int id, City* city, unsigned int distance);
};

#endif
