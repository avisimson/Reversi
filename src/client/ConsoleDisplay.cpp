/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include <iostream>
#include "ConsoleDisplay.h"
#include "ReversiGame.h"

//print player type wrong.
void ConsoleDisplay :: playerTypeWrong(int num) {
    cout << "Game cannot be initialized, player" << num << "type is wrong" << endl;
}
//print game menu.
void ConsoleDisplay :: initialMenu() {
    cout << "Reversi Game" << endl << endl;
    cout << "Opponet choices:" << endl;
    cout << "Type " << HUMAN << " for human player opponet" << endl;
    cout << "Type " << PC << " for PC opponet" << endl;
    cout << "Type " << REMOTE << " for remote player opponet" << endl;
    cout << "Type " << QUIT << " to quit game." << endl;
}
//print client menu.
void ConsoleDisplay :: printRemoteMenu() {
    cout << "please choose operation number and a name of the game (for 1,3) " << endl;
    cout << "1 for starting a new game." << endl;
    cout << "2 for viewing the list of waiting games." << endl;
    cout << "3 for joining a waiting game." << endl;
}
//print wrong types for players.
void ConsoleDisplay :: notInitializedTypes(char c) {
    cout << c <<
         " is not initialized as player1 or player2" << endl;
}
//print player has no possible moves.
void ConsoleDisplay :: noPossibleMoves(char c) {
    cout << c
         << " You have no possible moves, turn passed." << endl;
}
//print its your move.
void ConsoleDisplay :: printItsYourMove(char c) {
    cout << c << ": it's your move" << endl;
    cout << "Your possible moves: ";
}
//print row col.
void ConsoleDisplay :: printRowCol(int row, int col) {
    cout << "(" << row << "," << col << ")";
}
void ConsoleDisplay :: printPsik() {
    cout << "," ;
}
//print one line down.
void ConsoleDisplay :: printLineDrop() {
    cout << "" << endl;
}
//print enter move.
void ConsoleDisplay :: printEnterMove() {
    cout << "Please enter your move- enter row,col: ";
}
//print wrong input.
void ConsoleDisplay :: printWrongInput() {
    cout << "Wrong input!" << endl;
}
//print player played-row,col.
void ConsoleDisplay :: printPlayerPlayedRowCol(char c, int row, int col) {
    cout << c << " played: ("
         << row << "," << col << ")" << endl;
}
//func gets board and print it.
void ConsoleDisplay :: printBoard(Board* board) {
    int j;
    for (int i = 0; i <= board->getSize(); i++) {
        for (j = 0; j <= board->getSize(); j++) {
            cout << board->getBoard()[i][j];
            if(j == 0) {
                cout << "| ";
                continue;
            }
            cout << " | ";
        }
        cout << "" <<endl;
        for (j = 0; j <= board->getSize(); j++) {
            cout << "----";
        }
        cout << "" << endl;
    }
}
//print no option.
void ConsoleDisplay :: printNoOption() {
    cout << "Wrong input, try again" << endl;
}
//computer cant play print.
void ConsoleDisplay :: printComCantPlay(char c) {
    cout << c << " coudn't play the move" << endl;
}
//print score of game.
void ConsoleDisplay :: printScore(char name1, char name2, int score1, int score2) {
    cout << name1 << ": Your score is " << score1 << endl;
    cout << name2 << ": Your score is " << score2 << endl;
    if(score1 > score2) {
        cout << "The Winner is- " << name1;
    } else if(score2 > score1) {
        cout << "The Winner is- " << name2;
    } else {
        cout << "The Game ended in a Draw." << endl;
    }
}
//print fail to connect and reason.
void ConsoleDisplay :: printFailToConnect(const char* msg) {
    cout << "Failed to connect to server. Reason:" << msg << endl;
}
//print you are player 1/2.
void ConsoleDisplay :: printYouArePlayer(int num) {
    cout << "You are player " << num << endl;
}
//print waiting for remote player.
void ConsoleDisplay :: printWaiting() {
    cout << "Waiting for other players move." << endl;
}
//print remote cant play.
void ConsoleDisplay :: printRemoteCantPlay() {
    cout << "Remote player did not have moves to play" << endl;
}
//wait for other player to join.
void ConsoleDisplay :: PrintWaitForRemoteToJoin() {
    cout << "Connected to server" << endl;
    cout << "Waiting for other player to join " << endl;
}
//print enter a name for game to create.
void ConsoleDisplay :: EnterNameOfGame() {
    cout << "Please enter the name of the game you want:" << endl;
}
//client tried to enter room that doesnt exist.
void ConsoleDisplay :: printNotExist() {
    cout << "You tried to join a game that doesnt exist. try again" << endl;
}
//print to client that he tried to start a room game that exists.
void ConsoleDisplay :: printAlreadyExist() {
    cout << "You tried to create a new game with a name that already exist, " <<
    "try to create game with new name" << endl;
}
//get string and print it to client.
void ConsoleDisplay :: printString(string str) {
    cout << str;
}