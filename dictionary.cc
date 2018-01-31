#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "word.h"
#include "dictionary.h"

using std::string;
using std::vector;

//----------------------------------USE THE GIVEN DATASTRUCTURES, even if they are inneficient
Dictionary::Dictionary() {
}

bool Dictionary::contains(const string& word) const {
//this function must be fast
		return true;
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
	add_trigram_suggestions(suggestions, word);
	rank_suggestions(suggestions, word);
	trim_suggestions(suggestions);
	return suggestions;
}
