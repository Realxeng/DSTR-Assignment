#include <iostream>
#include <fstream>
#include "..//Array_Implementation/Cleaning.hpp";

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
    rarr.insertToArray(rfile, rarr.list);
    tarr.insertToArray(tfile, tarr.list);
    //rarr.showAllReviews(rarr.list, reviewSize);
    //tarr.showAllTransactions(tarr.list, transactionSize);
    Cleaning cr = Cleaning(rarr);
    cr.reviewCleanNullEntry();
    cr.reviewCleanInvalidRating();
    cr.reviewQuote();
    cr.exportReview("..//data//reviews_cleaned.csv");
    Cleaning ct = Cleaning(tarr);
    ct.transactionCleanNullEntry();
    ct.transactionCleanNanEntry();
    ct.transactionCleanInvalidDate();
    ct.exportTransaction("..//data//transactions_cleaned.csv");
}