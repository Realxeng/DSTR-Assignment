#include <iostream>
#include "../Array_Implementation/transactionsArray.hpp"
#include "../LinkedList_Implementation/TransactionsLinkedList.hpp"

using namespace std;


//Q: What percentage of purchases in the “Electronics” category were made using Credit Card payments ?

int main()
{
	transactionsArray ta;
	ifstream tfile("../data/transactions_cleaned.csv");
	ta.insertFromFile(tfile);
	ta = ta.insertionSortCid(ta);
	ta = ta.bubbleSortDate(ta);
	ta.showAllTransactions();
	//cout << "Total transactions: " << ta.getTop() << endl;
	//cout << "Total transactions in Electronics: " << ta.linearSearchCategory(ta, "Electronics").getTop() << endl;
	//cout << "Total transactions in Electronics using Credit Card: " << ta.linearSearchPayment(ta, "Credit Card").getTop() << endl;
	return 0;
}