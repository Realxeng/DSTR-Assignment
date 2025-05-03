#pragma once
#include <algorithm>
#include <cctype>
#include "reviewsArray.hpp"

struct Words
{
	string word;
	int count = 0;
};

class wordsArray
{
private:
	Words* words;
	int size = 0;
	Words* addNewWords(Words* words, string word);
	Words* mostUsedWords(reviewsArray& ra);
	string cleanWord(string str);
public:
	wordsArray();
	wordsArray(reviewsArray& ra);
	~wordsArray();
	void showMostUsedWords();
};
