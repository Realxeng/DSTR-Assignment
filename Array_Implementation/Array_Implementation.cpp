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

transactionsArray insertionSortCid(ifstream& file, transactionsArray ar)
{
    if (file.is_open()) {
        Transactions temp;
        string line;
        while (getline(file, line, '\n')) {
            istringstream iss(line);
            getline(iss, temp.cid, ',');
            getline(iss, temp.product, ',');
            getline(iss, temp.cat, ',');
            getline(iss, temp.price, ',');
            getline(iss, temp.date, ',');
            getline(iss, temp.payment, '\n');
            int size = ar.getTop();
            int i = ar.getTop() - 1;
            while (i >= 0 && temp.cid < ar.list[i].cid) {
                ar.list[i + 1] = ar.list[i];
                i--;
            }
            //cout << " Record: " << top << " Progress: " << (float)top / 4128 * 100 << "%\n";
            ar.list[i + 1] = temp;
            size++;
            ar.setTop(size);
        }
    }
    else {
        cerr << "Unable to open file!";
    }
    file.close();
    return ar;
}

reviewsArray insertionSortRating(ifstream& file, reviewsArray ar)
{
    if (file.is_open()) {
        Reviews temp;
        string line;
        while (getline(file, line, '\n')) {
            istringstream iss(line);
            getline(iss, temp.pid, ',');
            getline(iss, temp.cid, ',');
            getline(iss, temp.rating, ',');
            getline(iss, temp.review, '\n');
            int size = ar.getTop();
            int i = ar.getTop() - 1;
            while (i >= 0 && temp.rating <= ar.list[i].rating) {
				if (temp.rating == ar.list[i].rating) {
					if (temp.pid <= ar.list[i].pid) {
                        if (temp.pid == ar.list[i].pid) {
							if (temp.cid < ar.list[i].cid) {
								ar.list[i + 1] = ar.list[i];
								i--;
							}
							else {
								break;
							}
                        }
					}
				}
                ar.list[i + 1] = ar.list[i];
                i--;
            }
            //cout << " Record: " << top << " Progress: " << (float)top / 4128 * 100 << "%\n";
            ar.list[i + 1] = temp;
            size++;
            ar.setTop(size);
        }
    }
    else {
        cerr << "Unable to open file!";
    }
    file.close();
    return ar;
}

void bubbleSortDate(transactionsArray ta)
{
    bool swapped = false;
    for (int i = 0; i < ta.getTop() - 1; i++) {
        swapped = false;
        for (int j = 0; j < ta.getTop() - i - 1; j++) {
            if (ta.isEarlier(ta.list[j + 1].date, ta.list[j].date)) {
                Transactions temp = ta.list[j];
                ta.list[j] = ta.list[j + 1];
                ta.list[j + 1] = temp;
                swapped = true;
            }
        }
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
    //rarr.insertFromFile(rfile);
	rarr = insertionSortRating(rfile, rarr);
    //tarr.insertFromFile(tfile);
    //auto start = high_resolution_clock::now();
    //tarr = insertionSortCid(tfile, tarr);
	//tarr.bubbleSortDate();
    //auto stop = high_resolution_clock::now();
    rarr.showAllReviews();
    //tarr.showAllTransactions();
    //tarr.displayByProduct("Monitor");
	//transactionsArray customerTransactions = tarr.binarySearchCustomer("CUST9944");
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