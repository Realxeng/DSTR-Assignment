#pragma once
#include <iostream>
#include <string>
using namespace std;

struct transactionsLL
{
    string customerID, product, category, date, paymentMethod;
    float price = 0.0f;

    transactionsLL* prev = nullptr;
    transactionsLL* next = nullptr;
};

class transactionsLinkedList
{
private:
    int size = 0;
    transactionsLL* head = nullptr;
    transactionsLL* tail = nullptr;

    transactionsLL* getMiddleNode(transactionsLL* start, transactionsLL* end);

public:
    // Constructor
    transactionsLinkedList();
    // Destructor
    ~transactionsLinkedList();

    void createTransactionNode(string customerID, string product, string category, float price, string date, string paymentMethod);
    void insertionSortByDate();
    void insertionSortByCusID();
    void bubbleSortByDate();
    void linearSearchByCategory(const string& targetCategory) const;
	transactionsLinkedList returnByCategory(const string& targetCategory) const;
    void linearSearchByPaymentMethod(const string& targetMethod) const;
	transactionsLinkedList returnByPaymentMethod(const string& targetMethod) const;
    transactionsLinkedList binarySearchByCustomerID(const std::string& targetID);
    void display();
    int getLLSize();
    transactionsLinkedList setUp_transactionLL();
};