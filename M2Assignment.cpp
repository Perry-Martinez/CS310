#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <locale>

using namespace std;

// Helper function to format numbers with thousands separator and fixed decimals
string format_currency(double amount) {
    // Use a stringstream to format
    stringstream ss;
    ss.imbue(locale(""));  // Use the user's locale to get thousands separator
    ss << fixed << setprecision(2) << amount;
    return "$" + ss.str();
}

int main() {
    double netBalance, payment, d1, d2, interest_rate;

    cout << "Enter net balance: ";
    cin >> netBalance;

    cout << "Enter payment: ";
    cin >> payment;

    cout << "Enter d1 (number of days in period): ";
    cin >> d1;

    cout << "Enter d2 (number of days payment was outstanding): ";
    cin >> d2;

    cout << "Enter interest rate per month (as decimal, e.g., 0.0152): ";
    cin >> interest_rate;

    double averageDailyBalance = (netBalance * d1 - payment * d2) / d1;
    double interest = averageDailyBalance * interest_rate;

    cout << "Interest: " << format_currency(interest) << endl;

    return 0;
}
