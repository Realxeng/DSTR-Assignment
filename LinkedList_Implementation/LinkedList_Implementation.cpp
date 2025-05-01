#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "ReviewsLinkedList.hpp"
#include "TransactionsLinkedList.hpp"

using namespace std;
using namespace std::chrono;  // So we can use high_resolution_clock directly
using namespace std;

//int main()
//{
//
//     transactionsLinkedList transLL;
//
//     ifstream file("../data/transactions_cleaned.csv");
//     if (!file.is_open()) {
//         cerr << "Error opening file!" << endl;
//         return 1;
//     }
//
//     string line;
//     getline(file, line); // Skip the header line
//
//     while (getline(file, line)) {
//         stringstream ss(line);
//         string customerID, product, category, priceStr, date, paymentMethod;
//         float price;
//
//         getline(ss, customerID, ',');
//         getline(ss, product, ',');
//         getline(ss, category, ',');
//         getline(ss, priceStr, ',');
//         getline(ss, date, ',');
//         getline(ss, paymentMethod, '\n');
//
//         if (priceStr.empty()) continue; // Prevents crash on malformed line
//         price = stof(priceStr); // Convert price string to float
//
//         // Insert into linked list
//         transLL.addNode(customerID, product, category, price, date, paymentMethod);
//     }
//
//     file.close();
//
//     // Display the sorted transactions
//     cout << "Transactions sorted by date:\n";
//     transLL.display();
//
//    return 0;
//}


int main()
{
    transactionsLinkedList transLL;
    ifstream file("../data/transactions_cleaned.csv");

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    getline(file, line); // Skip header

    int totalRecords = 0; // Counter for number of valid records

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
        transLL.addNode(customerID, product, category, price, date, paymentMethod);
        totalRecords++;
    }

    file.close();

    cout << "Total transactions loaded: " << totalRecords << endl;

    auto start = high_resolution_clock::now();

    transLL.SortByDate();
    transLL.display();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "\nTime taken to sort and display: " << duration.count() << " milliseconds" << endl;

    return 0;
}