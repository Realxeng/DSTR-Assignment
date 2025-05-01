#include "ReviewsLinkedList.hpp"

// Constructor
ReviewsLinkedList::ReviewsLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// Destructor
ReviewsLinkedList::~ReviewsLinkedList() {
    cout << "Destructor called. Deleting the linked list." << endl;
}

reviewNode* ReviewsLinkedList::createNewReviewNode(string productID, string customerID, int rate, string reviewDesc) {
    // Create a new node in heap
    reviewNode* newNode = new reviewNode;

    // Assign the values to the new node
    newNode->productID = productID;
    newNode->customerID = customerID;
    newNode->rate = rate;
    newNode->reviewDesc = reviewDesc;

    // Set the next and prev pointers to null
    newNode->next = nullptr;
    newNode->prev = nullptr;

    // Return the new node
    return newNode;
}