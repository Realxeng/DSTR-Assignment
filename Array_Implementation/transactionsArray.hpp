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

    void bubbleSortCid() {
        bool swapped;
        //int totalComparisons = top * (top - 1) / 2;
        //int count = 0;

        for (int i = 0; i < top - 1; i++) {
            swapped = false;
            for (int j = 0; j < top - i - 1; j++) {
                //count++;
                if (list[j].cid > list[j + 1].cid) {
                    Transactions temp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = temp;
                    swapped = true;
                }
            }
            //cout << "Progress: " << ((float)count / totalComparisons) * 100 << "%\n";
            if (!swapped) break;
        }
    }

    void bubbleSortDate() {
        bool swapped = false;
        for (int i = 0; i < top - 1; i++) {
            swapped = false;
            for (int j = 0; j < top - i - 1; j++) {
                if (isEarlier(list[j + 1].date, list[j].date)) {
                    Transactions temp = list[j];
					list[j] = list[j + 1];
					list[j + 1] = temp;
					swapped = true;
                }
            }
        }
    }

	void displayByCategory(string category) {
		for (int i = 0; i < top; i++) {
			if (list[i].cat == category) {
				cout << list[i].cid << "|";
				cout << list[i].product << "|";
				cout << list[i].cat << "|";
				cout << list[i].price << "|";
				cout << list[i].date << "|";
				cout << list[i].payment << "|";
				cout << endl;
			}
		}
	}

    void displayByPayment(string payment) {
        for (int i = 0; i < top; i++) {
            if (list[i].payment == payment) {
                cout << list[i].cid << "|";
                cout << list[i].product << "|";
                cout << list[i].cat << "|";
                cout << list[i].price << "|";
                cout << list[i].date << "|";
                cout << list[i].payment << "|";
                cout << endl;
            }
        }
    }

    void displayByProduct(string product) {
        int count = 0;
        for (int i = 0; i < top; i++) {
            if (list[i].product == product) {
                cout << list[i].cid << "|";
                cout << list[i].product << "|";
                cout << list[i].cat << "|";
                cout << list[i].price << "|";
                cout << list[i].date << "|";
                cout << list[i].payment << "|";
                cout << endl;
                count++;
            }
        }
		if (count == 0) {
			cout << "No transaction found for product: " << product << endl;
		}
    }

    transactionsArray linearSearchCategory(string category) {
		Transactions* result = new Transactions[top];
		int count = 0;
        for (int i = 0; i < top; i++) {
            if (list[i].cat == category) {
                result[count] = list[i];
                count++;
            }
        }
        if (count == 0) {
            return transactionsArray();
        }
        else {
            cout << "Transaction(s) found: " << count << endl;
            transactionsArray resultArray = transactionsArray(result, count);
            return resultArray;
        }
    }

    transactionsArray linearSearchPayment(string payment) {
        Transactions* result = new Transactions[top];
        int count = 0;
        for (int i = 0; i < top; i++) {
            if (list[i].payment == payment) {
                result[count] = list[i];
                count++;
            }
        }
        if (count == 0) {
            return transactionsArray();
        }
        else {
            cout << "Transaction(s) found: " << count << endl;
            transactionsArray resultArray = transactionsArray(result, count);
            return resultArray;
        }
    }

    transactionsArray linearSearchProduct(string product) {
        Transactions* result = new Transactions[top];
        int count = 0;
        for (int i = 0; i < top; i++) {
            if (list[i].product == product) {
                result[count] = list[i];
                count++;
            }
        }
        if (count == 0) {
            return transactionsArray();
        }
        else {
            cout << "Transaction(s) found: " << count << endl;
            transactionsArray resultArray = transactionsArray(result, count);
            return resultArray;
        }
    }

    transactionsArray binarySearchCustomer(string cid) {
        bubbleSortCid(); // Ensure the list is sorted by `cid`
        Transactions* result = new Transactions[top];
        int left = 0, right = top - 1, count = 0;

        while (left <= right) {
            int mid = (left + right) / 2;

            if (list[mid].cid == cid) {
                // Collect all matching transactions
                int i = mid;
                while (i >= 0 && list[i].cid == cid) { // Check left side of mid
                    result[count] = list[i];
                    count++;
                    i--;
                }
                i = mid + 1;
                while (i < top && list[i].cid == cid) { // Check right side of mid
                    result[count] = list[i];
                    count++;
                    i++;
                }
                break;
            }

            if (list[mid].cid < cid) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        if (count == 0) {
            return transactionsArray(); // Return an empty array if no match is found
        }
        else {
            cout << "Transaction(s) found: " << count << endl;
            transactionsArray resultArray = transactionsArray(result, count);
            return resultArray;
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