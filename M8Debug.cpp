#include <iostream>
using namespace std;

class Person {
public:
    string name;
    int age;

    void display() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    void setName(string n){
        name = n;
    }
};

class Student : public Person {
public:
    string school;
    string grade;
    void displayInfo() {
        display(); // Calls Person's display
        cout << "School: " << school << endl;
    }
};

int main() {
    Student s;
    s.name = "Alice";
    s.age = 20;
    s.school = "Greenwood High";

    s.displayInfo();

    Person p;
    p.setName("Bob"); // ❌ Fix 1: setName is now a defined member function in Person

    Student s2;
    s2.grade = "A"; // ❌ Fix 2: 'grade' is now a declared member attribute in Student

    return 0;
}