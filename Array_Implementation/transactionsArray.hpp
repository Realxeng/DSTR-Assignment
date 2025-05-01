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

    void insertFromFileRaw(ifstream& file) {
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
                if (ta.list[j + 1].cid < ta.list[j].cid) {
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
};