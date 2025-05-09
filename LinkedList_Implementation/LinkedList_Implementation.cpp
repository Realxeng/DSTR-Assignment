#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <Windows.h>
#include <Psapi.h>

//#include "../Memory_Monitor/memory_monitor_MacOS.hpp"  // Memory monitor for MacOS to get the peak memory usage
#include "ReviewsLinkedList.hpp"
//#include "ReviewsLinkedList.cpp"
#include "TransactionsLinkedList.hpp"
// #include "TransactionsLinkedList.cpp"
using namespace std;
using namespace std::chrono;

size_t getPeakMemory() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.PeakWorkingSetSize / 1024;  // in kilobytes
    }
    return 0;
}

void performSearch(transactionsLinkedList& transLL, bool sortedByCusID)
{
    int searchChoice;
    cout << "\nSearch by:\n"
        << "1. Category (Linear Search)\n"
        << "2. Payment Method (Linear Search)\n";

    if (sortedByCusID) {
        cout << "3. Customer ID (Binary Search)\n";
    }

    cout << "Enter choice: ";
    cin >> searchChoice;
    cin.ignore(); // clear newline

    string searchTerm;

    if (searchChoice == 1)
    {
        cout << "Enter category: ";
        getline(cin, searchTerm);

        auto start = high_resolution_clock::now();
        transLL.linearSearchByCategory(searchTerm);
        auto end = high_resolution_clock::now();
        cout << "Search completed in " << duration_cast<microseconds>(end - start).count() << " microseconds.\n";
        cout << "Peak memory usage: " << getPeakMemory() << "KB" << endl;
    }
    else if (searchChoice == 2)
    {
        cout << "Enter payment method: ";
        getline(cin, searchTerm);

        auto start = high_resolution_clock::now();
        transLL.linearSearchByPaymentMethod(searchTerm);
        auto end = high_resolution_clock::now();
        cout << "Search completed in " << duration_cast<microseconds>(end - start).count() << " microseconds.\n";
        cout << "Peak memory usage: " << getPeakMemory() << "KB" << endl;
    }
    else if (searchChoice == 3 && sortedByCusID)
    {
        cout << "Enter customer ID (e.g. CUST1234): ";
        getline(cin, searchTerm);

        auto start = high_resolution_clock::now();
        transactionsLinkedList result = transLL.binarySearchByCustomerID(searchTerm);
        auto end = high_resolution_clock::now();

        if (result.getLLSize() > 0)
        {
            cout << "\nTransaction Found:\n";
            result.display();
        }
        else
        {
            cout << "Customer ID not found.\n";
        }

        cout << "Search completed in " << duration_cast<microseconds>(end - start).count() << " microseconds.\n";
        cout << "Peak memory usage: " << getPeakMemory() << "KB" << endl;
    }
    else
    {
        cout << "Invalid choice or unsupported search (list must be sorted by Customer ID for binary search).\n";
    }
}




void performBinarySearch(transactionsLinkedList& transLL) {
    string searchTerm;
    cout << "Enter customer ID (e.g. CUST1234): ";
    getline(cin, searchTerm);

    auto start = high_resolution_clock::now();
    transactionsLinkedList result = transLL.binarySearchByCustomerID(searchTerm);
    auto end = high_resolution_clock::now();

    if (result.getLLSize() > 0) // Check if the result contains any nodes
    {
        cout << "\nTransaction Found:\n";
        result.display(); // Display the matching transaction(s)
    }
    else
    {
        cout << "Customer ID not found.\n";
    }

    cout << "Search completed in " << duration_cast<microseconds>(end - start).count() << " microseconds.\n";
    cout << "Peak memory usage: " << getPeakMemory() << "KB" << endl;
}

