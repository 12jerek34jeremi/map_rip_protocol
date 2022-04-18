#ifndef SLL_CITY_H
#define SLL_CITY_H
#include "sll.h"
#include <iostream>
#include "city.h"

class SLLCities : public SLL<unsigned int, City>
{
public:
	SLLCities();
	~SLLCities();
	City& operator[](std::string);
	bool is_in(std::string);
	City& get(std::string);

};

#endif // !SLL_CONNECTION_H