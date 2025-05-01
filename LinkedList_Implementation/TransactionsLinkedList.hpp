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
    transactionsLL* head = nullptr;
    transactionsLL* tail = nullptr;

    bool isEarlier(string d1, string d2); // declaration only

public:
    void addSorted(string customerID, string product, string category, float price, string date, string paymentMethod);
    void display();
};