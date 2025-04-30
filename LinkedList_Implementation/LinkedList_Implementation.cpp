#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "ReviewsLinkedList.h"
#include "TransactionsLinkedList.hpp"
using namespace std;

int main()
{
    transactionsLinkedList transLL;

    ifstream file("..\\transactions_cleaned.csv");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        string customerID, product, category, priceStr, date, paymentMethod;
        float price;

        
        getline(file, customerID, ',');
        getline(file, product, ',');
        getline(file, category, ',');
        getline(file, priceStr, ',');
        getline(file, date, ',');
        getline(file, paymentMethod, '\n');

        price = stof(priceStr); // Convert price string to float

        // Insert into linked list
        transLL.addSorted(customerID, product, category, price, date, paymentMethod);
    }

    file.close();

    // Display the sorted transactions
    cout << "Transactions sorted by date:\n";
    transLL.display();

    return 0;
}