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
Dictionary::Dictionary(){//(int length)  {
	wordset = {};
	//pre_process();
	load_words();
}


void Dictionary::load_words() {
	std::ifstream input("words.txt");
	string line;
	string tempstr;
	while(std::getline(input, line)) {
		tempstr = line;
		string delimiter = " ";
		Word w = create_word(tempstr); //gets the whole line "word 2 ord wor"
		int word_size = w.get_word().length();
		words[word_size].push_back(w);

	 	tempstr = tempstr.substr(0, tempstr.find(delimiter));
		wordset.insert(tempstr);

		std::cout << "added word: " << tempstr << std::endl;


	}
}

Word Dictionary::create_word(const string line) {
	size_t pos = 0;
	std::string delimiter = " ";
	string tempstr = line;
	string word = tempstr.substr(0, pos = tempstr.find(delimiter));
	tempstr.erase(0, pos + delimiter.length());
	string nbr_trigrams = tempstr.substr(0, pos = tempstr.find(delimiter));
	tempstr.erase(0, pos + delimiter.length());
	int iterations = std::stoi(nbr_trigrams);

	vector<string> vec_trigrams = {};

	for(int i = 0; i < iterations; ++i) {
		string tri = tempstr.substr(0, pos = tempstr.find(delimiter));
		tempstr.erase(0, pos + delimiter.length());
		vec_trigrams.push_back(tri);
	}

	Word w = Word(word, vec_trigrams);
	return w;
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
void Dictionary::process_word(std::string& word) const{
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

	add_trigram_suggestions(suggestions, word);
	rank_suggestions(suggestions, word);
	//trim_suggestions(suggestions);
	return suggestions;
}

void Dictionary::add_trigram_suggestions(vector<string>& suggestions, const string& word) const {
	//ta fram trigrams för word
		std::cout << "In add_tri" << std::endl;
	string temp_word = word;
	process_word(temp_word);


	size_t pos = 0;
	std::string delimiter = " ";
	string tempstr = temp_word;
	string trash = tempstr.substr(0, pos = tempstr.find(delimiter));
	tempstr.erase(0, pos + delimiter.length());
	string nbr_trigrams = tempstr.substr(0, pos = tempstr.find(delimiter));
	tempstr.erase(0, pos + delimiter.length());
	int iterations = std::stoi(nbr_trigrams);

	std::cout << "In add_tri, after stoi" << std::endl;

	vector<string> word_trigrams = {};

	for(int i = 0; i < iterations; ++i) {
		string tri = tempstr.substr(0, pos = tempstr.find(delimiter));
		tempstr.erase(0, pos + delimiter.length());
		word_trigrams.push_back(tri);
	}

	std::cout << "after first for" << std::endl;

	int word_length = word.length();
	int i1 = word.length() - 1;
	int i2 = word.length();
	int i3 = word.length() + 1;


		int matches = 0;

		for(int i = -1; i < 2; ++i) {
			const vector<Word>& v = words[word_length + i];
			//std::cout << "getting vector: " << (i+word_length) << std::endl;
			for(int j = 0; j < v.size(); ++j) {
				//std::cout << "getting matches" << std::endl;

				matches = v[j].get_matches(word_trigrams);
		//		if(matches > 0) {
		//			std::cout << "got matches: " << matches << "which is counted as: " << matches/2 << ", compare to " << iterations <<std::endl;
		//		}

				if(matches >= iterations/2) {
					suggestions.push_back(v[j].get_word());
					std::cout << "suggestion added" << std::endl;



				}
			}
		}
/*
	if(!(i1 < 1)) {
		const vector<Word>& v1 = words[word_length -1];
		for(const Word& w : v1) {
			matches = w.get_matches(word_trigrams);
			if(matches/2 >= iterations) {
				suggestions.push_back(w.get_word());
			}
		}
	}
	if(!(i2 > (max_letters))) {
		const vector<Word>& v2 = words[word_length];
		for(const Word& w : v2) {
			matches = w.get_matches(word_trigrams);
			if(matches/2 >= iterations) {
				suggestions.push_back(w.get_word());
			}
		}
	}
	if(!(i3 > (max_letters +1))) {
		const vector<Word>& v3 = words[word_length +1];
		for(const Word& w : v3) {
			matches = w.get_matches(word_trigrams);
			if(matches/2 >= iterations) {
				suggestions.push_back(w.get_word());
			}
		}
	}
	*/
	std::cout << "In add_tri done" << std::endl;
}


bool compare_pair(const std::pair<int, string>&i, const std::pair<int, string>&j){
	if(i.first != j.first) {
		return i.first < j.first;
	} else {
		return i.second < j.second;
	}
}
void Dictionary::rank_suggestions(vector<string>& suggestions, const string& word) const {
	string p = word;
	vector<std::pair<int, string>> rank_vector = {};

	for(string& q : suggestions) {
		int d[26][26];
		int cost;
		for(int i = 0; i < 26; ++i) {
			d[i][0] = i;
			for(int j = 0; j < 26; ++j) {
				d[0][j] = j;
				int smallest;
				if(p[i] == q[j]) {
					smallest = d[i-1][j-1];
				} else {
					smallest = d[i-1][j-1] + 1;
				}
				if((d[i-1][j] + 1) < smallest) {
					smallest = d[i-1][j] + 1;
				}
				if((d[i][j-1] + 1) < smallest) {
					smallest = d[i][j-1] + 1;
				}


				if(i == 25 && j == 25) {
					int x = d[25][25];
							std::cout << "cost: " << x << std::endl;
				}

				//cost = d[i][j];
			}
		}
		//--------------det går inte att ta ut cost, den är alltid noll VARFÖR:!::!::GSFDLÖGKOÖGKSDF
		cost = d[25][25];
		std::cout << "cost: " << &cost << std::endl;
		std::pair<int, string> pair = std::make_pair(cost, q);
		std::cout << "rank vector, pushing word: " << q << ", cost: " << cost << std::endl;
		rank_vector.push_back(pair);

	}
	std::sort (rank_vector.begin(), rank_vector.end(), compare_pair);
	suggestions.clear();

	for(int i = 0; i < rank_vector.size(); ++i) {
		suggestions.push_back(rank_vector[i].second);
	}


}

//bool ranksort (SugContainer i, SugContainer j) { return (i.rank<j.rank); }
