#include "myfunctions.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h> // for getch()

void player_turn(Die dice[], Player player[], int amountOfDice, int amountOfPlayers, int currentPlayer);
void roll_dice(Player player[], Die dice[], int amountOfDice, int currentPlayer, int &rollsLeft);
void reset_dice_and_tempScore(Player player[], Die dice[], int amountOfDice, int currentPlayer);

int main()
{
    int amountOfPlayers{0};
    // This value will be changed by the user. Initialized with 0, which is an unvalid value.

    int amountOfDice{5};
    // KEEP IN MIND!
    // The program is designed to accept any amount of dices. I've decided to let this size be unchancable
    // by the user. This is becaues I noticed that any other size than 5 dices, will result in either
    // impossible calculations for lower section, or them being too "easy".
    // Changing the value of "amountOfDice" will update the game dynamically though (for testing purposes)

    while (amountOfPlayers < 1 || amountOfPlayers > 9) {
        std::cout << "\n\n How many players are playing?\n"
                     " (1 - 9) : ";
        std::cin >> amountOfPlayers;
        system("CLS");
    }

    Player *player = new Player[amountOfPlayers];
    Die *dice = new Die[amountOfDice];

    int currentPlayer{0}; // 0 = player 1
    int roundsCounter{0}; // when roundsCounter reaches 13, a winner is calculated
    int winner{0};
    // The player who won is equal to winner.

    // The scores: SUM, BONUS and TOTAL_SCORE can't be directly manipulated by the player.
    // Therefore, acts the same way as an ocupied score (a score that is already set).
    for (int i{0}; i < amountOfPlayers; i++) {
        player[i].setOcupiedScore(SUM, true);
        player[i].setOcupiedScore(BONUS, true);
        player[i].setOcupiedScore(TOTAL_SCORE, true);
    }

    std::cout << "CONTROLS\n-------------------------\n"
                 "(w)/(s)  =  navigation\n"
                 "(SPACE)  =  switch board\n"
                 "(ENTER)  =  keep / select\n"
                 "(r)      =  roll\n";
    std::cout << std::endl;
    print_static_scoreboard(player, amountOfPlayers);
    std::cout << std::endl;
    system("PAUSE");

    do{
        // this is one turn for one player
        player_turn(dice, player, amountOfDice, amountOfPlayers, currentPlayer);

        // if one turn has passed for everyone
        if (currentPlayer >= amountOfPlayers - 1){
            roundsCounter ++;
            currentPlayer = 0;
            std::cout << "\n\n\n\n\n\n         OVERVIEW\n";
            print_static_scoreboard(player, amountOfPlayers);
            std::cout << '\n';

            // there are 13 directly manipulative scores, which means
            // that when the roundsCounter = 13, game is over.
            if (roundsCounter >= 13){
                winner = calculate_Winner(player, amountOfPlayers);
                if (winner == DRAW){ // DRAW = -1
                    std::cout << "It's a DRAW!!\n";
                    break; // break will exit the infinite do while loop

                } else if (winner == SINGLEPLAYER_MODE){ // SINGLEPLAYER_MODE = -2
                    std::cout << "Singleplayer mode doesn't have a winner!\n";
                    break;

                } else {
                    std::cout << "Player " << winner + 1 << " WINS!!\n";
                    break;
                }
            }
            system("PAUSE");

        } else {
            currentPlayer ++;
        }


    // will loop forever until a winner is calculated (will exit by break)
    } while (true);

    std::cout << std::endl;
    return 0;
}

