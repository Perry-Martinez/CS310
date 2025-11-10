//M9 -> Changed to a comment
#include <iostream>
using namespace std;

class Animal {
public:
    void speak() {
        cout << "Animal sound" << endl;
    }
};

class Dog : public Animal {
public:
    void speak() {
        cout << "Woof!" << endl;
    }
};

class Cat : public Animal {
public:
    void speak() {
        cout << "Meow!" << endl;
    }
};

int main() {
    Dog dog;
    Cat cat;

    dog.speak();
    cat.speak();

    // doog.speak(); -> type in object identifier. 
    dog.speak();
    //cat.speak; -> missing parenthesis for proper function call
    cat.speak();

    return 0;
}
