#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include <cstdlib>
#include <ctime>

// each and every score contains both a value and a bool
class Scores{
private:
    int scoreValue;
    bool ocupiedSpace;
public:
    Scores();
    void setScoreValue(int inputScore);
    void setOcupiedSpace(bool inputBool);
    int getScoreValue();
    bool getOcupiedSpace();
};

// singular of dice
class Die
{
private:
    int value;
    bool keepDie;
public:
    Die();
    void setKeepDie(bool inputBool);
    void setValue(int inputInt);
    void roll_die();
    int getValue();
    bool getKeepDie();
};

// The different scores between all the players are kept inside
// an array in the class Player (which are of type Scores).
class Player
{
private:
    Scores score[16]{};
    int tempScore[16]{};
    // The reason behind why I decided to make "score" be of type Scores (and not int),
    // is because I need to store more than just an integer for each element in the array.
    // I also need to know if I have "overwritten" each of these values. So the class Scores
    // contains an int and a bool to keep track of this information.
    // tempScore is the potential score the player can obtain by selecting it.
public:
    void setScore(int inputIndex,int inputScore);
    void setTempScore(int inputIndex,int inputScore);
    void setOcupiedScore(int inputIndex ,bool inputBool);
    int getScore(int inputIndex);
    int getTempScore(int inputIndex);
    bool getOcupiedScore(int inputIndex);
};

// I use an enum to make the code easier to read.
// Instead of writing "player1.getScore(10)" I can write
// the equivalent "player1.getScore(FULL_HOUSE)".
enum Name_of_Score
{
    ONES,   // assigned 0
    TWOS,   // assigned 1
    THREES, // assigned 2
    FOURS,
    FIVES,
    SIXES,
    SUM,
    BONUS,
    THREE_OF_A_KIND,
    FOUR_OF_A_KIND,
    FULL_HOUSE,
    SMALL_STRAIGHT,
    LARGE_STRAIGHT,
    CHANCE,
    YAHTZEE,    // assigned 14
    TOTAL_SCORE // assigned 15
};

enum For_Winner_Calculations{
    SINGLEPLAYER_MODE = - 2,
    DRAW = -1,
};

// Functions located in "calculations.cpp"
void calculate_amount_of_points(Player player[], Die dice[], int amountOfDice, int currentPlayer);
void calculate_One_to_Six(Player player[], Die dice[], int amountOfDice, int currentPlayer);
void calculate_Kinds_and_Yahtzee(Player player[], Die dice[], int amountOfDice, int currentPlayer);
void calculate_Full_House(Player player[], Die dice[], int amountOfDice, int currentPlayer);
void calculate_Small_Large_Straight(Player player[], Die dice[], int amountOfDice, int currentPlayer);
void calculate_Sum(Player player[], int currentPlayer);
void calculate_TotalScore(Player player[], int currentPlayer);
void calculate_Bonus(Player player[], int currentPlayer);
int calculate_Winner(Player player[], int amountOfPlayers);
int calculate_Sum_of_Dices(Die dice[], int amountOfDice);

// Functions located in "printing.cpp"
void print_rolls(Die dice[], int amountOfDice, int currentlySelected, bool toggleScoreboard);
void print_dynamic_scoreboard(Player player[], int amountOfPlayers, short int currentlySelected, bool toggleScoreboard, int currentPlayer);
void print_static_scoreboard(Player player[], int amountOfPlayers);

#endif
