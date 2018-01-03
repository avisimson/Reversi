/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include "CloseCommand.h"
using namespace std;
//constructor.
CloseCommand :: CloseCommand(vector<Game> *listOfGames1) {
    listOfGames = listOfGames1;
}
//function gets command, name of a game and a client of a game and check which game to close,
//and removes the game from list, and close sockets.
bool CloseCommand :: execute(string command, string args, int client){
    for(int i = 0; i < (*listOfGames).size(); i++) { //search specific game to close by name.
        if(args == (*listOfGames)[i].name) {
            //closing player of game.
            cout << "close Client "<< (*listOfGames)[i].socket1<< endl;
            close((*listOfGames)[i].socket1);
            cout << "close Client " << (*listOfGames)[i].socket2 << endl;
            close((*listOfGames)[i].socket2);
            //remove the game from list
            (*listOfGames).erase((*listOfGames).begin()+i);
            break;
        }
    }
    return true;
}