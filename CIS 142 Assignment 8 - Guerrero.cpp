// Author: Francesca Guerrero
// Due Date: 11/8/2024
// Assignment 8: Write a function that scores a word in Hasbro’s Scrabble Classic Crossword game.

#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>  // for isalpha and toupper functions

using namespace std;

// The set up
int calculateScrabbleScore(const string& word) {
    unordered_map<char, int> letterScores = {
        {'A', 1}, {'E', 1}, {'I', 1}, {'L', 1}, {'N', 1}, {'O', 1}, {'R', 1}, {'S', 1}, {'T', 1}, {'U', 1},
        {'D', 2}, {'G', 2},
        {'B', 3}, {'C', 3}, {'M', 3}, {'P', 3},
        {'F', 4}, {'H', 4}, {'V', 4}, {'W', 4}, {'Y', 4},
        {'K', 5},
        {'J', 8}, {'X', 8},
        {'Q', 10}, {'Z', 10}
    };

    int score = 0;
    for (char ch : word) {
        char upperCh = toupper(ch);
        if (letterScores.find(upperCh) != letterScores.end()) {
            score += letterScores[upperCh];
        }
    }
    return score;
}

// The failproof
bool isAlphabetic(const string& word) {
    for (char ch : word) {
        if (!isalpha(ch)) return false;
    }
    return true;
}

// The exit
bool isExitCommand(const string& input) {
    string lowerInput = input;
    for (char& ch : lowerInput) {
        ch = tolower(ch);
    }
    return lowerInput == "exit";
}

// The interface part
int main() {
    string word;

    do {
        cout << "Enter a word to calculate its Scrabble score (or type 'exit' to quit): ";
        cin >> word;

        if (isExitCommand(word)) {
            break;
        }

        if (word.empty()) {
            cout << "Empty input is not allowed. Please enter a valid word.\n";
            continue;
        }

        if (!isAlphabetic(word)) {
            cout << "Invalid input. Please enter alphabetic characters only.\n";
            continue;
        }

        int score = calculateScrabbleScore(word);
        cout << "The Scrabble score for \"" << word << "\" is: " << score << endl;

    } while (true);

    cout << "Sounds good. Goodbye!" << endl;
    return 0;
}