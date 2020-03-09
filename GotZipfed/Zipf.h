#pragma once
#include <map>
#include <fstream>
#include <string>


class Zipf {
private:
	std::map<std::string, int>* word_map;
private:
	void format_word(std::string& word);
public:
	Zipf(std::string file_name);
	~Zipf();
	std::map<std::string, int>* get_map() { return word_map; };
};
