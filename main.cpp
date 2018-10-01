#include <iostream>
#include "myVector.h"

using namespace std;


int main() {
	myVector V1(10);
	myVector V2(20);

	//int A[] = {1,2,3,4};

	for (int i = 0; i<7; i++) {
		V1.pushBack(rand() % 100);
	}

	for (int i = 0; i<5; i++) {
		V2.pushBack(rand() % 100);
	}

	cout << V1 << endl;
	cout << V2 << endl;

	myVector V = V1 + V2;

	// V.print();

	// cout<<V.size()<<endl;
	// cout<<V.vSize()<<endl;

	// for(int i=0;i<498;i++){
	//   V.popBack();
	// }

	// cout<<V.size()<<endl;

	// V.size(15);

	// cout<<V.vSize()<<endl;

	// V.print();

	// cout<<V[3]<<endl;

	// V.print();

	// V[2] = 11;

	// cout<<V[2]<<endl;

	// int x = 99;

	// //this statement when overloading
	// cout<<x<<endl;
	// //is equivalent to this:
	// cout<<*(&x)<<endl;

	// V.print();

	// int *a = new int[10]; //a[0]
	// int *b = a;
	// for(int i=0;i<10;i++){
	//   *b = rand()%99;
	//   b++;
	// }
	// for(int i=0;i<10;i++){
	//   cout<<a[i]<<" ";
	// }

	system("pause");
}