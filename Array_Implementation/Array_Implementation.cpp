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

transactionsArray bubbleSortDate(transactionsArray ta)
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
        if (!swapped) break;
    }
    return ta;
}

transactionsArray bubbleSortCid(transactionsArray ta)
{
    bool swapped = false;
    for (int i = 0; i < ta.getTop() - 1; i++) {
        swapped = false;
        for (int j = 0; j < ta.getTop() - i - 1; j++) {
            if (ta.list[j+1].cid < ta.list[j].cid) {
                Transactions temp = ta.list[j];
                ta.list[j] = ta.list[j + 1];
                ta.list[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    return ta;
}

transactionsArray linearSearchCategory(transactionsArray ta, string cat) {
    int count = 0;
    for (int i = 0; i < ta.getTop(); i++) {
        if (ta.list[i].cat == cat) {
            count++;
        }
    }
    if (count == 0) {
        return transactionsArray();
    }
    cout << "Transaction(s) found: " << count << endl;
    Transactions* result = new Transactions[count];
	int index = 0;
    for (int i = 0; i < count; i++) {
        if (ta.list[i].cat == cat) {
            result[index] = ta.list[i];
			index++;
        }
    }
    transactionsArray resultArray = transactionsArray(result, count);
    delete[] result;
    return resultArray;
}

transactionsArray linearSearchPayment(transactionsArray ta, string payment) {
	int count = 0;
    for (int i = 0; i < ta.getTop(); i++) {
        if (ta.list[i].payment == payment) {
            count++;
        }
    }
    if (count == 0) {
        return transactionsArray();
    }
    cout << "Transaction(s) found: " << count << endl;
    Transactions* result = new Transactions[count];
	int index = 0;
    for (int i = 0; i < count; i++) {
        if (ta.list[i].payment == payment) {
            result[index] = ta.list[i];
			index++;
        }
    }
    transactionsArray resultArray = transactionsArray(result, count);
    delete[] result;
    return resultArray;
}

transactionsArray linearSearchProduct(transactionsArray ta, string product) {
    int count = 0;
    for (int i = 0; i < ta.getTop(); i++) {
        if (ta.list[i].product == product) {
            count++;
        }
    }
    if (count == 0) {
        return transactionsArray();
    }
    cout << "Transaction(s) found: " << count << endl;
    Transactions* result = new Transactions[count];
	int index = 0;
    for (int i = 0; i < count; i++) {
        if (ta.list[i].product == product) {
            result[index] = ta.list[i];
            index++;
        }
    }
    transactionsArray resultArray = transactionsArray(result, count);
    delete[] result;
    return resultArray;
}

transactionsArray binarySearchCustomer(transactionsArray tarr, string cid) {  
   transactionsArray ta = bubbleSortCid(tarr); // Ensure the list is sorted by `cid`  
   int maxSize = ta.getTop();  
   Transactions* result = new Transactions[maxSize]; // Allocate memory based on the maximum possible size  
   int left = 0, right = maxSize - 1, count = 0;  

   while (left <= right) {  
       int mid = (left + right) / 2;  

       if (ta.list[mid].cid == cid) {  
           // Collect all matching transactions  
           int i = mid;  
           while (i >= 0 && ta.list[i].cid == cid) { // Check left side of mid  
               result[count] = ta.list[i];  
               count++;  
               i--;  
           }  
           i = mid + 1;  
           while (i < maxSize && ta.list[i].cid == cid) { // Check right side of mid  
               result[count] = ta.list[i];  
               count++;  
               i++;  
           }  
           break;  
       }  

       if (ta.list[mid].cid < cid) {  
           left = mid + 1;  
       }  
       else {  
           right = mid - 1;  
       }  
   }  

   if (count == 0) {  
       delete[] result; // Free allocated memory if no match is found  
       return transactionsArray(); // Return an empty array  
   }  
   else {  
       cout << "Transaction(s) found: " << count << endl;  
       Transactions* list = new Transactions[count];  
       for (int i = 0; i < count; i++) {  
           list[i] = result[i];  
       }  
       delete[] result; // Free the temporary result array  
       transactionsArray resultArray = transactionsArray(list, count);  
       return resultArray;  
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
    //auto start = high_resolution_clock::now();
	//rarr = insertionSortRating(rfile, rarr);
    tarr.insertFromFile(tfile);
    //tarr = insertionSortCid(tfile, tarr);
	//tarr = bubbleSortDate(tarr);
    //auto stop = high_resolution_clock::now();
    //rarr.showAllReviews();
    //tarr.showAllTransactions();
    //tarr.displayByProduct("Monitor");
	tarr.showTransaction(binarySearchCustomer(tarr, "CUST9944"));
    //tarr.showTransaction(linearSearchProduct(tarr, "Mouse"));
	//auto stop = high_resolution_clock::now();
	//auto duration = duration_cast<microseconds>(stop - start);
	//cout << "Time taken to sort: " << duration.count() << " microseconds" << endl;
	//auto duration = duration_cast<microseconds>(stop - start);
	//cout << "Time taken to sort: " << duration.count() << " microseconds" << endl;
	tfile.close();
	rfile.close();
	return 0;
}