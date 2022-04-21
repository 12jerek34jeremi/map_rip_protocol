#include "map.h"

Map::Map() : cities(), names(), next_id(0)
{
}

bool Map::link(std::string city1_name, std::string city2_name, unsigned int distance)
{
	City* city1; City* city2;

	if (cities.is_in(city1_name))
		city1 = &cities[city1_name];
	else {
		city1 = cities.insert_back(city1_name, City(next_id));
		next_id++;
		names.push_back(city1_name);
	}
	if (cities.is_in(city2_name))
		city2 = &cities[city2_name];
	else {
		city2 = cities.insert_back(city2_name, City(next_id));
		next_id++;
		names.push_back(city2_name);
	}
	city1->add_neigbour(city2->get_id(), city2, distance);
	return city1->add_neigbour(city1->get_id(), city1, distance);
}

bool Map::unlink(std::string city_name1, std::string city_name2, unsigned int distance)
{
	if(!cities.is_in(city_name1))	return false;
	if(!cities.is_in(city_name2))	return false;

	City& city1 = cities[city_name1];
	City& city2 = cities[city_name2];
	city1.remove_me(city1.get_id());
	city2.remove_me(city2.get_id());
	return true;
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

void Map::print_city_neighbours(std::string city1)
{
}

void Map::print_city_connection(std::string city2)
{
}
