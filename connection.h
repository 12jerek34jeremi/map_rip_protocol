#ifndef CONNECTION_H
#define CONNECTION_H
#include "path.h"
#include <iostream>
#include <vector>

class Connection
{
public:
	Connection(Path* the_path);
	Connection(const Connection& source); //move constructor
	Connection(Connection&& source); //move constructor
	~Connection();
	void update(Path* the_path);
	void print(std::ostream& stream, std::vector<std::string> & names);

private:
	Path* best_path;
	Path* second_best_path;
	unsigned int destination;
};

#endif // !CONNECTION_H