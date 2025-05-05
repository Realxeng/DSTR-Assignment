#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "ReviewsLinkedList.hpp"
#include "TransactionsLinkedList.hpp"

using namespace std;
using namespace std::chrono;
using namespace std;

//constructor
transactionsLinkedList::transactionsLinkedList() : head(nullptr), tail(nullptr), size(0) {}
//destructor
transactionsLinkedList::~transactionsLinkedList() {}

//Function to get the middle node of the linked list
transactionsLL* transactionsLinkedList::getMiddleNode(transactionsLL* start, transactionsLL* end) {
    if (!start) return nullptr;

    transactionsLL* slow = start;
    transactionsLL* fast = start;

    while (fast != end && fast->next != end) {
        fast = fast->next;
        if (fast != end) {
            fast = fast->next;
            slow = slow->next;
        }
    }

    return slow;
}

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
void transactionsLinkedList::insertionSortByDate()
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
        else if (current->date < sorted->date)//insert to the front
        {
            current->next = sorted;
            sorted->prev = current;
            sorted = current;
        }
        else//insert to middle or behind
        {
            transactionsLL* temp = sorted;
            while (temp->next && temp->next->date < current->date) //loop to find date that is later than current node date
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

//insertion sort sorted by customer ID
void transactionsLinkedList::insertionSortByCusID()
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
		else if (current->customerID < sorted->customerID)//insert to the front
		{
			current->next = sorted;
			sorted->prev = current;
			sorted = current;
		}
		else//insert to middle or behind
		{
			transactionsLL* temp = sorted;
			while (temp->next && temp->next->customerID < current->customerID) //loop to find date that is later than current node date
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
            if (ptr1->date > ptr1->next->date) {
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

//Linear Search
void transactionsLinkedList::linearSearchByCategory(const string& targetCategory) const {
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

//Linear search category and return the records in a new linked list
transactionsLinkedList transactionsLinkedList::returnByCategory(const string& targetCategory) const {
	transactionsLinkedList result;
	if (!head) {
		cout << "No transactions available.\n";
		return result;
	}
	transactionsLL* current = head;
	while (current) {
		if (current->category == targetCategory) {
			result.createTransactionNode(current->customerID, current->product, current->category, current->price, current->date, current->paymentMethod);
		}
		current = current->next;
	}
	if (result.head == nullptr) {
		cout << "No transactions found in category: " << targetCategory << endl;
	}
	return result;
}

//Linear Search
void transactionsLinkedList::linearSearchByPaymentMethod(const string& targetMethod) const {
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

//Linear search payment method and return the records in a new linked list
transactionsLinkedList transactionsLinkedList::returnByPaymentMethod(const string& targetMethod) const {
	transactionsLinkedList result;
	if (!head) {
		cout << "No transactions available.\n";
		return result;
	}
	transactionsLL* current = head;
	while (current) {
		if (current->paymentMethod == targetMethod) {
			result.createTransactionNode(current->customerID, current->product, current->category, current->price, current->date, current->paymentMethod);
		}
		current = current->next;
	}
	if (result.head == nullptr) {
		cout << "No transactions found with payment method: " << targetMethod << endl;
	}
	return result;
}

//Binary Search by customer ID
transactionsLinkedList transactionsLinkedList::binarySearchByCustomerID(const string& targetID) {
    if (!head) return transactionsLinkedList();

    // Define boundaries
    transactionsLL* left = head;
    transactionsLL* right = tail;

    while (left != nullptr && right != nullptr && left != right->next) {
        // Find middle node
        transactionsLL* mid = getMiddleNode(left, right);

        if (!mid) return transactionsLinkedList();

        if (mid->customerID == targetID) {
            // Create a new linked list with the found node
            transactionsLinkedList result;
            result.createTransactionNode(mid->customerID, mid->product, mid->category, mid->price, mid->date, mid->paymentMethod);
            return result;
        }
        else if (mid->customerID < targetID) {
            left = mid->next;
        }
        else {
            right = mid->prev;
        }
    }

    return transactionsLinkedList(); // Not found
}

//display all nodes
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

transactionsLinkedList transactionsLinkedList::setUp_transactionLL()
{
    transactionsLinkedList transLL;

    ifstream file("../data/transactions_cleaned.csv");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return transLL;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string customerID, product, category, priceStr, date, paymentMethod;
        float price;

        getline(ss, customerID, ',');
        getline(ss, product, ',');
        getline(ss, category, ',');
        getline(ss, priceStr, ',');
        getline(ss, date, ',');
        getline(ss, paymentMethod, '\n');

        if (priceStr.empty()) continue;
        price = stof(priceStr);

        transLL.createTransactionNode(customerID, product, category, price, date, paymentMethod);
    }

    file.close();
    cout << "\nTransactions linked list created and populated.\n";
    cout << "Number of transactions: " << transLL.getLLSize() << endl;

    return transLL;
}


