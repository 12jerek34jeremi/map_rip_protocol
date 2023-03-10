#include "include/map.h"
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>

Map::Map() : cities(), names(), next_id(0)
{
}

bool Map::link(std::string city1_name, std::string city2_name, unsigned int distance, std::ostream& stream)
{
	City* city1; City* city2;

	if (city1_name.find(';') != std::string::npos) {
		stream << "City name can't contain any semicolons (;)." << std::endl;
		stream << "City name " << city1_name << " is inproper.";
		return false;
	}
	if (city1_name.find(';') != std::string::npos) {
		stream << "City name can't contain any semicolons (;)." << std::endl;
		stream << "City name " << city1_name << " is inproper.";
		return false;
	}

	if (cities.is_in(city1_name))
		city1 = &cities[city1_name];
	else {
		city1 = cities.insert_back(city1_name, City(next_id));
		next_id++;
		names.push_back(city1_name);
		stream << "City "<<city1_name<<" was created."<<std::endl;
	}
	if (cities.is_in(city2_name))
		city2 = &cities[city2_name];
	else {
		city2 = cities.insert_back(city2_name, City(next_id));
		next_id++;
		names.push_back(city2_name);
		stream << "City " << city2_name << " was created." << std::endl;
	}
	city1->add_neigbour(city2->get_id(), city2, distance);
	bool result = city2->add_neigbour(city1->get_id(), city1, distance);
	if (result)
		std::cout<<"Cities " << city1_name << " and " << city2_name
		<< " were linked. Distance between them was set to " << distance << "." << std::endl;
	else
		std::cout << "Distnace between " << city1_name << " and " << city2_name
		<< " was reset to " << distance << "." << std::endl;
	return result;
}

bool Map::unlink(std::string city_name1, std::string city_name2, std::ostream& stream)
{
	if (!cities.is_in(city_name1)) {
		std::cout << "City" << city_name1 << " is not on the map" << std::endl;
		return false;
	}
	if(!cities.is_in(city_name2)) {
		std::cout << "City" << city_name2 << " is not on the map" << std::endl;
		return false;
	}

	City& city1 = cities[city_name1];
	City& city2 = cities[city_name2];
	city1.remove_me(city2.get_id());
	bool result = city2.remove_me(city1.get_id());
	if(result)
		std::cout << "Cities " << city_name1 << " and " << city_name2 << " are no longer linked." << std::endl;
	else
		std::cout << "Cities " << city_name1 << " and " << city_name2 << " weren't linked." << std::endl;
	return result;

}

bool Map::how_to_get(std::string city_name1, std::string city_name2, std::ostream& stream) const
{
	if (!cities.is_in(city_name1)) {
		stream << "I'm sorry, city " << city_name1 << " is not on the map. :)" << std::endl;
		return false;
	}
	if (!cities.is_in(city_name2)) {
		stream << "I'm sorry, city " << city_name2 << " is not on the map. :)" << std::endl;
		return false;
	}

	const City& city1 = cities[city_name1];
	const City& city2 = cities[city_name2];
	city1.print_connection(stream, names, city2.get_id());
	return true;
}

void Map::recalculate_map()
{
	for (auto iter = cities.begin(); iter != nullptr; ++iter) {
		(*iter).forget_all_connections();
	}

	for (auto iter = cities.begin(); iter != nullptr; ++iter) {
		(*iter).call_update();
	}
}

void Map::print_all_cities(std::ostream& stream) const
{
	if (names.size() == 0) {
		std::cout<<"There are no cities on this map!"<<std::endl;
	}
	else {
		for (int i = 0; i<names.size(); ++i) {
			stream << i << ": " << names[i];
			if (i!=0 && (i+1) % 5 == 0) {
				stream << std::endl;
			}
			else if(i != names.size() - 1) {
				stream << "    ";
			}
		}
		stream << std::endl;
	}
}

void Map::print_city_neighbours(std::string city_name, std::ostream& stream) const
{
	if (!cities.is_in(city_name)) {
		stream << "City of name " << city_name << " is not on the map. :(" << std::endl;
		return;
	}
	const City& city = cities[city_name];
	stream << "Neigbours of city "<<city_name <<" (id: " << city.get_id()<<")" << std::endl;
	cities[city_name].print_neghbours(stream, names);
}

void Map::print_city_connections(std::string city_name, std::ostream& stream) const
{
	if (!cities.is_in(city_name)) {
		stream << "City of name " << city_name << " is not on the map. :(" << std::endl;
		return;
	}

	stream << "Connections of city " << city_name << std::endl;
	cities[city_name].print_all_connections(stream, names);
}

bool Map::save(std::string filename, std::ostream& stream) const
{
	std::stringstream output;
	for (auto iter = cities.begin(); iter != nullptr; ++iter) {
		(*iter).save_connections(output, names);
	}
	
	bool all_good = true;
	std::ofstream file;
	file.open(filename, std::ios::out | std::ios::trunc);
	if (file.good()) {
		file << output.rdbuf();
		stream << "Successfully saved map structure to file " << filename << std::endl;
	}
	else {
		stream << "Couldn't open file " << filename <<" to save informations." << std::endl;
		all_good = false;
	}

	file.close();
	return all_good;
}

bool Map::load(std::string filename, std::ostream& stream)
{
	std::ifstream file;
	bool all_good = true;

	file.open(filename, std::ios::in);
	if (!file.good()) {
		stream << "Couldn't open file " << filename << std::endl;
		all_good = false;
	}
	else {
		unsigned int i = 0;
		std::string line;
		for (std::getline(file, line); !line.empty(); i++, std::getline(file, line)) {
			//stream << line << std::endl;
			std::size_t first_semicolon = line.find(';');
			//stream << first_semicolon << "   ";
			if (first_semicolon == std::string::npos) {
				stream << "Can't find semicolond.";
				all_good = false;
				break;
			}
			std::size_t second_semicolon = line.find(';', first_semicolon + 1);
			//stream << second_semicolon << std::endl;
			if (second_semicolon == std::string::npos) {
				stream << "Can't find second semicolond.";
				all_good = false;
				break;
			}

			std::string distance_str = line.substr(second_semicolon + 1);
			if (distance_str.empty()) {
				stream << "After second semicolane shoudl be a distance.";
				all_good = false;
				break;
			}
			for (unsigned i = 0; i < distance_str.size(); i++) {
				if (distance_str[i] < '0' || distance_str[i] > '9') {
					stream << "Can't convert " << distance_str << " to intiger." << std::endl;
					all_good = false;
					break;
				}
			}
			if (!all_good)
				break;
			unsigned int distance = stoi(distance_str);

			link(line.substr(0, first_semicolon),
				line.substr(first_semicolon + 1, second_semicolon - first_semicolon - 1),
				distance, stream);
		}

		if (all_good)
			stream << "Successfully added map structure from file " << filename << std::endl;
		else {
			stream << "Problem occured while reading line nr " << i << std::endl;
			stream << "Abording loading map structure from file " << filename << std::endl;
		}
	}
	
	file.close();

	return all_good;
}
