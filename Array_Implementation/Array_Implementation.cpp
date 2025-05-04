#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <Windows.h>
#include <Psapi.h>
#include "transactionsArray.hpp"
#include "wordsArray.hpp"
#include "reviewsArray.hpp"

using namespace std;
using namespace std::chrono;

const string reviewsFile = "../data/reviews_cleaned.csv";
const string transactionsFile = "../data/transactions_cleaned.csv";

size_t getPeakMemory() {
	PROCESS_MEMORY_COUNTERS pmc;
	if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
		return pmc.PeakWorkingSetSize/1024;  // in kilobytes
	}
	return 0;
}

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
				auto start = high_resolution_clock::now();
				transactionsArray tacat = tarr.linearSearchCategory(cat);
				tacat.showAllTransactions();
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				cout << "Time taken to filter by category: " << duration.count() << " microseconds" << endl;
				break;
			}
			case(3):
			{
				string payment;
				cout << "Enter payment method: ";
                cin.ignore(1000, '\n');
				getline(cin, payment);
				cin.clear();
				auto start = high_resolution_clock::now();
				transactionsArray tapay = tarr.linearSearchPayment(payment);
				tapay.showAllTransactions();
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				cout << "Time taken to filter by payment: " << duration.count() << " microseconds" << endl;
				break;
			}
			case(4):
			{
				string product;
				cout << "Enter product name: ";
				cin.ignore(1000, '\n');
				getline(cin, product);
				cin.clear();
				auto start = high_resolution_clock::now();
				transactionsArray taprod = tarr.linearSearchProduct(product);
				taprod.showAllTransactions();
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				cout << "Time taken to filter by product: " << duration.count() << " microseconds" << endl;
				break;
			}
			case(5):
			{
				string cid;
				cout << "Enter customer ID: ";
				cin >> cid;
				cin.clear();
				transactionsArray tasort = tarr.insertionSortCid();
				auto start = high_resolution_clock::now();
				transactionsArray tacid = tasort.binarySearchCustomer(cid);
				tacid.showAllTransactions();
				auto stop = high_resolution_clock::now();
				auto duration = duration_cast<microseconds>(stop - start);
				cout << "Time taken to filter by customer id: " << duration.count() << " microseconds" << endl;
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

void menuShowReviews(reviewsArray& rarr) {
	int choice;
	cout << "--------------------------" << endl <<
		"1. Show all reviews" << endl <<
		"2. Search by rating" << endl <<
		"3. Search by product" << endl <<
		"4. Exit to reviews menu" << endl <<
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
		int rating;
		cout << "Enter rating: ";
		cin >> rating;
		auto start = high_resolution_clock::now();
		reviewsArray rarat = rarr.linearSearchRating(rating);
		rarat.showAllReviews();
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << "Time taken to filter by rating: " << duration.count() << " microseconds" << endl;
		break;
	}
	case(3):
	{
		string pid;
		cout << "Enter product id: ";
		cin >> pid;
		auto start = high_resolution_clock::now();
		reviewsArray raprod = rarr.linearSearchProduct(pid);
		raprod.showAllReviews();
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << "Time taken to filter by product id: " << duration.count() << " microseconds" << endl;
		break;
	}
	case(4):
	{
		return;
		break;
	}
	default:
	{
		cout << "Invalid input!";
		break;
	}
	}
}

void reviews() {
	ifstream rfile(reviewsFile);
	reviewsArray rarr = reviewsArray(rfile);
	int choice = 0;
	while (choice != 5)
	{
		cout << "--------------------------" << endl <<
			"1. Show reviews" << endl <<
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
			menuShowReviews(rarr);
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
			break;
		}
		case(5):
		{
			cout << "Exiting to menu..." << endl;
			return;
			break;
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
				cout << "Peak Memory Usage: " << getPeakMemory() << "KB" << endl;
				cout << "Exiting program..." << endl;
				return 0;
			}
		}
	}
	return 0;
}