#include <iostream>
#include <chrono>
#include "../Array_Implementation/transactionsArray.hpp"
#include "../Array_Implementation/reviewsArray.hpp"
#include "../LinkedList_Implementation/TransactionsLinkedList.hpp"

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
	auto durationbubble = duration_cast<microseconds>(stopbubble - startbubble);
	auto startinsertion = high_resolution_clock::now();
	tarr.insertionSortDate();
	auto stopinsertion = high_resolution_clock::now();
	auto durationinsertion = duration_cast<microseconds>(stopinsertion - startinsertion);
	cout << "Time taken to sort transactions by date using Bubble Sort: " << durationbubble.count() << " microseconds" << endl;
	cout << "Time taken to sort reviews by cid using Insertion Sort: " << durationinsertion.count() << " microseconds" << endl;
	cout << "Total transactions in transactions dataset: " << tarr.getTop() << endl;
	cout << "Total transactions in reviews dataset: " << rarr.getTop() << endl;
}