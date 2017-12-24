#ifndef REVERSI_DISPLAY_H
#define REVERSI_DISPLAY_H

#include "Board.h"
/**
 * This is an abstract class for the display.
 */
class Display {
public:
    virtual void playerTypeWrong(int num) = 0; //print player type wrong.
    virtual void initialMenu() = 0; //print game type options.
    virtual void printClientMenu() = 0; //print command options to server.
    virtual void notInitializedTypes(char c) = 0; //print wrong types for players.
    virtual void noPossibleMoves(char c) = 0; //print no possible moves.
    virtual void printItsYourMove(char c) = 0; // print its your moves.
    virtual void printRowCol(char row, char col) = 0; //print row col.
    virtual void printPsik() = 0; //print psik.
    virtual void printLineDrop() = 0; //get one line down.
    virtual void printEnterMove() = 0; //print enter move.
    virtual void printWrongInput() = 0; //print wrong input.
    virtual void printPlayerPlayedRowCol(char c, int row, int col) = 0; //print player played row,col.
    virtual void printBoard(Board* board) = 0; //print Board.
    virtual void printNoOption() = 0; //print no option.
    virtual void printComCantPlay(char c) = 0; //print computer cant play.
    virtual void printScore(char name1, char name2, int score1, int score2) = 0; //score print.
    virtual void printFailToConnect(const char msg) = 0; //print fail to connect and why.
    virtual void printYouArePlayer(int num) = 0; //print you are player 1/2.
    virtual void printWaiting() = 0; //print waiting for other player.
    virtual void printRemoteCantPlay() = 0; //print remote player didnt have moves.
    virtual void PrintWaitForRemoteToJoin() = 0; //print waiting for remote to join.

};

#endif //REVERSI_DISPLAY_H
