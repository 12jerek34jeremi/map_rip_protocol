#include "map.h"

Map::Map() : cities(), names(), next_id(0)
{
}

bool Map::link(std::string city1_name, std::string city2_name, unsigned int distance, std::ostream& stream)
{
	City* city1; City* city2;

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

bool Map::how_to_get(std::string city_name1, std::string city_name2, std::ostream& stream)
{
	if (!cities.is_in(city_name1)) {
		stream << "I'm sorry, city " << city_name1 << " is not on the map. :)" << std::endl;
		return false;
	}
	if (!cities.is_in(city_name2)) {
		stream << "I'm sorry, city " << city_name2 << " is not on the map. :)" << std::endl;
		return false;
	}

	City& city1 = cities[city_name1];
	City& city2 = cities[city_name2];
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

void Map::print_all_cities(std::ostream& stream)
{
	if (cities.get_element_nr() == 0) {
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

void Map::print_city_neighbours(std::string city_name, std::ostream& stream)
{
	if (!cities.is_in(city_name)) {
		stream << "City of name " << city_name << " is not on the map. :(" << std::endl;
		return;
	}
	City& city = cities[city_name];
	stream << "Neigbours of city "<<city_name <<" (id: " << city.get_id()<<")" << std::endl;
	cities[city_name].print_neghbours(stream, names);
}

void Map::print_city_connections(std::string city_name, std::ostream& stream)
{
	if (!cities.is_in(city_name)) {
		stream << "City of name " << city_name << " is not on the map. :(" << std::endl;
		return;
	}

	stream << "Connections of city " << city_name << std::endl;
	cities[city_name].print_all_connections(stream, names);
}
