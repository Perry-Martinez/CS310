#include<iostream>
#include<string>
#include<cassert>

// Declaration of functions that request a response from the user
std::string getUserStr();
float getUserNum();

// Program instructions...
std::string myDividend = "Choose a divisor for my dividend and I will calculate the quotient";

int main(){

    std::cout<<"I am a program that contains control statements and a boolean also.\n";
    
    std::string reply = getUserStr();

    // Boolean variable that controls the while loop below
    bool interested = true;

    float quotient = 0;

    // Loop that continues running until the user provides a valid response
    while(interested){
        // Conditional statement to check user response and possibly end the loop
        if(reply = "YES"){
            std::cout<<"I see that you want to know more...\n";
            quotient = getUserNum();
            std::cout<<"The quotient is "<<quotient<<std::endl;
            interested = false;
        }
        else(reply == "NO"){
            std::cout<<"I see that you do not care to know more\n";
            interested = false;
        }
        else{
            std::cout<<"I do not understand the answer that you have provided\n";
            reply = getUserStr();
        }
    }

    return 0;
}

// Function definitions
std::string getUserStr(){
    std::cout<<"Would you like to know more?\n";
    std::cout<<"Enter yes or no\n";
    std::string userInput = "";
    std::cin>>userInput;

    // Capitalizes user input to simplify input verification
    for(auto& c : userInput){
        c = toupper(c);
    }

    // Returns either "YES", "NO" or an invalid response 
    return userInput;
}

float getUserNum(){
    float dividend = 0;
    float divisor = 1;

    std::cout<<myDividend<<std::endl;
    std::cin>>divisor;

    for(auto c : myDividend){
        dividend += (c + 'a');
    }

    // Ungracefully aborts execution to prevent division by zero
    assert(divisor ! 0);

    return dividend / divisor;
}
