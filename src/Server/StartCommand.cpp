#include <unistd.h>
#include <iostream>
#include "StartCommand.h"
#define WAITING 3000
//constructor get list of games and a socket and initial its private variables.
StartCommand :: StartCommand(vector<Game> *listOfGames1) {
    listOfGames = listOfGames1;
}
//func gets vector of commands and checks if new game name already exists.
//if new game already exists-send error to client.
//if new game name not exist-open a new game on server.
//command is the start command, args is name of game, client is the socket of client.
bool StartCommand :: execute(string command, string args, int client){
    for(int i = 0; i < listOfGames.size(); i++) {
        if (args == listOfGames[i].name) { //game already exists with the same name
            return false;                   //so send client that he cant play.
        }
    }
    Game game;
    game.socket1 = client;
    game.status = Waiting;
    game.name = args; //define game name in game.
    listOfGames.insert(game);
    return  true; //added the game to list of games played and now client is waiting.
}
