#include "transactionsArray.hpp"

using namespace std;
using namespace std::chrono;

int transactionsArray::getMaxLine(ifstream& file) {
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
    file.clear(); // Clear EOF flag
    file.seekg(0, ios::beg); // Move cursor to the beginning
    return count;
}

bool transactionsArray::isEarlier(string date1, string date2) {
    return date1 < date2;
}

string transactionsArray::cleanWord(string str) {
    str.erase(remove_if(str.begin(), str.end(), ::ispunct), str.end());
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

transactionsArray::transactionsArray() {
    list = nullptr;
    top = 0, max = 0;
}
transactionsArray::transactionsArray(Transactions* list, int top) {
    this->top = this->max = top;
    this->list = new Transactions[top];
    for (int i = 0; i < top; i++) {
        this->list[i] = list[i];
    }
}
transactionsArray::transactionsArray(int size) {
    list = new Transactions[size];
    this->max = size;
}
transactionsArray::transactionsArray(ifstream& file) {
    this->max = getMaxLine(file);
    this->top = 0;
	list = new Transactions[max];
	insertFromFile(file);
}
transactionsArray::~transactionsArray() {
    /*if (list != nullptr) {
        delete[] list;
        list = nullptr;
    }*/
}


int transactionsArray::getTop() { return top; }
void transactionsArray::setTop(int top) { this->top = top; }
int transactionsArray::getMax() { return max; }
void transactionsArray::setMax(int max) { this->max = max; }

void transactionsArray::insertToArray(Transactions data) {
	list[top] = data;
    top++;
}

void transactionsArray::insertToArray(Transactions data, int index) {
	if (index < 0 || index > top) {
		cout << "Invalid index!" << endl;
		return;
	}
	for (int i = index; i < top; i++) {
		list[i] = list[i + 1];
	}
}

void transactionsArray::insertFromFile(ifstream& file) {
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
            insertToArray(temp);
        }
    }
    else {
        cerr << "Unable to open file!";
    }
    file.close();
}

void transactionsArray::insertFromFileRaw(ifstream& file) {
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
            insertToArray(temp);
        }
    }
    else {
        cerr << "Unable to open file!";
    }
	file.close();
}

