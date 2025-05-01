#pragma once
#include <iostream>
#include <string>
using namespace std;

struct transactionsLL
{
    string customerID, product, category, date, paymentMethod;
    float price = 0.0f;

    transactionsLL* prev;
    transactionsLL* next;
};

class transactionsLinkedList
{
private:
    int size = 0;
    transactionsLL* head;
    transactionsLL* tail;

    bool isEarlier(string d1, string d2);

public:
    //// Constructor
    //transactionsLinkedList();
    //// Destructor
    //~transactionsLinkedList();

    void addNode(string customerID, string product, string category, float price, string date, string paymentMethod);
    void SortByDate();
    void display();
};