#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "transactionsArray.hpp"
#include "reviewsArray.hpp"

using namespace std;
using namespace std::chrono;

const string reviewsFile = "../data/reviews_cleaned.csv";
const string transactionsFile = "../data/transactions_cleaned.csv";

void menuShowTransactions(transactionsArray& tarr) {
	int choice;
	cout << "--------------------------" << endl <<
		"1. Show all transactions" << endl <<
		"2. Insertion Sort by customer ID" << endl <<
		"3. Insertion Sort by date" << endl <<
		"4. Bubble Sort by customer ID" << endl <<
		"5. Bubble Sort by date" << endl <<
		"6. Exit to Transactions Menu" << endl;
	cin >> choice;
	switch (choice)
	{
		case(1):
		{
			tarr.showAllTransactions();
			break;
		}
		case(2):
		{
			tarr = tarr.insertionSortCid();
			tarr.showAllTransactions();
			break;
		}
		case(3):
		{
			tarr = tarr.insertionSortDate();
			tarr.showAllTransactions();
			break;
		}
		case(4):
		{
			tarr = tarr.bubbleSortCid();
			tarr.showAllTransactions();
			break;
		}
		case(5):
		{
			tarr = tarr.bubbleSortDate();
			tarr.showAllTransactions();
			break;
		}
		case(6):
		{
			cout << "Exiting to transactions menu..." << endl;
			return;
		}
		default:
		{
			cout << "Invalid choice. Please try again." << endl;
			break;
		}
	}
};

void transactions() {
	ifstream tfile(transactionsFile);
	transactionsArray tarr = transactionsArray(tfile);
	int choice = 0;
	while (true)
	{
		cout << "--------------------------" << endl <<
			"1. Show transactions" << endl <<
			"2. Search by category" << endl <<
			"3. Search by payment method" << endl <<
			"4. Search by product name" << endl <<
			"5. Search by customer ID" << endl <<
			"6. Exit to Menu" << endl;
		cin >> choice;
		switch (choice)
		{
		case(1):
		{
			menuShowTransactions(tarr);
			return;
			break;
		}
		case(2):
		{
			string cat;
			cout << "Enter category: ";
			cin >> cat;
			transactionsArray tacat = tarr.linearSearchCategory(cat);
			tacat.showAllTransactions();
			continue;
			break;
		}
		case(3):
		{
			string payment;
			cout << "Enter payment method: ";
			cin >> payment;
			transactionsArray tapay = tarr.linearSearchPayment(payment);
			tapay.showAllTransactions();
			continue;
			break;
		}
		case(4):
		{
			string product;
			cout << "Enter product name: ";
			cin >> product;
			transactionsArray taprod = tarr.linearSearchProduct(product);
			taprod.showAllTransactions();
			continue;
			break;
		}
		case(5):
		{
			string cid;
			cout << "Enter customer ID: ";
			cin >> cid;
			transactionsArray tacid = tarr.binarySearchCustomer(cid);
			tacid.showAllTransactions();
			continue;
			break;
		}
		case(6):
		{
			cout << "Exiting to menu..." << endl;
			return;
			break;
		}
		default:
		{
			cout << "Invalid choice. Please try again." << endl;
			continue;
			break;
		}
		}
	}
	tfile.close();
	tarr.~transactionsArray();
};

void reviews() {
	ifstream rfile(reviewsFile);
	reviewsArray rarr = reviewsArray(rfile);
	int choice = 0;
	cout << "--------------------------" << endl <<
		"1. Show all reviews" << endl <<
		"2. Sort by product ID" << endl <<
		"3. Sort by customer ID" << endl <<
		"4. Exit to Menu" << endl;
	cin >> choice;
	while (choice != 5)
	{
		switch (choice)
		{
		case(1):
		{
			rarr.showAllReviews();
			continue;
			break;
		}
		case(2):
		{
			rarr.mergeSortByPID(0, -1);
			rarr.showAllReviews();
			continue;
			break;
		}
		case(3):
		{
			rarr = rarr.insertionSortCid();
			rarr.showAllReviews();
			continue;
			break;
		}
		case(4):
		{
			cout << "Exiting to menu..." << endl;
			return;
		}
		default:
		{
			cout << "Invalid choice. Please try again." << endl;
			continue;
			break;
		}
		}
	}
	rfile.close();
	rarr.~reviewsArray();
};

int main()
{
	while (true)
	{
		int choice = 0;
		cout << "--------------------------" << endl <<
			"1. Transactions Menu" << endl <<
			"2. Reviews Menu" << endl <<
			"3. Exit program" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
			case(1):
			{
				transactions();
				break;
			}
			case(2):
			{
				reviews();
				break;
			}
			default:
			{
				cout << "Exiting program..." << endl;
				return 0;
			}
		}
	}
	return 0;
}