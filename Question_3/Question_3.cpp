#include <iostream>
#include "../Array_Implementation/wordsArray.hpp"

using namespace std;

const string reviewsFile = "../data/reviews_cleaned.csv";

int main()
{
    ifstream rfile(reviewsFile);
    reviewsArray rarr = reviewsArray(rfile);
    reviewsArray reviewOneRating = rarr.linearSearchRating(1);
    wordsArray warr = wordsArray(reviewOneRating);
    warr.showMostUsedWords();
    cout << "\nThe most frequent word is: \"" << warr.showWord(1) << "\"" << endl;
}
