#include "reviewsArray.hpp"

using namespace std;

reviewsArray::reviewsArray() {
    list = NULL;
    top = 0;
}
reviewsArray::reviewsArray(Reviews* list, int top) {
    this->list = list;
    this->top = top;
}
reviewsArray::reviewsArray(int size) {
    list = new Reviews[size];
    this->max = size;
}
reviewsArray::reviewsArray(ifstream& file) {
    this->max = getMaxLine(file);
    this->top = 0;
    list = new Reviews[max];
    insertFromFile(file);
}
reviewsArray::~reviewsArray() {

}

int reviewsArray::getTop() { return top; }
void reviewsArray::setTop(int top) { this->top = top; }

int reviewsArray::getMaxLine(ifstream& file) {
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

void reviewsArray::insertToArray(Reviews data) {
    list[top] = data;
    top++;
}

void reviewsArray::insertFromFile(ifstream& file) {
    if (file.is_open()) {
        Reviews temp;
        while (file.good()) {
            string wholeline;
            getline(file, wholeline, '\n');
            istringstream iss(wholeline);
            getline(iss, temp.pid, ',');
            getline(iss, temp.cid, ',');
            getline(iss, temp.rating, ',');
            getline(iss, temp.review, '\n');
            insertToArray(temp);
        }
    }
    else {
        cerr << "Unable to open file!";
    }
}

void reviewsArray::insertFromFileRaw(ifstream& file) {
    if (file.is_open()) {
        Reviews temp;
        string header;
        getline(file, header);
        while (file.good()) {
            string wholeline;
            getline(file, wholeline, '\n');
            istringstream iss(wholeline);
            getline(iss, temp.pid, ',');
            getline(iss, temp.cid, ',');
            getline(iss, temp.rating, ',');
            getline(iss, temp.review, '\n');
            insertToArray(temp);
        }
    }
    else {
        cerr << "Unable to open file!";
    }
}

Reviews* reviewsArray::deleteAtIndex(Reviews* list, int index) {
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

void reviewsArray::deleteAtIndex(int index) {
    if (index < 0 || index > top) {
        cout << "Nothing to delete!";
        return;
    }
    for (int i = index; i < top - 1; i++) {
        list[i] = list[i + 1];
    }
    top--;
}

void reviewsArray::showAllReviews() {
    for (int lines = 0; lines < max; lines++) {
        cout << list[lines].pid << "|";
        cout << list[lines].cid << "|";
        cout << list[lines].rating << "|";
        cout << list[lines].review << "|";
        cout << endl;
    }
}

reviewsArray reviewsArray::insertionSortCid()
{
    Reviews temp;
    reviewsArray result = reviewsArray(top);
    for (int i = 0; i < top; i++) {
        temp.pid = list[i].pid;
        temp.cid = list[i].cid;
        temp.rating = list[i].rating;
        temp.review = list[i].review;
        if (i == 0) {
            result.list[0] = temp;
        }
        else {
            int j = 0;
            while (j<i && temp.cid > result.list[j].cid) {
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

void reviewsArray::mergeSortByPID(int left, int right) {
    if (right == -1) right = top - 1;
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    // Recursively divide
    mergeSortByPID(left, mid);
    mergeSortByPID(mid + 1, right);

    // Temporary arrays
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Reviews* L = new Reviews[n1];
    Reviews* R = new Reviews[n2];

    for (int i = 0; i < n1; i++) L[i] = list[left + i];
    for (int i = 0; i < n2; i++) R[i] = list[mid + 1 + i];

    // Merge step
    //cout << "left: " << left << endl;
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].pid <= R[j].pid) list[k++] = L[i++];
        else list[k++] = R[j++];
    }
    while (i < n1) {
        //cout << "Adding remaining L[" << i << "] = " << L[i].pid << " to list[" << k << "]" << endl;
        list[k++] = L[i++];
    }
    while (j < n2) {
        //cout << "Adding remaining R[" << j << "] = " << R[j].pid << " to list[" << k << "]" << endl;
        list[k++] = R[j++];
    }

    delete[] L;
    delete[] R;
}

