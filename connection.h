#ifndef CONNECTION_H
#define CONNECTION_H
#include "path.h"
#include <iostream>
#include <vector>

class Connection
{
	Connection(Path* the_path);
	void update(Path* path);
	void print(std::ostream& stream, std::vector<std::string> & names);

private:
	Path* best_path;
	Path* second_best_path;
	unsigned int destination;
};

#endif // !CONNECTION_H