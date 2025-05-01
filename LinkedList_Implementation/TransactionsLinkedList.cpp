#include "TransactionsLinkedList.hpp"
#include <iostream>
#include <string>
#include <cstdio> // for sscanf_s

using namespace std;

// Function to check which date is earlier
bool transactionsLinkedList::isEarlier(string d1, string d2)
{
    int day1, month1, year1;
    int day2, month2, year2;

    if (sscanf_s(d1.c_str(), "%d/%d/%d", &year1, &month1, &day1) != 3)
        cerr << "Invalid date format: " << d1 << endl;

    if (sscanf_s(d2.c_str(), "%d/%d/%d", &year2, &month2, &day2) != 3)
        cerr << "Invalid date format: " << d2 << endl;

    if (year1 != year2) return year1 < year2;
    if (month1 != month2) return month1 < month2;
    return day1 < day2;
}

//Insert node in sorted order
void transactionsLinkedList::addSorted(string customerID, string product, string category, float price, string date, string paymentMethod)
{
    transactionsLL* newNode = new transactionsLL{ customerID, product, category, date, paymentMethod, price };

    if (head == nullptr)
    {
        head = tail = newNode;
        return;
    }

    transactionsLL* currentNode = head;

    while (currentNode != nullptr && isEarlier(currentNode->date, date))
    {
        currentNode = currentNode->next;
    }


    if (currentNode == nullptr)//insert to end
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    else if (currentNode == head)//insert to front
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    else//insert to middle basically in the middle of currentNode.prev & currentNode
    {
        newNode->next = currentNode;//changing next pointer of new node to current node
        newNode->prev = currentNode->prev;//changing previous pointer of new node to current node previous pointer
        currentNode->prev->next = newNode;//changing current node previous's next pointer to new node
        currentNode->prev = newNode;//changing current node's previous pointer to new node
    }
}

// Display all nodes
void transactionsLinkedList::display()
{
    transactionsLL* temp = head;
    while (temp)
    {
        cout << temp->customerID << " - " << temp->product << " - " << temp->price << " - " << temp->date << endl;
        temp = temp->next;
    }
}

