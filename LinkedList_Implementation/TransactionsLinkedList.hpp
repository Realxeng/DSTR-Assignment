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

    bool isEarlier(string d1, string d2);

public:
    //idk what to do with this
    //// Constructor
    //transactionsLinkedList();
    //// Destructor
    //~transactionsLinkedList();

    void createTransactionNode(string customerID, string product, string category, float price, string date, string paymentMethod);
    void SortByDate();
    void bubbleSortByDate();
    void searchByCategory(const string& targetCategory) const;
    void searchByPaymentMethod(const string& targetMethod) const;
    void display();
    int getLLSize();
};

transactionsLinkedList setUp_transactionLL();