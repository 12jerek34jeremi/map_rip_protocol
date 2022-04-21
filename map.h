#ifndef MAP_H
#define MAP_H
#include <vector>
#include <iostream>
#include "sll.h"
#include "city.h"


class Map{
public:
	Map(); //creates new Map with no cities
	bool link(std::string city1, std::string city2, unsigned int distance);
	/*If any of passed cites is not yet on the map, function first creates new city on new map with given name.
	If cities were unlink before (one wasn’t a neighbour of other) function links them (adds second city to list of neighbours of city1 and vice versa).
	If cities were linked before function reset distance between them, so user can use this function to change distance between cities.
	Function returns true if new link was created, false otherwise.
	*/
	bool unlink(std::string city1, std::string city2, unsigned int distance);
	/*Function returns false and do nothing if at least one of the cities wasn’t on the map, or if cities weren’t linked.
	If given cities were linked, function unlinks them and returns true. Unlinking means removing first city of
	neighbours list of second city and removing second city from neighbours list of first city.
	*/
	bool how_to_get(std::string from, std::string destination, std::ostream& stream);
	/*If any of two passed cities is not on the map fuction ”how_to_get” will print this information.
	If there is no way to get from one city to another fuction ”how_to_get” will print this information.
	If there is only one convenient path from one city to another, fuction ”how_to_get” will print this path and print that this is the only possible path.
	If there are at least two possible paths connecting those two cities fuction ”how_to_get” will print those path as best_path and second_best_path.
	*/
	void recalculate_map();
	void print_city_neighbours(std::string city1);
	//prints all neighbours of given city. If city is not on the map this information will be printed.
	void print_city_connection(std::string city2);
	//prints all connections (where you can get from this city) of given city.
	//If city is not on the map this information will be printed.
	
private:
	SLL<std::string, City> cities; 
	/*the singles linkded list representing all cities which are on the map.
	the keys are cities names (like Warszawa) and values are cities objects.
	Each time new city is added on the map the new city object is pushed at the end of this list.*/
	unsigned int next_id;
	//this id will be given to each new added on the map. Id of first city will be 0, id of second city will be 1 and so on
	//this value is incremented after each new city additions
	std::vector<std::string> names;
	/*Because of the fact that each city, connetcion or path object knows only ids of the cities, no names, while printing
	any connecton or path  we need to some howe tell what is the name of each city.
	Names is vector which indices are cities idsand values are cities names.
	For example name of city of id 7 is names[7].
	This vector is passed as reference to each path, connecton or city object method which prints sth on some strem.
	Each time new city is added on the map the new name is pushed at the end of this vector.
	*/
};

#endif // !MAP_H



