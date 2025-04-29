#pragma once
#include <iostream>
using namespace std;

class LinkedList
{
    struct reviewsLL //Linked List for the reviews
    {
        string productID, customerID, reviewDesc;
        int Rate;

        reviewsLL* prev;
        reviewsLL* next;
    }*head, * tail;

    struct transactionsLL
    {
        string customerID, product, category, date, paymentMethod;
        float price;

        transactionsLL* prev;
        transactionsLL* next;
    }*head, *tail;


};

