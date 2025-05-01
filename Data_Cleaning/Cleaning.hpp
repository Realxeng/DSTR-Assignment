#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "..//Array_Implementation/reviewsArray.hpp"
#include "..//Array_Implementation/transactionsArray.hpp"

using namespace std;

class Cleaning {
	Reviews* rlist;
	reviewsArray ra;
	Transactions* tlist;
	transactionsArray ta;
public:
	Cleaning(Reviews* list, int top) {
		ra = reviewsArray();
		rlist = list;
		tlist = NULL;
		ra.setTop(top);
	}
	Cleaning(Transactions* list, int top) {
		ta = transactionsArray();
		tlist = list;
		rlist = NULL;
		ta.setTop(top);
	}
	~Cleaning() {
		if (rlist != NULL) {
			delete[] rlist;
			rlist = nullptr;
		}
		if (tlist != NULL) {
			delete[] tlist;
			tlist = nullptr;
		}
	}
	
	void reviewCleanNullEntry() {
		for (int i = 0; i < ra.getTop(); i++){
			if (rlist[i].cid.empty() || rlist[i].pid.empty() || rlist[i].rating.empty() || rlist[i].review.empty()) {
				cout << "Deleted null review at index: " << i << endl;
				rlist = ra.deleteAtIndex(rlist, i);
				i--;
			}
		}
	}

	void reviewCleanInvalidRating() {
		for (int i = 0; i < ra.getTop(); i++) {
			if (rlist[i].rating == "Invalid Rating") {
				cout << "Deleted invalid rating at index: " << i << endl;
				rlist = ra.deleteAtIndex(rlist, i);
				i--;
			}
		}
	}

	void reviewQuote() {
		for (int i = 0; i < ra.getTop(); i++) {
			string review = rlist[i].review;
			if (review.find('"') != string::npos) {
				return;
			}
			else {
				rlist[i].review = "\"" + review + "\"";
			}
		}
	}

	void transactionCleanNullEntry() {
		for (int i = 0; i < ta.getTop(); i++) {
			if (tlist[i].cid.empty() || tlist[i].product.empty() || tlist[i].cat.empty() 
				|| tlist[i].price.empty() || tlist[i].date.empty() || tlist[i].payment.empty()) {
				cout << "Deleted transaction at index: " << i << endl;
				tlist = ta.deleteAtIndex(tlist, i);
				i--;
			}
		}
	}

	void transactionCleanNanEntry() {
		for (int i = 0; i < ta.getTop(); i++) {
			if (tlist[i].price == "NaN") {
				cout << "Deleted transaction at index: " << i << endl;
				tlist = ta.deleteAtIndex(tlist, i);
				i--;
			}
		}
	}

	void transactionCleanInvalidDate() {
		for (int i = 0; i < ta.getTop(); i++) {
			if (tlist[i].date == "Invalid Date") {
				cout << "Deleted transaction at index: " << i << endl;
				tlist = ta.deleteAtIndex(tlist, i);
				i--;
			}
		}
	}

	void exportReview(string path) {
		ofstream file(path);
		for (int i = 0; i < ra.getTop(); i++) {
			file<< rlist[i].pid << ","
				<< rlist[i].cid << ","
				<< rlist[i].rating << ","
				<< rlist[i].review << endl;
		}
		file.close();
		cout << "Exported reviews. " << "Total Reviews: " << ra.getTop() << endl;
	}

	void exportTransaction(string path) {
		ofstream file(path);
		for (int i = 0; i < ta.getTop(); i++) {
			file << tlist[i].cid << ","
				<< tlist[i].product << ","
				<< tlist[i].cat << ","
				<< tlist[i].price << ","
				<< ta.convertDate(tlist[i].date) << ","
				<< tlist[i].payment << endl;
		}
		file.close();
		cout << "Exported transactions. " << "Total Transactions: " << ta.getTop() << endl;
	}
};