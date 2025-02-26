// Author: Francesca Guerrero
// Due Date: 10/21/2024
// Assignment 6: Build a program that allows airplane seat booking through user input
// This program handles various user errors gracefully.

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <iomanip>
#include <algorithm> // For transform function
#include <limits>    // For clearing cin

using namespace std;

// Function to get allowed rows based on ticket type
pair<int, int> getAllowedRows(const string& ticketType) {
    if (ticketType == "FIRST") {
        return { 0, 1 }; // Rows 1 and 2 (0-based index)
    }
    else if (ticketType == "BUSINESS") {
        return { 2, 6 }; // Rows 3 to 7 (0-based index)
    }
    else if (ticketType == "ECONOMY") {
        return { 7, 12 }; // Rows 8 to 13 (0-based index)
    }
    return { -1, -1 }; // Invalid type
}

// Function to book seats in the seating plan
bool bookSeats(vector<vector<char>>& seatingPlan, int rowIndex, int startSeatIndex, int seatCount) {
    // Check if the requested seats are available
    for (int seatIndex = startSeatIndex; seatIndex < startSeatIndex + seatCount; ++seatIndex) {
        if (seatingPlan[rowIndex][seatIndex] == 'X') {
            return false; // One or more seats are already taken, booking fails
        }
    }
    // If available, mark the seats as taken once booked
    for (int seatIndex = startSeatIndex; seatIndex < startSeatIndex + seatCount; ++seatIndex) {
        seatingPlan[rowIndex][seatIndex] = 'X';
    }
    return true; // Booking succeeded
}

// Function to display the current seating plan of the airplane
void displaySeating(const vector<vector<char>>& seatingPlan) {
    cout << "\n       A B C D E F\n"; // Display seat labels (columns)

    for (int rowIndex = 0; rowIndex < seatingPlan.size(); ++rowIndex) {
        cout << "Row " << setw(2) << rowIndex + 1 << " "; // Display the row number (1-based)
        for (char seatStatus : seatingPlan[rowIndex]) {
            cout << seatStatus << " "; // Print each seat (either '*' for available or 'X' for taken)
        }
        cout << endl; // Move to the next line after each row
    }
}

void clearCin() {
    cin.clear();  // Clear error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
}

int main() {
    // Create the seating plan, initialized to available seats '*'
    vector<vector<char>> seatingPlan(13, vector<char>(6, '*'));
    string ticketType; // The type of ticket (First, Business, or Economy)

    while (true) {
        displaySeating(seatingPlan); // Display the current seating plan

        cout << "\nMenu:\n";
        cout << "1. Book a single seat\n";
        cout << "2. Book a family (up to 4 seats)\n";
        cout << "3. Exit\n";
        cout << "Choice (1, 2, or 3): ";

        int choice;
        cin >> choice;
        if (cin.fail()) {
            clearCin();
            cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            continue;
        }

        if (choice == 3) { // Exit option
            break;
        }

        cout << "\nPlease note, our seats' rows are limited to ticket class:\n"
            "First Class = Rows 1 and 2.\n"
            "Business Class = Rows 3 through 7.\n"
            "Economy Class = Rows 8 through 13.\n"
            "Enter ticket type (First, Business, or Economy): ";
        cin >> ticketType;

        // Normalize the input to handle case sensitivity
        transform(ticketType.begin(), ticketType.end(), ticketType.begin(), ::toupper);

        // Get allowed rows based on ticket type
        pair<int, int> allowedRows = getAllowedRows(ticketType);
        if (allowedRows.first == -1) {
            cout << "Invalid ticket type! Please enter 'First', 'Business', or 'Economy'.\n";
            continue;
        }

        if (choice == 1) { // Single seat booking
            cout << "Enter row number (" << allowedRows.first + 1 << "-" << allowedRows.second + 1 << ") and seat letter (A-F): ";
            int row;
            char seatLetter;
            cin >> row >> seatLetter;

            if (cin.fail() || seatLetter < 'A' || seatLetter > 'F') {
                clearCin();
                cout << "Invalid input! Please enter a valid row number and seat letter (A-F).\n";
                continue;
            }

            // Input Validation for Single Seat Booking
            int seatIndex = toupper(seatLetter) - 'A';
            row -= 1; // Convert to 0-based index

            if (row >= allowedRows.first && row <= allowedRows.second && seatIndex >= 0 && seatIndex < 6) {
                if (bookSeats(seatingPlan, row, seatIndex, 1)) {
                    cout << "Seat successfully booked!\n";
                }
                else {
                    cout << "Sorry, that seat is already taken! Please choose a different seat.\n";
                }
            }
            else {
                cout << "Invalid row or seat! Ensure the row is within your ticket's range and seat is A-F.\n";
            }
        }
        else if (choice == 2) { // Family booking
            cout << "Enter row number (" << allowedRows.first + 1 << "-" << allowedRows.second + 1 << ") and family size (1-4): ";
            int row, familySize;
            cin >> row >> familySize;

            if (cin.fail() || familySize < 1 || familySize > 4) {
                clearCin();
                cout << "Invalid input! Enter a valid row number and family size between 1 and 4.\n";
                continue;
            }

            // Input Validation for Family Booking
            row -= 1; // Convert to 0-based index
            if (row >= allowedRows.first && row <= allowedRows.second && familySize >= 1 && familySize <= 4) {
                bool bookingSuccessful = false;
                for (int startSeatIndex = 0; startSeatIndex <= 6 - familySize; ++startSeatIndex) {
                    if (bookSeats(seatingPlan, row, startSeatIndex, familySize)) {
                        bookingSuccessful = true;
                        break;
                    }
                }
                if (bookingSuccessful) {
                    cout << "Family seats successfully booked!\n";
                }
                else {
                    cout << "Sorry, not enough available seats for the whole family! Try a different row or size.\n";
                }
            }
            else {
                cout << "Invalid row or family size! Ensure the row is within your ticket's range and family size is 1-4.\n";
            }
        }
        else {
            cout << "Invalid choice! Please enter 1, 2, or 3.\n";
        }
    }

    cout << "Thank you for flying with Fran! Goodbye!\n";
    return 0;
}
