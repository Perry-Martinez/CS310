// GitHub2ErrorDiscussion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main() {
    int num1, num2;

    cout << "Enter first number: ";
    cin >> num1;

    cout << "Enter second number: ";
    cin >> num2;

    //  Error #1: wrong variable name (numm2 instead of num2)
    int sum = num1 + num2;

    // Error #2: using wrong operator (<<< instead of <<)
    cout << "The sum of the two numbers is: " << sum << endl;

    return 0;
}
