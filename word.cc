#include <string>
#include <vector>
#include "word.h"

using std::vector;
using std::string;

//the vector t must be alphaptecially sorted
Word::Word(const string& w, const vector<string>& t) {
	trigrams = t;
	word = w;
}

string Word::get_word() const {
	return word;
}

unsigned int Word::get_matches(const vector<string>& t) const {
	//calculate how many of the trigrams of this word is present in the vector t
	//write an efficient implementation of get matches

	int count = 0;
	int t_size = t.size();

	for(int i = 0; i < t_size; ++i) {
		if(trigrams.contains(t[i])) {
			++count;
		}
	}
	return count;
}
