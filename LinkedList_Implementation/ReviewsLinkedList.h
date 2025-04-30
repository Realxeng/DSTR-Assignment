#pragma once
#include <iostream>
using namespace std;

class ReviewsLinkedList
{
    struct reviewsLL //Linked List for the reviews
    {
        string productID, customerID, reviewDesc;
        int rate;

        reviewsLL* prev = nullptr;
        reviewsLL* next = nullptr;
    };
    reviewsLL* head = nullptr;
    reviewsLL* tail = nullptr;

public:
    reviewsLL* addNode(string productID, string customerID, int rate, string reviewDesc)
    {
        reviewsLL* newNode = new reviewsLL;

        newNode->productID = productID;
        newNode->customerID = customerID;
        newNode->rate = rate;
        newNode->reviewDesc = reviewDesc;

        newNode->prev = nullptr;
        newNode->next = nullptr;

        return newNode;
    }
};

