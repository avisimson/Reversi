/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include "MakeMoveCommand.h"
#include <unistd.h>
using namespace std;
//constructor.
MakeMoveCommand :: MakeMoveCommand(vector<Game>* listOfGames1) {
    listOfGames = listOfGames1;
}
/*func-get command, args(name of game), and a Game struct and makes one turn
 *for one of the sockets in the game*/
bool MakeMoveCommand :: execute(string command, string args, int client) {
    int i;
    for(i = 0; i < (*listOfGames).size(); i++) { //search the specific game in list.
        if(args == (*listOfGames)[i].name) {
            break;
        }
    }
    if(i == (*listOfGames).size()) { //if game wasnt found in list-probably will never happen.
        return false;
    }
    int rowInput;
    int colInput;
    //get from one of players and send to other player,
    //taking input form client 1 for row, game end or no move turn.
    int n = read((*listOfGames)[i].socket1 , &rowInput, sizeof(int));
    //if player1 see that game is over
    if(n == -1) { //if reading row failed.
        cout << "Error reading row" << endl;
        return false;
    }
    if(n == 0) { //check if player 1 disconnected
        cout << "client send disconnected" << endl;
        rowInput = End;
        write((*listOfGames)[i].socket2, &rowInput, sizeof(int));
        write((*listOfGames)[i].socket2, &rowInput, sizeof(int));
        return false; //to end game.
    }
    if (rowInput == End) {
        write((*listOfGames)[i].socket2, &rowInput, sizeof(int));
        write((*listOfGames)[i].socket2, &colInput, sizeof(int));
        return false;
    }
        //if to player1 no moves to play , send message to player1
    else if (rowInput == NoMove) { //returning the message to player 2
        write((*listOfGames)[i].socket2, &rowInput, sizeof(int));
        write((*listOfGames)[i].socket2, &colInput, sizeof(int));
        return true;
    }
    //check the current col
    n = read((*listOfGames)[i].socket1, &colInput, sizeof(int));
    if(n == -1) {
        cout << "Error reading col" << endl;
        return false;
    }
    //send the move to player2
    n = write((*listOfGames)[i].socket2, &rowInput, sizeof(int));
    if(n == -1) { //check if message send
        cout << "Error writing ROW to socket" << endl;
        return false;
    }
    n = write((*listOfGames)[i].socket2, &colInput, sizeof(int));
    if(n == -1) { //check if message send
        cout << "Error writing COL to socket" << endl;
        return false;
    }
    return true; //turn success, game continues.
}