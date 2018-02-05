#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include <unordered_set>
#include <word.h>


class Dictionary {
public:
	Dictionary();//(int length);
	bool contains(const std::string& word) const;
	std::vector<std::string> get_suggestions(const std::string& word) const;
	void pre_process();
private:
	void add_trigram_suggestions(std::vector<std::string>& suggestions, const std::string& word) const;
	void rank_suggestions(std::vector<std::string>& suggestions, const std::string& word) const;
	void trim_suggestions(std::vector<std::string>& suggestions) const;
	void process_word(std::string& word) const;
	static bool alphabetic_compare(std::string a, std::string b);
	void load_words();
	Word create_word(const std::string line);
	std::unordered_set<std::string> wordset;
	static const int max_letters = 25;
	std::vector<Word> words[max_letters + 1];


	//std::vector<Word> words[length + 1];
};

#endif
