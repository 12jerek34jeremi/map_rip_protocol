#include "include/city.h"

City::City(unsigned int id): id(id), neighbours(), connections()
{
}

void City::update(const Path* the_path)
{
	this;
	for (auto iter = neighbours.begin(); iter != nullptr; ++iter) {
		Neighbour& my_neighbour = *iter;
		if (!the_path->is_in(&iter))
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

void City::print_neghbours(std::ostream& stream, const std::vector<std::string>& names) const
{
	if (neighbours.get_element_nr() == 0) {
		stream << "(This city has no neigbours)" << std::endl;
		return;
	}

	for (auto iter = neighbours.begin(); iter != nullptr; ++iter) {
		const Neighbour & my_neighbour = *iter;
		stream << "id: " << &iter << ", name: " << names[&iter] << ", distance: " << (*iter).distance << std::endl;
	}
}

void City::print_all_connections(std::ostream& stream, const std::vector<std::string>& names) const
{
	if (connections.get_element_nr() == 0) {
		stream << "(No known connection to other cities)" << std::endl;
		return;
	}
	for (auto iter = connections.begin(); iter != nullptr; ++iter) {
		(*iter).print(stream, names);
		stream << std::endl << std::endl;
	}
}

bool City::print_connection(std::ostream& stream, const std::vector<std::string>& names, unsigned int destination) const
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

unsigned int City::get_id() const
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

void City::save_connections(std::stringstream& stream, const std::vector<std::string> & names) const
{
	for (auto iter = neighbours.begin(); iter != nullptr; ++iter) {
		if (&iter > id)
			stream << names[id] << ";" << names[&iter] << ";" << (*iter).distance << "\n";
	}
}
