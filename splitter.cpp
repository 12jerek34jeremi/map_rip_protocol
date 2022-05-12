#include "splitter.h"
#include <iostream>

Splitter::Splitter() : position(0), text("")
{
}

std::string Splitter::get_next(int mode)
{
	std::size_t start = position, end = 0, len = text.size();
	for (; start < len; start++) {
		char the_char = text[start];
		if (the_char != ' ' && the_char != '\t') {
			break;
		}
	}

	if (start == len) {
		position = start;
		return "";
	}

	if(mode == 1){
		for (end = start; end < len; end++) {
			char the_char = text[end];
			if (the_char == ' ' || the_char == '\t') {
				break;
			}
		}
		position = end;
	}
	else {
		end = text.find(';', start);
		if (end == std::string::npos) {
			end = len;
			position = len;
		}
		else {
			position = end + 1;
		}
	}
	return text.substr(start, end - start);
}

void Splitter::reset(std::string& the_text)
{
	text = the_text;
	position = 0;
}
