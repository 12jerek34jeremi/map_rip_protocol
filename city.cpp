#include "city.h"

City::City(unsigned int id): id(id), neighbours(), connections()
{
}

void City::update(Path* the_path)
{
	for (auto iter = neighbours.begin(); iter != nullptr; ++iter) {
		Neighbour& my_neighbour = *iter;
		if (!the_path->is_in(my_neighbour.distance))
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

bool City::add_neigbour(unsigned int id, City* neighbour, unsigned int distance)
{
	if (neighbours.is_in(id)) {
		neighbours[id].distance = distance;
		return false;
	}
	neighbours.insert_back(id, Neighbour(neighbour, distance));
	return true;
}

bool City::remove_me(unsigned int id)
{
	return neighbours.remove(id);
}

void City::print_neghbours(std::ostream& stream, std::vector<std::string>& names)
{
	for (auto iter = neighbours.begin(); iter != nullptr; ++iter) {
		Neighbour& my_neighbour = *iter;
		stream << "\tid: " << &iter << ", name: " << names[&iter] << ", distance: " << (*iter).distance;
	}
}

bool City::print_connection(std::ostream& stream, std::vector<std::string>& names, unsigned int destination)
{
	std::cout << "From city " << names[id] << " :" << std::endl;
	if (connections.is_in(destination)) {
		connections[destination].print(stream, names);
		return true;
	}
	stream << "I don't know any path to city " << names[destination] << " . :(" << std::endl;
	return false;
}

void City::forget_all_connections()
{
	connections.clear();
}

unsigned int City::get_id()
{
	return id;
}

void City::call_update()
{
	for (auto iter = neighbours.begin(); iter != nullptr; ++iter) {
		Neighbour& my_neighbour = *iter;
		my_neighbour.city->update(new Path(id, my_neighbour.distance));
	}
}
