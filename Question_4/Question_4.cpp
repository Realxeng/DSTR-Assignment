#include <iostream>
#include "../Array_Implementation/reviewsArray.hpp"
#include "../Array_Implementation/wordsArray.hpp"

using namespace std;

const string reviewsFile = "../data/reviews_cleaned.csv";

//Q: Which rating occurs most frequently for product PROD820 in the reviews dataset?

int main() {
	ifstream rfile(reviewsFile);
	reviewsArray rarr = reviewsArray(rfile);
	string pid;
	cout << "Enter the Product ID your want to search: ";
	cin >> pid;
	cout << endl;
	reviewsArray raProduct = rarr.linearSearchProduct(pid);
	wordsArray wa = wordsArray(raProduct, 1);
	wa.showMostFrequentRatings();
	cout << "The most frequent rating for "<< raProduct.list[0].pid<< " is: " << wa.showWord(1);
}