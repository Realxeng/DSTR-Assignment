#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Reviews
{
    string pid, cid, rating, review;
	int size = 0;
};

class reviewsArray
{
    int top = 0;
public:
    Reviews* list;
    reviewsArray() {
        list = nullptr;
        top = 0;
    }
    reviewsArray(Reviews* list, int top) {
        this->list = list;
        this->top = top;
    }
    reviewsArray(int size) {
        list = new Reviews[size];
    }

    int getTop() { return top; }
    void setTop(int top) { this->top = top; }

    void insertToArray(Reviews data) {
        list[top] = data;
        top++;
    }

    void insertFromFile(ifstream& file) {
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
                temp.size = top + 1;
                setTop(temp.size);
            }
        }
        else {
            cerr << "Unable to open file!";
        }
    }

    Reviews* deleteAtIndex(Reviews* list, int index) {
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

    void showAllReviews() {
        for (int lines = 0; lines < top; lines++) {
            cout << list[lines].pid << "|";
            cout << list[lines].cid << "|";
            cout << list[lines].rating << "|";
            cout << list[lines].review << "|";
            cout << endl;
        }
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

    void mergeSortByPID(int left = 0, int right = -1, bool isTopLevel = true) {
        if (right == -1) right = top - 1;
        if (left >= right) return;

        int mid = left + (right - left) / 2;

        // Recursive sort
        mergeSortByPID(left, mid, false);
        mergeSortByPID(mid + 1, right, false);

        // Merge step
        int n1 = mid - left + 1;
        int n2 = right - mid;
        Reviews* L = new Reviews[n1];
        Reviews* R = new Reviews[n2];

        for (int i = 0; i < n1; i++) L[i] = list[left + i];
        for (int i = 0; i < n2; i++) R[i] = list[mid + 1 + i];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i].pid <= R[j].pid) list[k++] = L[i++];
            else list[k++] = R[j++];
        }
        while (i < n1) list[k++] = L[i++];
        while (j < n2) list[k++] = R[j++];

        delete[] L;
        delete[] R;

        // After full merge sort, delete index 0
        if (isTopLevel) {
            deleteAtIndex(0);
        }
    }
};