#include "wordsArray.hpp"

using namespace std;

wordsArray::wordsArray() {
	this->words = new Words[1];
	this->size = 0;
}
wordsArray::wordsArray(reviewsArray& ra, int i) {
	if (i == 0) {
		this->words = mostUsedWords(ra);
	}
	if (i == 1) {
		this->words = mostFrequentRating(ra);
	}
}
wordsArray::~wordsArray() {

}

Words* wordsArray::addNewWords(Words* words, string word) {
	word = cleanWord(word);
	if (size == 0) {
		words[0].word = word;
		words[0].count = 1;
		size++;
		return words;
	}
	for (int i = 0; i < size; i++) {
		if (words[i].word == word) {
			words[i].count++;
			// sort the array by count
			for (int j = i; j > 0 && words[j].count > words[j - 1].count; j--) {
				Words temp = words[j];
				words[j] = words[j - 1];
				words[j - 1] = temp;
			}
			return words;
		}
	}
	size++;
	Words* newWords = new Words[size];
	for (int i = 0; i < size-1; i++) {
		newWords[i] = words[i];
	}
	newWords[size-1].word = word;
	newWords[size-1].count = 1;
	delete[] words;
	return newWords;
}

Words* wordsArray::mostUsedWords(reviewsArray& ra) {
	Words* words = new Words[1];
	size = 0;
	for (int i = 0; i < ra.getTop(); i++) {
		string line = ra.list[i].review;
		istringstream iss(line);
		string word;
		for (int i = 0; i < line.length(); i++) {
			if (getline(iss, word, ' ')) {
				if (word.length() > 0) {
					words = addNewWords(words, word);
				}
			}
		}
	}
	return words;
}

Words* wordsArray::mostFrequentRating(reviewsArray& ra) {
	Words* words = new Words[1];
	size = 0;
	for (int i = 0; i < ra.getTop(); i++) {
		string rating = ra.list[i].rating;
		addNewWords(words, rating);
	}
	return words;
}

string wordsArray::cleanWord(string str) {
	// Remove punctuation and convert to lowercase
	str.erase(remove_if(str.begin(), str.end(), ::ispunct), str.end());
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

void wordsArray::showMostUsedWords() {
	if (size > 0) {
		for (int i = 0; i < size; i++) {
			cout << words[i].count << " Occurrence of the word: \"" << words[i].word << "\"" << endl;
		}
	}
	else {
		cout << "No words added!";
	}
}

void wordsArray::showMostFrequentRatings() {
	if (size > 0) {
		for (int i = 0; i < size; i++) {
			cout << words[i].count << " Occurrence of the rating: \"" << words[i].word << "\"" << endl;
		}
	}
	else {
		cout << "No ratings added!";
	}
}

string wordsArray::showWord(int rank) {
	return words[rank - 1].word;
}
