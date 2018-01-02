#include <iostream>
#include <unistd.h>
#include "JoinGameCommand.h"
#define PLAYERTWO 2
//constructor initial current list of games in server.
JoinGameCommand::JoinGameCommand(vector<Game> *listOfGames1) {
    listOfGames = listOfGames1;
}
//func gets a vector of commands,
// add socket to specific game as player2 and makes game active.
//command is the start command, args is name of game, client is the socket of client.
//return: false if args name is not in list of games, true if it is and join him to game.
bool JoinGameCommand :: execute(string command, string args, int client) {
    for(int i = 0; i < listOfGames.size(); i++) {
        if (args == listOfGames[i].name) { //search client input with names in list.
            listOfGames[i].socket2 = client; //set client as player2.
            listOfGames[i].status = Active; //2 players are now connected to game.
            int p2 = PLAYERTWO;
            //write to player 1 that player 2 connected.
            int n = write(listOfGames[i].socket1, &p2, sizeof(int));
            if(n == -1) {
                throw "coudlnt send player 1 in game " << i << " that player 2 connected\n";
            }
        }
    }
    return false; //game name not found in list.
}
