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
    // dummy node to help with merging
    reviewNode* dummy = new reviewNode;
    reviewNode* tailMerge = dummy;  // Pointer to the last node in the merged list

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
    reviewNode* mergedHead = dummy->next;  // The head of the merged list
    mergedHead->prev = nullptr;  // Set the prev of the head to null
    delete dummy;  // Delete the dummy node
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