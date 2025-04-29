#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "reviewsArray.hpp";
#include "transactionsArray.hpp";

using namespace std;

class Cleaning {
	reviewsArray ra;
	transactionsArray ta;
public:
	Cleaning(reviewsArray ra) {
		this->ra = ra;
	}
	Cleaning(transactionsArray ta) {
		this->ta = ta;
	}
	
	void reviewCleanNullEntry() {
		for (int i = 0; i<=ra.getTop(); i++){
			if (ra.list[i].cid.empty() || ra.list[i].pid.empty() || ra.list[i].rating.empty() || ra.list[i].review.empty()){
				ra.deleteAtIndex(i);
			}
		}
	}

	void reviewCleanInvalidRating() {
		for (int i = 0; i <= ra.getTop(); i++) {
			if (ra.list[i].rating == "Invalid Rating") {
				ra.deleteAtIndex(i);
			}
		}
	}

	void reviewQuote() {
		for (int i = 0; i <= ra.getTop(); i++) {
			string review = ra.list[i].review;
			if (review.find('"')) {
				return;
			}
			else {
				ra.list[i].review = "\"" + review + "\"";
			}
		}
	}

	void transactionCleanNullEntry() {
		for (int i = 0; i <= ta.getTop(); i++) {
			if (ta.list[i].cid.empty() || ta.list[i].product.empty() || ta.list[i].cat.empty() 
				|| ta.list[i].price.empty() || ta.list[i].date.empty() || ta.list[i].payment.empty()) {
				ta.deleteAtIndex(i);
			}
		}
	}

	void transactionCleanNanEntry() {
		for (int i = 0; i <= ta.getTop(); i++) {
			if (ta.list[i].price == "NaN") {
				ta.deleteAtIndex(i);
			}
		}
	}

	void transactionCleanInvalidDate() {
		for (int i = 0; i <= ta.getTop(); i++) {
			if (ta.list[i].date == "Invalid Date") {
				ta.deleteAtIndex(i);
			}
		}
	}

	void exportReview() {
		ofstream file("..//data//reviews_cleaned.csv");
		for (int i = 0; i <= ra.getTop(); i++) {
			file<< ra.list[i].pid << ","
				<< ra.list[i].cid << ","
				<< ra.list[i].rating << ","
				<< ra.list[i].review << endl;
		}
		file.close();
	}

	void exportTransaction() {
		ofstream file("..//data//transactions_cleaned.csv");
		for (int i = 0; i <= ta.getTop(); i++) {
			file << ta.list[i].cid << ","
				<< ta.list[i].product << ","
				<< ta.list[i].cat << ","
				<< ta.list[i].price << ","
				<< ta.list[i].date << ","
				<< ta.list[i].payment << endl;
		}
		file.close();
	}
};