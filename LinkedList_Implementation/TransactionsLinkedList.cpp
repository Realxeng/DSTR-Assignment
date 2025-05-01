#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "ReviewsLinkedList.hpp"
#include "TransactionsLinkedList.hpp"

using namespace std;
using namespace std::chrono;
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
};

void transactionsLinkedList::addNode(string customerID, string product, string category, float price, string date, string paymentMethod)
{
    transactionsLL* newNode = new transactionsLL{customerID, product, category, date, paymentMethod, price};

    if (!head) 
    {
        head = tail = newNode;
    }
    else 
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
};

//insertion sort sorted by date from newest to oldest
void transactionsLinkedList::SortByDate()
{
    if (!head or !head->next) 
    {
        return;
    }

    transactionsLL* sorted = nullptr;
    transactionsLL* current = head;

    while (current != nullptr)//loop through the original LL
    {
        transactionsLL* next = current->next;

        // Disconnect current
        current->prev = current->next = nullptr;

        if (!sorted)//insert current node into new LL as Head
        {
            sorted = current;
        }
        else if (isEarlier(current->date, sorted->date))//insert to the front
        {
            current->next = sorted;
            sorted->prev = current;
            sorted = current;
        }
        else//insert to middle or behind
        {
            transactionsLL* temp = sorted;
            while (temp->next && isEarlier(temp->next->date, current->date)) //loop to find date that is later than current node date
            {
                temp = temp->next;
            }

            current->next = temp->next;
            if (temp->next)
            {
                temp->next->prev = current;
            }
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

