#pragma once
#include <iostream>
using namespace std;

class LinkedList
{
    struct reviewsLL //Linked List for the reviews
    {
        string ProductID, CustomerID, ReviewDesc;
        int Rate;

        reviewsLL* prev;
        reviewsLL* next;
    }*head, * tail;
};

