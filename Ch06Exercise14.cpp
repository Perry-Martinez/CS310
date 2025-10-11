#include<iostream>
#include<iomanip>
// constant values that are used throughout the program
const double HOUR = 60;
const double HALF_HOUR = 30;
const double THIRD_HOUR = 20;
const double LOW_INCOME_RATE = 0.4;
const double HIGH_INCOME_RATE = 0.7;
const double INCOME_THRESHOLD = 25000.0;
const int BUFFER_LIMIT = 10000;

// function declaration
double getBillingAmount(double,double,bool);

int main(){
    
    //  variables set by the user
    double hourlyRate = 0.0;
    double consultingTime = 0.0;
    double income = 0.0;
    bool lowIncome = false;

    std::cout<<"Please enter the hourly rate, consulting time (in minutes) and your income\n";
    //  gets user input. Clears the console input and requests input again if necessary
    while(!(std::cin>>hourlyRate>>consultingTime>>income)){
        std::cout<<"Invalid values. Please reenter\n";
        std::cin.clear();
        std::cin.ignore(BUFFER_LIMIT, '\n');
    }
    if(income <= INCOME_THRESHOLD) lowIncome = true;

    // attempts to format output
    std::cout << std::fixed << std::setprecision(2);
    try {
        std::locale loc("");
        std::cout.imbue(loc);
    } catch (const std::exception& e) {
        std::cout << "Warning: Could not set locale for thousands separator formatting.\n" << std::endl;
    }
    std::cout<<"The total billing amount is $"<<getBillingAmount(hourlyRate,consultingTime,lowIncome)<<std::endl;

    return 0;
}

//  function that takes the hourly rate, consulting time and whether the user is classified as low income, then it returns the total billing amount
double getBillingAmount(double rate,double minutes,bool lIncome){
    if(lIncome){
        if(minutes <= HALF_HOUR) return 0.0;
        else{
            return rate * LOW_INCOME_RATE * (minutes - HALF_HOUR) / HOUR;
        }
    }
    else{
        if(minutes <= THIRD_HOUR) return 0.0;
        else{
            return rate * HIGH_INCOME_RATE * (minutes - THIRD_HOUR) / HOUR;
        }
    }
}
