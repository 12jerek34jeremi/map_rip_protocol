#ifndef SLL_CONNECTION_H
#define SLL_CONNECTION_H
#include "sll.h"
#include "connection.h"
#include <iostream>

class SLLConnection : public SLL<unsigned int, Connection>
{
public:
	SLLConnection();
	bool update(Path * the_path);
	bool print(std::ostream& stream, std::vector<std::string>& names, unsigned int destination);
};

#endif // !SLL_CONNECTION_H