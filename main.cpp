#include "map.h"
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>

void poland(Map& map);
bool split_to_words(std::vector<std::string>& words, std::string& source);
void clear_screan();

int main()
{
	Map map;
	while (true) {
		std::cout << "type the command: ";
		std::string user_input;
		std::getline(std::cin, user_input);
		if (user_input == "") {
			//std::cout << "Please write a command. (Type 'help' to see available commands')" << std::endl;
			continue;
		}

		std::vector<std::string> words;
		split_to_words(words, user_input);
		std::string command = words[0];

		if (command == "link" || command == "l") {
			if (words.size() != 4) {
				std::cout << "The link command takes two cities names as arguments and distance beetween them.\n"
					"(Type 'help' for more info)" << std::endl;
				continue;
			}
			unsigned int distance;
			bool all_good = false;
			try {
				distance = std::stoi(words[3]);
				all_good = true;
			}
			catch (std::exception e) {
				std::cout << "Could not convert " << words[3] << "positive intiger number. :("<<std::endl;
			}
			if (!all_good) continue;
			map.link(words[1], words[2], distance, std::cout);
		}
		else if (command == "recalculate" || command == "rec") {
			std::cout << "Starting recalculation." << std::endl;
			map.recalculate_map();
			std::cout << "Recalculation done." << std::endl;
		}
		else if (command == "unlink" || command == "ul") {
			if (words.size() != 3) {
				std::cout << "The unlink command takes two cities names as arguments.\n"
					"(Type 'help' for more info)" << std::endl;
				continue;
			}
			int result = map.unlink(words[1], words[2], std::cout);

		}
		else if (command == "how_to_get" || command == "h2g") {
			if (words.size() != 3) {
				std::cout << "The how_to_get command takes two cities names as arguments.\n"
					"(Type 'help' for more info)" << std::endl;
				continue;
			}
			map.how_to_get(words[1], words[2], std::cout);
		}
		else if (command == "print_all_cities" || command == "pac") {
			map.print_all_cities(std::cout);
		}
		else if (command == "print_city_neighbours" || command == "pcn") {
			if (words.size() != 2) {
				std::cout << "The print_city_neighbours command takes city name as an argument.\n"
					"(Type 'help' for more info)" << std::endl;
				continue;
			}
			map.print_city_neighbours(words[1], std::cout);
		}
		else if (command == "print_city_connections" || command == "pcc") {
			if (words.size() != 2) {
				std::cout << "The print_city_neighbours command takes city name as an argument.\n"
					"(Type 'help' for more info)" << std::endl;
				continue;
			}
			map.print_city_connections(words[1], std::cout);
		}
		else if (command == "exit") {
			break;
		}else if (command == "cls" || command == "clear") {
			clear_screan();
		}
		else if (command == "help" || command == "h") {
			//TO DO:
			//IMPLEMENT
		}
		else if (command == "poland") {
			poland(map);
			std::cout << "Map of poland created. Remember to call recalculate now." << std::endl;
		}
		else {
			std::cout << "Command '"<<command<<"' not known. :(" << std::endl;
		}
	}
	return 0;
}

void poland(Map& map)
{
	map.link("Gdansk", "Warszawa", 350, std::cout);
	map.link("Krakow", "Warszawa", 300, std::cout);
	map.link("Krakow", "Katowice", 80, std::cout);
	map.link("Katowice", "Lodz", 200, std::cout);
	map.link("Lodz", "Gdansk", 340, std::cout);
	map.link("Lodz", "Warszawa", 140, std::cout);
	map.link("Katowice", "Wroclaw", 450, std::cout);
	map.link("Szczecin", "Gdansk", 350, std::cout);
	map.link("Bialystok", "Warszawa", 200, std::cout);
	map.link("Warszawa", "Lublin", 200, std::cout);
	map.link("Rzeszow", "Lublin", 170, std::cout);
	map.link("Wroclaw", "Lodz", 220, std::cout);
	map.link("Wroclaw", "Szczecin", 350, std::cout);
}

bool split_to_words(std::vector<std::string>& words, std::string& source) {
	if (!words.empty())
		return false;

	size_t pos = 0;
	while ((pos = source.find(' ')) != std::string::npos) {
		words.push_back(source.substr(0, pos));
		source.erase(0, pos + 1);
	}
	words.push_back(source);
	return true;
}

void clear_screan()
{
#ifdef _WIN32
	system("cls");
#endif // _WIN32
#ifdef __linux__
	system('clear');
#endif // __linux__s
}
