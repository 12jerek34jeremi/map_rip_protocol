#ifndef CITY_H
#define CITY_H
#include "path.h"
#include <iostream>
#include "sll.h"
#include "neighbour.h"
#include "connection.h"
#include <vector>


class City {
public:
	City(unsigned int id); //creates a new city with given id
	void update(const Path* the_path);
	/*
		If the origin city (first city) of the_path is not yet in connection table the new Connection object with
		best_path as the_path is created and added to connection table.
		If origin city of the path is in the connection table the update method is called on Connection object
		represented the connection to the origin city. See void Connection::update(Path* the_path) for more info.

		Then to each neighbour city which is not yet in on the path thisthe copy of the path with addition of
		neighbour id and distance is send. Sending path means calling the update function (recursively) on city object.
	*/
	bool add_neigbour(unsigned int id, City* neighbour, unsigned int distance);
	/*	If city of given id is not yet in  neighbour cities list this city is added to the list. Funciton
	* retunrns true in this case.
		If city of given id is already in given list distance between neighbour and this city is set on
		argument distance value.
	*/
	bool remove_me(unsigned int id);
	/*If city of given id is in neigbours list of this city, city of given id is removed from neigbours list.
	* Function retunrs true in that case.
	* 
	* If given city is not in the neighbour list function do nothing and return false.
	*/
	void print_neghbours(std::ostream& stream, const std::vector<std::string> & names);
	/*This function print on passed stream all neighbours of  this city.
	Arguments:
		std::ostream& my_stream:
			The stream on which path will be printed (like std::cout).
		std::vector<std::string> & names:
			Because of the fact that Path knows only ids of the city, no names while printing
			path object we need to some howe tell what is the name of each city in the path.
			Names is vector which indices are cities ids and values are cities names. For example
			name of city of id 7 is names[7].
	*/
	void print_all_connections(std::ostream& stream, const std::vector<std::string>& names);
	bool print_connection(std::ostream& stream, const std::vector<std::string> & names, unsigned int id);
	/*This function print on passed stream a best path (and if exists second best path) to given city.
	If connection to given city is not on the connection table function prints that information on screan and
	returns false.
	Otherwise function returns false.
	Arguments:
		std::ostream& my_stream:
			The stream on which path will be printed (like std::cout).
		std::vector<std::string> & names:
			Because of the fact that Path knows only ids of the city, no names while printing
			path object we need to some howe tell what is the name of each city in the path.
			Names is vector which indices are cities ids and values are cities names. For example
			name of city of id 7 is names[7].
		unsigned int id:
			The distination, the id of the city to which we want to print connection.
	Exemplatory otput on stream from this function:

	From city Gdansk :
	Best path to Wroclaw (total lengh is 560 ):
	--> Lodz (340) --> Wroclaw (220)
	Alternative path to Wroclaw (total lengh is 800 ):
	--> Szczecin (350) --> Wroclaw (450)
	*/
	void forget_all_connections(); //forces to forget all connections (to clear connection table)
	unsigned int get_id() const; //returns the id of this city
	void call_update();
	/*The path sending process needs to start somewhere. This function calls update mehtod on all it's neighbours.
	* (Its sends the path conating id of this city and distance to given neighbour to all it's neigbour)
	*/

private:
	const unsigned int id; //every city has an unique id number
	SLL<unsigned int, Neighbour>  neighbours; //the neigbours list
	SLL<unsigned int, Connection> connections; //the connection list
};

#endif



