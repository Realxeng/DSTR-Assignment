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

void ReviewsLinkedList::insertNode_atEnd(string productID, string customerID, int rate, string reviewDesc) {
    // Create a new node
    reviewNode* newNode = createNewReviewNode(productID, customerID, rate, reviewDesc);

    // Insert the new node at the end of the list
    if (head == nullptr) {  // If the list is empty
        head = newNode;     // Set head and tail to the new node
        tail = newNode;
    } else {                // If the list is not empty, insert at the end
        tail->next = newNode;  // Set the next of the current tail to the new node
        newNode->prev = tail;  // Set the prev of the new node to the current tail
        tail = newNode;        // Update tail to point to the new node
    }
    size++;  // Increase size of the list
}

void ReviewsLinkedList::deleteNode_atEnd() {
    if (head == nullptr) {  // If the list is empty
        cout << "List is empty. Cannot delete." << endl;
        return;
    }

    reviewNode* temp = tail;  // Create a temp pointer to the tail

    tail = tail->prev;  // Move tail to the previous node
    if (tail != nullptr) {
        tail->next = nullptr;  // Set the next of the new tail to null
    } else {
        head = nullptr;  // If the list is now empty, set head to null
    }

    cout << "Deleted Review: " << temp->reviewDesc << endl;  // Display the deleted review
    delete temp;  // Delete the temp node
    size--;  // Decrease the size of the list
}

void ReviewsLinkedList::display() {
    reviewNode* temp = head;  // Create a temp pointer to traverse the list

    while (temp != nullptr) {  // Traverse the list
        cout << temp->productID << ", " << temp->customerID
             << ", Rating: " << temp->rate << ", Review: " << temp->reviewDesc << endl;
        temp = temp->next;  // Move to the next node
    }
}

int ReviewsLinkedList::getSize() {
    return size;
}

reviewNode* ReviewsLinkedList::getHead() {
    return head;
}

reviewNode* ReviewsLinkedList::getTail() {
    return tail;
}

// Merge Sort
reviewNode* ReviewsLinkedList::mergeSort(reviewNode* head) {
    if ()
}