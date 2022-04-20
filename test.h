#ifdef TESTING_MODE
#define TEST_CASE 2

#include "path.h"
#include <vector>
#include "connection.h"
#include "city.h"
typedef std::vector<std::string> str_vec;

void test_path();
Path* create_path(str_vec& path_cities, std::vector<unsigned int>& distances, str_vec& all_cities);
unsigned get_id(std::string city, str_vec& all_cities);
void test_connection();
void test_city();

void test_path() {
	str_vec names{"Zakopane", "Wieliczka", "Krakow", "Warzawa", "Gdansk", " Wroclaw"};
	unsigned int distances[6]{ 30 ,100, 30, 300, 350, 450 };
	
	Path* the_path = new Path(0, distances[0]);

	for (int i = 1; i < 6; i++) {
		std::cout << "\n\n\nThe path is now: " << std::endl;
		the_path->print(std::cout, names);
		std::cout << "\ntotal length is: " <<the_path->get_length()<< std::endl;
		std::cout << "it is from city of id: " << the_path->from() << std::endl;
		Path* new_path = the_path->add(i, distances[i]);
		delete the_path;
		the_path = new_path;
	}

	std::cout << "\n\n\nThe path is now: " << std::endl;
	the_path->print(std::cout, names);
	std::cout << "\nTotal length is: " << the_path->get_length() << std::endl;
	std::cout << "It is from city of id: " << the_path->from() << std::endl;
	delete the_path;

}

Path* create_path(str_vec &path_cities, std::vector<unsigned int>& distances, str_vec& all_cities){

	auto iter_distances = distances.begin();
	auto iter_city = path_cities.begin();

	Path* the_path = new Path(get_id(*iter_city, all_cities), *iter_distances);

	for (++iter_city, ++iter_distances; iter_city != path_cities.end(); ++iter_city, ++iter_distances) {
		Path* new_path = the_path->add(get_id(*iter_city, all_cities), *iter_distances);
		delete the_path;
		the_path = new_path;
	}
	return the_path;
}

unsigned int get_id(std::string city, str_vec& all_cities)
{
	int i = 0;
	for (auto iter = all_cities.begin(); iter != all_cities.end(); ++iter, ++i) {
		if (*iter == city) return i;
	}
	
	std::cout<<"City "<< city<< " was not in the given list, can't find id!";

	return 0;
}

void test_connection()
{
	str_vec all_cities{ "Krakow", "Kielce", "Warszawa", "Gdansk","Katowice",
		"Lodz", "Szczecin", "Wroclaw", "Rzeszow", "Lublin", "Bialystok"};

	str_vec path_cities1{ "Krakow", "Katowice", "Lodz" };
	std::vector<unsigned int> distances1{ 80, 200, 340 };
	str_vec path_cities2{ "Krakow", "Warszawa" };
	std::vector<unsigned int> distances2{ 300, 350};
	str_vec path_cities3{ "Krakow", "Katowice", "Wroclaw", "Szczecin"};
	std::vector<unsigned int> distances3{ 80, 190, 450, 350};
	str_vec path_cities4{ "Krakow", "Rzeszow", "Lublin", "Warszawa"};
	std::vector<unsigned int> distances4{170, 200, 200, 350};

	Path* path1 = create_path(path_cities1, distances1, all_cities);
	Path* path2 = create_path(path_cities2, distances2, all_cities);
	Path* path3 = create_path(path_cities3, distances3, all_cities);
	Path* path4 = create_path(path_cities4, distances4, all_cities);

	std::cout << "Path1 ("<<path1->get_length() << "):" << std::endl;
	path1->print(std::cout, all_cities);
	std::cout << "Path2 (" << path2->get_length() << "):" << std::endl;
	path2->print(std::cout, all_cities);
	std::cout << "Path3 (" << path3->get_length() << "):" << std::endl;
	path3->print(std::cout, all_cities);
	std::cout << "Path4 (" << path4->get_length() << "):" << std::endl;
	path4->print(std::cout, all_cities);

#if  TEST_CASE == 1
	Connection the_con(path2);
	the_con.print(std::cout, all_cities);
	std::cout << "\n\n";
	the_con.update(path3);
	the_con.print(std::cout, all_cities);
	std::cout << "\n\n";
	the_con.update(path1);
	the_con.print(std::cout, all_cities);
	std::cout << "\n\n";
	the_con.update(path4);
	the_con.print(std::cout, all_cities);
	
#elif TEST_CASE == 2
	Connection the_con(path2);
	the_con.print(std::cout, all_cities);
	std::cout << "\n\n";
	the_con.update(path1);
	the_con.print(std::cout, all_cities);
	std::cout << "\n\n";
	the_con.update(path4);
	the_con.print(std::cout, all_cities);
	delete path3;
#else
	delete path2, delete path3, delete path4;
#endif
	
}

void test_city()
{
	//not finished

	str_vec all_cities{ "Krakow", "Kielce", "Warszawa", "Gdansk","Katowice",
	"Lodz", "Szczecin", "Wroclaw", "Rzeszow", "Lublin", "Bialystok" };

	str_vec path_cities1{ "Krakow", "Katowice", "Lodz" };
	std::vector<unsigned int> distances1{ 80, 200, 340 };
	str_vec path_cities2{ "Krakow", "Warszawa" };
	std::vector<unsigned int> distances2{ 300, 350 };
	str_vec path_cities3{ "Krakow", "Katowice", "Wroclaw", "Szczecin" };
	std::vector<unsigned int> distances3{ 80, 190, 450, 350 };
	str_vec path_cities4{ "Krakow", "Rzeszow", "Lublin", "Warszawa" };
	std::vector<unsigned int> distances4{ 170, 200, 200, 350 };

	str_vec path_cities5{"Bialystok", "Warszawa"};
	std::vector<unsigned int> distances5{200, 350};

	str_vec path_cities6{"Wroclaw", "Lodz"};
	std::vector<unsigned int> distances6{220, 340};
	str_vec path_cities7{"Wroclaw", "Szczecin"};
	std::vector<unsigned int> distances7{450, 350};

	Path* path1 = create_path(path_cities1, distances1, all_cities);
	Path* path2 = create_path(path_cities2, distances2, all_cities);
	Path* path3 = create_path(path_cities3, distances3, all_cities);
	Path* path4 = create_path(path_cities4, distances4, all_cities);
	Path* path5 = create_path(path_cities5, distances5, all_cities);
	Path* path6 = create_path(path_cities6, distances6, all_cities);
	Path* path7 = create_path(path_cities7, distances7, all_cities);
	
	City my_city(get_id("Gdansk", all_cities));
	my_city.update(path1);
	my_city.update(path2);
	my_city.update(path3);
	my_city.update(path4);
	my_city.update(path5);
	my_city.update(path6);
	my_city.update(path7);

	my_city.print_connection(std::cout, all_cities, get_id("Krakow", all_cities));
	std::cout << "\n\n\n";
	my_city.print_connection(std::cout, all_cities, get_id("Bialystok", all_cities));
	std::cout << "\n\n\n";
	my_city.print_connection(std::cout, all_cities, get_id("Wroclaw", all_cities));
	std::cout << "\n\n\n";
}

#endif // !TESTING_MODE
