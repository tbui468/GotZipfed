#include "Zipf.h"

Zipf::Zipf(std::string file_name) {
	word_map = new std::map < std::string, int>;
	std::ifstream my_file(file_name);
	std::string word; 
	while (my_file >> word) {
		std::map<std::string, int>::iterator iter = word_map->find(word);
		if (iter == word_map->end()) {
			word_map->insert(std::pair<std::string, int>(word, 1));
		}
		else {
			iter->second++;
		}
	}
	my_file.close();
}

//removes non-letter characters such as ",',_,?,commas
//lowercase the entire word
void Zipf::format_word(std::string& word) {

}

Zipf::~Zipf() {
	delete word_map;
}