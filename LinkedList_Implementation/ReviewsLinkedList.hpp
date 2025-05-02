#ifndef REVIEWS_LINKED_LIST_HPP
#define REVIEWS_LINKED_LIST_HPP

#include <iostream>
using namespace std;

struct reviewNode //Linked List for the reviews
{
    string productID, customerID, reviewDesc;
    int rate = 0;

    reviewNode* prev;   // Pointer to the previous node
    reviewNode* next;   // Pointer to the next node
};

class ReviewsLinkedList
{
    reviewNode* head;   // Pointer to the head of the linked list
    reviewNode* tail;   // Pointer to the tail of the linked list
    int size;      // Size of the list

public:
    // === Constructor ===
    ReviewsLinkedList();
    // === Destructor ===
    ~ReviewsLinkedList();

    // === Methods ===
    reviewNode* createNewReviewNode(string productID, string customerID, int rate, string reviewDesc);
    void insertNode_atEnd(string productID, string customerID, int rate, string reviewDesc);
    void deleteNode_atEnd();
    void display();
    int getSize();
    reviewNode* getHead();
    reviewNode* getTail();

    // === Merge Sort ===
    void sortByProductID();
    reviewNode* mergeSort(reviewNode* head);
    reviewNode* merge(reviewNode* left, reviewNode* right);
    reviewNode* split(reviewNode* head);
};

#endif