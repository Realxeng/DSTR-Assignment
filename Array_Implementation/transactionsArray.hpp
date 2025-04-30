#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Transactions
{
    string cid, product, cat, price, date, payment;
};

class transactionsArray
{
    int top = 0;
public:
    Transactions* list;
	transactionsArray() {
        list = NULL;
	}
    transactionsArray(Transactions* list, int top) {
		this->list = list;
        this->top = top;
    }
    transactionsArray(int size) {
        list = new Transactions[size];
    }

    int getTop() { return top; }
	void setTop(int top) { this->top = top; }

    void insertToArray(ifstream& file, Transactions* list) {
        if (file.is_open()) {
            string header;
            getline(file, header);
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

    Transactions* deleteAtIndex(Transactions* list, int index) {
        if (index < 0 || index > top) {
            cout << "No transaction found at index " << index << ". Top: " << top << endl;
            return list;
        }
        for (int i = index; i < top - 1; i++) {
            list[i] = list[i + 1];
        }
        top--;
        return list;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index > top) {
            cout << "Nothing to delete!";
            return;
        }
        for (int i = index; i < top - 1; i++) {
            list[i] = list[i + 1];
        }
        top--;
    }

    void showAllTransactions() {
        for (int lines = 0; lines <= top; lines++) {
            cout << list[lines].cid << "|";
            cout << list[lines].product << "|";
            cout << list[lines].cat << "|";
            cout << list[lines].price << "|";
            cout << list[lines].date << "|";
            cout << list[lines].payment << "|";
            cout << endl;
        }
    }
};