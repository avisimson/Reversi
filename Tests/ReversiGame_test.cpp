/*
 * ReversiGame_test.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
 */
#include "ReversiGame_test.h"
#define SYMBOL1 'X'
#define SYMBOL2 'O'
#define HUMAN 'H'
#define PC 'C'
/*
 * function tests the spaces in game board in the beginning of a game, and
 * in the end of the game.
 */
TEST(Reversi_Test, BoardSpace_Test) {
    //initial game, making player1 as PC player to make test faster.
    ReversiGame* game = new ReversiGame(SYMBOL1, SYMBOL2, PC);
    //check if space is right in the beginning of the game.
    EXPECT_EQ(game->getBoardSpace(),
              (game->getBoard()->getSize() * game->getBoard()->getSize()) - 4);
    int initialGameSpace = game->getBoardSpace();
    //play the game, space is being lowered.
    game->playGame();
    if(initialGameSpace > 0) { //board size is bigger than 2x2.
        //check if space was actually lowered throughout the game.
        EXPECT_NE(initialGameSpace, game->getBoardSpace());
    } else {
        EXPECT_EQ(initialGameSpace, game->getBoardSpace());
    }
    delete game;
}
//function tests if Human turn happened.
TEST(Reversi_Test, HumanTurn_Test) {
    ReversiGame* game = new ReversiGame(SYMBOL1, SYMBOL2, HUMAN);
    EXPECT_TRUE(game->HumanplayOneTurn(game->getPlayerOne()));
    delete game;
}