#include "Zipf.h"

Zipf::Zipf(std::string file_name) {
	word_map = new std::map < std::string, int>;
	std::ifstream my_file(file_name);
	std::string word; 
	while (my_file >> word) {
		format_word(word);
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

Zipf::~Zipf() {
	//delete word_map;
}


//removes non-letter characters such as ",',_,?,commas
//lowercase the entire word
void Zipf::format_word(std::string& word) {
	for (unsigned int i = 0; i < strlen(chars); ++i) {
		word.erase(remove(word.begin(), word.end(), chars[i]), word.end());
	}
	for (unsigned int i = 0; i < word.length(); ++i) {
		word[i] = std::tolower(word[i]);
	}
}


void Zipf::sort_map() {

}