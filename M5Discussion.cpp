#include<iostream>
#include<string>
// Create a simple C++ program using user-defined functions and at least two errors. 
// The program should not execute and there should be at least two errors in the code.

void getMessage(int);

int main(){

    getMessage("three");

    return 0;
}

void getMessages(int c){

    for(int i = 0; i < c;i++){
        std::cout<<"hello world\n";
    }
}
