// ---- Ashtyn Ellison - Programming with C++ ---
// --- Module 6 Troubleshooting Discussion ---

#include <iostream>
using namespace std;

// define an enumeration for pet types
enum PetType { DOG, CAT, BIRD, FISH };

void askPetInfo() {   
    string petName;
    int var;
    cout << "Select your pet type (0 = Dog, 1 = Cat, 2 = Bird, 3 = Fish): ";
    cin >> var;
    PetType pet = static_cast<PetType>(var);  // variable of type PetType

    cout << "What is your pet's name? ";
    cin >> petName;

    cout << "You have a ";

    if (pet == 0)
        cout << "dog";
    else if (pet == 1)
        cout << "cat";
    else if (pet == 2)
        cout << "bird";
    else if (pet == 3)
        cout << "fish";
    else
        cout << "mystery creature";

    cout << " named " << petName << "!" << endl;  }

int main() {
    askPetInfo();
    return 0;
}
