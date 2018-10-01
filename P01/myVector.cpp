//Brent Laden
//myVector.cpp
#include <iostream>
#include "myVector.h"

using namespace std;

double myVector::percentFull(){
	double level;
	level = (vSize / vCap);
	return level;
}
//removes element from array
void myVector::pop_back() {
	if (vSize == 0) {
		cout << "This Opperation is not valid";
		return;
	}
	else
		vSize--;
}
//adds onto array
void myVector::push_back(int item) {
	double level;
	level = (vSize / vCap);
	//increase size if needed
	if (level == 1) {
		int newSize = vCap*1.5;
		myVector tempVect (newSize);
		for (int i = 0; i < vSize; i++) {
			theVector[i] = tempVect[i];
		}
		theVector = tempVect;
	}
	theVector[vSize] = item;
	vSize++;
}
//prints out the size of container that is filled
void myVector::printSize()
{
	int size = vSize;
	cout << size << endl;
}
//creates vector emulator
myVector::myVector(int size) {
	vCap = size;
	vSize = 0;
	theVector = new int[vCap];
}
//prints out contents of container
void myVector::print() {
	for (int i = 0; i<vSize; i++)
		cout << theVector[i] << " ";
	cout << endl;
}
//checks if container needs to be shrunk and will do if needed
void myVector::shrinkCheck() {
	double level;
	level = (vSize / vCap);
	if (level <= .4) {
		int newSize = vCap*.4;
		myVector tempVect(newSize);
		for (int i = 0; i < vSize; i++) {
			theVector[i] = tempVect[i];
		}
		theVector = tempVect;
	}
 }
