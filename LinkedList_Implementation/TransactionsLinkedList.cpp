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

void transactionsLinkedList::createTransactionNode(string customerID, string product, string category, float price, string date, string paymentMethod)
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
    size++;
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

//bubble sort
void transactionsLinkedList::bubbleSortByDate() {
    if (!head or !head->next) return;

    bool swapped;
    transactionsLL* ptr1;
    transactionsLL* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (!isEarlier(ptr1->date, ptr1->next->date)) {
                // Swap data values instead of nodes
                swap(ptr1->customerID, ptr1->next->customerID);
                swap(ptr1->product, ptr1->next->product);
                swap(ptr1->category, ptr1->next->category);
                swap(ptr1->price, ptr1->next->price);
                swap(ptr1->date, ptr1->next->date);
                swap(ptr1->paymentMethod, ptr1->next->paymentMethod);

                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void transactionsLinkedList::searchByCategory(const string& targetCategory) const {
    if (!head) {
        cout << "No transactions available.\n";
        return;
    }

    bool found = false;
    transactionsLL* current = head;

    while (current) {
        if (current->category == targetCategory) {
            cout << current->customerID << " - "
                << current->product << " - "
                << current->category << " - "
                << current->price << " - "
                << current->date << " - "
                << current->paymentMethod << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "No transactions found in category: " << targetCategory << endl;
    }
}

void transactionsLinkedList::searchByPaymentMethod(const string& targetMethod) const {
    if (!head) {
        cout << "No transactions available.\n";
        return;
    }

    bool found = false;
    transactionsLL* current = head;

    while (current) {
        if (current->paymentMethod == targetMethod) {
            cout << current->customerID << " - "
                << current->product << " - "
                << current->category << " - "
                << current->price << " - "
                << current->date << " - "
                << current->paymentMethod << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "No transactions found with payment method: " << targetMethod << endl;
    }
}

// Display all nodes
void transactionsLinkedList::display()
{
    transactionsLL* temp = head;
    while (temp)
    {
        cout << "Customer ID: \"" << temp->customerID << "\", Product Name: \"" << temp->product << "\", Category: \"" << temp->category << "\", Price:  \"" << temp->price << "\", Payment Method: \"" << temp->paymentMethod << "\", Date: \"" << temp->date << "\"" << endl;
        temp = temp->next;
    }
};

//count records in LL
int transactionsLinkedList::getLLSize()
{
    int count = 0;
    transactionsLL* temp = head;
    while (temp) 
    {
        count++;
        temp = temp->next;
    }
    return count;
}


