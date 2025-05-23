#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct Reviews
{
	string pid, cid, rating, review;
};

class reviewsArray
{
private:
    int top = 0, max = 0;
	string cleanWord(string str);
public:
	Reviews* list;
	reviewsArray();
	reviewsArray(Reviews* list, int top);
	reviewsArray(int size);
	reviewsArray(ifstream& file);
	~reviewsArray();
	int getTop();
	void setTop(int top);
	int getMaxLine(ifstream& file);
	void insertToArray(Reviews data);
	void insertFromFile(ifstream& file);
	void insertFromFileRaw(ifstream& file);
	Reviews* deleteAtIndex(Reviews* list, int index);
	void deleteAtIndex(int index);
	void showAllReviews();
	reviewsArray insertionSortCid();
	void mergeSortByPID(int left = 0, int right = -1);
	reviewsArray linearSearchRating(int rating);
	reviewsArray linearSearchProduct(string pid);
};