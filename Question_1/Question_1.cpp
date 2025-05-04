#include <iostream>
#include <chrono>
#include "../Array_Implementation/transactionsArray.hpp"
#include "../Array_Implementation/reviewsArray.hpp"
#include "../LinkedList_Implementation/TransactionsLinkedList.hpp"
#include "../LinkedList_Implementation/ReviewsLinkedList.hpp"

using namespace std;
using namespace std::chrono;

const string transactionsFile = "../data/transactions_cleaned.csv";
const string reviewsFile = "../data/reviews_cleaned.csv";

/*
Q: How can you efficiently sort customer transactions by date and display the total number of
transactions in both datasets ?
*/

int main()
{
	ifstream rfile(reviewsFile);
	ifstream tfile(transactionsFile);
	transactionsArray tarr = transactionsArray(tfile);
	reviewsArray rarr = reviewsArray(rfile);
	auto startbubble = high_resolution_clock::now();
	tarr.bubbleSortDate();
	auto stopbubble = high_resolution_clock::now();
	auto durationbubble = duration_cast<milliseconds>(stopbubble - startbubble);
	auto startinsertion = high_resolution_clock::now();
	transactionsArray sorted = tarr.insertionSortDate();
	auto stopinsertion = high_resolution_clock::now();
	auto durationinsertion = duration_cast<milliseconds>(stopinsertion - startinsertion);
	sorted.showAllTransactions();
	cout << "Time taken to sort transactions by date using Array Bubble Sort: " << durationbubble.count() << " ms" << endl;
	cout << "Time taken to sort transactions by date using Array Insertion Sort: " << durationinsertion.count() << " ms" << endl;
	cout << "Total transactions in transactions dataset: " << tarr.getTop() << endl;
	cout << "Total transactions in reviews dataset: " << rarr.getTop() << endl;
	transactionsLinkedList tll = tll.setUp_transactionLL();
	auto startll = high_resolution_clock::now();
	tll.bubbleSortByDate();
	auto stopll = high_resolution_clock::now();
	auto durationllbs = duration_cast<milliseconds>(stopll - startll);
	tll.display();
	cout << "Time taken to sort transactions by date using Linked List Bubble Sort: " << durationllbs.count() << " ms" << endl;
	auto startllis = high_resolution_clock::now();
	tll.SortByDate();
	auto stopllis = high_resolution_clock::now();
	auto durationllis = duration_cast<milliseconds>(stopllis - startllis);
	cout << "Time taken to sort transactions by date using Linked List Insertion Sort: " << durationllis.count() << " ms" << endl;
}