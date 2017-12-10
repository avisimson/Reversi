/*
 * Player.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
 */
#include <iostream>
#include "Player.h"
using namespace std;
//constructor-gets name and type and initializing player with them.
Player :: Player(char name1, char type1, int num1) {
    name = name1;
    type = type1;
    num = num1;
}
// destructor-remove player from heap.
Player :: ~Player() {};
//function returns players name(usually X or O.
char Player :: getName() {
    return name;
}
//function returns player type-'C' or 'H',
char Player :: getType() {
    return type;
}
//function changes number of player to parameter num1.
void Player :: setNum(int num1) {
    num = num1;
}
//function get players num (if player is player1 or player2.
int Player :: getNum() {
    return num;
}
//set players name from x to o or from o to x.
void Player :: setName(char name1) {
    name = name1;
}