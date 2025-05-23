#include <iostream>
#include <chrono>
#include "../Memory_Monitor/memory_monitor_MacOS.hpp"  // Memory monitor for MacOS to get the peak memory usage
//#include <sys/resource.h> (for Linux)
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>
#include <Psapi.h>
#include "../Array_Implementation/wordsArray.hpp"
#include "../LinkedList_Implementation/ReviewsLinkedList.hpp"
#include "../LinkedList_Implementation/ReviewsLinkedList.cpp"

using namespace std;
using namespace std::chrono;

const string reviewsFile = "../data/reviews_cleaned.csv";

ReviewsLinkedList setUp_reviewLL();

size_t getPeakMemory() { //get peak memory usage
	PROCESS_MEMORY_COUNTERS pmc; //holds memory information
	if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) { //get process memory information (pmc)
        return pmc.PeakWorkingSetSize / 1024;  // converts to display in kilobytes
    }
	return 0; //if unable to get memory info
}

int main()
{
    cout << "Question 3: Which words are most frequently used in product reviews rated 1-star?" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Which implementation you want to run:" << endl;
    cout << "1. Array Implementation" << endl;
    cout << "2. Linked List Implementation" << endl;
    cout << "Enter your choice: ";
    int choice; //user input
    cin >> choice;
    cin.ignore(); // Ignore the newline character left in the buffer

	switch (choice) { //decide which implementation to run based on user input
    case 1: {
        // Array Implementation
        ifstream rfile(reviewsFile); //open file
		reviewsArray rarr = reviewsArray(rfile); //create reviewsArray obj
		auto startarray = high_resolution_clock::now();// start timer
		reviewsArray reviewOneRating = rarr.linearSearchRating(1); //search for 1-star reviews
		wordsArray warr = wordsArray(reviewOneRating, 0); //create wordsArray obj
		auto stoparray = high_resolution_clock::now(); //stop timer
		auto durationarray = duration_cast<microseconds>(stoparray - startarray); //calculate duration
		warr.showMostUsedWords(); //show most used words
        cout << "\nThe most frequent word is: \"" << warr.showWord(1) << "\"" << endl;
        cout << "Time taken to show the most frequent word with array and linear search is: " << durationarray.count() << " microseconds" << endl;
        cout << "Peak Memory Usage: " << getPeakMemory() << "KB" << endl;
        break;
    }
        case 2: {
            //// Linked List Implementation
            //ReviewsLinkedList reviewsLL = setUp_reviewLL();  // Set up the linked list with reviews
            //cout << "How many top words do you want to display? ";
            //int topN;
            //cin >> topN;
            //cin.ignore(); // Ignore the newline character left in the buffer
            //cout << "Sorted Reviews (" << topN << " words): " << endl;
            //auto start = high_resolution_clock::now();
            //reviewsLL.sortByWordFrequency(topN);  // Sort the linked list by word frequency
            //auto end = high_resolution_clock::now();
            //cout << "\nThe most frequent word is: \"" << reviewsLL.wf_head->word << "\"" << endl;
            //cout << "Time taken to show the most frequent word with linked list and merge sort is: " 
            //    << duration_cast<microseconds>(end - start).count() << " microseconds" << endl;
            //cout << "Peak memory usage: " << peakMemoryKB() << " KB\n";
            //
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