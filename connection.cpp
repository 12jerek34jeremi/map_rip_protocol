#include "connection.h"

Connection::Connection(Path*  the_path) : best_path(the_path), second_best_path(nullptr), destination(the_path->from())
{
}

Connection::Connection(const Connection& source) : best_path(nullptr), second_best_path(nullptr), destination(source.destination)
{
	if (source.best_path != nullptr)
		best_path = new Path(source.best_path);

	if (source.second_best_path != nullptr)
		second_best_path = new Path(second_best_path);
}

Connection::Connection(Connection&& source) : best_path(source.best_path), second_best_path(source.second_best_path), destination(source.destination)
{
	source.best_path = nullptr;
	source.second_best_path = nullptr;
	source.destination = 0;
}

Connection::~Connection()
{
	if (best_path != nullptr) delete best_path;
	if (second_best_path != nullptr) delete second_best_path;
}

void Connection::update(Path* the_path)
{
	if (the_path->from() != destination) {
		throw std::exception("To connection object was sent the path which origin"
			"is different than destination of this object\n."
			"(The distination is id of the city to which best connection is being chosen).");
	}

	if (second_best_path == nullptr) {
		if (best_path->get_length() > the_path->get_length()) {
			second_best_path = best_path;
			best_path = the_path;
		}
		else {
			second_best_path = the_path;
		}
	}
	else {
		if (the_path->get_length() >= second_best_path->get_length()) {
			delete the_path;
		}else if (best_path->get_length() > the_path->get_length()) {
			delete second_best_path;
			second_best_path = best_path;
			best_path = the_path;
		}
		else{
			delete second_best_path;
			second_best_path = the_path;
		}
	}
}

void Connection::print(std::ostream& stream, std::vector<std::string>& names)
{
	if (second_best_path == nullptr) {
		stream << "There is only one known path to city " << names[destination] <<
			". (total length is " << best_path->get_length() << " ):" << std::endl;
		best_path->print(stream, names);
	}
	else {
		stream<<"Best path to "<< names[destination]<<" (total lengh is "<<
			best_path->get_length() << " ):" << std::endl;
		best_path->print(stream, names);

		stream << "Alternative path to " << names[destination] << " (total lengh is " <<
			second_best_path->get_length() << " ):" << std::endl;
		second_best_path->print(stream, names);
	}
}
