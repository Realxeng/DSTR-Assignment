#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "transactionsArray.hpp"
#include "reviewsArray.hpp"

using namespace std;
const string reviewsFile = "..//data//reviews_cleaned.csv";
const string transactionsFile = "..//data//transactions_cleaned.csv";

int getMaxLine(ifstream file) {
    int count = 0;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            count++;
        }
    }
    else {
        cerr << "Unable to open file!";
    }
    return count;
}

int main()
{
    int reviewSize = getMaxLine(ifstream(reviewsFile));
    reviewsArray rarr = reviewsArray(reviewSize);
    int transactionSize = getMaxLine(ifstream(transactionsFile));
    transactionsArray tarr = transactionsArray(transactionSize);
    ifstream rfile(reviewsFile);
    ifstream tfile(transactionsFile);
    rarr.insertToArray(rfile);
    tarr.insertionSort(tfile);
    //rarr.showAllReviews();
    tarr.showAllTransactions();
}