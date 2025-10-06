// ---- Ashtyn Ellison - Programming with C++ ---
// --- Module 4 Troubleshooting Discussion ---

#include <iostream>      
using namespace std;     

int main() {
    string petType;      // variable to store type of pet (dog, cat, etc.)
    string petName;      // variable to store the pet's name
    char morePets = 'y'; // stores users answer

    // while (morePets = 'y') {  // loops if the user says yes <--- assignment operator instead of comparison
    while(morePets == 'y'){
        cout << "What kind of pet do you have? ";
        cin >> petType;    

        cout << "What is your pet's name? ";
        // cin >> petNmae;   <--- variable name typo
        cin >> petName;

        cout << "You have a " << petType << " named " << petName << "!" << endl;

        cout << "Do you have another pet? (y/n): ";
        cin>>morePets; // <--- missing input stream object

        if (morePets != 'y' && morePets != 'n') { 
            cout << "Invalid input, try again!";
        }
    }   //<--- missing close curly brace
    // retrun 0; <--- Typo in return statement.
    return 0;
}
