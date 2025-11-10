#include<iostream>
#include<string>
#include<limits>

// BankAccount declaration and implementation
class BankAccount{
    std::string ownerName;
    int number;
    double balance;
    double interestRate;
    public:
    static int accountID;
    static bool isInitialized;
    BankAccount(std::string name, double rate):ownerName(name),interestRate(rate){
        balance = 0;
        number = ++accountID;
    }
    static void initializeAccountTracker(){
        if(!isInitialized){
            isInitialized = true;
        }
        else std::cout<<"Already Initialized"<<std::endl;
    }
    double getBalance(){
        return balance;
    }
    void setBalance(double amt){
        balance += amt;
    }
    void depositFunds(double amt){
        balance += amt;
        std::cout<<'$'<<balance<<" deposited in accout: "<<number<<'\n'<<std::endl;
    }
    virtual void withdraw(double w){
        balance -= w;
    }

    void setInterestRate(double iRate){
        interestRate = iRate;
    }

    double getInterestRate(){
        return interestRate;
    }
    std::string getOwnerName(){
        return ownerName;
    }
    int getAccNumber(){
        return number;
    }
};

// Static member initialization. Keeps count of how many accounts exist and increments account number assignment
bool BankAccount::isInitialized = false;
int BankAccount::accountID = 100000;

// Helper template func to create new bank accounts
template <typename C>
C* openAccount();

class CheckingAccount : public BankAccount{
    double minBalance;
    double serviceCharges;

    public:
    CheckingAccount(std::string name, double rate, double min) : minBalance(min), BankAccount(name, rate){};
    void setMinBalance(double minB){
        minBalance = minB;
    }
    double getMinBalance(){
        return minBalance;
    }
    void setServiceCharges(double serviceC){
        serviceCharges = serviceC;
    }
    double getServiceCharges(){
        return serviceCharges;
    }
    double postInterest(){
        return getBalance() * getInterestRate();
    }
    bool isAboveMinBalance(){
        return getBalance() > minBalance;
    }
    void writeCheck(double amt){
        setBalance(-amt);
    }
    void withdraw(double amt) override{
        if(amt > getBalance()){
            std::cout<<"Notice: you are attempting to withdraw an amount greater than your current balance\n";
            setBalance(-amt);
        }
        else{
            std::cout<<"You are withdrawing $"<<amt<<" from your account\n";
        }
    }
    void displayAccountInfo(){
        std::cout<<"\n---------Account information---------\n\n";
        std::cout<<"Account Number: "<<getAccNumber()<<'\n';
        std::cout<<"Owner: "<<getOwnerName()<<'\n';
        std::cout<<"Balance: $"<<getBalance()<<'\n';
        std::cout<<"Interest Rate: "<<getInterestRate()<<'\n';
        std::cout<<"Minimum Balance: "<<getMinBalance()<<"\n\n";
    }
};

class SavingsAccount : public BankAccount{
    public:
    SavingsAccount(std::string name, double rate) : BankAccount(name, rate){};
    double postInterest(){
        return getBalance() * getInterestRate();
    }
    void writeCheck(double amt){
        setBalance(-amt);
    }
    void withdraw(double amt) override{
        if(amt > getBalance()){
            std::cout<<"Notice: you are attempting to withdraw an amount greater than your current balance\n";
            setBalance(-amt);
        }
        else{
            std::cout<<"You are withdrawing $"<<amt<<" from your account\n";
        }
    }
    void displayAccountInfo(){
        std::cout<<"\n---------Account information---------\n\n";
        std::cout<<"Account Number: "<<getAccNumber()<<'\n';
        std::cout<<"Owner: "<<getOwnerName()<<'\n';
        std::cout<<"Balance: $"<<getBalance()<<'\n';
        std::cout<<"Interest Rate: "<<getInterestRate()<<'\n';
    }
};

// Program entry point
int main(){

    CheckingAccount* myCheckingAcc = openAccount<CheckingAccount>();
    SavingsAccount* mySavingAcc = openAccount<SavingsAccount>();

    myCheckingAcc->displayAccountInfo();
    mySavingAcc->displayAccountInfo();

    myCheckingAcc->depositFunds(500.50);
    mySavingAcc->depositFunds(100.25);

    myCheckingAcc->withdraw(600.0);
    mySavingAcc->withdraw(1000.0);

    myCheckingAcc->displayAccountInfo();
    mySavingAcc->displayAccountInfo();

    return 0;
}

// Using a template function to control the type of object pointer that is returned for created account objects

template <typename C>
C* openAccount(){
    std::string firstName;
    std::string lastName;
    double intRate = 0.0;
    double minBalance = 0.0;
    std::cout<<"Enter account holder's first name:\n"<<std::endl;
    std::cin>>firstName;
    std::cout<<"Enter account holder's last name:\n"<<std::endl;
    std::cin>>lastName;
    std::string fullName = firstName+' '+lastName;

    while(true){
        std::cout<<"Enter the interest rate for the account:\n"<<std::endl;
        std::cin>>intRate;

        if(std::cin.fail()){
            std::cout<<"Invalid input. Try again."<<std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        else{
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            if constexpr(std::is_same_v<C,CheckingAccount>){ 
                std::cout<<"Enter minimum balance for account\n";
                std::cin>>minBalance;
                std::cout<<"New account created for "<<fullName<<'\n'<<std::endl;
                return new C(fullName, intRate, minBalance);
            }
            else if constexpr(std::is_same_v<C, SavingsAccount>){ 
                std::cout<<"New account created for "<<fullName<<'\n'<<std::endl;
                return new C(fullName, intRate);
            }

        }
    }
}