Transactions* transactionsArray::deleteAtIndex(Transactions* list, int index) {
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

void transactionsArray::deleteAtIndex(int index) {
    if (index < 0 || index >= top) {
        cout << "Nothing to delete!";
        return;
    }
    for (int i = index; i < top - 1; i++) {
        list[i] = list[i + 1];
    }
    top--;
}

void transactionsArray::showAllTransactions() {
	if (max == 0) {
		cout << "No transaction to be displayed!" << endl;
		return;
	}
    for (int lines = 0; lines < max; lines++) {
        cout << list[lines].cid << "|";
        cout << list[lines].product << "|";
        cout << list[lines].cat << "|";
        cout << list[lines].price << "|";
        cout << list[lines].date << "|";
        cout << list[lines].payment << "|";
        cout << endl;
    }
}

void transactionsArray::showTransaction(transactionsArray tarr) {
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

transactionsArray transactionsArray::insertionSortCid()
{
    //create new transactions array
    Transactions temp;
    transactionsArray result = transactionsArray(top);
    //iterate through the source array
    for (int i = 0; i < top; i++) {
        temp = list[i];
        //Assign the first value to the new array
        if (i == 0) {
            result.list[0] = temp;
        }
        else{
			int j = 0;
            //check if the value in the array is larger than the match value
            while (j<i && temp.cid > result.list[j].cid) {
                j++;
                continue;
            }
            //assign the value at the end if the value is largest
            if (j == i) {
				result.list[i] = temp;
			}
            //move all the larger value forward
			else {
				for (int k = i; k > j; k--) {
					result.list[k] = result.list[k - 1];
				}
                //assign the value to the space created
				result.list[j] = temp;
			}
        }
        //cout << " Record: " << top << " Progress: " << (float)top / 4128 * 100 << "%\n";
    }
    return result;
}

transactionsArray transactionsArray::insertionSortDate()
{
    Transactions temp;
    transactionsArray result = transactionsArray(top);
    for (int i = 0; i < top; i++) {
        temp = list[i];
        if (i == 0) {
            result.list[0] = temp;
        }
        else {
            int j = 0;
            while (j<i && temp.date > result.list[j].date) {
                j++;
                continue;
            }
            if (j == i) {
                result.list[i] = temp;
            }
            else {
                for (int k = i; k > j; k--) {
                    result.list[k] = result.list[k - 1];
                }
                result.list[j] = temp;
            }
        }
        //cout << " Record: " << top << " Progress: " << (float)top / 4128 * 100 << "%\n";
    }
    return result;
}

transactionsArray transactionsArray::bubbleSortDate()
{
    //create a new array to be returned
	transactionsArray ta = transactionsArray(top);
    //copy all the values
	ta.list = this->list;
    bool swapped = false;
    //iterate through the whole array values
    for (int i = 0; i < top - 1; i++) {
        swapped = false;
        //iterate the value through the whole array
        for (int j = 0; j < top - i - 1; j++) {
            //check if the next value is smaller
            if (ta.isEarlier(ta.list[j + 1].date, ta.list[j].date)) {
                //move the next value backward
                Transactions temp = ta.list[j];
                ta.list[j] = ta.list[j + 1];
                ta.list[j + 1] = temp;
                swapped = true;
            }
        }
        //continue next iteration if its swapped
        if (!swapped) break;
    }
    //return the result
    return ta;
}

transactionsArray transactionsArray::bubbleSortCid()
{
    transactionsArray ta = transactionsArray(top);
    ta.list = this->list;
    bool swapped = false;
    for (int i = 0; i < top - 1; i++) {
        swapped = false;
        for (int j = 0; j < top - i - 1; j++) {
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

transactionsArray transactionsArray::linearSearchCategory(string cat) {
    int count = 0;
    //create a temporary list
    Transactions* result = new Transactions[top];
    //iterate through the whole array
    for (int i = 0; i < top; i++) {
        //find the matching record
        if (cleanWord(list[i].cat) == cleanWord(cat)) {
            //assign the matching record to the list
            result[count] = list[i];
            count++;
        }
    }
    //check if there are any matches
    if (count == 0) {
        delete[] result;
        //return empty array if no match
        return transactionsArray();
    }
    //return array with the results
    transactionsArray resultArray = transactionsArray(result, count);
    return resultArray;
}

transactionsArray transactionsArray::linearSearchPayment(string payment) {
    int count = 0;
    Transactions* result = new Transactions[top];
    for (int i = 0; i < top; i++) {
        if (cleanWord(list[i].payment) == cleanWord(payment)) {
            result[count] = list[i];
            count++;
        }
    }
    //cout << "Transaction(s) found: " << count << endl;
    if (count == 0) {
        delete[] result;
        return transactionsArray();
    }
    transactionsArray resultArray = transactionsArray(result, count);
    return resultArray;
}

transactionsArray transactionsArray::linearSearchProduct(string product) {
    int count = 0;
    Transactions* result = new Transactions[top];
    for (int i = 0; i < top; i++) {
        if (cleanWord(list[i].product) == cleanWord(product)) {
            result[count] = list[i];
            count++;
        }
    }
    //cout << "Transaction(s) found: " << count << endl;
    if (count == 0) {
        delete[] result;
        return transactionsArray();
    }
    transactionsArray resultArray = transactionsArray(result, count);
    return resultArray;
}

transactionsArray transactionsArray::binarySearchCustomer(string cid) {
    transactionsArray ta = bubbleSortCid(); // Ensure the list is sorted by `cid`
    auto start = high_resolution_clock::now();
    int maxSize = top;
    Transactions* result = new Transactions[maxSize]; // Allocate memory based on the maximum possible size  
    int left = 0, right = maxSize - 1, count = 0;

    //iterate until the end of the array
    while (left <= right) {
        //find the middle
        int mid = (left + right) / 2;

        //check if the middle is the match
        if (cleanWord(ta.list[mid].cid) == cleanWord(cid)) {
            // Collect all matching transactions  
            int i = mid;
            while (i >= 0 && cleanWord(ta.list[i].cid) == cleanWord(cid)) { // Check left side of mid  
                result[count] = ta.list[i];
                count++;
                i--;
            }
            i = mid + 1;
            while (i < maxSize && cleanWord(ta.list[i].cid) == cleanWord(cid)) { // Check right side of mid  
                result[count] = ta.list[i];
                count++;
                i++;
            }
            break;
        }
        
        //eliminate the first half if the mid is smaller than the match
        if (cleanWord(ta.list[mid].cid) < cleanWord(cid)) {
            left = mid + 1;
        }
        //eliminate the second half if the mid is already larger
        else {
            right = mid - 1;
        }
    }

    if (count == 0) {
        delete[] result; // Free allocated memory if no match is found  
        return transactionsArray(); // Return an empty array  
    }
    else {
        //create a new list with all the result
        Transactions* list = new Transactions[count];
        for (int i = 0; i < count; i++) {
            list[i] = result[i];
        }
        delete[] result; // Free the temporary result array  
        //return the result as an array
        transactionsArray resultArray = transactionsArray(list, count);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken to do binary search for transactions is: " << duration.count() << "microseconds" << endl;
        return resultArray;
    }
}