#ifndef MAP_H
#define MAP_H
#include "sll_cities.h"
#include <vector>
#include <iostream>


class Map{
	bool link(std::string city1, std::string city2, unsigned int distance);
	bool unlink(std::string city1, std::string city2, unsigned int distance);
	bool how_to_get(std::string city1, std::string city2, std::ostream& stream);
	bool recalculate_map();
	
private:
	SLLCities cities;
	unsigned int next_id;
	std::vector<std::string> names;
};

#endif // !MAP_H



