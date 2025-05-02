#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "..//Array_Implementation/reviewsArray.hpp"
#include "..//Array_Implementation/transactionsArray.hpp"

using namespace std;

class Cleaning {
	reviewsArray ra;
	transactionsArray ta;
public:
	Cleaning(reviewsArray ra) {
		this->ra = ra;
		ta = NULL;
	}
	Cleaning(transactionsArray ta) {
		this->ta = ta;
		ta = NULL;
	}
	~Cleaning() {
		if (ra.list != NULL) {
			delete[] ra.list;
			ra.list = nullptr;
		}
		if (ta.list != NULL) {
			delete[] ta.list;
			ta.list = nullptr;
		}
	}
	
	void reviewCleanNullEntry() {
		for (int i = 0; i < ra.getTop(); i++){
			if (ra.list[i].cid.empty() || ra.list[i].pid.empty() || ra.list[i].rating.empty() || ra.list[i].review.empty()) {
				cout << "Deleted null review at index: " << i << endl;
				ra.deleteAtIndex(i);
				i--;
			}
		}
	}

	void reviewCleanInvalidRating() {
		for (int i = 0; i < ra.getTop(); i++) {
			if (ra.list[i].rating == "Invalid Rating") {
				cout << "Deleted invalid rating at index: " << i << endl;
				ra.deleteAtIndex(i);
				i--;
			}
		}
	}

	void reviewQuote() {
		for (int i = 0; i < ra.getTop(); i++) {
			string review = ra.list[i].review;
			if (review.find('"') != string::npos) {
				continue;
			}
			else {
				cout << "Added double quotes at index: " << i << endl;
				ra.list[i].review = "\"" + review + "\"";
			}
		}
	}

	void transactionCleanNullEntry() {
		for (int i = 0; i < ta.getTop(); i++) {
			if (ta.list[i].cid.empty() || ta.list[i].product.empty() || ta.list[i].cat.empty() 
				|| ta.list[i].price.empty() || ta.list[i].date.empty() || ta.list[i].payment.empty()) {
				cout << "Deleted null transaction at index: " << i << endl;
				ta.list = ta.deleteAtIndex(ta.list, i);
				i--;
			}
		}
	}

	void transactionCleanNanEntry() {
		for (int i = 0; i < ta.getTop(); i++) {
			if (ta.list[i].price == "NaN") {
				cout << "Deleted NaN price transaction at index: " << i << endl;
				ta.list = ta.deleteAtIndex(ta.list, i);
				i--;
			}
		}
	}

	void transactionCleanInvalidDate() {
		for (int i = 0; i < ta.getTop(); i++) {
			if (ta.list[i].date == "Invalid Date") {
				cout << "Deleted invalid date transaction at index: " << i << endl;
				ta.list = ta.deleteAtIndex(ta.list, i);
				i--;
			}
		}
	}

	string convertDate(string sdate) {
		int day, month, year;
		sscanf_s(sdate.c_str(), "%d/%d/%d", &day, &month, &year);
		return to_string(year) + "/" + (month < 10 ? "0" : "") + to_string(month) + "/" + (day < 10 ? "0" : "") + to_string(day);
	}

	void exportReview(string path) {
		ofstream file(path);
		for (int i = 0; i < ra.getTop(); i++) {
			if (i != 0) {
				file << endl;
			}
			file<< ra.list[i].pid << ","
				<< ra.list[i].cid << ","
				<< ra.list[i].rating << ","
				<< ra.list[i].review;
		}
		file.close();
		cout << "Exported reviews. " << "Total Reviews: " << ra.getTop() << endl;
	}

	void exportTransaction(string path) {
		ofstream file(path);
		for (int i = 0; i < ta.getTop(); i++) {
			if (i != 0) {
				file << endl;
			}
			file << ta.list[i].cid << ","
				<< ta.list[i].product << ","
				<< ta.list[i].cat << ","
				<< ta.list[i].price << ","
				<< convertDate(ta.list[i].date) << ","
				<< ta.list[i].payment;
		}
		file.close();
		cout << "Exported transactions. " << "Total Transactions: " << ta.getTop() << endl;
	}
};