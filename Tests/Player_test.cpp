/*
 * Player_test.cpp
 *
 *  Created on: Nov 27, 2017
 *  Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#define TYPE 'l'
#include "Player_test.h"
#define NAME 'X'
#define NUM 7
//function tests getName method in Player class.
TEST(Player_Test, getName_Test) {
    Player* player = new Player(NAME, TYPE, NUM);
    EXPECT_EQ(NAME, player->getName());
    delete player;
}
//function tests getType method in Player class.
TEST(Player_Test, getType_Test) {
    Player* player = new Player(NAME, TYPE, NUM);
    EXPECT_EQ(TYPE, player->getType());
    delete player;
}
//function tests getNum method in Player class.
TEST(Player_Test, getNum_Test) {
    Player* player = new Player(NAME, TYPE, NUM);
    EXPECT_EQ(NUM, player->getNum());
    delete player;
}
//function tests setNum method in Player class.
TEST(Player_Test, setNum_Test1) {
    Player* player = new Player(NAME, TYPE, NUM);
    player->setNum(NUM + 1);
    EXPECT_EQ(NUM + 1, player->getNum());
    delete player;
}