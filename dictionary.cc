#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "word.h"
#include "dictionary.h"

using std::string;
using std::vector;
using std::sort;
#include <unordered_set>

//----------------------------------USE THE GIVEN DATASTRUCTURES, even if they are inneficient
Dictionary::Dictionary()  {
	wordset = {};
	pre_process();
	load_words();
}


void Dictionary::load_words() {
	std::ifstream input("words.txt");
	string line;
	string tempstr;
	while(std::getline(input, line)) {
		tempstr = line;
		string delimiter = " ";
	 	tempstr = tempstr.substr(0, tempstr.find(delimiter));
		wordset.insert(tempstr);
		std::cout << "added word: " << tempstr << std::endl;
	}
}

void Dictionary::pre_process() {
	std::ifstream testinput("words.txt");
	if(testinput.good()) {
		std::cout << "words.txt exists, will not process words" << std::endl;
		return;
	}
	std::ifstream input("words");
	std::ofstream output("words.txt", std::ios_base::app | std::ios_base::out);


	string line;
	string tempstr;
	while(std::getline(input, line)) {
		tempstr = line;
		process_word(tempstr);
		output << tempstr << "\n";
	}
}

bool Dictionary::alphabetic_compare (string a, string b) {return a<b;}
void Dictionary::process_word(std::string& word) {
	//make the word lower case
	transform(word.begin(), word.end(), word.begin(), ::tolower);

	//create trigrams of the word
	vector<string> trigrams;
	int size = word.size();
	string tempstr;
	for(int i = 0; i < size; ++i) {
		tempstr = word.substr(i, 3);
		if(tempstr.length() < 3) {
			break;
		}
		trigrams.push_back(tempstr);
	}

	// sort the trigrams in alphabetic order
	sort(trigrams.begin(), trigrams.end(), alphabetic_compare);

	// make the word output format: "word 2 ord wor"

	word.append(" ");
	word.append(std::to_string(trigrams.size())	);
	word.append(" ");
	for(string& s : trigrams) {
		word.append(s);
		word.append(" ");
	}
	word.pop_back();
}


bool Dictionary::contains(const string& word) const {
//this function must be fast
	std::cout << "looking for word: " << word << std::endl;
	if (wordset.count(word) != 0) {
		std::cout << word << " found in set" << std::endl;
		return true;
	}
	return false;
}

vector<string> Dictionary::get_suggestions(const string& word) const {
	//this function is okey to be slower
	// search the dictionary and find candidates for correction
	// 1. Find the words with same length +-1 of the word to be corrected
	// 2. Do another sorting and keep the words witch contaisn atleast half of all the trigrams of the original word
	// 2a. Start with splitting up the original words in trigrams
	// 3. Sort the correction candidates so that the best is first. " The sort key
	//    is the cost to change the misspelled word to one of the candidate words"
	// 4. Keep the 5 best words
	vector<string> suggestions;
	//add_trigram_suggestions(suggestions, word);
	//rank_suggestions(suggestions, word);
	//trim_suggestions(suggestions);
	return suggestions;
}
