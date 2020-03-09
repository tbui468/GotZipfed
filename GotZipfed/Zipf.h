#pragma once
#include <map>
#include <fstream>
#include <string>
#include <algorithm>


class Zipf {
private:
	std::map<std::string, int>* word_map;
	const char* chars = "\"'.,?!;:_";
private:
	void format_word(std::string& word);
public:
	Zipf(std::string file_name);
	~Zipf();
	std::map<std::string, int>* get_map() { return word_map; };
};
