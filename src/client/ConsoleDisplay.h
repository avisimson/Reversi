/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#ifndef REVERSI_CONSOLEDISPLAY_H
#define REVERSI_CONSOLEDISPLAY_H


#include "Board.h"
#include "Display.h"
#include <string.h>
#include <stdio.h>
#include <string>
using namespace std;
/**
 * This class is used to print on the console.
 */
class ConsoleDisplay : public Display {
public:
    ConsoleDisplay() {};
    ~ConsoleDisplay() {};
    void playerTypeWrong(int num);
    void initialMenu();
    void printRemoteMenu();
    void notInitializedTypes(char c);
    void noPossibleMoves(char c);
    void printItsYourMove(char c);
    void printRowCol(int row, int col);
    void printPsik();
    void printLineDrop();
    void printEnterMove();
    void printWrongInput();
    void printPlayerPlayedRowCol(char c, int row, int col);
    void printBoard(Board* board);
    void printNoOption();
    void printComCantPlay(char c);
    void printScore(char name1, char name2, int score1, int score2);
    void printFailToConnect(const char *msg);
    void printYouArePlayer(int num);
    void printWaiting();
    void printRemoteCantPlay();
    void PrintWaitForRemoteToJoin();
    void EnterNameOfGame();
    void printNotExist();
    void printAlreadyExist();
    void printString(string str);
};

#endif //EX3WITHTESTS_CONSOLEDISPLAY_H
