//Brent Laden
//myVector.h
#pragma once
#include <iostream>

using namespace std;

class myVector {
private:
	int *theVector;
	int vCap;
	double percentFull();
	int vSize;
public:
	myVector(int size);
	void print();
	void shrinkCheck();
	void pop_back();
	void push_back(int item);
	void printSize();
};
