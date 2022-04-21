#ifndef NEIGHBOUR
#define NEIGHBOUR

class City;

class Neighbour{

public:
	Neighbour(City* city, unsigned int distance); //creates a new Neigbour class of given values
	City* city; //ponter on the neighbour city
	unsigned int distance; //distance to that city
};

#endif

