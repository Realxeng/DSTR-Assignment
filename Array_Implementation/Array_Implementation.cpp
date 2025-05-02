#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "transactionsArray.hpp"
#include "reviewsArray.hpp"

using namespace std;
using namespace std::chrono;

const string reviewsFile = "../data/reviews_cleaned.csv";
const string transactionsFile = "../data/transactions_cleaned.csv";

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
    ifstream rfile(reviewsFile);
    ifstream tfile(transactionsFile);
    //int reviewSize = getMaxLine(ifstream(reviewsFile));
    //reviewsArray rarr = reviewsArray(reviewSize);
    //int transactionSize = getMaxLine(ifstream(transactionsFile));
    transactionsArray tarr = transactionsArray(tfile);
    //rarr.insertFromFile(rfile);
    //auto start = high_resolution_clock::now();
	//rarr = insertionSortRating(rfile, rarr);
    //tarr.showAllTransactions();
    //tarr = tarr.insertionSortCid();
	//tarr = tarr.bubbleSortDate();
    //auto stop = high_resolution_clock::now();
    //rarr.showAllReviews();
	//tarr.showAllTransactions();
    //tarr.displayByProduct("Monitor");
	//rarr.mergeSortByPID();
	//tarr.showTransaction(tarr.binarySearchCustomer("CUST9944"));
    tarr.showTransaction(tarr.linearSearchProduct("Mouse"));
	//auto stop = high_resolution_clock::now();
	//auto duration = duration_cast<microseconds>(stop - start);
	//cout << "Time taken to sort: " << duration.count() << " microseconds" << endl;
	//auto duration = duration_cast<microseconds>(stop - start);
	//cout << "Time taken to sort: " << duration.count() << " microseconds" << endl;
    if (tfile.is_open()) tfile.close();
	if (rfile.is_open()) rfile.close();
	delete[] tarr.list;
	//delete[] rarr.list;
	//delete[] rarr;
	return 0;
}