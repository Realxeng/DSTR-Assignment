#include <iostream>
#include "../Array_Implementation/transactionsArray.hpp"
#include "../LinkedList_Implementation/TransactionsLinkedList.hpp"

using namespace std;

const string transactionsFile = "../data/transactions_cleaned.csv";


//Q: What percentage of purchases in the “Electronics” category were made using Credit Card payments ?

int main()
{
	int choice;
	while (true) {
		cout << "-------------------------------\n";
		cout << "Choose" << endl;
		cout << "1. Array Implementation" << endl;
		cout << "2. Linked List Implementation" << endl;
		cout << "3. Exit" << endl;
		cin >> choice;
		if (choice == 1) {
			ifstream tfile(transactionsFile);
			transactionsArray ta = transactionsArray(tfile);
			transactionsArray electronicsTransactions = ta.linearSearchCategory("Electronics");
			//electronicsTransactions.showAllTransactions();
			cout << "Total transactions: " << ta.getTop() << endl;
			cout << "Total transactions in Electronics: " << electronicsTransactions.getTop() << endl;
			transactionsArray creditCardTransactions = electronicsTransactions.linearSearchPayment("Credit Card");
			cout << "Total transactions in Electronics using Credit Card: " << creditCardTransactions.getTop() << endl;
			float percentage = (float)creditCardTransactions.getTop() / (float)electronicsTransactions.getTop() * 100;
			cout << "Percentage of purchases in Electronics using Credit Card: " << percentage << "%" << endl;
		}
		else if (choice == 2) {
			transactionsLinkedList tll = tll.setUp_transactionLL();
			transactionsLinkedList tllcat = tll.returnByCategory("Electronics");
			transactionsLinkedList tllcatpay = tllcat.returnByPaymentMethod("Credit Card");
			cout << "Total transactions: " << tll.getLLSize() << endl;
			cout << "Total transactions in Electronics: " << tllcat.getLLSize() << endl;
			cout << "Total transactions in Electronics using Credit Card: " << tllcatpay.getLLSize() << endl;
			float percentage = (float)tllcatpay.getLLSize() / (float)tllcat.getLLSize() * 100;
			cout << "Percentage of purchases in Electronics using Credit Card: " << percentage << "%" << endl;
		}
		else {
			cout << "Exiting Program.." << endl;
			return 0;
		}
	}
}