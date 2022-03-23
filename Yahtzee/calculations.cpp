#include "myfunctions.h"


void calculate_amount_of_points(Player player[], Die dice[], int amountOfDice, int currentPlayer)
{
    calculate_One_to_Six(player, dice, amountOfDice, currentPlayer);
    calculate_Kinds_and_Yahtzee(player, dice, amountOfDice, currentPlayer);
    calculate_Full_House(player, dice, amountOfDice, currentPlayer);
    calculate_Small_Large_Straight(player, dice, amountOfDice, currentPlayer);
    player[currentPlayer].setTempScore(CHANCE, calculate_Sum_of_Dices(dice, amountOfDice)); // Chance is just sum of dices
}

void calculate_One_to_Six(Player player[], Die dice[], int amountOfDice, int currentPlayer)
{
    int counter{0};

    // this checks the points from score ONES to SIXES
    for (int i{1}; i <= 6; i++) {
        for (int j{0}; j < amountOfDice; j++) {
            if (dice[j].getValue() == i){
                counter++;
            }
        }
        player[currentPlayer].setTempScore(i - 1, counter * i);
        counter = 0;
    }
}

void calculate_Kinds_and_Yahtzee(Player player[], Die dice[], int amountOfDice, int currentPlayer)
{
    int counter{0};

    bool threeKind = false;
    bool fourKind = false;
    bool yahtzee = false;

    for (int i{1}; i <= 6; i++) {
        for (int j{0}; j < amountOfDice; j++) {
            if (dice[j].getValue() == i){
                counter ++;
            }
        }
        if (counter >= 3){
            player[currentPlayer].setTempScore(THREE_OF_A_KIND, calculate_Sum_of_Dices(dice, amountOfDice));
            threeKind = true;
        }
        if (counter >= 4){
            player[currentPlayer].setTempScore(FOUR_OF_A_KIND, calculate_Sum_of_Dices(dice, amountOfDice));
            fourKind = true;
        }
        if (counter >= 5){
            player[currentPlayer].setTempScore(YAHTZEE, 50);
            yahtzee = true;
        }
        counter = 0;
    }
    if (threeKind == false){
        player[currentPlayer].setTempScore(THREE_OF_A_KIND, 0);
    }
    if (fourKind == false){
        player[currentPlayer].setTempScore(FOUR_OF_A_KIND, 0);
    }
    if (yahtzee == false){
        player[currentPlayer].setTempScore(YAHTZEE, 0);
    }
}

void calculate_Full_House(Player player[], Die dice[], int amountOfDice, int currentPlayer)
{
    // To calculate if there has been a full house, I look at it as two stages:
    // 1. If there are 3 dices with the same value.
    // 2. If 2 other dices have the same value.
    // if both of these are true, then there is a full house.

    bool firstStage = false;
    bool secondStage = false;
    int counter{0}; // counter keeps count of how many dices are equal.
    int temp{};     // temp is a temporarily variable for stage one.
    int oldTemp{};  // oldTemp is for stage 2. I can't use the same temp.
                    // I need to know what value there was three of in stage 1
                    // to avoid checking the same dices in stage 2.

    // First stage:
    for (int i{0}; i < amountOfDice; i++) {
        temp = dice[i].getValue();
        for (int j{0}; j < amountOfDice; j++) {
            if (temp == dice[j].getValue()){
                counter ++; // counter ++ for every equal die
            }
        }
        if (counter >= 3){
            firstStage = true;
            oldTemp = temp;
            counter = 0;
            break;
        }
        counter = 0;
    }

    // Second stage:
    if (firstStage == true)
    {
        for (int i{0}; i < amountOfDice; i++) {
            temp = dice[i].getValue();
            if (temp != oldTemp){ // it should not check for the already equal dices
                for (int j{0}; j < amountOfDice; j++) {
                    if (temp == dice[j].getValue()){
                        counter ++;
                    }
                }
                if (counter >= 2){ // if you started with 3 equal dices, then you need 2 more to be equal
                    secondStage = true;
                    break;
                }
                counter = 0;
            }
        }
    }

    if (firstStage == true && secondStage == true){
        player[currentPlayer].setTempScore(FULL_HOUSE, 25);
    } else {
        player[currentPlayer].setTempScore(FULL_HOUSE, 0);
    }
}

