// Author: Francesca Guerrero
// Due Date: 10/5/2024
// CIS 142 Assignment 5: Rock-Paper-Scissors Game, using arrays and modulo arithmetic

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int main() {
    srand(time(0)); // Seed
    string moves[] = { "Rock", "Paper", "Scissors" };
    char playAgain = 'y';  // Use 'y' for a single character

    while (playAgain == 'y') {
        int playerMove, computerMove = rand() % 3;

        cout << "Choose your weapon: Rock(0), Paper(1), Scissors(2): ";
        cin >> playerMove;

        cout << "You chose " << moves[playerMove] << ", I chose " << moves[computerMove] << "... ";

       // Result calculations 
        if (playerMove == computerMove)
            cout << "It's a tie!\n";
        else if ((playerMove + 1) % 3 == computerMove)
            cout << "You lose!\n";
        else
            cout << "You win!\n";

        if (playerMove == 0,1,2)
                        

        // Using "y" or "n" input to play again or close program
        cout << "Play again? (y/n): ";
        cin >> playAgain;
    }

    return 0;
}

