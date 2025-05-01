#include "TransactionsLinkedList.hpp"
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

// Function to check which date is earlier
bool transactionsLinkedList::isEarlier(string d1, string d2)
{
    int day1, month1, year1;
    int day2, month2, year2;

    if (sscanf(d1.c_str(), "%d/%d/%d", &year1, &month1, &day1) != 3)
        cerr << "Invalid date format: " << d1 << endl;

    if (sscanf(d2.c_str(), "%d/%d/%d", &year2, &month2, &day2) != 3)
        cerr << "Invalid date format: " << d2 << endl;

    if (year1 != year2) return year1 < year2;
    if (month1 != month2) return month1 < month2;
    return day1 < day2;
};

void transactionsLinkedList::addNode(string customerID, string product, string category, float price, string date, string paymentMethod)
{
    transactionsLL* newNode = new transactionsLL{ customerID, product, category, date, paymentMethod, price };

    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
};

// Insertion sort for doubly linked list by date
void transactionsLinkedList::insertionSortByDate()
{
    if (!head || !head->next) return;

    transactionsLL* sorted = nullptr;

    transactionsLL* current = head;
    while (current != nullptr) {
        transactionsLL* next = current->next;

        // Disconnect current
        current->prev = current->next = nullptr;

        // Insert into sorted list
        if (!sorted) {
            sorted = current;
        }
        else if (isEarlier(current->date, sorted->date)) {
            // Insert at beginning
            current->next = sorted;
            sorted->prev = current;
            sorted = current;
        }
        else {
            transactionsLL* temp = sorted;
            while (temp->next && isEarlier(temp->next->date, current->date)) {
                temp = temp->next;
            }

            current->next = temp->next;
            if (temp->next) temp->next->prev = current;
            current->prev = temp;
            temp->next = current;
        }

        current = next;
    }

    // Recalculate tail
    head = sorted;
    tail = head;
    while (tail->next) {
        tail = tail->next;
    }
};

//Insert node in sorted order
//void transactionsLinkedList::addSorted(string customerID, string product, string category, float price, string date, string paymentMethod)
//{
//    transactionsLL* newNode = new transactionsLL{ customerID, product, category, date, paymentMethod, price };
//
//    if (head == nullptr)
//    {
//        head = tail = newNode;
//        return;
//    }
//
//    transactionsLL* currentNode = head;
//
//    while (currentNode != nullptr && isEarlier(currentNode->date, date))
//    {
//        currentNode = currentNode->next;
//    }
//
//
//    if (currentNode == nullptr)//insert to end
//    {
//        tail->next = newNode;
//        newNode->prev = tail;
//        tail = newNode;
//    }
//    else if (currentNode == head)//insert to front
//    {
//        newNode->next = head;
//        head->prev = newNode;
//        head = newNode;
//    }
//    else//insert to middle basically in the middle of currentNode.prev & currentNode
//    {
//        newNode->next = currentNode;//changing next pointer of new node to current node
//        newNode->prev = currentNode->prev;//changing previous pointer of new node to current node previous pointer
//        currentNode->prev->next = newNode;//changing current node previous's next pointer to new node
//        currentNode->prev = newNode;//changing current node's previous pointer to new node
//    }
//}

// Display all nodes
void transactionsLinkedList::display()
{
    transactionsLL* temp = head;
    while (temp)
    {
        cout << temp->customerID << " - " << temp->product << " - " << temp->price << " - " << temp->date << endl;
        temp = temp->next;
    }
};

