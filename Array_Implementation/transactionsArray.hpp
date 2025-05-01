#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Transactions
{
    string cid, product, cat, price, date, payment;
    int size = 0;
};

class transactionsArray
{
    int top = 0;
public:
    Transactions* list;
	transactionsArray() {
        list = nullptr;
        top = 0;
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

    void insertToArray(Transactions data) {
		list[top] = data;
        top++;
    }

    void insertFromFile(ifstream& file) {
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
                getline(iss, temp.payment, '\n');
                temp.size = top + 1;
                insertToArray(temp);
                setTop(temp.size);
            }
        }
        else {
            cerr << "Unable to open file!";
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

	bool isEarlier(string date1, string date2) {
		return date1 < date2;
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
		if (top == 0) {
			cout << "No transaction to be displayed!" << endl;
			return;
		}
        for (int lines = 0; lines < top; lines++) {
            cout << list[lines].cid << "|";
            cout << list[lines].product << "|";
            cout << list[lines].cat << "|";
            cout << list[lines].price << "|";
            cout << list[lines].date << "|";
            cout << list[lines].payment << "|";
            cout << endl;
        }
    }

    void showTransaction(transactionsArray tarr) {
		if (tarr.getTop() > 0) {
			for (int i = 0; i < tarr.getTop(); i++) {
				cout << tarr.list[i].cid << "|";
				cout << tarr.list[i].product << "|";
				cout << tarr.list[i].cat << "|";
				cout << tarr.list[i].price << "|";
				cout << tarr.list[i].date << "|";
				cout << tarr.list[i].payment << "|";
				cout << endl;
			}
		}
        else {
            cout << "No transaction to be displayed!" << endl;
        }
	}
};