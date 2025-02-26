// Author: Francesca Guerrero
// Due Date: 10/5/2024
// Assignment 7: Currency breakdown/explanation of change through user's input of cents

#include <iostream>

using namespace std;

int main() {
    int cents, dollars, quarters, dimes, nickels, pennies;

    cout << "Enter the total number of cents: ";
    cin >> cents;

    dollars = cents / 100;       // 1 dollar = 100 cents
    cents = cents % 100;         // Remaining cents

    quarters = cents / 25;       // 1 quarter = 25 cents
    cents = cents % 25;          // Remaining cents

    dimes = cents / 10;          // 1 dime = 10 cents
    cents = cents % 10;          // Remaining cents

    nickels = cents / 5;         // 1 nickel = 5 cents
    pennies = cents % 5;         // Remaining cents are pennies

    cout << "That breaks down into:\n";
    cout << dollars << " dollar" << (dollars != 1 ? "s" : "") << endl;
    cout << quarters << " quarter" << (quarters != 1 ? "s" : "") << endl;
    cout << dimes << " dime" << (dimes != 1 ? "s" : "") << endl;
    cout << nickels << " nickel" << (nickels != 1 ? "s" : "") << endl;
    cout << pennies << " penn" << (pennies != 1 ? "ies" : "y") << endl;

    return 0;
}
