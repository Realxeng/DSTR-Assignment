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
	transactionsArray electronicsTransactions = ta.linearSearchCategory("Electronics");
	electronicsTransactions.showAllTransactions();
	cout << "Total transactions: " << ta.getTop() << endl;
	cout << "Total transactions in Electronics: " << electronicsTransactions.getTop() << endl;
	transactionsArray creditCardTransactions = electronicsTransactions.linearSearchPayment("Credit Card");
	cout << "Total transactions in Electronics using Credit Card: " << creditCardTransactions.getTop() << endl;
	float percentage = (float)creditCardTransactions.getTop() / (float)electronicsTransactions.getTop() * 100;
	cout << "Percentage of purchases in Electronics using Credit Card: " << percentage << "%" << endl;
	return 0;
}