#include <iostream>
#include "../Array_Implementation/transactionsArray.hpp"
#include "../LinkedList_Implementation/TransactionsLinkedList.hpp"

using namespace std;

const string transactionsFile = "../data/transactions_cleaned.csv";


//Q: What percentage of purchases in the “Electronics” category were made using Credit Card payments ?

int main()
{
	ifstream tfile(transactionsFile);
	transactionsArray ta = transactionsArray(tfile);
	ta = ta.insertionSortCid();
	ta = ta.bubbleSortDate();
	ta.showAllTransactions();
	//cout << "Total transactions: " << ta.getTop() << endl;
	//cout << "Total transactions in Electronics: " << ta.linearSearchCategory(ta, "Electronics").getTop() << endl;
	//cout << "Total transactions in Electronics using Credit Card: " << ta.linearSearchPayment(ta, "Credit Card").getTop() << endl;
	return 0;
}