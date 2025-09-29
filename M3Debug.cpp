//This program is written with with weekly progressions//

#include <iostream> 

using namespace std;

//week 1 function//
void week1 () {
    cout << "Hello, C++!" << endl;
}

/*This program demostrates basic input and output operations in C++ using cin and cout*/
/*This program will contain two syntax errors as per assignment deliverables.*/
//week 2 function//

void week2 () {
    int num;
    cout << "Enter a number: ";
    // DEBUG: first error below. An invalid > operator was used at the end of the statement. 
    // cin >> num;>
    cin >> num;
    cout << "You entered: " << num << endl;
}

//Week 3 selection function synax errors using if/else/while//
void week3 () {
    //hint: You're stuck...//
    int choice;
    cout << "Enter a number other than 1: ";
    cin >> choice;
    //DEBUG: usage of assignment operator instead of equality comparison
    // if (choice = 1) {
    if(choice == 1){
        while (true) {
            //DEBUG: missing semicolon
            // cout << "You are stuck!\n"
            cout << "You are stuck!\n";
        }
    }
    else {
            cout << "You are free!\n" <<endl;
        }
}

int main() { 
    //week1();//comment out to run without// 
    //week2();// comment out to run without//
    week3();//comment out to run without//
    return 0;
}
    //DEBUG: The return statement is outside of the main() function.
    // return 0;