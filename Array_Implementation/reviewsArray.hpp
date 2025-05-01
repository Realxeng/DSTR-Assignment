#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Reviews
{
    string pid, cid, rating, review;
};

class reviewsArray
{
    int top = 0;
public:
    Reviews* list;
	reviewsArray() {
		list = NULL;
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
};