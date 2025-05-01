#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "ReviewsLinkedList.hpp"
#include "TransactionsLinkedList.hpp"
using namespace std;

int main()
{
    transactionsLinkedList transLL;

    ifstream file("../data/transactions_cleaned.csv");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    getline(file, line); // Skip the header line

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

        if (priceStr.empty()) continue; // Prevents crash on malformed line
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