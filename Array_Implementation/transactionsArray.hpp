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

    void insertToArray(ifstream& file) {
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

    void insertToArray(Transactions data) {
		list[top] = data;
    }

	void insertionSortCid(ifstream& file) {
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
                getline(iss, temp.payment, ',');
                int i = top - 1;
				if (temp.cid.length() < 8) {
					cout << "Invalid transaction ID: " << temp.cid << endl;
					continue;
				}
                while (i>=0 && stoi(temp.cid.substr(4,4)) < stoi(list[i].cid.substr(4,4))) {
					list[i + 1] = list[i];
                    i--;
                }
                //cout << " Record: " << top << " Progress: " << (float)top / 4128 * 100 << "%\n";
				list[i + 1] = temp;
                top++;
            }
        }
        else {
			cerr << "Unable to open file!";
        }
        file.close();
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
        for (int i = 0; i < top; i++) {
            if (list[i].product == product) {
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

    Transactions* linearSearchCategory(string category) {
		Transactions* result = new Transactions[top];
		int count = 0;
        for (int i = 0; i < top; i++) {
            if (list[i].cat == category) {
                result[count] = list[i];
                count++;
            }
        }
		return result;
    }

    Transactions* linearSearchPayment(string payment) {
        Transactions* result = new Transactions[top];
        int count = 0;
        for (int i = 0; i < top; i++) {
            if (list[i].payment == payment) {
                result[count] = list[i];
                count++;
            }
        }
        return result;
    }

    Transactions* linearSearchProduct(string product) {
        Transactions* result = new Transactions[top];
        int count = 0;
        for (int i = 0; i < top; i++) {
            if (list[i].product == product) {
                result[count] = list[i];
                count++;
            }
        }
        return result;
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

    string convertDate(string sdate) {
        int day, month, year;
        sscanf_s(sdate.c_str(), "%d/%d/%d", &day, &month, &year);
        return to_string(year) + "/" + (month < 10 ? "0" : "") + to_string(month) + "/" + (day < 10 ? "0" : "") + to_string(day);
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
};