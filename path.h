#ifndef PATH_H
#define PATH_H
#include <iostream>
#include <vector>

class Path{
public:
	Path(unsigned int id, unsigned int legth);
	~Path();

	bool is_in(unsigned int id);
	Path* add(unsigned int id, unsigned int legth);
	void print(std::ostream& my_stream, std::vector<std::string> & names);
	unsigned int from();
	unsigned int get_length;

private:
	unsigned int* the_path;
	unsigned int n; //hops numober (how many cities are in the path)
	unsigned int length;
	Path(unsigned int* the_path, unsigned int n, unsigned int length);
};


#endif

