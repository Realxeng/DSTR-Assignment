#pragma once
#include <iostream>
using namespace std;

class transactionsLinkedList
{
    struct transactionsLL
    {
        string customerID, product, category, date, paymentMethod;
        float price = 0.0f;

        transactionsLL* prev = nullptr;
        transactionsLL* next = nullptr;
    };
    transactionsLL* head = nullptr;
    transactionsLL* tail = nullptr;

    //Function to check which date is earlier
    bool isEarlier(string d1, string d2)
    {
        int day1, month1, year1;
        int day2, month2, year2;

        // Parse first date
        if (sscanf_s(d1.c_str(), "%d/%d/%d", &day1, &month1, &year1) != 3) {
            cerr << "Invalid date format!";
        }
        // Parse second date
        
        if (sscanf_s(d2.c_str(), "%d/%d/%d", &day2, &month2, &year2) != 3) {
            cerr << "Invalid date fornat!";
        }

        if (year1 != year2) return year1 < year2;
        if (month1 != month2) return month1 < month2;
        return day1 <= day2;
    }

public:
    //to do data population with insertion slot
    void addSorted(string customerID, string product, string category, float price, string date, string paymentMethod)
    {
        transactionsLL* newNode = new transactionsLL;

        newNode->customerID = customerID;
        newNode->product = product;
        newNode->category = category;
        newNode->price = price;
        newNode->date = date;
        newNode->paymentMethod = paymentMethod;

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }

        transactionsLL* currentNode = head;

        while (currentNode!=nullptr && isEarlier(currentNode->date, date))//to loop until the end to compare the dates
        {
            currentNode = currentNode->next;
        }

        if (currentNode == nullptr)//insert at the end
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
            newNode->next = currentNode; //changing next pointer of new node to current node
            newNode->prev = currentNode->prev; //changing previous pointer of new node to current node previous pointer
            currentNode->prev->next = newNode; //changing current node previous's next pointer to new node
            currentNode->prev = newNode; // changing current node's previous pointer to new node
        }
    }

    void display()//display each lines
    {
        transactionsLL* temp = head;
        while (temp)
        {
            cout << temp->customerID << " - " << temp->product << " - " << temp->price << " - " << temp->date << endl;
            temp = temp->next;
        }
    }
};