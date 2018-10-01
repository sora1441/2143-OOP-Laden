/*
Brent Laden
13 September 2018
This program is made to emulate a vector class. Within the program,
the user can create a vector, add or remove elements, print out the
elements, and print out the number of elements in the vector array.
*/

#include <iostream>
#include "myVector.h"

using namespace std;

int main() {
	myVector V(1000);
	for (int i = 0; i < 1000; i++) {
		V.push_back(10);
	}
	V.printSize();
	for (int i = 0; i < 998; i++) {
		V.pop_back();
	}
	V.printSize();

	system("pause");
	return 0;
}