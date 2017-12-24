/*
 * ReversiGame.h
 *
 *  Created on: Nov 10, 2017
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
 */
#ifndef REVERSI_REVERSIGAME_H
#define REVERSI_REVERSIGAME_H
#include "Board.h"
#include "Player.h"
#include "GameType.h"
#include "Display.h"
#include "ConsoleDisplay.h"
#include "NetworkClient.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib> //for std::atoi
#define HUMAN 'H'
#define PC 'C'
#define QUIT 'Q'
#define REMOTE 'R'
class ReversiGame: public GameType {
    //class has a board, space left in board, 2 matrixes of x,y of
    // possible moves for both players and 2 players.
private:
    Board* board;
    Player* player1;
    Player* player2;
    int space;
    int** possiblePointsone; //possible moves for player1.
    int** possiblePointstwo; //possible moves for player2.
    Display* display;
public:
    ReversiGame(char p1, char p2, char p1Type, int sizeOfBoard);
    ~ReversiGame();
    void playGame();
    void playGameVsRemote();
    bool HumanplayOneTurn(Player* player);
    bool ComputerplayOneTurn(Player* player);
    bool PlayTurnAgainstRemote(NetworkClient* client, Player* player);
    void scoreGame();
    void checkPossibleMoves(Player* player, Board* board1);
    bool checkUp(Player* player, int i, int j, bool flip, Board* b1);
    bool checkDown(Player* player, int i, int j, bool flip, Board* b1);
    bool checkLeft(Player* player, int i, int j, bool flip, Board* b1);
    bool checkRight(Player* player, int i, int j, bool flip, Board* b1);
    bool checkUpLeft(Player* player, int i, int j, bool flip, Board* b1);
    bool checkUpRight(Player* player, int i, int j, bool flip, Board* b1);
    bool checkDownLeft(Player* player, int i, int j, bool flip, Board* b1);
    bool checkDownRight(Player* player, int i, int j, bool flip, Board* b1);
    int checkBoard(Board* board, Player* player);
    void playPossiblePoints(Player* player, int i, int j, Board* b1);
    //these getters are for the ReversiGame_test.
    Board* getBoard();
    Player* getPlayerOne();
    Player* getPlayerTwo();
    int getBoardSpace();
    int** getPossiblePointsOne();
    int** getPossiblePointsTwo();
};
#endif //REVERSI_REVERSIGAME_H
