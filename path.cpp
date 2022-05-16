#include "path.h"
#include <cstring>

Path::Path(unsigned int id, unsigned int length) : n(1), length(length), the_path(new unsigned int[2]{id, length})
{
}

Path::Path(const Path* source): the_path(new unsigned int[source->n * 2]), n(source->n), length(source->length) {

	std::memcpy(the_path, source->the_path, n * 2 * sizeof(unsigned int));
}

Path::Path(unsigned int* the_path, unsigned int n, unsigned int length) : the_path(the_path), n(n), length(length)
{

}


Path::~Path()
{
	delete[] the_path;
}

bool Path::is_in(unsigned int id) const
{
	for (unsigned int i = 0; i < n * 2; i++, i++) {
		if (the_path[i] == id)
			return true;
	}
	return false;
}

Path* Path::add(unsigned int id, unsigned int distance) const
{
	unsigned int* new_path = new unsigned int[n * 2 + 2];
	std::memcpy(new_path, the_path, n * 2 * sizeof(unsigned int));
	new_path[n * 2] = id;
	new_path[n * 2 + 1] = distance;
	return new Path(new_path, n + 1, distance + length);
}

void Path::print(std::ostream& my_stream, const std::vector<std::string>& names) const
{
	for (int i = n * 2 - 2; i >= 0; i--, i--) {
		my_stream << "--> " << names[the_path[i]] << " (" << the_path[i + 1] << ") ";
	}
	my_stream << std::endl;
}

unsigned int Path::from() const
{
	return the_path[0];
}

unsigned int Path::get_length() const
{
	return length;
}




