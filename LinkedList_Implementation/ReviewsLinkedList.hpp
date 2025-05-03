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

struct WordFreqNode{
    string word;
    int frequency;
    WordFreqNode* next;
    WordFreqNode* prev;
    
    // Constructor for WordFreqNode
    WordFreqNode(const string& word, int frequency);

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
    // Reviews Linked List
    reviewNode* createNewReviewNode(string productID, string customerID, int rate, string reviewDesc);
    void insertNode_atEnd(string productID, string customerID, int rate, string reviewDesc);
    void deleteNode_atEnd();
    void display();
    int getSize();
    reviewNode* getHead();
    reviewNode* getTail();

    // === Merge Sort by Word Frequency ===
    void sortByWordFrequency(int topN = 10);
    WordFreqNode* wf_head;
    WordFreqNode* wf_tail;
    WordFreqNode* mergeSortFreq(WordFreqNode* head);
    WordFreqNode* mergeFreq(WordFreqNode* left, WordFreqNode* right);
    WordFreqNode* splitFreq(WordFreqNode* head);

    // === Merge Sort by Product ID ===
    void sortByProductID();
    reviewNode* mergeSort(reviewNode* head);
    reviewNode* merge(reviewNode* left, reviewNode* right);
    reviewNode* split(reviewNode* head);
};

#endif