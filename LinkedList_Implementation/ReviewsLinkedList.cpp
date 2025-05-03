#include "ReviewsLinkedList.hpp"
#include <cctype> // for tolower
#include <map>   // to use map for word frequency

// Constructor
ReviewsLinkedList::ReviewsLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;

    wf_head = nullptr;  // Initialize the head of the word frequency linked list
    wf_tail = nullptr;  // Initialize the tail of the word frequency linked list
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
    if (head == nullptr || head->next == nullptr) {   // if the list is empty or has only one node
        return head;
    }

    // Split the list into two halves
    reviewNode* second = split(head);

    // Recursively sort the two halves
    head = mergeSort(head);
    second = mergeSort(second);

    // Merge the sorted halves
    return merge(head, second);
}

reviewNode* ReviewsLinkedList::split(reviewNode* head) {
    // use fast and slow pointers to find the middle of the list
    reviewNode* fast = head;
    reviewNode* slow = head;

    while (fast->next != nullptr && fast->next->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }

    reviewNode* secondHalf = slow->next;  // The second half starts after the middle
    slow->next = nullptr;  // Split the list into two halves
    if (secondHalf != nullptr) {
        secondHalf->prev = nullptr;  // Set the prev of the new head of the second half to null
    }
    return secondHalf;  // Return the head of the second half

}

reviewNode* ReviewsLinkedList::merge(reviewNode* left, reviewNode* right) {
    // temp node to help with merging
    reviewNode* temp = new reviewNode;
    reviewNode* tailMerge = temp;  // Pointer to the last node in the merged list

    while (left != nullptr && right != nullptr) {
        if (left->productID < right->productID) {  // Compare product IDs
            tailMerge->next = left;  // Add left node to merged list
            left->prev = tailMerge;  // Set the prev of the left node
            left = left->next;  // Move to the next node in the left list
        } else {
            tailMerge->next = right;  // Add right node to merged list
            right->prev = tailMerge;  // Set the prev of the right node
            right = right->next;  // Move to the next node in the right list
        }
        tailMerge = tailMerge->next;  // Move to the last node in the merged list
    }

    // If there are remaining nodes in either list, add them to the merged list
    if (left != nullptr) {
        tailMerge->next = left;  // Add remaining left nodes
        left->prev = tailMerge;  // Set the prev of the left nodes
    } else if (right != nullptr) {
        tailMerge->next = right;  // Add remaining right nodes
        right->prev = tailMerge;  // Set the prev of the right nodes
    }
    reviewNode* mergedHead = temp->next;  // The head of the merged list
    mergedHead->prev = nullptr;  // Set the prev of the head to null
    delete temp;  // Delete the temp node
    return mergedHead;  // Return the head of the merged list
}

void ReviewsLinkedList::sortByProductID() {
    if (head == nullptr) {  // If the list is empty
        cout << "List is empty. Cannot sort." << endl;
        return;
    }

    head = mergeSort(head);  // Sort the list using merge sort

    // Update the tail pointer
    tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;  // Move to the last node
    }
}

static string normalise(const string& word) {
    string t;
    for (char c : word) {
        if (isalnum(c)) {  // Check if the character is an alphabet
            t += tolower(c);  // Convert to lowercase
        }
    }
    return t;  // Return the normalized word
}

// Word Frequency
WordFreqNode::WordFreqNode(const string& word, int frequency) {
    this->word = word;  // Assign the word
    this->frequency = frequency;  // Assign the frequency
    this->next = nullptr;  // Set next to null
    this->prev = nullptr;  // Set prev to null
}

