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
	vector<string> suggestions;
	return suggestions;
}
