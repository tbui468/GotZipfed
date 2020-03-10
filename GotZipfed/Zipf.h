#pragma once
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>


class Zipf {
private:
	std::map<std::string, int>* word_map;
	std::multimap<int, std::string>* final_map;
	const char* chars = "\"'.,?!;:_";
private:
	void format_word(std::string& word);
	std::pair<int, std::string> flip_pair(const std::pair<std::string, int>& pair);
	
public:
	Zipf(const std::string& file_name);
	~Zipf();
	std::multimap<int, std::string > * get_map() { return final_map; };
	void flip_map();
};