void player_turn(Die dice[], Player player[], int amountOfDice, int amountOfPlayers, int currentPlayer)
{
    int rollsLeft{3};
    bool toggleScoreboard = false; // swtich between selecting dices and scores
    bool roundIsOver = false;
    bool skipIfStatement = false;
    char playerInput{};
    short int currentlySelected{0}; // 0 is equal to die number 1 if toggleScoreboard == false.
                                    // 0 is equal to score  ONES  if toggleScoreboard == true.

    reset_dice_and_tempScore(player, dice, amountOfDice, currentPlayer);
    system("CLS");

    do{
        skipIfStatement = false;
        print_rolls(dice, amountOfDice, currentlySelected, toggleScoreboard);
        print_dynamic_scoreboard(player, amountOfPlayers, currentlySelected, toggleScoreboard, currentPlayer);
        std::cout << "\nPLAYER " << currentPlayer + 1 << '\n';
        if (rollsLeft == 3){
            std::cout << "(r) = roll\n";
        } else {
            std::cout << "(w)/(s)  =  navigation\n"
                         "(SPACE)  =  switch board\n"
                         "(ENTER)  =  keep / select\n"
                         "(r)      =  roll\n";
        }
        playerInput = getch();
        system("CLS");

        // navigation for "dice rolls" is enabled
        if (toggleScoreboard == false)
        {
            switch (playerInput) {
            case 'w': case 'W':
                // if you go above the top, you will loop to the bottom
                if (currentlySelected == 0){
                    currentlySelected += amountOfDice -1;
                } else {
                    currentlySelected --;
                }
                break;
            case 's': case 'S':
                // if you go below the bottom, you will loop to the top
                if (currentlySelected == amountOfDice - 1){
                    currentlySelected -= amountOfDice - 1;
                } else {
                    currentlySelected ++;
                }
                break;
            case 13: // 13 is the ASCII code for 'return'
                // This makes it impossible to "keep" a die that is equal to 0.
                // A die is only equal to 0 if the player has not rolled.
                // This keeps the player from "holding" an unrolled die.
                if (dice[currentlySelected].getValue() != 0){
                    if (dice[currentlySelected].getKeepDie() == false){ // this makes it possible to unselect
                        dice[currentlySelected].setKeepDie(true);
                    } else {
                        dice[currentlySelected].setKeepDie(false);
                    }
                }
                break;
            case 'r': case 'R':
                    roll_dice(player, dice, amountOfDice, currentPlayer, rollsLeft);
                if (rollsLeft <= 0) {
                    toggleScoreboard = true;

                    currentlySelected = 0;
                    // if the first score is already ocupied when forced to move over to scoreboard,
                    // the player will select the most top un-ocupied score.
                    while (player[currentPlayer].getOcupiedScore(currentlySelected) == true){
                        currentlySelected ++;
                    }

                    for (int i{0}; i < amountOfDice; i++) {
                        dice[i].setKeepDie(true);
                    }
                }
                break;
            case 32: // 32 = spacebar
                toggleScoreboard = true;

                // skipIfStatement will be true until next loop (is equal to false at the start of each loop).
                // toggleScoreboard will still be true though, so the conditions for the if statement below will be true.
                // "if statement below" = if statement for navigation for scorebaord
                skipIfStatement = true;
                currentlySelected = 0;

                // if the first score is already ocupied (currentlySelected = 0) when changing
                // over to the board, the player will select the most top un-ocupied score.
                while (player[currentPlayer].getOcupiedScore(currentlySelected) == true){
                    currentlySelected ++;
                }
                break;
            default:
                break;
            }
        }

        // navigation for scoreboard is enabled
        if (toggleScoreboard == true && skipIfStatement == false)
        {
            switch (playerInput) {
            case 'w': case 'W':
                // if you go above the top, you will loop to the bottom
                if (currentlySelected <= 0){
                    currentlySelected = 14;
                } else {
                    currentlySelected --;
                }

                // this makes sure that you can't select already selected scores
                while (player[currentPlayer].getOcupiedScore(currentlySelected) == true){
                    currentlySelected --;
                    if (currentlySelected < 0){
                        currentlySelected = 14;
                    }
                }
                break;
            case 's': case 'S':
                // if you go below the bottom, you will loop to the top
                if (currentlySelected == 14){
                    currentlySelected = 0;
                } else {
                    currentlySelected ++;
                }

                // this makes sure that you can't select already selected scores
                while (player[currentPlayer].getOcupiedScore(currentlySelected) == true){
                    currentlySelected ++;
                    if (currentlySelected > 14){
                        currentlySelected = 0;
                    }
                }
                break;
            case 13: // 13 is the ASCII code for 'return'
                player[currentPlayer].setScore(currentlySelected, player[currentPlayer].getTempScore(currentlySelected));
                player[currentPlayer].setOcupiedScore(currentlySelected, true);
                roundIsOver = true;
                break;
            case 'r': case 'R':
                roll_dice(player, dice, amountOfDice, currentPlayer, rollsLeft);
                if (rollsLeft <= 0){
                    for (int i{0}; i < amountOfDice; i++) {
                        dice[i].setKeepDie(true);
                    }
                }
                break;
            case 32: // 32 = spacebar
                if (rollsLeft > 0){
                    toggleScoreboard = false;
                    currentlySelected = 0;
                }
                break;
            default:
                break;
            }

        }

    } while (roundIsOver == false);

    calculate_Sum(player, currentPlayer);
    calculate_Bonus(player, currentPlayer);
    calculate_TotalScore(player, currentPlayer);
}

void roll_dice(Player player[], Die dice[], int amountOfDice, int currentPlayer, int &rollsLeft)
{
    for (int i{0}; i < amountOfDice; i++) {
        // if you have decided to hold the die
        if (dice[i].getKeepDie() == false){
            dice[i].roll_die();
        }
    }

    rollsLeft --;

    // for each new roll, the tempValues should be updated so
    // that the player can see the potential points.
    calculate_amount_of_points(player, dice, amountOfDice, currentPlayer);
}

void reset_dice_and_tempScore(Player player[], Die dice[], int amountOfDice, int currentPlayer)
{
    // Makes sure that all dices are "unselected"  for each new round.
    for (int i{0}; i < amountOfDice; i++) {
        dice[i].setKeepDie(false);
    }

    // Makes sure that all the values for the dices are "reset" for each new round.
    for (int i{0}; i < amountOfDice; i++) {
        dice[i].setValue(0);
    }

    // Makes all the tempScores for currentPlayer equal back to 0 between each round.
    for (int j{0}; j < 16; j++) {
        player[currentPlayer].setTempScore(j, 0);
    }
}

