#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "transactionsArray.hpp";
#include "reviewsArray.hpp";

using namespace std;
const string reviewsFile = "..//data//reviews_raw.csv";
const string transactionsFile = "..//data//transactions_raw.csv";

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
    rarr.insertToArray(rfile, rarr.list);
    tarr.insertToArray(tfile, tarr.list);
    rarr.showAllReviews(rarr.list, reviewSize);
    tarr.showAllTransactions(tarr.list, transactionSize);
}