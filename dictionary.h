#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>

class Dictionary {
public:
	Dictionary();
	bool contains(const std::string& word) const;
	std::vector<std::string> get_suggestions(const std::string& word) const;
	void pre_process();
private:
	void add_trigram_suggestions(std:string& suggestions, const std::string& word);
	void rank_suggestions(std:string& suggestions, const std::string& word);
	void trim_suggestions(std:string& suggestions);
	void process_word(string& word);
	bool alphabetic_compare(std::string a, std::string b) {return a<b;} 
};

#endif
