#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

struct Transactions
{
	string cid, product, cat, price, date, payment;
};

class transactionsArray
{
private:
	int top = 0;	
	int max = 0;
	Transactions* list;
	int getMaxLine(ifstream& file);
	bool isEarlier(string date1, string date2);
	string cleanWord(string str);
public:
	transactionsArray();
	transactionsArray(Transactions* list, int top);
	transactionsArray(int size);
	transactionsArray(ifstream& file);
	~transactionsArray();
	int getTop();
	void setTop(int top);
	int getMax();
	void setMax(int max);
	void insertToArray(Transactions data);
	void insertToArray(Transactions data, int index);
	void insertFromFile(ifstream& file);
	void insertFromFileRaw(ifstream& file);
	Transactions* deleteAtIndex(Transactions* list, int index);
	void deleteAtIndex(int index);
	void showAllTransactions();
	void showTransaction(transactionsArray tarr);
	transactionsArray insertionSortCid();
	transactionsArray insertionSortDate();
	transactionsArray bubbleSortDate();
	transactionsArray bubbleSortCid();
	transactionsArray linearSearchCategory(string cat);
	transactionsArray linearSearchPayment(string payment);
	transactionsArray linearSearchProduct(string product);
	transactionsArray binarySearchCustomer(string cid);
};