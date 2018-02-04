#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include <unordered_set>


class Dictionary {
public:
	Dictionary(int length);
	bool contains(const std::string& word) const;
	std::vector<std::string> get_suggestions(const std::string& word) const;
	void pre_process();
private:
	void add_trigram_suggestions(std::vector<string>& suggestions, const std::string& word);
	void rank_suggestions(std::string& suggestions, const std::string& word);
	void trim_suggestions(std::string& suggestions);
	void process_word(std::string& word);
	static bool alphabetic_compare(std::string a, std::string b);
	void load_words();
	std::unordered_set<std::string> wordset;
	std::vector<Word> words[length];
};

#endif
