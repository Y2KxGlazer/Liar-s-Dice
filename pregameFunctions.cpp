
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "pregame.h"

using namespace std;

int totalPlayers;

bool gamePlayable;
int nerdge;



int userNum;
int tries;





// TODO: Game loop function that first prints rules, then starts game based on gamePlayable.
// TODO: Create a menu system for the game.
// TODO: Create a dice rolling mechanism so the first player with the highest number goes first.

void startingPlayerCount() { // Function that asks for starting player count
    cout << "Enter the starting player count for Liar's Dice." << endl;
    cin >> totalPlayers;
    if (totalPlayers < 2) {
        notEnoughPlayers();
    }
    else {
        gamePlayable = true;
        askForRules();
    }

}

void notEnoughPlayers() { // Function that asks for more players if players is less than 2 and sets game state to playable.
    do {
        cout << "There are not enough players,\nPlease input 2 or more players!" << endl;
        cin >> totalPlayers;
    } while (totalPlayers < 2);
    if (totalPlayers > 1) {
        gamePlayable = true;
        gamePlayable ? askForRules() :void();


    }

}

bool isPlayable() { //  Function that determines if the game is playable or not.'
    return gamePlayable;

}

// TODO: 
void printGameRules() { // Function that prints game rules from a text file.
    string rulesText;

    ifstream gamesRules("Rules.txt");
    while (getline(gamesRules, rulesText))
        cout << rulesText << endl;
}

void askForRules() { // Asks the user if they'd want to read the game rules
    char userChoice;
    cout << "Would you like to read the rules?: Y/N" << endl;
    cin >> userChoice;

    switch (userChoice)
    {
    case 'Y':
        printGameRules();
        break;
    case 'N':
        break;
    default:
        askForRules();
    }

}

// Move to dice sim eventually



int diceSum(int x, int y) { // Returns the sum of two numbers
    return x + y;
}






