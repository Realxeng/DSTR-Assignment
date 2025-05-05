#include "reviewsArray.hpp"

using namespace std;

reviewsArray::reviewsArray() {
    list = NULL;
    top = 0;
} //default constructor

// parameterized constructor
reviewsArray::reviewsArray(Reviews* list, int top) {
    this->list = list;
    this->top = this->max = top;
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

//destructor
reviewsArray::~reviewsArray() {

}


string reviewsArray::cleanWord(string str) {
    // remove punctuation and convert to lowercase
    str.erase(remove_if(str.begin(), str.end(), ::ispunct), str.end());
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// getter setter
int reviewsArray::getTop() { return top; }
void reviewsArray::setTop(int top) { this->top = top; }

// determines max size by getting number of line
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

// inserts review to array
void reviewsArray::insertToArray(Reviews data) {
    list[top] = data;
    top++;
}

// inserts review to array from file
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

// inserts review to array from file without header
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

// deletes review from specified index, then return the list
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

// just deletes review from specified index
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

// displays all reviews
void reviewsArray::showAllReviews() {
    for (int lines = 0; lines < max; lines++) {
        cout << list[lines].pid << "|";
        cout << list[lines].cid << "|";
        cout << list[lines].rating << "|";
        cout << list[lines].review << "|";
        cout << endl;
    }
}

//insertion sort based on product id
reviewsArray reviewsArray::insertionSortCid()
{
    Reviews temp;
	reviewsArray result = reviewsArray(top); // create temporary array for result
    for (int i = 0; i < top; i++) { // go through every index
        temp.pid = list[i].pid;
        temp.cid = list[i].cid;
        temp.rating = list[i].rating;
        temp.review = list[i].review;
        if (i == 0) {
            result.list[0] = temp;
        }
        else {
            int j = 0;
            while (j<i && temp.cid > result.list[j].cid) { // finds correct position based on CID
                j++;
                continue;
            }
			if (j == i) { // if the position is at the end
                result.list[i] = temp;
            }
            else {
                for (int k = i; k > j; k--) { // Place temp in the correct position
                    result.list[k] = result.list[k - 1];
                }
                result.list[j] = temp;
            }
        }
        //cout << " Record: " << top << " Progress: " << (float)top / 4128 * 100 << "%\n";
    }
    return result;
}

//merge sort based on product id
// merge sort: good for large dataset, bad for memory usage
void reviewsArray::mergeSortByPID(int left, int right) {
    if (right == -1) right = top - 1; // defaults right to top-1 if not specified
	if (left >= right) return; // base case: return if single element or invalind

	int mid = left + (right - left) / 2; // calculate mid-point

    // repeat sorting
    mergeSortByPID(left, mid);
    mergeSortByPID(mid + 1, right);

    // temporary arrays
	int n1 = mid - left + 1; // L subarray size
	int n2 = right - mid; // R subarray size
    Reviews* L = new Reviews[n1]; // L temp array
	Reviews* R = new Reviews[n2]; // R temp array

	//copy data to temp arrays
    for (int i = 0; i < n1; i++) L[i] = list[left + i];
    for (int i = 0; i < n2; i++) R[i] = list[mid + 1 + i];

    // Merge step
    //cout << "left: " << left << endl;
	int i = 0, j = 0, k = left; //index for Main, L, R array
    while (i < n1 && j < n2) { //compare and merge elements
        if (L[i].pid <= R[j].pid) list[k++] = L[i++]; //take left if smaller or equal
		else list[k++] = R[j++]; //take right if smaller
    }
	while (i < n1) { //copt remaining elements from L
        //cout << "Adding remaining L[" << i << "] = " << L[i].pid << " to list[" << k << "]" << endl;
        list[k++] = L[i++];
    }
	while (j < n2) { //copy remaining elements from R
        //cout << "Adding remaining R[" << j << "] = " << R[j].pid << " to list[" << k << "]" << endl;
        list[k++] = R[j++];
    }

	//erase temp arrays
    delete[] L;
    delete[] R;
}

// display specific rating 
// easy to implement, checks whole array with no need of preprocessing
reviewsArray reviewsArray::linearSearchRating(int rating) {
	int count = 0; //amt of  matching reviews
    Reviews* list = new Reviews[top]; //temp array
	for (int i = 0; i < top; i++) { //check every ine
		if (stoi(this->list[i].rating) == rating) { //if rating match -
			list[count] = this->list[i]; //- add to temp array
			count++; //increment count
        }
    }
	if (count == 0) { // no match
        return reviewsArray(); //empty
    }
	reviewsArray result = reviewsArray(list, count); //result
    return result; //return result
}

//display review with specific product id
reviewsArray reviewsArray::linearSearchProduct(string pid) {
	int count = 0; //amt of matching 
    Reviews* list = new Reviews[top];
    for (int i = 0; i < top; i++) {
        if (cleanWord(this->list[i].pid) == cleanWord(pid)) { //ignore case
            list[count] = this->list[i];
            count++;
        }
    }
    if (count == 0) {
        delete[] list;
        return reviewsArray();
    }
    reviewsArray result = reviewsArray(list, count);
    return result;
}