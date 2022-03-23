#include "myfunctions.h"


// definitions for class "Scores"
Scores::Scores()
    : scoreValue{0}, ocupiedSpace{false} {}

void Scores::setScoreValue(int inputScore){
    scoreValue = inputScore;
}
void Scores::setOcupiedSpace(bool inputBool){
    ocupiedSpace = inputBool;
}
int Scores::getScoreValue(){ return scoreValue; }
bool Scores::getOcupiedSpace(){ return ocupiedSpace; }



// definitions for class "Die"
Die::Die()
    : value{0}, keepDie{false} {}

void Die::setKeepDie(bool inputBool){
    keepDie = inputBool;
}
void Die::setValue(int inputInt){
    value = inputInt;
}
void Die::roll_die(){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    value = (rand() % 6) + 1;
}
int Die::getValue(){ return value; }
bool Die::getKeepDie(){ return keepDie; }



// definitions for class "Player"
void Player::setScore(int inputIndex,int inputScore){
    score[inputIndex].setScoreValue(inputScore);
}
void Player::setTempScore(int inputIndex,int inputScore){
    tempScore[inputIndex] = inputScore;
}
void Player::setOcupiedScore(int inputIndex ,bool inputBool){
    score[inputIndex].setOcupiedSpace(inputBool);
}
int Player::getScore(int inputIndex){
    return score[inputIndex].getScoreValue();
}
int Player::getTempScore(int inputIndex){
    return tempScore[inputIndex];
}
bool Player::getOcupiedScore(int inputIndex){
    return score[inputIndex].getOcupiedSpace();
}
