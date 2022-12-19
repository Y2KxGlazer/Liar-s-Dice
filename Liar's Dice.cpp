/* This is a project that allows users to play Liar's Dice, 
The current iteration of the game isn't finished as it would go on forever
Because the dice aren't removed after challenges. Another problem is that in the actual game of liar's dice,
The dice value of 1 wouldn't be equal to 1 but instead it would be equal to the faceValue of the current 
wages, this can be accounted for by just summing the number of 1's and adding it to the the sum of current faceValues.
Another problem is that the dice won't be rerolled after a challenge has started. I know the faults with this 
program but I want to turn something that'll work in,
as opposed to adding these new but vital features of liars dice which would cause 
other problems wot arise. I've had a great deal of fun and my understanding of pointers has grown immensely 
because I'm lucky enough that I've gotten this far,

This has been a very hard endeavor, I also couldn't refactor the code so it's a bit messy but ya'know
*/
#include <iostream>
#include <iomanip>
#include <numeric>
#include <random>
#include <cstdlib>
#include "pregame.h"



void initPlayers();
void getWagers();
int totalDiceInPlay;

extern int totalPlayers;
using namespace std;
void startGame();
random_device rd;
mt19937 rng(rd());
int player1Index;





//      Variables TODO: Move to a header file fo rless clutter.

// Dice rolling logic, compare sum total. Loop through player array comparing the values.
class Player {
private:
    int playerWageDiceAmount, playerWageFaceValue;

    
    int totalPlayersStillIn = totalPlayers;
    string playerName;
    
    
public:
    std::vector<int> arr;
    int m_rolledDiceTotal; // Stores the sum of all the rolled dice.
    
    
    int m_diceCount; // quantity of dice person has.
    Player* next; // Next person in order
    Player* previous; // Previous person in order.
    bool head;
    bool tail;
    
    
 
    void reduceDiceAmount() { // Reduces the amount of die that player has.
        this->m_diceCount--;
        totalDiceInPlay--;
        if (this->m_diceCount == 0) {// Also removes a player from the LL if 
            totalPlayersStillIn--;
            removePlayer();
            // we need a function that will take the this object pointers
            // and initiate the deletion of that node from the circular linked list.

        }
    }

    void rollDice() { //Generates random ints in a range and returns the sum of the dice.
        arr.clear();
        // Roll the dice and store their values in the vector.
        for (int n = 0; n < m_diceCount; ++n) {
            uniform_int_distribution<int> uni(1, 6);
            int ranDice = uni(rng);
            arr.push_back(ranDice);
        }
        m_rolledDiceTotal = std::accumulate(arr.begin(), arr.end(), 0);
    }

    void removePlayer() { // Removes a player from the linked list and fixes the pointers
        this->next->previous = this->previous;
        this->previous->next = this->next;
        this->next = nullptr;
        this->previous = nullptr;
        // This will just remove the pointers and fix the linked list.
        // It will NOT clear the memory that it used. That shouldn't be a problem
        // for a project of this size.
        
    }
    void setPlayerName(string name) {
        this->playerName = name;
    }
    string getPlayerName() {
        return this->playerName;
    }
    Player* getNextPlayer() {
        return this->next;
    }
    void setWagerDiceAmount(int x) {
        this->playerWageDiceAmount = x;
    }
    void setWagerFaceValue(int x) {
        this->playerWageFaceValue = x;
    }
    int getWagerDiceAmount() {
        return this->playerWageDiceAmount;
    }
    int getWagerFaceValue() {
        return this->playerWageFaceValue;
    }
    std::vector<int> getPlayerDice() {
        return this->arr;
    }

    Player() {
        this->m_diceCount = 5;
        this->m_rolledDiceTotal = 0;
        this->next = NULL;
        this->previous = NULL;
        this->arr;
        head = false;
        tail = false;
        
    }

};

vector<Player> individual;
int determineFirstPlayer(vector<Player> &vect);
void onChallengeYes(vector<Player>& individual);



int main( )
{
    individual.resize(totalPlayers);
    extern int totalPlayers;
    
    startingPlayerCount(); // Works perfectly
    initPlayers();// Works perfectly
    



    startGame();
    getWagers();


    
        
    system("pause>0");
    return 0;
}


