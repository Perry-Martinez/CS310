#include <iostream>
using namespace std;

int main() {
    int value = 42;
    int* p = &value;

    cout << *p << endl;

    // int* arr; -> declared a pointer to an int and then attempted to access an index
    int* arr = new int[1]; // -> dynamically allocated array of int
    arr[0] = 10;

    char c = 'A';
    // int* q = &c; -> attempting to initialize a pointer to an int to the address of a variable of type char
    char* q = &c;

    cout << *q << endl;
    return 0;
}
