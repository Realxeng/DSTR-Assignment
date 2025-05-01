#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

#include "ReviewsLinkedList.hpp"
#include "TransactionsLinkedList.hpp"
using namespace std;
using namespace std::chrono;


// Define Function in MAIN
ReviewsLinkedList setUp_reviewLL();

int main()
{
    int choice;
    cout << "Menu:\n";
    cout << "1. Reviews Linked List\n";
    cout << "2. Transactions Linked List\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); // Ignore the newline character left in the buffer

    if (choice == 1) 
    {
        // Reviews Linked List
        ReviewsLinkedList reviewsLL = setUp_reviewLL();

        cout << "Review Linked List Menu:\n";
        cout << "1. Display Reviews\n";
        cout << "2. Sort by Product ID (using Merge Sort)\n";

        cin >> choice;
        cin.ignore(); // Ignore the newline character left in the buffer

        switch (choice) {
        case 1:
            // Display Reviews
            cout << "Displaying Reviews:\n";
            reviewsLL.display();
            break;

        case 2:
        default:
            cout << "Invalid choice.\n";
        }

    }
    else if (choice == 2) 
    {
        transactionsLinkedList transLL = setUp_transactionLL();

        cout << "Transactions Linked List Menu:\n";
        cout << "1. Display Transaction Records\n";
        cout << "2. Sort by Date (using insertion sort)\n";
        cout << "3. Sort by Date (using bubble sort)\n";

        cin >> choice;
        cin.ignore();

        if (choice == 1) 
        {
            cout << "Total Records: " << transLL.getLLSize() << endl;
            transLL.display();
        }
        else if (choice == 2) 
        {
            auto start = high_resolution_clock::now();
            transLL.SortByDate();
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);

            transLL.display();
            cout << "\nInsertion sort completed in: " << duration.count() << " ms" << endl;
            
            int searchChoice;
            cout << "\nSearch by:\n1. Category\n2. Payment Method\nEnter choice: ";
            cin >> searchChoice;

            cin.ignore(); // clear newline from input buffer
            string searchTerm;

            if (searchChoice == 1) 
            {
                cout << "Enter category: ";
                getline(cin, searchTerm);

                auto searchStart = high_resolution_clock::now();
                transLL.searchByCategory(searchTerm);
                auto searchEnd = high_resolution_clock::now();

                auto searchDuration = duration_cast<milliseconds>(searchEnd - searchStart);
                cout << "Search completed in " << searchDuration.count() << " ms.\n";

            }
            else if (searchChoice == 2) 
            {
                cout << "Enter payment method: ";
                getline(cin, searchTerm);

                auto searchStart = high_resolution_clock::now();
                transLL.searchByPaymentMethod(searchTerm);
                auto searchEnd = high_resolution_clock::now();

                auto searchDuration = duration_cast<milliseconds>(searchEnd - searchStart);
                cout << "Search completed in " << searchDuration.count() << " ms.\n";
            }
            else 
            {
                cout << "Invalid choice.\n";
            }
        }
        else if (choice == 3)
        {
            auto start = high_resolution_clock::now();
            transLL.bubbleSortByDate();
            auto end = high_resolution_clock::now();

            auto duration = duration_cast<milliseconds>(end - start);
            transLL.display();
            cout << "Bubble Sort completed in " << duration.count() << " ms.\n";

            int searchChoice;
            cout << "\nSearch by:\n1. Category\n2. Payment Method\nEnter choice: ";
            cin >> searchChoice;

            cin.ignore(); // clear newline from input buffer
            string searchTerm;

            if (searchChoice == 1) 
            {
                cout << "Enter category: ";
                getline(cin, searchTerm);

                auto searchStart = high_resolution_clock::now();
                transLL.searchByCategory(searchTerm);
                auto searchEnd = high_resolution_clock::now();

                auto searchDuration = duration_cast<milliseconds>(searchEnd - searchStart);
                cout << "Search completed in " << searchDuration.count() << " ms.\n";

            }
            else if (searchChoice == 2) 
            {
                cout << "Enter payment method: ";
                getline(cin, searchTerm);

                auto searchStart = high_resolution_clock::now();
                transLL.searchByPaymentMethod(searchTerm);
                auto searchEnd = high_resolution_clock::now();

                auto searchDuration = duration_cast<milliseconds>(searchEnd - searchStart);
                cout << "Search completed in " << searchDuration.count() << " ms.\n";
            }
            else 
            {
                cout << "Invalid choice.\n";
            }
        }
    }
    return 0;
}

ReviewsLinkedList setUp_reviewLL() 
{
    // Reviews Linked List
    ReviewsLinkedList reviewsLL;

    ifstream file("../data/reviews_cleaned.csv");
    if (!file.is_open()) 
    {
        cerr << "Error opening file!" << endl;
        return reviewsLL; // Return empty linked list
    }

    string line;

    while (getline(file, line)) 
    {
        stringstream ss(line);
        string productID, customerID, reviewDesc;
        int rate;

        getline(ss, productID, ',');
        getline(ss, customerID, ',');
        ss >> rate;
        ss.ignore(); // Ignore the comma
        getline(ss, reviewDesc);

        // Insert into linked list
        reviewsLL.insertNode_atEnd(productID, customerID, rate, reviewDesc);
    }

    file.close();
    cout << "\nReviews linked list created and populated.\n";
    cout << "Number of reviews: " << reviewsLL.getSize() << endl;

    return reviewsLL;

}

transactionsLinkedList setUp_transactionLL()
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