#pragma once
#include <iostream>
using namespace std;

class transactionsLinkedList
{
    struct transactionsLL
    {
        string customerID, product, category, date, paymentMethod;
        float price;

        transactionsLL* prev = nullptr;
        transactionsLL* next = nullptr;
    };
    transactionsLL* head = nullptr;
    transactionsLL* tail = nullptr;

    bool isEarlier(string d1, string d2) 
    {
        int day1, month1, year1;
        int day2, month2, year2;

        // Parse first date
        sscanf(d1.c_str(), "%d/%d/%d", &day1, &month1, &year1);
        // Parse second date
        sscanf(d2.c_str(), "%d/%d/%d", &day2, &month2, &year2);

        if (year1 != year2) return year1 < year2;
        if (month1 != month2) return month1 < month2;
        return day1 < day2;
    }

public:
    void addNode(string customerID, string product, string category, float price, string date, string paymentMethod)
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
        else
        {
            transactionsLL* currentNode = head;
            while (currentNode->next != nullptr)
            {
                if (isEarlier)
                {

                }
            }
        }

    }

};

