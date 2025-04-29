#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Transactions
{
    string cid, product, cat, price, date, payment;
};

class transactionsArray {
    int top = 0;
public:
    Transactions* list;
    transactionsArray(int size) {
        list = new Transactions[size];
    }

    ~transactionsArray() {
        delete[] transactionsArray::list;
    }

    void insertToArray(ifstream& file) {
        if (file.is_open()) {
            while (file.good()) {
                string wholeline;
                getline(file, wholeline, '\n');
                istringstream iss(wholeline);
                getline(iss, list[top].cid, ',');
                getline(iss, list[top].product, ',');
                getline(iss, list[top].cat, ',');
                getline(iss, list[top].price, ',');
                getline(iss, list[top].date, ',');
                getline(iss, list[top].payment, ',');
                top++;
            }
        }
    }
};