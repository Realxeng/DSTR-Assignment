#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "transactionsArray.hpp"
#include "wordsArray.hpp"
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
		"6. Exit to Transactions Menu" << endl <<
		"Enter your choice: ";
	cin >> choice;
	cin.clear();
	switch (choice)
	{
		case(1):
		{
			tarr.showAllTransactions();
			break;
		}
		case(2):
		{
			auto start = high_resolution_clock::now();
			tarr = tarr.insertionSortCid();
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			tarr.showAllTransactions();
			cout << "Time taken to do insertion sort by customer ID: " << duration.count() << " microseconds" << endl;
			break;
		}
		case(3):
		{
			auto start = high_resolution_clock::now();
			tarr = tarr.insertionSortDate();
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			tarr.showAllTransactions();
			cout << "Time taken to do insertion sort by date: " << duration.count() << " microseconds" << endl;
			break;
		}
		case(4):
		{
			auto start = high_resolution_clock::now();
			tarr = tarr.bubbleSortCid();
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			tarr.showAllTransactions();
			cout << "Time taken to do bubble sort by customer ID: " << duration.count() << " microseconds" << endl;
			break;
		}
		case(5):
		{
			auto start = high_resolution_clock::now();
			tarr = tarr.bubbleSortDate();
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			tarr.showAllTransactions();
			cout << "Time taken to do bubble sort by date: " << duration.count() << " microseconds" << endl;
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
	while (true)
	{
		ifstream tfile(transactionsFile);
		transactionsArray tarr = transactionsArray(tfile);
		int choice = 0;
		cout << "--------------------------" << endl <<
			"1. Show transactions" << endl <<
			"2. Search by category" << endl <<
			"3. Search by payment method" << endl <<
			"4. Search by product name" << endl <<
			"5. Search by customer ID" << endl <<
			"6. Exit to Menu" << endl <<
			"Enter your choice: ";
		cin >> choice;
		cin.clear();
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
				cin.clear();
				transactionsArray tacat = tarr.linearSearchCategory(cat);
				tacat.showAllTransactions();
				break;
			}
			case(3):
			{
				string payment;
				cout << "Enter payment method: ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				getline(cin, payment);
				cin.clear();
				transactionsArray tapay = tarr.linearSearchPayment(payment);
				tapay.showAllTransactions();
				break;
			}
			case(4):
			{
				string product;
				cout << "Enter product name: ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				getline(cin, product);
				cin.clear();
				transactionsArray taprod = tarr.linearSearchProduct(product);
				taprod.showAllTransactions();
				break;
			}
			case(5):
			{
				string cid;
				cout << "Enter customer ID: ";
				cin >> cid;
				cin.clear();
				transactionsArray tacid = tarr.binarySearchCustomer(cid);
				tacid.showAllTransactions();
				break;
			}
			case(6):
			{
				cin.clear();
				cout << "Exiting to menu..." << endl;
				return;
				break;
			}
			default:
			{
				cin.clear();
				cout << "Invalid choice. Please try again." << endl;
				break;
			}
		}
		tfile.close();
	}
};

void reviews() {
	ifstream rfile(reviewsFile);
	reviewsArray rarr = reviewsArray(rfile);
	int choice = 0;
	while (choice != 5)
	{
		cout << "--------------------------" << endl <<
			"1. Show all reviews" << endl <<
			"2. Sort by product ID" << endl <<
			"3. Sort by customer ID" << endl <<
			"4. Show most used words" << endl <<
			"5. Exit to Menu" << endl<<
			"Enter your choice: ";
		cin >> choice;
		cin.clear();
		switch (choice)
		{
		case(1):
		{
			rarr.showAllReviews();
			break;
		}
		case(2):
		{
			auto start = high_resolution_clock::now();
			rarr.mergeSortByPID(0,-1);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			rarr.showAllReviews();
			cout << "Time taken to do merge sort by product ID: " << duration.count() << " microseconds" << endl;
			break;
		}
		case(3):
		{
			auto start = high_resolution_clock::now();
			rarr = rarr.insertionSortCid();
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			rarr.showAllReviews();
			cout << "Time taken to do insertion sort by customer ID: " << duration.count() << " microseconds" << endl;
			break;
		}
		case(4):
		{
			int rating;
			cout << "Enter rating (0 to not filter): ";
			cin >> rating;
			cin.clear();
			if (rating == 0) {
				auto start = high_resolution_clock::now();
				wordsArray wa = wordsArray(rarr, 0);
				wa.showMostUsedWords();
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				wa.~wordsArray();
				cout << "Time taken to show most used words: " << duration.count() << " microseconds" << endl;
			}
			else if (rating >= 1 && rating <= 5) {
				auto start = high_resolution_clock::now();
				reviewsArray filterRating = rarr.linearSearchRating(rating);
				wordsArray wa = wordsArray(filterRating, 0);
				wa.showMostUsedWords();
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				wa.~wordsArray();
				cout << "Time taken to show most used words: " << duration.count() << " microseconds" << endl;
			}
			else {
				cout << "Invalid rating!";
				break;
			}
		}
		case(5):
		{
			cout << "Exiting to menu..." << endl;
			return;
		}
		default:
		{
			cout << "Invalid choice. Please try again." << endl;
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
		cin.clear();
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