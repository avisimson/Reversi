/*
 *  Created on: jan 01 2018
 *      Author: avi simson & yakir pinchas
 *      Avi id: 205789100
 *      Yakir: 203200530
*/
#include <unistd.h>
#include <iostream>
#include "StartCommand.h"
//constructor get list of games and a socket and initial its private variables.
StartCommand :: StartCommand(vector<Game>* listOfGames1) {
    listOfGames = listOfGames1;
}
//func gets vector of commands and checks if new game name already exists.
//if new game already exists-send error to client.
//if new game name not exist-open a new game on server.
//command is the start command, args is name of game, client is the socket of client.
bool StartCommand :: execute(string command, string args, int client){
    for(int i = 0; i < listOfGames->size(); i++) {
        if (args == (*listOfGames)[i].name) { //game already exists with the same name
            return false;                   //so send client that he cant play.
        }
    }
    Game game;
    game.socket1 = client;
    game.status = Waiting;
    game.name = args; //define game name in game.
    pthread_mutex_lock(&lock); //ONLY ONE THREAD WILL EXECUTE AT A TIME.
    listOfGames->push_back(game); // add new game to list.
    pthread_mutex_unlock(&lock);
    return  true; //added the game to list of games played and now client is waiting.
}
