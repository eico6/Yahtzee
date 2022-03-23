#include "myfunctions.h"
#include <iostream>


void print_rolls(Die dice[], int amountOfDice, int currentlySelected, bool toggleScoreboard)
{
    // using extended ASCII characters
    char leftUpCorner = static_cast<char>(218);    // ┌
    char rightUpCorner = static_cast<char>(191);   // ┐
    char horizontalLine = static_cast<char>(196);  // ─
    char verticalLine = static_cast<char>(179);    // |
    char leftDownCorner = static_cast<char>(192);  // └
    char rightDownCorner = static_cast<char>(217); // ┘

    std::cout << leftUpCorner;
    for (int a{0}; a < 15; a++) {
        std::cout << horizontalLine;
    }
    std::cout << rightUpCorner << std::endl;

    for (int i{0}; i < amountOfDice; i++) {
            std::cout << verticalLine << "Die " << i+1 << ": ";
        if (dice[i].getKeepDie() == true){
            std::cout << "[" << dice[i].getValue() << "]";
        } else if (dice[i].getValue() == 0){
            std::cout << "-";
        } else {
            std::cout << dice[i].getValue();
        }

        if (i == currentlySelected && dice[i].getKeepDie() == false && toggleScoreboard == false){
            std::cout << " <--   " << verticalLine;
        } else if (i == currentlySelected && dice[i].getKeepDie() == true && toggleScoreboard == false){
            std::cout << " <-- " << verticalLine;
        } else if (dice[i].getKeepDie() == true){
            std::cout << "     " << verticalLine;
        } else {
            std::cout << "       " << verticalLine;
        }

        std::cout << '\n';
    }

    std::cout << leftDownCorner;
    for (int a{0}; a < 15; a++) {
        std::cout << horizontalLine;
    }
    std::cout << rightDownCorner << '\n';
}

// Difference between the dynamic and the static scoreboard:
// DYNAMIC: prints out temporarily scores except ocupied spaces/scores, and is interactable.
// STATIC: only prints out "real" scores and is uninteractable.
// I could've put all of this into one function, but I figued it would be difficult to read.
// This is also why there is a lot of similar code in these two functions.
void print_dynamic_scoreboard(Player player[], int amountOfPlayers, short int currentlySelected, bool toggleScoreboard, int currentPlayer)
{
    char verticalLine = 179; // 179 = |
    char scores[][16] = {
        "Ones           ",  "Twos           ",  "Threes         ",
        "Fours          ",  "Fives          ",  "Sixes          ",
        "Sum            ",  "Bonus          ",  "Three of a kind",
        "Four of a kind ",  "Full house     ",  "Small straight ",
        "Large straight ",  "Chance         ",  "Yahtzee        ",
        "TOTAL SCORE    "
    };

    std::cout << "___________________";
    for (int i{0}; i < amountOfPlayers; i++) {
        std::cout << "____";
    } std::cout << std::endl;

    std::cout << verticalLine << " PLAYER          " << verticalLine;
    for (int i{0}; i < amountOfPlayers; i++) {
        std::cout << "P" << i + 1 << " " << verticalLine;
    } std::cout << std::endl;

    for (int i{0}; i < 16; i++) {
        std::cout << verticalLine << " " << scores[i] << " " << verticalLine;
        for (int j{0}; j < amountOfPlayers; j++) {

            if (j == currentPlayer){
                if (player[currentPlayer].getOcupiedScore(i) == true){
                    std::cout << "-  " << verticalLine;
                } else {
                    std::cout << player[j].getTempScore(i);

                    if (player[j].getTempScore(i) > 9) {
                        std::cout << " " << verticalLine;
                    } else {
                        std::cout << "  " << verticalLine;
                    }
                }
            } else {
                std::cout << "-  " << verticalLine;
            }
        }

        if (toggleScoreboard == true) {
            if (currentlySelected == i){
                std::cout << " <--";
            }
        }
        std::cout << std::endl;
    }
}

void print_static_scoreboard(Player player[], int amountOfPlayers)
{
    char verticalLine = 179; // 179 = |
    char scores[][16] = {
        "Ones           ",  "Twos           ",  "Threes         ",
        "Fours          ",  "Fives          ",  "Sixes          ",
        "Sum            ",  "Bonus          ",  "Three of a kind",
        "Four of a kind ",  "Full house     ",  "Small straight ",
        "Large straight ",  "Chance         ",  "Yahtzee        ",
        "TOTAL SCORE    "
    };

    std::cout << "___________________";
    for (int i{0}; i < amountOfPlayers; i++) {
        std::cout << "____";
    } std::cout << std::endl;

    std::cout << verticalLine << " PLAYER          " << verticalLine;
    for (int i{0}; i < amountOfPlayers; i++) {
        std::cout << "P" << i + 1 << " " << verticalLine;
    } std::cout << std::endl;


    for (int i{0}; i < 16; i++) {
        std::cout << verticalLine << " " << scores[i] << " " << verticalLine;
        for (int j{0}; j < amountOfPlayers; j++) {
            if (player[j].getOcupiedScore(i) == false){
                std::cout << "-";
            } else {
                std::cout << player[j].getScore(i);
            }

            if (player[j].getScore(i) > 99) {
                std::cout << verticalLine;
            } else if (player[j].getScore(i) > 9){
                std::cout << " " << verticalLine;
            } else {
                std::cout << "  " << verticalLine;
            }
        }

        std::cout << std::endl;
    }
}