void calculate_Small_Large_Straight(Player player[], Die dice[], int amountOfDice, int currentPlayer)
{
    bool smallStraight = false;
    bool largeStraight = false;
    int temp{};
    int counter{0};
    // counter = 3, is small straight
    // counter = 4, is large straight

    for (int i{0}; i < amountOfDice; i++) {
        temp = dice[i].getValue();
        for (int j{0}; j < amountOfDice; j++) {

            // if the die is one higher value than temp
            if (temp + 1 == dice[j].getValue()){
                counter ++;
                temp = dice[j].getValue(); // temp is now that higher value (which will always be temp += 1)
                j = - 1;
                // This restarts the loop with updated temp value and increased counter value.
                // "j = - 1" and not "j = 0" because when it reaches the end of the loop,
                // j will be added 1. So at the start of the next loop, j will be equal to 0.
            }
        }
        if (counter == 3){
            smallStraight = true;
        }
        if (counter == 4){
            largeStraight = true;
        }
        counter = 0;
    }

    if (smallStraight == true){
        player[currentPlayer].setTempScore(SMALL_STRAIGHT, 30);
    } else {
        player[currentPlayer].setTempScore(SMALL_STRAIGHT, 0);
    }

    if (largeStraight == true){
        player[currentPlayer].setTempScore(LARGE_STRAIGHT, 40);
    } else {
        player[currentPlayer].setTempScore(LARGE_STRAIGHT, 0);
    }
}

void calculate_Sum(Player player[], int currentPlayer)
{
    int theSum{0};

    for (int i{0}; i < SUM; i++) {
        theSum += player[currentPlayer].getScore(i);
    }

    player[currentPlayer].setScore(SUM, theSum);
}

void calculate_TotalScore(Player player[], int currentPlayer)
{
    int theSum{0};

    // Adds all the scores from "Sum" to "Total Score"
    // "Sum" is equal to the sum of the upper section.
    for (int i{SUM}; i < TOTAL_SCORE; i++) {
        theSum += player[currentPlayer].getScore(i);
    }

    player[currentPlayer].setScore(TOTAL_SCORE, theSum);
}

void calculate_Bonus(Player player[], int currentPlayer)
{
    if (player[currentPlayer].getScore(SUM) >= 63){
        player[currentPlayer].setScore(BONUS, 35);
    } else {
        player[currentPlayer].setScore(BONUS, 0);
    }
}

int calculate_Winner(Player player[], int amountOfPlayers)
{
    int winner{0};
    int drawCounter{0};
    int temp{};

    temp = player[0].getScore(TOTAL_SCORE);

    if (amountOfPlayers == 1){
        return SINGLEPLAYER_MODE;
        // SINGLEPLAYER_MODE = -2. if winner is -2, then it was a singleplayer game
    }

    for (int i{0}; i < amountOfPlayers; i++) {
        if (temp < player[i].getScore(TOTAL_SCORE)){
            temp = player[i].getScore(TOTAL_SCORE);
            winner = i;
            i = 0;
        }
    }

    for (int i{0}; i < amountOfPlayers; i++) {
        if (player[winner].getScore(TOTAL_SCORE) == player[i].getScore(TOTAL_SCORE)){
            drawCounter ++;

            // if there are any other players with the same score, there is a draw.
            // The score of winner is already "filtered" to be the highest score.
            // If there are minimum 1 other player with the same score, it's a draw.
            if (drawCounter > 1){
                return DRAW;
                // winner is now player -1, which will cause a draw
            }
        }
    }

    return winner;
}

int calculate_Sum_of_Dices(Die dice[], int amountOfDice)
{
    int sum{0};

    for (int i{0}; i < amountOfDice; i++) {
        sum += dice[i].getValue();
    }

    return sum;
}

