#include <iostream>
#include <fstream>
#include <string>
#include "bubbleSort.h"

using namespace std;

class reviewsArray {
    string* list;
public:
    reviewsArray(int size) {
        list = new string[size];
    }
    ~reviewsArray() {
        delete[] list;
    }
};

int getMaxLine(string filename) {
    ifstream file(filename);
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
    return count;
}

int main()
{
    reviewsArray rarr = reviewsArray(getMaxLine("..//data/reviews_raw.txt"));
}