#include<iostream>
#include<string>
#include<iomanip>
#include<locale>

// Payment amounts for option 1.
const float OPT1_MANUSCRIPT_PAYMENT = 5000;
const float OPT1_POSTPUBLISH_PAYMENT = 20000;
const float OPT1_FIXED_PAYMENT = OPT1_MANUSCRIPT_PAYMENT + OPT1_POSTPUBLISH_PAYMENT;

// Payment percentage for option 2.
const float OPT2_ROYALTY_RATE = 0.125;

// Sale threshold and corresponding percentage values for option 3. 
const int OPT3_SALES_THRESHOLD = 4000;
const float UNDER_THRESHOLD_RATE = 0.1;
const float OVER_THRESHOLD_RATE = 0.14;

// Function declaration for each payment calculator

// Option 1: fixed payment of initial $5k for final manuscript then $20k after publication
float calcfixedPayment(float*,std::string*);
// Option 2: variable payment of 12.5% of the net price of each novel per copy
float calcfixedPercentagePayment(float*,int*,float*,std::string*);
// Option 3: payment of 10% net price of novel for the first 4,000 sold then 14% net price for all subsequent novels
float calcvariablePercentagePayment(float*,int*,float*,std::string*);

// Checks if multiple options yield the same value
void checkMultiOption(std::string,float);

// Variables to handle multiple options that produce equal payment, for example 10000 books at $20. 
bool multiOptions = false;
bool anyOption = false;
std::string altOption = "";

int main(){
    /* Variables to hold user defined values and program output. I made 'numbers sold' a variable 
    of type INT since the number of novels sold has to be a discreet value*/
    float novelPrice = 0;
    int numSold = 0;
    float totalPayment = 0;
    std::string bestOption = "failed";
    
    std::cout<<"\nThis is a book publishing royalties calculator\n";
    std::cout<<"\nEnter the expected price of each novel:\n";
    std::cin>>novelPrice;
    std::cout<<"\nEnter the expected number of novels that will be sold:\n";
    std::cin>>numSold;

    // Variables to hold the option payment values. The execution of the functions is order agnostic
    float option1Payment = calcfixedPayment(&totalPayment,&bestOption);
    float option2Payment = calcfixedPercentagePayment(&novelPrice,&numSold,&totalPayment,&bestOption);
    float option3Payment = calcvariablePercentagePayment(&novelPrice,&numSold,&totalPayment,&bestOption);

    std::cout << std::fixed << std::setprecision(2);
    try {
        std::locale loc("");
        std::cout.imbue(loc);
    } catch (const std::exception& e) {
        std::cout << "Warning: Could not set locale for thousands separator formatting." << std::endl;
    }

    std::cout<<'\n';
    std::cout<<"Option 1: $"<<option1Payment<<'\n';
    std::cout<<"Option 2: $"<<option2Payment<<'\n';
    std::cout<<"Option 3: $"<<option3Payment<<'\n';

    // Output based on the best royalties option or options
    if(anyOption){
        /* Note: based on the current percentages in options 2 and 3 there isnt a possibility of all three options producing the same payment
        but I thought it would be good to think through this possibility if the percentanges were changed in the future. 
        */
        std::cout<<"\nBased on those factors any option would yield the same amount of money\n"<<std::endl;
    }
    else if(multiOptions){
        std::cout<<"\nBased on those factors the best options would be "<<bestOption<<" and "<<altOption<<'\n'<<std::endl;
    }
    else{
        std::cout<<"\nBased on those factors the best option would be "<<bestOption<<'\n'<<std::endl;
    }
}

/* Function definitions for each payment calculation function. Each function checks if the current total payment amount
is less than the value calculated for that option and updates the payment value if necessary*/

float calcfixedPayment(float* currentMax, std::string* option){
    if(*currentMax < OPT1_FIXED_PAYMENT){
        *currentMax = OPT1_FIXED_PAYMENT;
        *option = "Option 1";
    }
    else if(*currentMax == OPT1_FIXED_PAYMENT){
        checkMultiOption("Option 1",OPT1_FIXED_PAYMENT);
    }
    return OPT1_FIXED_PAYMENT;
}

float calcfixedPercentagePayment(float* price, int* numSold, float* currentMax, std::string* option){
    float option2Payment = *numSold * *price * OPT2_ROYALTY_RATE;
    if(*currentMax < option2Payment){
        *currentMax = option2Payment;
        *option = "Option 2";
    }
    else if(*currentMax == option2Payment){
        checkMultiOption("Option 2",option2Payment);
    }
    return option2Payment;
}

float calcvariablePercentagePayment(float* price, int* numSold, float* currentMax, std::string* option){
    float option3Payment = 0;
    if(*numSold <= OPT3_SALES_THRESHOLD) option3Payment = *numSold * *price * UNDER_THRESHOLD_RATE;
    else if(*numSold > OPT3_SALES_THRESHOLD) option3Payment = (OPT3_SALES_THRESHOLD * *price * UNDER_THRESHOLD_RATE) + ((*numSold - OPT3_SALES_THRESHOLD) * *price * OVER_THRESHOLD_RATE);

    if(*currentMax < option3Payment){
        *currentMax = option3Payment;
        *option = "Option 3";
    }
    else if(*currentMax == option3Payment){
        checkMultiOption("Option 3",option3Payment);
    }
    return option3Payment;
}

void checkMultiOption(std::string option, float total){
    if(multiOptions) anyOption = true;
    else{
        multiOptions = true;
        altOption = option;
    }
}