#include <iostream>
#include <fstream>
#include <string>
#include "bubbleSort.h"

using namespace std;

class reviewsArray {
public:
    string* list;
    reviewsArray(int size) {
        list = new string[size * 4];
    }
    ~reviewsArray() {
        delete[] list;
    }
};

class transactionsArray {
public:
    string* list;
    transactionsArray(int size) {
        list = new string[size * 6];
    }
    ~transactionsArray() {
        delete[] list;
    }
};

int getMaxLine(string filename) {
    ifstream file(filename);
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

void showAll(string* list, int colsize, int rowsize) {
    for (int lines = 0; lines < rowsize; lines++) {
        for (int line = 0; line < colsize; line++) {
            cout << list[lines][line] << ", ";
        }
        cout << endl;
    }
}

int main()
{
    int reviewSize = getMaxLine("..//data/reviews_raw.txt");
    reviewsArray rarr = reviewsArray(reviewSize);
    int transactionSize = getMaxLine("..//data/transactions_raw.txt");
    transactionsArray tarr = transactionsArray(transactionSize);
    showAll(tarr.list, 4, reviewSize);
}