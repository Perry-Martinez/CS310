#include <iostream>
#include <iomanip>
#include <locale>
#include <limits>

using namespace std;

// Function to clear input buffer
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Verifies the range of the user input
double getValidDouble(const string& prompt, double minVal = 0.0, double maxVal = numeric_limits<double>::max()) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= minVal && value <= maxVal) {
                return value;
            } else {
                cout << "Error: Value must be between " << minVal << " and " << maxVal << endl;
            }
        } else {
            cout << "Error: Please enter a valid number." << endl;
            clearInput();
        }
    }
}

// Verifies the range of the user input
int getValidInt(const string& prompt, int minVal = 0, int maxVal = numeric_limits<int>::max()) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= minVal && value <= maxVal) {
                return value;
            } else {
                cout << "Error: Value must be between " << minVal << " and " << maxVal << endl;
            }
        } else {
            cout << "Error: Please enter a valid integer." << endl;
            clearInput();
        }
    }
}

int main() {
    double netBalance, payment, interestRate, averageDailyBalance, interest;
    int d1, d2;
    
    cout << " Credit Card Interest Calc" << endl << endl;
    
    netBalance = getValidDouble("Enter the net balance: $", 0.0);
    
    payment = getValidDouble("Enter the payment amount: $", 0.0, netBalance);
    
    d1 = getValidInt("Enter the number of days in billing cycle: ", 1, 31);
    
    d2 = getValidInt("Enter the number of days payment made before billing cycle: ", 0, d1);
    
    interestRate = getValidDouble("Enter the monthly interest rate (as decimal, e.g., 0.0152): ", 0.0, 1.0);
    
    // Validate that days in billing makes sense
    if (d2 > d1) {
        cout << "Days that payment are made before billing cycle cannot exceed billing cycle days." << endl;
        return 1;
    }
    
    // Calculates average daily balance
    averageDailyBalance = (netBalance * d1 - payment * d2) / d1;
    
    // Checks if average daily balance is negative in the event of large payment
    if (averageDailyBalance < 0) {
        cout << "Warning: Average daily balance is negative. Setting to $0.00 for interest calculation." << endl;
        averageDailyBalance = 0.0;
    }
    
    // Calculates interest
    interest = averageDailyBalance * interestRate;
    
    // Formats output to two decimal places with thousands separator
    cout << fixed << setprecision(2);
    try {
        locale loc("");
        cout.imbue(loc);
    } catch (const exception& e) {
        cout << "Warning: Could not set locale for thousands separator formatting." << endl;
    }
    
    cout << "Interest charged: $" << interest << endl;
    
    return 0;
}