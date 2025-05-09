#include <iostream>
#include <chrono>
#include <fstream>
#include <Windows.h>
#include <Psapi.h>
#include <sstream>
#include "../Memory_Monitor/memory_monitor_MacOS.hpp"  // Memory monitor for MacOS to get the peak memory usage
#include "../Array_Implementation/reviewsArray.hpp"
#include "../Array_Implementation/wordsArray.hpp"
#include "../LinkedList_Implementation/ReviewsLinkedList.hpp"
#include "../LinkedList_Implementation/ReviewsLinkedList.cpp"


using namespace std;
using namespace std::chrono;

const string reviewsFile = "../data/reviews_cleaned.csv";

ReviewsLinkedList setUp_reviewLL();

//Q: Which rating occurs most frequently for product PROD820 in the reviews dataset?

size_t getPeakMemory() { //get peak memory usage
    PROCESS_MEMORY_COUNTERS pmc; //holds memory information
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) { //get process memory information (pmc)
        return pmc.PeakWorkingSetSize / 1024;  // converts to display in kilobytes
    }
    return 0; //if unable to get memory info
}

int main() {
    cout << "Question 4: Which rating occurs most frequently for product PROD820 in the reviews dataset?" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Which implementation you want to run:" << endl;
    cout << "1. Array Implementation" << endl;
    cout << "2. Linked List Implementation" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    cin.ignore(); // Ignore the newline character left in the buffer

    switch (choice) {
        case 1: {
            // Array Implementation
			ifstream rfile(reviewsFile); //open file
			reviewsArray rarr = reviewsArray(rfile); //create reviewsArray obj
            string pid; //user input variable
            cout << "Enter the Product ID your want to search: ";
            cin >> pid;
            cout << endl;
			reviewsArray raProduct = rarr.linearSearchProduct(pid); //search for product reviews
			wordsArray wa = wordsArray(raProduct, 1); //create wordsArray obj
			wa.showMostFrequentRatings(); //show most frequent ratings
            cout << "The most frequent rating for "<< raProduct.list[0].pid<< " is: " << wa.showWord(1) << endl;
            cout << "Peak Memory Usage: " << getPeakMemory() << "KB" << endl;
            break;
        }
        case 2: {
            ReviewsLinkedList reviewsLL = setUp_reviewLL();  // Set up the linked list with reviews
            string productID;
            cout << "Enter the Product ID your want to search: ";
            getline(cin, productID);
            auto start = high_resolution_clock::now();  // Start timing
            reviewsLL.sortByRating(productID);  // Sort the linked list by rating with Merge Sort
            auto end = high_resolution_clock::now();    // End timing
            
            cout << "\nThe most frequent rating for " << productID << " is: " << reviewsLL.rf_head->rating << endl;
            cout << "Sorting of Reviews by Rating using Merge Sort completed in: "
                << duration_cast<microseconds>(end - start).count() << " microseconds\n";
            //cout << "Peak memory usage: " << peakMemoryKB() << " KB\n";
            break;
        }
    }
    
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
