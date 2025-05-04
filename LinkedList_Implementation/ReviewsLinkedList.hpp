#ifndef REVIEWS_LINKED_LIST_HPP
#define REVIEWS_LINKED_LIST_HPP

#include <sstream>
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

struct RatingFreqNode{
    int rating;
    int frequency;
    RatingFreqNode* next;
    RatingFreqNode* prev;

    // Constructor for RatingFreqNode
    RatingFreqNode(int rating, int frequency);
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

    // === Linear Search by Product ID ===
    reviewNode* searchByProductID(string productID);

    // === Merge Sort for Rating ===
    void sortByRating(string pid);
    RatingFreqNode* rf_head;  // Pointer to the head of the rating frequency linked list
    RatingFreqNode* rf_tail;  // Pointer to the tail of the rating frequency linked list
    RatingFreqNode* mergeSortRating(RatingFreqNode* head);
    RatingFreqNode* mergeRating(RatingFreqNode* left, RatingFreqNode* right);
    RatingFreqNode* splitRating(RatingFreqNode* head);


    // === Merge Sort by Word Frequency ===
    void sortByWordFrequency(int topN);
    WordFreqNode* wf_head;  // Pointer to the head of the word frequency linked list
    WordFreqNode* wf_tail;  // Pointer to the tail of the word frequency linked list
    WordFreqNode* mergeSortFreq(WordFreqNode* head);
    WordFreqNode* mergeFreq(WordFreqNode* left, WordFreqNode* right);
    WordFreqNode* splitFreq(WordFreqNode* head);

    // === Merge Sort by Product ID ===
    void sortByProductID();
    reviewNode* mergeSortByProductID(reviewNode* head);
    reviewNode* mergeByProductID(reviewNode* left, reviewNode* right);
    reviewNode* split(reviewNode* head);
};

#endif