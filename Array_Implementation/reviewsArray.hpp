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
    reviewsArray(int size) {
        list = new Reviews[size];
    }
    ~reviewsArray() {
        delete[] list;
    }
    void insertToArray(ifstream& file, Reviews* list) {
        if (file.is_open()) {
            while (file.good()) {
                string wholeline;
                getline(file, wholeline, '\n');
                istringstream iss(wholeline);
                getline(iss, list[top].pid, ',');
                getline(iss, list[top].cid, ',');
                getline(iss, list[top].rating, ',');
                getline(iss, list[top].review, ',');
                top++;
            }
        }
    }
    void showAllReviews(Reviews* list, int rowsize) {
        for (int lines = 0; lines < rowsize; lines++) {
            cout << list[lines].pid << "|";
            cout << list[lines].cid << "|";
            cout << list[lines].rating << "|";
            cout << list[lines].review << "|";
            cout << endl;
        }
    }
};