void ReviewsLinkedList::sortByWordFrequency(int topN) {
    // Count words in 1-star reviews
    map<string, int> freq;  // Map to store word frequency
    for (reviewNode* temp = head; temp != nullptr; temp = temp->next) {
        if (temp->rate == 1) {  // Only consider 1-star reviews
            istringstream iss(temp->reviewDesc);    // Split the review into words
            string word;
            while (iss >> word) {   // while there are words in the review
                // Convert word to lowercase
                word = normalise(word);
                if (!word.empty()) {  // If the word is not empty
                    freq[word]++;  // Increment the frequency of the word
                }
            }

        }
    }

    // Create a linked list of word frequencies
    for (const auto& [word, count] : freq) {     // auto pick datatype, 
        auto* node = new WordFreqNode(word, count);  // Create a new node

        if (wf_head == nullptr) {  // If the list is empty
            wf_head = node;  // Set head to the new node
            wf_tail = node;  // Set tail to the new node
        } else {
            wf_tail->next = node;  // Add the new node to the end of the list
            node->prev = wf_tail;  // Set the prev of the new node
            wf_tail = node;  // Update tail to point to the new node
        }

        size++;  // Increase the size of the list
    }

    // Sort the linked list by frequency
    wf_head = mergeSortFreq(wf_head);  // Sort the list using merge sort

    // redo the tail pointer
    wf_tail = wf_head;
    while (wf_tail->next != nullptr) {
        wf_tail = wf_tail->next;  // Move to the last node
    }

    // Display the top N words
    cout << "Top " << topN << " words in 1-star reviews:\n";
    WordFreqNode* temp = wf_head;  // Create a temp pointer to traverse the list

    for (int i = 0; i < topN && temp != nullptr; i++) {
        cout << temp->word << ": " << temp->frequency << endl;  // Display the word and its frequency
        temp = temp->next;  // Move to the next node
    }
}

WordFreqNode* ReviewsLinkedList::mergeSortFreq(WordFreqNode* head) {
    if (head == nullptr || head->next == nullptr) {  // if the list is empty or has only one node
        return head;
    }

    // Split the list into two halves
    WordFreqNode* second = splitFreq(head);

    // Recursively sort the two halves
    head = mergeSortFreq(head);
    second = mergeSortFreq(second);

    // Merge the sorted halves
    return mergeFreq(head, second);
}

WordFreqNode* ReviewsLinkedList::splitFreq(WordFreqNode* head) {
    // use fast and slow pointers to find the middle of the list
    WordFreqNode* fast = head;
    WordFreqNode* slow = head;

    while (fast->next != nullptr && fast->next->next != nullptr) { 
        fast = fast->next->next;
        slow = slow->next;
    }

    WordFreqNode* secondHalf = slow->next;  // The second half starts after the middle
    slow->next = nullptr;  // Split the list into two halves
    if (secondHalf != nullptr) {
        secondHalf->prev = nullptr;  // Set the prev of the new head of the second half to null
    }
    return secondHalf;  // Return the head of the second half
}

WordFreqNode* ReviewsLinkedList::mergeFreq(WordFreqNode* left, WordFreqNode* right) {
    // temp node to help with merging
    WordFreqNode* temp = new WordFreqNode("", 0);  // Create a temp node
    WordFreqNode* tailMerge = temp;  // Pointer to the last node in the merged list

    while (left != nullptr && right != nullptr) {
        if (left->frequency > right->frequency) {  // Compare frequencies
            tailMerge->next = left;  // Add left node to merged list
            left->prev = tailMerge;  // Set the prev of the left node
            left = left->next;  // Move to the next node in the left list
        } else {
            tailMerge->next = right;  // Add right node to merged list
            right->prev = tailMerge;  // Set the prev of the right node
            right = right->next;  // Move to the next node in the right list
        }
        tailMerge = tailMerge->next;  // Move to the last node in the merged list
    }

    // If there are remaining nodes in either list, add them to the merged list
    if (left != nullptr) {
        tailMerge->next = left;  // Add remaining left nodes
        left->prev = tailMerge;  // Set the prev of the left nodes
    } else if (right != nullptr) {
        tailMerge->next = right;  // Add remaining right nodes
        right->prev = tailMerge;  // Set the prev of the right nodes
    }
    WordFreqNode* mergedHead = temp->next;  // The head of the merged list
    mergedHead->prev = nullptr;  // Set the prev of the head to null
    delete temp;  // Delete the temp node
    return mergedHead;  // Return the head of the merged list
}