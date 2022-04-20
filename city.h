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
	City(unsigned int id);
	void update(Path* the_path);
	void add_neigbour(unsigned int id, City* neighbour);
	void remove_me(unsigned int id);
	void print_neghbours(std::ostream& stream, std::vector<std::string> & names);
	void print_connection(std::ostream& stream, std::vector<std::string> & names, unsigned int id);
	void forget_all_connections();

private:
	unsigned int id;
	SLL<unsigned int, Neighbour>  neighbors;
	SLL<unsigned int, Connection> connections;
};

#endif



