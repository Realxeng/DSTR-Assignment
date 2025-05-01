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

transactionsArray insertToArray(ifstream& file, transactionsArray list) {
    if (file.is_open()) {
        Transactions temp;
        string header;
        getline(file, header);
        while (file.good()) {
            string wholeline;
            getline(file, wholeline, '\n');
            istringstream iss(wholeline);
            getline(iss, temp.cid, ',');
            getline(iss, temp.product, ',');
            getline(iss, temp.cat, ',');
            getline(iss, temp.price, ',');
            getline(iss, temp.date, ',');
            getline(iss, temp.payment, ',');
            temp.size = list.getTop() + 1;
            list.insertToArray(temp);
            list.setTop(temp.size);
        }
        return list;
    }
    else {
        cerr << "Unable to open file!";
        return list;
    }
}

reviewsArray insertToArray(ifstream& file, reviewsArray list) {
    if (file.is_open()) {
        Reviews temp;
        string header;
        getline(file, header);
        while (file.good()) {
            string wholeline;
            getline(file, wholeline, '\n');
            istringstream iss(wholeline);
            getline(iss, temp.pid, ',');
            getline(iss, temp.cid, ',');
            getline(iss, temp.rating, ',');
            getline(iss, temp.review, ',');
            list.insertToArray(temp);
        }
        return list;
    }
    else {
        cerr << "Unable to open file!";
        return list;
    }
}

int main()
{
    int reviewSize = getMaxLine(ifstream(reviewsFile));
    reviewsArray rarr = reviewsArray(reviewSize);
    int transactionSize = getMaxLine(ifstream(transactionsFile));
    transactionsArray tarr = transactionsArray(transactionSize);
    ifstream rfile(reviewsFile);
    ifstream tfile(transactionsFile);
    rarr = insertToArray(rfile, rarr);
    tarr = insertToArray(tfile, tarr);
    //auto start = high_resolution_clock::now();
    //tarr.insertionSortCid(tfile);
	//tarr.bubbleSortDate();
    //auto stop = high_resolution_clock::now();
    rarr.showAllReviews();
    tarr.showAllTransactions();
    tarr.displayByProduct("Monitor");
	transactionsArray customerTransactions = tarr.binarySearchCustomer("CUST9944");
    //tarr.showTransaction(customerTransactions);
	//auto stop = high_resolution_clock::now();
	//auto duration = duration_cast<microseconds>(stop - start);
	//cout << "Time taken to sort: " << duration.count() << " microseconds" << endl;
	//auto duration = duration_cast<microseconds>(stop - start);
	//cout << "Time taken to sort: " << duration.count() << " microseconds" << endl;
	tfile.close();
	rfile.close();
	return 0;
}