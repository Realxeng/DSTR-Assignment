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

void performSearch(transactionsLinkedList& transLL) {
    int searchChoice;
    cout << "\nSearch by:\n1. Category\n2. Payment Method\nEnter choice: ";
    cin >> searchChoice;

    cin.ignore(); // clear newline
    string searchTerm;

    if (searchChoice == 1) {
        cout << "Enter category: ";
        getline(cin, searchTerm);

        auto start = high_resolution_clock::now();
        transLL.searchByCategory(searchTerm);
        auto end = high_resolution_clock::now();
        cout << "Search completed in " << duration_cast<milliseconds>(end - start).count() << " ms.\n";

    }
    else if (searchChoice == 2) {
        cout << "Enter payment method: ";
        getline(cin, searchTerm);

        auto start = high_resolution_clock::now();
        transLL.searchByPaymentMethod(searchTerm);
        auto end = high_resolution_clock::now();
        cout << "Search completed in " << duration_cast<milliseconds>(end - start).count() << " ms.\n";
    }
    else {
        cout << "Invalid choice.\n";
    }
}

void performSortAndSearch(transactionsLinkedList& transLL, bool useInsertionSort) {
    auto start = high_resolution_clock::now();

    if (useInsertionSort)
        transLL.SortByDate();
    else
        transLL.bubbleSortByDate();

    auto end = high_resolution_clock::now();
    transLL.display();
    cout << (useInsertionSort ? "\nInsertion Sort" : "\nBubble Sort")
        << " completed in: "
        << duration_cast<milliseconds>(end - start).count() << " ms\n";

    performSearch(transLL);
}

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
        transactionsLinkedList transLL = transLL.setUp_transactionLL();

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
            performSortAndSearch(transLL, true);  //true = insertion sort
        }
        else if (choice == 3) 
        {
            performSortAndSearch(transLL, false); //false = bubble sort
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