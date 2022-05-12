#ifndef SPLITTER_H
#include <string>

class Splitter
{
public:
	Splitter();
	std::string get_next(int mode = 1);
	void reset(std::string & the_text);

private:
	std::string text;
	size_t position;
};

#endif // !SPLITTER_H



