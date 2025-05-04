#include <iostream>
#include <chrono>
#include "../Array_Implementation/transactionsArray.hpp"
#include "../LinkedList_Implementation/TransactionsLinkedList.hpp"

using namespace std;
using namespace std::chrono;

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
			auto start = high_resolution_clock::now();
			transactionsArray ta = transactionsArray(tfile);
			transactionsArray electronicsTransactions = ta.linearSearchCategory("Electronics");
			cout << "Total transactions: " << ta.getTop() << endl;
			cout << "Total transactions in Electronics: " << electronicsTransactions.getTop() << endl;
			transactionsArray creditCardTransactions = electronicsTransactions.linearSearchPayment("Credit Card");
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Total transactions in Electronics using Credit Card: " << creditCardTransactions.getTop() << endl;
			float percentage = (float)creditCardTransactions.getTop() / (float)electronicsTransactions.getTop() * 100;
			cout << "Percentage of purchases in Electronics using Credit Card: " << percentage << "%" << endl;
			cout << "Time taken to do linear search for payment using array is: " << duration.count() << " microseconds" << endl;
		}
		else if (choice == 2) {
			auto start = high_resolution_clock::now();
			transactionsLinkedList tll = tll.setUp_transactionLL();
			transactionsLinkedList tllcat = tll.returnByCategory("Electronics");
			transactionsLinkedList tllcatpay = tllcat.returnByPaymentMethod("Credit Card");
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			cout << "Total transactions: " << tll.getLLSize() << endl;
			cout << "Total transactions in Electronics: " << tllcat.getLLSize() << endl;
			cout << "Total transactions in Electronics using Credit Card: " << tllcatpay.getLLSize() << endl;
			float percentage = (float)tllcatpay.getLLSize() / (float)tllcat.getLLSize() * 100;
			cout << "Percentage of purchases in Electronics using Credit Card: " << percentage << "%" << endl;
			cout << "Time taken to do linear search for payment using linked list is: " << duration.count() << " microseconds" << endl;
		}
		else {
			cout << "Exiting Program.." << endl;
			return 0;
		}
	}
}