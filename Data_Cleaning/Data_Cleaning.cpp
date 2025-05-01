#include <iostream>
#include <fstream>
#include "Cleaning.hpp"

const string reviewsRaw = "..//data//reviews_raw.csv";
const string transactionsRaw = "..//data//transactions_raw.csv";

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
    int reviewSize = getMaxLine(ifstream(reviewsRaw));
    reviewsArray rarr = reviewsArray(reviewSize);
    int transactionSize = getMaxLine(ifstream(transactionsRaw));
    transactionsArray tarr = transactionsArray(transactionSize);
    ifstream rfile(reviewsRaw);
    ifstream tfile(transactionsRaw);
    rarr.insertToArray(rfile);
    tarr.insertToArray(tfile);
    //rarr.showAllReviews();
    //tarr.showAllTransactions();
    Cleaning cr = Cleaning(rarr.list, rarr.getTop());
    cr.reviewCleanNullEntry();
    cr.reviewCleanInvalidRating();
    cr.reviewQuote();
    Cleaning ct = Cleaning(tarr.list, tarr.getTop());
    ct.transactionCleanNullEntry();
    ct.transactionCleanNanEntry();
    ct.transactionCleanInvalidDate();
    cr.exportReview("..//data//reviews_cleaned.csv");
    cr.~Cleaning();
    ct.exportTransaction("..//data//transactions_cleaned.csv");
    ct.~Cleaning();
}