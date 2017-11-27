/*
 * Author: avi simson & yakir pinchas
        *      Avi id: 205789100
*      Yakir: 203200530
 *      */
#include <iostream>
#include "Game.h"
#define SYMBOL1 'X'
#define SYMBOL2  'O'
using namespace std;
//program creates reversi game board and prints it as output.
int main() {
    GameType* reversi = new ReversiGame(SYMBOL1, SYMBOL2);
    Game* game = new Game(reversi);
    game->Run();
    delete game;
}