void initPlayers() { // Connects nodes to form doubly circular linked list, ask for names, and rolls the dice 
    for (int i = 0; i < totalPlayers; i++) { // Creates the nodes
        individual.push_back(Player());
        //individual[i].removePlayer(); will be used when a player needs to be removed.
    }
    for (int i = 0; i < totalPlayers; ++i) { // Links the nodes forwards
        individual[i].next = &individual[(i + 1) % totalPlayers];
        if (i == 0) {
            individual[i].head = true;
        }
        else if (i == totalPlayers - 1) {
            individual[i].tail = true;
        }
    }
    for (int i = 0; i < totalPlayers; ++i) { // Links the nodes backwards
        individual[i].previous = &individual[(i + totalPlayers - 1) % totalPlayers];
    }
    for (int i = 0; i < totalPlayers; ++i) { // Requests name
        cout << "Player " << (i + 1) << ", enter your name: ";
        string name;
        cin >> name;
        individual[i].setPlayerName(name);
    }
    for (int i = 0; i < totalPlayers; ++i) {// Rolls die
        individual[i].rollDice();
    }
    totalDiceInPlay = totalPlayers * 5;
    
}


    // what to do after starting game?
    // for loop, ask players for name, maybe.

    // Order the linked list by dice rolled, akin to swapping variables.
        // roll dice first, input struct into function by reference,
        // that function should compare m_totaldicecount and just swap the variables 
        // 
        // This is a bit complex as I've done a little bit of research on 
        // I found it easier since we're using  circular linked list to instead 
        // start the game at the index of the player who had the highest roll.
        // 
        // 
    // Loop through linked list until challenge happens.... 
        // WOW big problem... So in liar's dice, you need to know who is challenging, 
        // and the person who's being challenged.With the way my program works, if player 3 challenges
        // player 4, I dont think there's a way for the program to know that it was player 3 so we can 
        // remove one of their die if they happen to lose the challenge.
        // One untested solution is to have a pinter member var == (total players - 1)+ &next) which should put us 
        // right to the player that preceeds the player that chose to challenge. This would create a doubly
        // circular linked list. As you may have noticed, 
        // my code always seems to work in theory but never in practice, so let's hope it's not hard to implement.
    // Ignore second half of this because some code was rewritten.




void startGame() { // This just determins who the first player should be at the start of the game.
    cout << "The game of liar dice has started and the first dices have been rolled!\n";
    player1Index = determineFirstPlayer(individual);
    string firstPlayer = individual[player1Index].getPlayerName();

    cout << "The player that will play first is " << firstPlayer << endl;

}

int determineFirstPlayer(vector<Player> &vect) { // The person with the highest values goes first
    int index = 0;
    int maxSum = vect[0].m_rolledDiceTotal;
    for (int i = 1; i < vect.size(); i++) {
        if (individual[i].m_rolledDiceTotal > maxSum) {
            maxSum = individual[i].m_rolledDiceTotal;
            index = i;
        }
    }
    return index;
}

void getWagers() { // This is the main function for the game
    Player* currentPlayer = &individual[player1Index];


    while (currentPlayer != nullptr) { // Asks each player for the dice amount and face value
        cout << "Player " << currentPlayer->getPlayerName() << ", enter your wager separated by space(dice amount and face value): ";
        int diceAmount, faceValue;
        cin >> diceAmount >> faceValue;

        // Loop that checks for valid input, It won't check if the previous players diceAmount is greater though.
        while (diceAmount > totalDiceInPlay || (currentPlayer->previous != nullptr && faceValue < currentPlayer->previous->getWagerFaceValue()) || faceValue > 6) {
            cout << "Invalid wager: ";
            if (diceAmount > totalDiceInPlay) { // Checks if the dice amount is more than in play.
                cout << "dice amount must not be higher than the total number of dice in play (" 
                    << totalDiceInPlay << ")\n" << "Enter a valid dice count.";
                cin >> diceAmount;
            }
            if (currentPlayer->previous != nullptr && faceValue < currentPlayer->previous->getWagerFaceValue()) { // Checks if face value of the previous player's wage is greater than the current wager.
                cout << "face value must be equal to or higher than the previous player's wager of (" 
                    << currentPlayer->previous->getWagerFaceValue() << ")";
                cin >> faceValue;
            }
            if (faceValue > 6) { // Checks if the face value is greater than 6
                cout << "face value must be less than or equal to 6";
                cin >> faceValue;
            }

        }
        currentPlayer->setWagerDiceAmount(diceAmount);
        currentPlayer->setWagerFaceValue(faceValue);
        currentPlayer = currentPlayer->getNextPlayer();

        // Challenges
        cout << currentPlayer->getPlayerName() << " Would you like to challenge the previous wager made by "
            << currentPlayer->previous->getPlayerName() << "?(Y/N)" << endl;
        char challengeChoice;
        cin >> challengeChoice;
        switch (challengeChoice) {
        case 'Y':
            onChallengeYes(individual);
            break;

        case 'N':
            break;
        }


    }
}



void onChallengeYes(vector<Player>& individual) {
    // Loop through the vector of player objects
    for (int i = 0; i < individual.size(); i++) {
        // Print the player's name
        cout << individual[i].getPlayerName() << ": ";
        // Loop through the vector of dice values for this player
        for (int j = 0; j < individual[i].getPlayerDice().size(); j++) {
            // Print the value of each dice
            cout << individual[i].getPlayerDice()[j] << " ";
        }
        cout << endl;
    }



}

void challenderLoser() {

}



// SOLVED: Problem 1. isPlayable() ternary won't return true or false???
// 
// Solved: Ask the user if they wish to read the rules

// Problem 2: Massive problem that I can't seem to fix. Been working on it for about a week now
// Basically calling the method to roll the dice always causes a crash. No clue how to fix this.
// Solved: Still don't know what the problem was, just rewrote the code and it worked.

// The coding has been going mostly smooth so far after that bug was fixed.
// I doubt I'll have enough time to make everything the way it should be but I hope I can.

// Again most things were create getters and setters.

// Problem 3: The double while loop in the game's main functino was a bit of a pain, because of how
// Liar's dice is meant to be played, I used mostly drawings in MSPaint to represent what 
// needed to happen as it was mostly just understand the values that are meant to be compared.






