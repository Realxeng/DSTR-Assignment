#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "ReviewsLinkedList.hpp"
#include "ReviewsLinkedList.cpp"
#include "TransactionsLinkedList.hpp"
#include "TransactionsLinkedList.cpp"
using namespace std;

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

    if (choice == 1) {
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

    } else if (choice == 2) {

        /*
        TODO: Insert transactions linked list code here <-----------
        */

    }
        


     //transactionsLinkedList transLL;

     //ifstream file("../data/transactions_cleaned.csv");
     //if (!file.is_open()) {
     //    cerr << "Error opening file!" << endl;
     //    return 1;
     //}

     //string line;
     //getline(file, line); // Skip the header line

     //while (getline(file, line)) {
     //    stringstream ss(line);
     //    string customerID, product, category, priceStr, date, paymentMethod;
     //    float price;

     //    getline(ss, customerID, ',');
     //    getline(ss, product, ',');
     //    getline(ss, category, ',');
     //    getline(ss, priceStr, ',');
     //    getline(ss, date, ',');
     //    getline(ss, paymentMethod, '\n');

     //    if (priceStr.empty()) continue; // Prevents crash on malformed line
     //    price = stof(priceStr); // Convert price string to float

     //    // Insert into linked list
     //    transLL.addSorted(customerID, product, category, price, date, paymentMethod);
     //}

     //file.close();

     //// Display the sorted transactions
     //cout << "Transactions sorted by date:\n";
     //transLL.display();

    return 0;
}

ReviewsLinkedList setUp_reviewLL(){
            // Reviews Linked List
            ReviewsLinkedList reviewsLL;

            ifstream file("../data/reviews_cleaned.csv");
            if (!file.is_open()) {
                cerr << "Error opening file!" << endl;
                return reviewsLL; // Return empty linked list
            }
    
            string line;
            getline(file, line); // Skip the header line
    
            while (getline(file, line)) {
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