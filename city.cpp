#include "city.h"

City::City(unsigned int id): id(id), neighbors(), connections()
{
}

void City::update(Path* the_path)
{
	for (auto iter = neighbors.begin(); iter != nullptr; ++iter) {
		Neighbour& my_neighbour = *iter;
		my_neighbour.city->update(the_path->add(id, my_neighbour.distance));
	}

	unsigned int from = the_path->from();
	if (connections.is_in(from)) {
		connections[from].update(the_path);
	}
	else {
		connections.insert_back(from, Connection(the_path));
	}

}

void City::print_connection(std::ostream& stream, std::vector<std::string>& names, unsigned int destination)
{
	std::cout << "From city " << names[id] << " :" << std::endl;
	if (connections.is_in(destination)) {
		connections[destination].print(stream, names);
	}
	else {
		stream << "I don't know any path to city " << names[destination] << " . :(" << std::endl;
	}
}