#include <iostream>
using namespace std;
/*
 * There are two kinds of unauthorized access:
 * 1. access an element which is out of bound
 * 2. access after free
 */
int main(){
	char* ptr = new char[10];
	// read out of bound
	cout << ptr[10] << endl;
	// write out of bound
	ptr[10] = 'a';
	delete[] ptr;
	// read after free
	cout << ptr[10] << endl;
	return 0;
}