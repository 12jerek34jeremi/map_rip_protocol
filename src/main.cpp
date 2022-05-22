#include "include/map.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "include/splitter.h"
#include <cstdlib>

//void poland(Map& map);
void clear_screan();
void check_files();
void start();

int main() {
	check_files();
	start();
	return 0;
}

void check_files() {
	std::ifstream file;

	file.open("data/help.txt", std::ios::in);
	if (!file.good())
		std::cout << "Couldn't open file help.txt from data directory. Command help not available." << std::endl;
	file.close();

	file.open("data/poland.txt", std::ios::in);
	if (!file.good())
		std::cout << "Couldn't open file poland.txt from data directory. Command poland not available." << std::endl;
	file.close();
}

void start()
{
	Map map;
	Splitter splitter;
	std::string user_input;

	while (true) {
		std::cout << "type the command: ";
		std::getline(std::cin, user_input);

		if (user_input[0] == '!') {
			system(user_input.substr(1).c_str());
		}
		else {

			splitter.reset(user_input);
			std::string command = splitter.get_next();


			if (command == "") {

			}
			else if (command == "link" || command == "l") {
				std::string city1 = splitter.get_next(2);
				std::string city2 = splitter.get_next(2);
				std::string distance_str = splitter.get_next(2);
				if (distance_str == "") {
					std::cout << "The link command takes two cities names as arguments and distance beetween them seperated by semicolon.\n"
						"(Type 'help' for more info)" << std::endl;
					continue;
				}
				unsigned int distance;
				bool all_good = false;
				try {
					distance = std::stoi(distance_str);
					all_good = true;
				}
				catch (std::exception e) {
					std::cout << "Could not convert " << distance_str << "positive intiger number. :(" << std::endl;
				}
				if (!all_good) continue;
				map.link(city1, city2, distance, std::cout);
			}
			else if (command == "recalculate" || command == "rec") {
				std::cout << "Starting recalculation." << std::endl;
				map.recalculate_map();
				std::cout << "Recalculation done." << std::endl;
			}
			else if (command == "unlink" || command == "ul") {
				std::string city1 = splitter.get_next(2);
				std::string city2 = splitter.get_next(2);
				if (city2 == "") {
					std::cout << "The unlink command takes two cities names as arguments them seperated by semicolon.\n"
						"(Type 'help' for more info)" << std::endl;
					continue;
				}
				map.unlink(city1, city2, std::cout);

			}
			else if (command == "how_to_get" || command == "h2g") {
				std::string city1 = splitter.get_next(2);
				std::string city2 = splitter.get_next(2);
				if (city2 == "") {
					std::cout << "The how_to_get command takes two cities names as arguments them seperated by semicolon.\n"
						"(Type 'help' for more info)" << std::endl;
					continue;
				}
				map.how_to_get(city1, city2, std::cout);
			}
			else if (command == "print_all_cities" || command == "pac") {
				map.print_all_cities(std::cout);
			}
			else if (command == "print_city_neighbours" || command == "pcn") {
				std::string city = splitter.get_next(2);
				if (city == "") {
					std::cout << "The print_city_neighbours command takes city name as an argument.\n"
						"(Type 'help' for more info)" << std::endl;
					continue;
				}
				map.print_city_neighbours(city, std::cout);
			}
			else if (command == "print_city_connections" || command == "pcc") {
				std::string city = splitter.get_next(2);
				if (city == "") {
					std::cout << "The print_city_neighbours command takes city name as an argument.\n"
						"(Type 'help' for more info)" << std::endl;
					continue;
				}
				map.print_city_neighbours(city, std::cout);
			}
			else if (command == "exit") {
				break;
			}
			else if (command == "cls" || command == "clear") {
				clear_screan();
			}
			else if (command == "help" || command == "h") {
				std::ifstream file;
				file.open("data/help.txt", std::ios::in);

				if (!file.good()) {
					std::cout << "Couldn't open file help.txt. Command help not available." << std::endl;
					continue;
				}
				else {
					std::cout << file.rdbuf();
				}
				file.close();
			}
			else if (command == "save" || command == "s") {

				std::string filepath = splitter.get_next(2);
				if (filepath == "") {
					std::cout << "The save command takes filepath name as an argument.\n"
						"(Type 'help' for more info)" << std::endl;
					continue;
				}
				map.save(filepath, std::cout);
			}
			else if (command == "load" || command == "ld") {
				std::string filepath = splitter.get_next(2);
				if (filepath == "") {
					std::cout << "The load command takes filepath name as an argument.\n"
						"(Type 'help' for more info)" << std::endl;
					continue;
				}
				map.load(filepath, std::cout);
			}
			else if (command == "poland" || command == "pl") {
				map.load("data/poland.txt", std::cout);
			}
			else {
				std::cout << "Command '" << command << "' not known. :(" << std::endl;
			}
		}
		
	}
}


//void poland(Map& map)
//{
//	map.link("Gdansk", "Warszawa", 350, std::cout);
//	map.link("Krakow", "Warszawa", 300, std::cout);
//	map.link("Krakow", "Katowice", 80, std::cout);
//	map.link("Katowice", "Lodz", 200, std::cout);
//	map.link("Lodz", "Gdansk", 340, std::cout);
//	map.link("Lodz", "Warszawa", 140, std::cout);
//	map.link("Katowice", "Wroclaw", 190, std::cout);
//	map.link("Szczecin", "Gdansk", 350, std::cout);
//	map.link("Bialystok", "Warszawa", 200, std::cout);
//	map.link("Warszawa", "Lublin", 200, std::cout);
//	map.link("Rzeszow", "Lublin", 200, std::cout);
//	map.link("Wroclaw", "Lodz", 220, std::cout);
//	map.link("Wroclaw", "Szczecin", 450, std::cout);
//}

void clear_screan()
{
#ifdef _WIN32
	system("cls");
#endif // _WIN32
#ifdef __linux__
	system('clear');
#endif // __linux__s
}
