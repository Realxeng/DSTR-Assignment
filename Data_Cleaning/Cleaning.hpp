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
	Cleaning(reviewsArray& ra);
	Cleaning(transactionsArray& ta);
	~Cleaning();
	void reviewCleanNullEntry();
	void reviewCleanInvalidRating();
	void reviewQuote();
	void transactionCleanNullEntry();
	void transactionCleanNanEntry();
	void transactionCleanInvalidDate();
	string convertDate(string sdate);
	void exportReview(string path);
	void exportTransaction(string path);
};