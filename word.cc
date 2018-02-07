#include <string>
#include <vector>
#include "word.h"
#include <iostream>

using std::vector;
using std::string;

//the vector t must be alphaptecially sorted
Word::Word(const string& w, const vector<string>& t) : trigrams(t), word(w) {

}

string Word::get_word() const {
	return word;
}

unsigned int Word::get_matches(const vector<string>& t) const {
	//calculate how many of the trigrams of this word is present in the vector t
	//write an efficient implementation of get matches
	//std::cout << "get_matches for word: " << get_word() << std::endl;

	int count = 0;

	int pointer_t = 0;
	int pointer_trigrams = 0;

	//std::cout << "t size: " << t.size() << std::endl;
	//std::cout << "trigrams size: " << trigrams.size() << std::endl;


	while((pointer_t != t.size()) && (pointer_trigrams != trigrams.size())) {
		//std::cout << "testing: " << t[pointer_t] << " and: " << trigrams[pointer_trigrams] << std::endl;
		if(t[pointer_t] < trigrams[pointer_trigrams]) {
				++pointer_t;
		} else if(t[pointer_t] == trigrams[pointer_trigrams]) {
				++pointer_t;
				++pointer_trigrams;
				++count;
				//std::cout << "trigram count++, count: " << count << std::endl;
		} else {
			++pointer_trigrams;
		}
 }


	return count;
}
