#include<iostream>
#include<string>

int main(){

    //  Variables to hold user input
    float a,b,t;
    int dish = 0;

    std::cout<<"Enter the amount of time for the initial dish, all subsequent dishes and the total allotted amount of time.\n";
    while (!(std::cin>>a>>b>>t)) {
        std::cout << "Invalid entry. Try one more time\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    //  Compares the amount of time (t) left with the amount of time it takes to make the next dish (a). 
    //  Adjusts remaining time, prep time and dish quantity each cycle
    for(;t>=a;a+=b){
        ++dish;
        t-=a;
    }

    //  "Dish" noun for use in output message.
    std::string dishQty = "";
  
    // Adjusts plurality of "dish" based on quantity prepared.
    dish > 1 || dish == 0 ? dishQty = "dishes" : dishQty = "dish";

    std::cout<<"At that rate, Bianca can prepare "<<dish<<" "<<dishQty<<"."<<std::endl;

    return 0;
}