void performSortAndSearch(transactionsLinkedList& transLL, int sortChoice)
{
    auto start = high_resolution_clock::now();

    switch (sortChoice)
    {
    case 1:
        transLL.insertionSortByDate();
        cout << "\nInsertion Sort by Date completed in: ";
        break;
    case 2:
        transLL.insertionSortByCusID();
        cout << "\nInsertion Sort by Customer ID completed in: ";
        break;
    case 3:
        transLL.bubbleSortByDate();
        cout << "\nBubble Sort by Date completed in: ";
        break;
    default:
        cout << "Invalid sort option.\n";
        return;
    }

    auto end = high_resolution_clock::now();
    transLL.display();
    cout << duration_cast<microseconds>(end - start).count() << " microseconds\n";
    cout << "Peak memory usage: " << getPeakMemory() << "KB" << endl;

    // Pass flag based on sort type
    bool sortedByCusID = (sortChoice == 2);
    performSearch(transLL, sortedByCusID);
}

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
        cout << "3. Sort by Frequently used word in product reviews rated 1-star (using Merge Sort)\n";
        cout << "4. Search Most frequet rating for a product (using Merge Sort and Linear Search)\n";
        cout << "5. Search by Product ID (using Linear Search)\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character left in the buffer

        switch (choice) {
        case 1: {
            // Display Reviews
            cout << "Displaying Reviews:\n";
            reviewsLL.display();
            break;
        }
        case 2: {
            // Sort by Product ID
            cout << "Sorting by Product ID...\n";
            auto start = high_resolution_clock::now();  // Start timing
            reviewsLL.sortByProductID();    // Sort the linked list by Product ID with Merge Sort
            auto end = high_resolution_clock::now();    // End timing
            cout << "Sorted Reviews:\n";
            reviewsLL.display();

            cout << "\nSorting of Reviews by ProductID using Merge Sort completed in: "
                << duration_cast<microseconds>(end - start).count() << " microseconds\n";
            //cout << "Peak memory usage: " << peakMemoryKB() << " KB\n";
            break;
        }
        case 3: {
            cout << "How many top words do you want to display? ";
            int topN;
            cin >> topN;
            cin.ignore(); // Ignore the newline character left in the buffer
            cout << "Sorted Reviews (" << topN << " words): " << endl;
            auto start = high_resolution_clock::now();
            reviewsLL.sortByWordFrequency(topN);  // Sort the linked list by word frequency
            auto end = high_resolution_clock::now();
            cout << "\nThe most frequent word is: \"" << reviewsLL.wf_head->word << "\"" << endl;
            cout << "Time taken to show the most frequent word with linked list and merge sort is: " 
                << duration_cast<microseconds>(end - start).count() << " microseconds" << endl;
            //cout << "Peak memory usage: " << peakMemoryKB() << " KB\n";

            break;
        }
        case 4: {
            cout << "Enter the product ID to search for: ";
            string productID;
            getline(cin, productID);  // Read the product ID from the user
            auto start = high_resolution_clock::now();  // Start timing
            reviewsLL.sortByRating(productID);  // Sort the linked list by rating with Merge Sort
            auto end = high_resolution_clock::now();    // End timing

            cout << "\nSorting of Reviews by Rating using Merge Sort completed in: "
                << duration_cast<microseconds>(end - start).count() << " microseconds\n";
            //cout << "Peak memory usage: " << peakMemoryKB() << " KB\n";

            break;
        }
        case 5: {
            cout << "Enter the Product ID to search for: ";
            string productID;
            getline(cin, productID);  // Read the product ID from the user
            auto start = high_resolution_clock::now();  // Start timing
            reviewNode* filteredHead = reviewsLL.searchByProductID(productID);  // Search for the product ID in the linked list
            auto end = high_resolution_clock::now();    // End timing
            cout << "Results of search for Product ID \"" << productID << "\":\n";
            for (reviewNode* cur = filteredHead; cur; cur = cur->next) {
                cout << cur->productID << ", " 
                     << cur->customerID << ", Rating: " 
                     << cur->rate << ", Review: \"" 
                     << cur->reviewDesc << "\"\n";
            }    
            cout << "Search completed in " << duration_cast<microseconds>(end - start).count() << " microseconds.\n";
            //cout << "Peak memory usage: " << peakMemoryKB() << " KB\n";
            break;
        }
        default: {
            cout << "Invalid choice.\n";
            break;
        }
        }

    }
    else if (choice == 2)
    {
        transactionsLinkedList transLL = transLL.setUp_transactionLL();

        cout << "Transactions Linked List Menu:\n";
        cout << "1. Display Transaction Records\n";
        cout << "2. Sort by Date (using Insertion Sort)\n";
        cout << "3. Sort by Customer ID (using Insertion Sort)\n";
        cout << "4. Sort by Date (using Bubble Sort)\n";

        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            cout << "Total Records: " << transLL.getLLSize() << endl;
            transLL.display();
        }
        else if (choice == 2)
        {
            performSortAndSearch(transLL, 1);  // 1 = insertion sort by date
        }
        else if (choice == 3)
        {
            performSortAndSearch(transLL, 2);  // 2 = insertion sort by customer ID
        }
        else if (choice == 4)
        {
            performSortAndSearch(transLL, 3);  // 3 = bubble sort by date
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}

ReviewsLinkedList setUp_reviewLL(){
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