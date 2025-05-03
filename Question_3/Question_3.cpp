#include <iostream>
#include <chrono>
#include "../Array_Implementation/wordsArray.hpp"

using namespace std;
using namespace std::chrono;

const string reviewsFile = "../data/reviews_cleaned.csv";

int main()
{
    ifstream rfile(reviewsFile);
    reviewsArray rarr = reviewsArray(rfile);
    auto startarray = high_resolution_clock::now();
    reviewsArray reviewOneRating = rarr.linearSearchRating(1);
    wordsArray warr = wordsArray(reviewOneRating);
    auto stoparray = high_resolution_clock::now();
    auto durationarray = duration_cast<microseconds>(stoparray - startarray);
    warr.showMostUsedWords();
    cout << "\nThe most frequent word is: \"" << warr.showWord(1) << "\"" << endl;
    cout << "Time taken to show the most frequent word with array and linear search is: " << durationarray.count() << " microseconds" << endl;
}
